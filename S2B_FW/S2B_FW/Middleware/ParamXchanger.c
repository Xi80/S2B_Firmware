/*
 * ParamXchanger.c
 *
 * Created: 2022/03/24 11:31:16
 *  Author: Owner
 */ 

#include "ParamXchanger.h"

struct FMParam_t fmParams[12];
struct SSGParam_t ssgParams[6];
struct MIDIParam_t midiParams[16];
struct RhythmVolume_t rhythmVol;

uint16_t nrpn[16];
uint16_t rpn[16];

uint8_t currentMap[16];

void PX_Init(void){
	for(uint8_t i = 0; i < 12;i++){
		fmParams[i].pan = Center;
	}

	for(uint8_t i = 0;i < 6;i++){
		ssgParams[i].useEnvelope = 0;
	}

	for(uint8_t i = 0;i < 16;i++){
		midiParams[i].exp = 127;
		midiParams[i].vol = 100;
		midiParams[i].pan = Center;
		midiParams[i].pbs = 2;
		midiParams[i].pb  = 8192;
		rpn[i] = 0x7f7f;
	}

	rhythmVol.BD = Center;
	rhythmVol.SD = Center;
	rhythmVol.TC = Center;
	rhythmVol.HH = Center;
	rhythmVol.TOM = Center;
	rhythmVol.RIM = Center;
	
	Rhythm_SetTotalLevel(0x3F);
	Rhythm_SetInstLevel(BD,Center,0x1F);
	Rhythm_SetInstLevel(SD,Center,0x1F);
	Rhythm_SetInstLevel(TC,Center,0x1F);
	Rhythm_SetInstLevel(HH,Center,0x1F);
	Rhythm_SetInstLevel(TOM,Center,0x1F);
	Rhythm_SetInstLevel(RIM,Center,0x1F);
}

void PX_ChangeVolume(uint8_t ch){
	uint8_t val = (uint8_t)(midiParams[ch].exp * midiParams[ch].vol / 127.0) >> 1;
	xprintf("%02x\n",val);
	if(ch == 9){
		Rhythm_SetTotalLevel(val);
		return;
	}
	struct NoteList_t notes;
	notes = VA_SearchVoices(ch);
	for(uint8_t i = 0;i < notes.count;i++){
		if(notes.noteId[i] < 12){
			SSG_SetVolume(notes.noteId[i],ssgParams[i - 12].useEnvelope,val >> 2);
		}
	}
}

void PX_ChangePan(uint8_t ch){
	struct NoteList_t notes;
	notes = VA_SearchVoices(ch);
	for(uint8_t i = 0;i < notes.count;i++){
		if(notes.noteId[i] > 11){
			FM_SetOutputchannelAMSPMS(notes.noteId[i],midiParams[ch].pan,0,0);
		}
	}
}

void PX_NoteOn(uint8_t ch,uint8_t note,uint8_t vel){
	if(ch == 9){
		PX_Drums(note,vel);
		return;
	}
	uint8_t assign = VA_AssignOn(ch,note);
	if(assign == 255)return;
	if(assign > 11){
		struct FNumber_t fnum;
		uint8_t vol = (uint8_t)(midiParams[ch].exp * midiParams[ch].vol / 127.0) >> 3;
		fnum = Scale_GetFnumber(SSG,note,midiParams[ch].pbs,midiParams[ch].pb);
		SSG_SetVolume(assign - 12,0,0);
		SSG_SetMelodyFreq(assign - 12,fnum);
		SSG_SetVolume(assign - 12,ssgParams[assign - 12].useEnvelope,vol);
		xprintf("NOTE ON %02x %02x %04x\n",assign - 12,fnum.fNumber);
	} else {
		struct FNumber_t fnum;
		fnum = Scale_GetFnumber(OPNA,note,midiParams[ch].pbs,midiParams[ch].pb);
		FM_Key(assign,0x00);
		FM_SetOutputchannelAMSPMS(assign,midiParams[ch].pan,0,0);
		FM_SetFNum(assign,fnum);
		//xprintf("NOTE ON %02x %02x %04x\n",ch,note,fnum.fNumber);
		FM_Key(assign,0xFF);
	}
}

void PX_NoteOff(uint8_t ch,uint8_t note){
	if(ch == 9){
		return;
	}
	uint8_t assign = VA_AssignOff(ch,note);
	if(assign == 255)return;
	if(assign > 11){
		SSG_SetVolume(assign - 12,0,0);
		//xprintf("NOTE OFF %02x\n",assign - 12);
	} else {
		FM_Key(assign,0x00);
	}
}

void PX_ControlChange(uint8_t ch,uint8_t ctrl,uint8_t val){
	struct NoteList_t notes;
	switch(ctrl){
		case 1:
			//MODULATION
			//DO NOTHING
			break;
		case 6:
			//DATA ENTRY
			//xprintf("DATA ENTRY RPN:%04X\n",rpn[ch]);
			if(rpn[ch] == 0x7F7F){
				if(nrpn[ch] == 0x7F7F)return;
				if(nrpn[ch] <= 12 && nrpn >= 0){
					currentMap[ch] = nrpn[ch];
				}
				nrpn[ch] = 0x7F7F;
			} else {
				if(rpn[ch] == 0x0000){midiParams[ch].pbs = val;xprintf("PBS %02x\n",val);}
				rpn[ch] = 0x7F7F;
			}
			break;
		case 7:
			//CHANNEL VOLUME
			midiParams[ch].vol = val;
			PX_ChangeVolume(ch);
			break;
		case 10:
			if(val > 64){
				midiParams[ch].pan = Right;
			} else if(val == 64){
				midiParams[ch].pan = Center;
			} else {
				midiParams[ch].pan = Left;
			}
			PX_ChangePan(ch);
			break;
		case 11:
			//EXPRESSION
			midiParams[ch].vol = val;
			PX_ChangeVolume(ch);
			break;
		case 64:
			//HOLD
			notes = VA_AssignSustain(ch,(val > 63)? 1 : 0);
			if(notes.count){
				for(uint8_t i = 0;i < notes.count;i++){
					if(notes.noteId[i] > 11){
						SSG_SetVolume(notes.noteId[i] - 12,0,0);
						//xprintf("NOTE OFF %02x\n",notes.noteId[i] - 12);
						} else {
						FM_Key(notes.noteId[i],0x00);
					}
				}
			}
			break;
		case 98:
			//NRPN LSB
			nrpn[ch] |= val;
			break;
		case 99:
			//NRPN MSB
			nrpn[ch] |= (val) << 8;
			break;
		case 100:
			//RPN LSB
			//xprintf("RPN LSB %02x\n",val);
			rpn[ch] &= 0xF0;
			rpn[ch] |= val;
			break;
		case 101:
			//RPN MSB
			//xprintf("RPN MSB %02x\n",val);
			rpn[ch] &= 0x0F;
			rpn[ch] |= (val) << 8;
			break;
	}
}

void PX_ProgramChange(uint8_t ch,uint8_t pgm){
	uint8_t idx = 0;
	uint8_t timbre[38];
	if(pgm < 24){
		//RAM
		idx = pgm;
		Timbre_Read(timbre,RAM,idx);
	} else if(pgm < 100){
		//ROM
		idx = pgm - 24;
		Timbre_Read(timbre,ROM,idx);
	} else {
		//EEPROM
		idx = pgm - 100;
		Timbre_Read(timbre,EEPROM,idx);
	}

	struct NoteList_t notes = VA_GetAssignMap(ch);

	for(uint8_t i = 0;i < notes.count;i++){
		if(i < 12){
			memcpy(fmParams[notes.noteId[i]].timbre,timbre,38);
			FM_SetOutputchannelAMSPMS(notes.noteId[i],fmParams[notes.noteId[i]].pan,0,0);
			FM_SetFeedbackConnection(notes.noteId[i],timbre[1],timbre[0]);
			for(uint8_t j = 0;j < 4;j++){
				uint8_t index = 2 + j * 9;
				//xprintf("%d %d KS:%d AR:%d DR:%d SR:%d SL:%d RR:%d TL:%d DT:%d MUL:%d\n",j,i,timbre[index + 6],timbre[index],timbre[index+1],timbre[index+2],timbre[index+4],timbre[index+3],timbre[index+5],timbre[index+8],timbre[index+7]);
				FM_SetKeyscaleAttackrate(notes.noteId[i],j,timbre[index + 6],timbre[index]);
				FM_SetAmDecayrate(notes.noteId[i],j,0,timbre[index + 1]);
				FM_SetSustainrate(notes.noteId[i],j,timbre[index + 2]);
				FM_SetSustainlevelReleaserate(notes.noteId[i],j,timbre[index + 4],timbre[index + 3]);
				FM_SetTotalLevel(notes.noteId[i],j,timbre[index + 5]);
				FM_SetDetuneMultiply(notes.noteId[i],j,timbre[index + 8],timbre[index + 7]);
			}
		} else {

		}
	}

}

void PX_PitchBend(uint8_t ch,uint16_t val){
	midiParams[ch].pb = val;
	struct NoteList_t notes = VA_SearchVoices(ch);
	struct FNumber_t fnum;
	for(uint8_t i = 0;i < notes.count;i++){
		if(notes.noteId[i] < 12){
			fnum = Scale_GetFnumber(OPNA,notes.noteNumber[i],midiParams[ch].pbs,midiParams[ch].pb);
			FM_SetFNum(notes.noteId[i],fnum);
		} else {
			fnum = Scale_GetFnumber(SSG,notes.noteNumber[i],midiParams[ch].pbs,midiParams[ch].pb);
			SSG_SetMelodyFreq(notes.noteId[i] - 12,fnum);
		}
	}
}

void PX_Drums(uint8_t note,uint8_t vel){
	if(note == 0x23 || note == 0x24)
	{
		Rhythm_SetInstLevel(BD,rhythmVol.BD,vel >> 2);
		Rhythm_Key(0,BD);
	}
	if(note == 0x26 || note == 0x28)
	{
		Rhythm_SetInstLevel(SD,rhythmVol.SD,vel >> 2);
		Rhythm_Key(0,SD);
	}
	if(note == 0x31 || note == 0x39)
	{
		Rhythm_SetInstLevel(TC,rhythmVol.TC,vel >> 2);
		Rhythm_Key(0,TC);
	}
	if(note == 0x2A || note == 0x2C || note == 0x2E)
	{
		Rhythm_SetInstLevel(HH,rhythmVol.HH,vel >> 2);
		Rhythm_Key(0,HH);
	}
	if(note == 0x29 || note == 0x2B || note == 0x2D || note == 0x2F || note == 0x30 || note == 0x32)
	{
		Rhythm_SetInstLevel(TOM,rhythmVol.TOM,vel >> 2);
		Rhythm_Key(0,TOM);
	}
	if(note == 0x25)
	{
		Rhythm_SetInstLevel(RIM,rhythmVol.RIM,vel >> 2);
		Rhythm_Key(0,RIM);
	}
}

void PX_SetEnvelopeShape(uint8_t ch,uint8_t shape){
	xprintf("Envelope Shape CH%02x,VAL%02x\n",ch,shape);
	struct NoteList_t notes = VA_GetAssignMap(ch);
	for(uint8_t i = 0;i < notes.count;i++){
		if(notes.noteId[i] > 11){
			ssgParams[i - 12].envelopeShape = shape;
		}
	}
}

void PX_SetEnvelopeFreq(uint8_t id,uint16_t freq){
	xprintf("Envelope FREQ ID%02x,VAL%02x\n",id,freq);
	struct FNumber_t fnum;
	fnum.block = 0;
	fnum.fNumber = (uint16_t)(7812.5 / freq);
	SSG_SetEnvelopeFreq((id)? YMF288_2 : YMF288_1,fnum);
}