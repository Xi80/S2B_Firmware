/*
 * FMCtrl.c
 *
 * Created: 2022/03/22 9:38:48
 *  Author: Owner
 */ 

#include "FMCtrl.h"

const uint8_t addrDiff[] = {
	0,	8,	4,	12,
	1,	9,	5,	13,
	2,	10,	6,	14,
	0,	8,	4,	12,
	1,	9,	5,	13,
	2,	10,	6,	14,
	0,	8,	4,	12,
	1,	9,	5,	13,
	2,	10,	6,	14,
	0,	8,	4,	12,
	1,	9,	5,	13,
	2,	10,	6,	14,
};

void FM_Init(void){
	//YMF288ÉÇÅ[Éh
	RegWrite(BOTH,FM0,0x20,0x02);
	//î≠âπêîê›íË:6
	RegWrite(BOTH,FM0,0x29,0x80);
}

void FM_SetDetuneMultiply(uint8_t ch,uint8_t slot,uint8_t dt,uint8_t ml){
	//xprintf("DT/ML\tCH:%02X,SLOT:%02X,DT:%02X,ML%02X\n",ch,slot,dt,ml);
	uint8_t addr = 0x30 + (addrDiff[(ch << 2) + slot]);
	uint8_t data = (ml & 0x0F) | ((dt & 0x07) << 4);
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, addr, data);
}

void FM_SetTotalLevel(uint8_t ch,uint8_t slot,uint8_t tl){
	//xprintf("TL\tCH:%02X,SLOT:%02X,TL:%02X\n",ch,slot,tl);
	uint8_t addr = 0x40 + (addrDiff[(ch << 2) + slot]);
	uint8_t data = tl & 0x7F;
	
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, addr, data);}

void FM_SetKeyscaleAttackrate(uint8_t ch,uint8_t slot,uint8_t ks,uint8_t ar){
	//xprintf("KS/AR\tCH:%02X,SLOT:%02X,KS:%02X,AR%02X\n",ch,slot,ks,ar);
	uint8_t addr = 0x50 + (addrDiff[(ch << 2) + slot]);
	uint8_t data = (ar & 0x1F) | ((ks & 0x03) << 6);
	
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, addr, data);
}

void FM_SetAmDecayrate(uint8_t ch,uint8_t slot,uint8_t am,uint8_t dr){
	//xprintf("DR\tCH:%02X,SLOT:%02X,DR:%02X\n",ch,slot,dr);
	uint8_t addr = 0x60 + (addrDiff[(ch << 2) + slot]);
	uint8_t data = (dr & 0x1F) | ((am & 0x01) << 7);
	
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, addr, data);
}

void FM_SetSustainrate(uint8_t ch,uint8_t slot,uint8_t sr){
	//xprintf("SR\tCH:%02X,SLOT:%02X,SR:%02X\n",ch,slot,sr);
	uint8_t addr = 0x70 + (addrDiff[(ch << 2) + slot]);
	uint8_t data = sr & 0x1F;
	
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, addr, data);
}

void FM_SetSustainlevelReleaserate(uint8_t ch,uint8_t slot,uint8_t sl,uint8_t rr){
	//xprintf("SL/RR\tCH:%02X,SLOT:%02X,SL:%02X,RR%02X\n",ch,slot,sl,rr);
	uint8_t addr = 0x80 + (addrDiff[(ch << 2) + slot]);
	uint8_t data = (rr & 0x0F) | ((sl && 0x0F) << 4);
	
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, addr, data);
}

void FM_SetSSGEg(uint8_t ch,uint8_t slot,uint8_t ssgeg){
	//xprintf("DT/ML CH:%02X,SLOT:%02X,DT:%02X,ML%02X\n",ch,slot,dt,ml);
	uint8_t addr = 0x90 + (addrDiff[(ch << 2) + slot]);
	uint8_t data = ssgeg & 0x0F;
	
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, addr, data);
}

void FM_SetFNum(uint8_t ch,struct FNumber_t fnum){
	//xprintf("FNUM\tCH:%02X,BLOCK:%02x,FNUM:%04x\n",ch,block,fnum);
	uint16_t data = (fnum.fNumber & 0x07FF) | ((fnum.block & 0x07) << 11);
	
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, 0xA4 + (ch % 3), (uint8_t)((data & 0xFF00) >> 8));
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, 0xA0 + (ch % 3), (uint8_t)(data & 0x00FF));
	
}

void FM_SetFeedbackConnection(uint8_t ch,uint8_t fb,uint8_t cn){
	//xprintf("FB/CN\tCH:%02X,FB:%02X,CN%02X\n",ch,fb,cn);
	uint8_t data = (cn & 0x07) | ((fb & 0x07) << 3);
	
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, 0xB0 + (ch % 3), data);
}

void FM_SetOutputchannelAMSPMS(uint8_t ch,enum Pan_t pan,uint8_t ams,uint8_t pms){
	//xprintf("OCH\tCH:%02X,L:%02X,R%02X\n",ch,l,r);
	uint8_t data = (uint8_t)pan | ((ams & 0x03) << 4) | (pms & 0x07);
	
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,((ch % 6) < 3)? FM0 : FM1, 0xB4 + (ch % 3), data);
}

void FM_Key(uint8_t ch,uint8_t slot){
	uint8_t data = ((slot & 0x0F) << 4) | (((ch % 6) > 2) << 2) |((ch % 3) & 0x03);
	RegWrite((ch < 6)? YMF288_1 : YMF288_2,FM0,0x28,data);
}