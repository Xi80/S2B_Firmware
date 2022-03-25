/*
* RegCtrl.c
*
* Created: 2022/03/20 9:54:09
*  Author: Owner
*/

#include "RegCtrl.h"

//ƒŒƒWƒXƒ^‘‚«‚İ
void RegWrite(enum YMF288_ChipSelect_t cs,enum YMF288_AccessSelect_t as,uint8_t addr,uint8_t data)
{
	switch(as) {
		case SSG:
		case FM0:
		//xprintf("Write SSG/FM0 Area : Chip %02x,Address %02x,Data %02x\n",cs,addr,data);
		BusXfer((uint8_t)cs,0x00,addr);
		_delay_us(2);
		BusXfer((uint8_t)cs,0x01,data);
		_delay_us(24);
		break;
		case FM1:
		//xprintf("Write FM1 Area : Chip %02x,Address %02x,Data %02x\n",cs,addr,data);
		BusXfer((uint8_t)cs,0x02,addr);
		_delay_us(2);
		BusXfer((uint8_t)cs,0x03,data);
		_delay_us(24);
		break;
	}
}

uint8_t RegRead(enum YMF288_ChipSelect_t cs,enum YMF288_AccessSelect_t as,uint8_t addr){
	switch(as) {
		case SSG:
		case FM0:
		//xprintf("Write SSG/FM0 Area : Chip %02x,Address %02x,Data %02x\n",cs,addr,data);
		BusXfer((uint8_t)cs,0x00,addr);
		return BusRead((uint8_t)cs,0x01);
		break;
		case FM1:
		//xprintf("Write FM1 Area : Chip %02x,Address %02x,Data %02x\n",cs,addr,data);
		BusXfer((uint8_t)cs,0x02,addr);
		return BusRead((uint8_t)cs,0x02);
		break;
	}
	return 0;
}