/*
 * MIDIParser.c
 *
 * Created: 2022/03/24 8:25:52
 *  Author: Owner
 */ 

#include "MIDIParser.h"

void (*MIDICallBack_NoteOn)(struct Note_t) = NULL;
void (*MIDICallBack_NoteOff)(struct Note_t) = NULL;

void (*MIDICallBack_ControlChange)(struct ControlChange_t) = NULL;
void (*MIDICallBack_ProgramChange)(struct ProgramChange_t) = NULL;

void (*MIDICallBack_PitchBend)(struct PitchBend_t) = NULL;

void (*MIDICallBack_SystemExclusive)(struct SysEx_t) = NULL;

uint8_t runningStatusBuffer = 0x00;
uint8_t threeBytesFlag = 0x00;
uint8_t systemExclusiveFlag = 0x00;

uint8_t systemExclusivePointer = 0;
uint8_t systemExclusiveBuffer[64];

uint8_t eventBuffer[3];

void MIDI_CallFunctions(void){
	struct Note_t note;
	struct ControlChange_t ctrlChg;
	struct ProgramChange_t pgmChg;
	struct PitchBend_t pb;
	struct SysEx_t sysEx;

	uint8_t op = runningStatusBuffer & 0xF0;
	uint8_t ch = runningStatusBuffer & 0x0F;

	if(op == 0x90 && eventBuffer[2] == 0x00)op = 0x80;

	if(op == 0x80){
		//NOTEOFF
		note.channel = ch;
		note.noteNunber = eventBuffer[1];
		note.velocity = 0x00;
		if(MIDICallBack_NoteOff != NULL)MIDICallBack_NoteOff(note);
		return;
	}

	if(op == 0x90){
		//NOTEON
		note.channel = ch;
		note.noteNunber = eventBuffer[1];
		note.velocity = eventBuffer[2];
		if(MIDICallBack_NoteOn != NULL)MIDICallBack_NoteOn(note);
	}

	if(op == 0xB0){
		//CTRLCHG
		ctrlChg.channel = ch;
		ctrlChg.ccNumber = eventBuffer[1];
		ctrlChg.value = eventBuffer[2];
		if(MIDICallBack_ControlChange != NULL)MIDICallBack_ControlChange(ctrlChg);
		return;
	}

	if(op == 0xC0){
		//PGMCHG
		pgmChg.channel = ch;
		pgmChg.value = eventBuffer[1];
		if(MIDICallBack_ProgramChange != NULL)MIDICallBack_ProgramChange(pgmChg);
		return;
	}

	if(op == 0xE0){
		//PB
		pb.channel = ch;
		pb.value = (eventBuffer[2] << 7) | (eventBuffer[1]);		
		if(MIDICallBack_PitchBend != NULL)MIDICallBack_PitchBend(pb);
	}

	if(op == 0xF0){
		sysEx.length = systemExclusivePointer;
		memcpy(&sysEx.value,systemExclusiveBuffer,systemExclusivePointer);
		if(MIDICallBack_SystemExclusive != NULL)MIDICallBack_SystemExclusive(sysEx);
		return;
	}

	return;
}

void MIDI_ParseParam(uint8_t data){
	if(threeBytesFlag){
		threeBytesFlag = 0x00;
		eventBuffer[2] = data;
		MIDI_CallFunctions();
		return;
	}
	
	if(!runningStatusBuffer)return;
	
	if(runningStatusBuffer < 0xC0){
		threeBytesFlag = 0x01;
		eventBuffer[1] = data;
		return;
	}
	
	if(runningStatusBuffer < 0xE0){
		eventBuffer[1] = data;
		MIDI_CallFunctions();
		return;
	}
	
	if(runningStatusBuffer < 0xF0){
		threeBytesFlag = 0x01;
		eventBuffer[1] = data;
		return;
	}
	
	if(runningStatusBuffer == 0xF2){
		runningStatusBuffer = 0x00;
		threeBytesFlag = 0x01;
		eventBuffer[1] = data;
		return;
	}
	
	if(runningStatusBuffer == 0xF3 ||runningStatusBuffer == 0xF1  ){
		runningStatusBuffer = 0x00;
		eventBuffer[1] = data;
		MIDI_CallFunctions();
		return;
	}
	
	runningStatusBuffer = 0x00;
	return;
}

void MIDI_ParseEvent(uint8_t data){
	if(data >= 0xF8)return;			//Ignore
	
	runningStatusBuffer = data;
	threeBytesFlag = 0;
	
	if(data == 0xF0){
		systemExclusiveFlag = 0x01;
		systemExclusivePointer = 0;
		memset(&systemExclusiveBuffer[0],0x00,64);
		return;
	}
	
	return;
}


void MIDI_Parse(uint8_t data){
	if(systemExclusiveFlag){

		if(data == 0xF7){
			systemExclusiveFlag = 0x00;
			MIDI_CallFunctions();
			return;
		}

		systemExclusiveBuffer[systemExclusivePointer++] = data;
		return;
	}

	if(data & 0x80){
		MIDI_ParseEvent(data);
	} else {
		MIDI_ParseParam(data);
	}
}