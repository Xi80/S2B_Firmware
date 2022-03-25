/*
* BusCtrl.c
*
* Created: 2022/03/20 9:23:56
*  Author: Owner
*/

#include "BusCtrl.h"

//バスの初期化
void BusInit(void)
{
	PORTA.DIRSET = 0xFF;	//データバス
	PORTB.DIRSET = 0x0F;	//A0,A1,!CS0,!CS1
	PORTE.DIRSET = 0x07;	//!WR,!RD,!IC
	
	PORTA.OUT = 0x00;
	
	PORTB.OUTCLR = 0x03;
	
	PORTB.OUTSET = 0x0C;
	
	PORTE.OUTSET = 0x07;
	
	//RESET
	PORTE.OUTCLR = 0x04;
	
	_delay_ms(50);
	
	PORTE.OUTSET = 0x04;
}

//バス転送
void BusXfer(uint8_t cs,uint8_t addr,uint8_t data)
{
	//!CSアサート
	PORTB.OUTCLR = (cs & 0x03) << 2;
	
	//アドレスセット
	PORTB.OUTCLR = 0x03;
	PORTB.OUTSET = (addr & 0x03);
	
	//データセット
	PORTA.OUT = data;
	
	//!WRアサート
	PORTE.OUTCLR = 0x01;
	
	_delay_us(WAIT_US);
	
	//!WRネゲート
	PORTE.OUTSET = 0x01;
	
	//!CSネゲート
	PORTB.OUTSET = (cs & 0x03) << 2;
	
	_delay_us(WAIT_US);
}

uint8_t BusRead(uint8_t cs,uint8_t addr){
	
	//アドレスセット
	PORTB.OUTCLR = 0x03;
	PORTB.OUTSET = (addr & 0x03);
	
	//!CSアサート
	PORTB.OUTCLR = (cs & 0x03) << 2;
	
	//データバスを入力設定
	PORTA.DIRCLR = 0xFF;
	
	//!RDアサート
	PORTE.OUTCLR = 0x02;
	
	_delay_us(20);
	
	//データ読み取り
	uint8_t ret = PORTA.IN;
		
	//!RDネゲート
	PORTE.OUTSET = 0x02;

	//!CSネゲート
	PORTB.OUTSET = (cs & 0x03) << 2;

	//データバスを出力設定
	PORTA.DIRSET = 0xFF;
	
	_delay_us(WAIT_US);
	
	return ret;
}