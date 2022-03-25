/*
 * RhythmCtrl.c
 *
 * Created: 2022/03/22 12:41:29
 *  Author: Owner
 */ 

#include "RhythmCtrl.h"

void Rhythm_Key(uint8_t dump,enum RhythmInstrument_t inst){
	RegWrite(YMF288_1,FM0,0x10,((dump & 0x01) << 7) | (uint8_t)inst);
}

void Rhythm_SetTotalLevel(uint8_t tl){
	RegWrite(YMF288_1,FM0,0x11,tl & 0x3F);
}

void Rhythm_SetInstLevel(enum RhythmInstrument_t inst,enum Pan_t pan,uint8_t tl){
	uint8_t addr = 0x00;
	uint8_t data = (uint8_t)pan | (tl & 0x1F);
	
	switch(inst){
		case BD:
			addr = 0x18;
			break;
		case SD:
			addr = 0x19;
			break;
		case TC:
			addr = 0x1A;
			break;
		case HH:
			addr = 0x1B;
			break;
		case TOM:
			addr = 0x1C;
			break;
		case RIM:
			addr = 0x1D;
			break;
	}
	
	RegWrite(YMF288_1,FM0,addr,data);
	
	_delay_us(24);
}

