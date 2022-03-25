/*
 * S2B_FW.c
 *
 * Created: 2022/03/19 11:26:07
 * Author : Owner
 */ 
#define F_CPU 32000000UL

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "YMF288/YMF288.h"
#include "Serial/SerialCtrl.h"
#include "MIDI/MIDIParser.h"
#include "Middleware/ParamXchanger.h"
#define BASE_FREQ		125000
#define TP_F(x)			((BASE_FREQ / x) & 0x0FFF)

const uint8_t timbre[] = {
2,7,
28, 4, 0, 5, 1,37, 2, 1, 3,
22, 9, 1, 2, 1,47, 2,12, 0,
29, 4, 3, 6, 1,37, 1, 3, 7,
18, 8, 0, 6, 6, 0, 2, 1, 0,
};

void playInitSound(void){
	struct FNumber_t fnum;
	fnum.block = 0;
	fnum.fNumber = TP_F(2000);
	SSG_SetMixer(YMF288_1,0b00111000);
	SSG_SetMixer(YMF288_2,0b00111000);
	SSG_SetMelodyFreq(0,fnum);
	SSG_SetVolume(0,0,15);
	_delay_ms(100);
	fnum.fNumber = TP_F(1000);
	SSG_SetMelodyFreq(0,fnum);
	_delay_ms(100);
	SSG_SetVolume(0,0,0);
}

void initClk(void){ 
	CCP = 0xD8;
	OSC.CTRL = 0x02;
	while(!(OSC.STATUS & 0x02));
	CCP = 0xD8;
	CLK.CTRL = 0x01;	
}

void testOn(struct Note_t note){
	PORTD.OUTCLR = 0xF0;
	PORTD.OUTSET = (note.noteNunber & 0x0F) << 4;
	PX_NoteOn(note.channel,note.noteNunber,note.velocity);
}

void testOff(struct Note_t note){
	PX_NoteOff(note.channel,note.noteNunber);
}

void testCtrl(struct ControlChange_t chg){
	PX_ControlChange(chg.channel,chg.ccNumber,chg.value);
}

void testPb(struct PitchBend_t pb){
	PX_PitchBend(pb.channel,pb.value);
}

void testPgm(struct ProgramChange_t pc){
	PX_ProgramChange(pc.channel,pc.value);
}

void testSysEx(struct SysEx_t sysex){
	SEP_Process(sysex.value,sysex.length);
}
int main(void)
{
	PORTD.DIRSET = 0xF0;

	initClk();
	BusInit();
	SerialInit_Debug();
	SerialInit_MIDI();
	FM_Init();
	VA_Init();
	PX_Init();	

	MIDICallBack_NoteOn = testOn;
	MIDICallBack_NoteOff = testOff;
	MIDICallBack_ControlChange = testCtrl;
	MIDICallBack_PitchBend = testPb;
	MIDICallBack_ProgramChange = testPgm;
	MIDICallBack_SystemExclusive = testSysEx;
	Timbre_Write(RAM,&timbre[0],0);

	sei();
	PMIC.CTRL = 0x07;

	playInitSound();
	while(1){
		int dat = MIDIRead();
		if(dat != -1){
			MIDI_Parse(dat);
		}
	}
}

