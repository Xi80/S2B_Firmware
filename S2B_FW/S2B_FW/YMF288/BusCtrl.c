/*
* BusCtrl.c
*
* Created: 2022/03/20 9:23:56
*  Author: Owner
*/

#include "BusCtrl.h"

//�o�X�̏�����
void BusInit(void)
{
	PORTA.DIRSET = 0xFF;	//�f�[�^�o�X
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

//�o�X�]��
void BusXfer(uint8_t cs,uint8_t addr,uint8_t data)
{
	//!CS�A�T�[�g
	PORTB.OUTCLR = (cs & 0x03) << 2;
	
	//�A�h���X�Z�b�g
	PORTB.OUTCLR = 0x03;
	PORTB.OUTSET = (addr & 0x03);
	
	//�f�[�^�Z�b�g
	PORTA.OUT = data;
	
	//!WR�A�T�[�g
	PORTE.OUTCLR = 0x01;
	
	_delay_us(WAIT_US);
	
	//!WR�l�Q�[�g
	PORTE.OUTSET = 0x01;
	
	//!CS�l�Q�[�g
	PORTB.OUTSET = (cs & 0x03) << 2;
	
	_delay_us(WAIT_US);
}

uint8_t BusRead(uint8_t cs,uint8_t addr){
	
	//�A�h���X�Z�b�g
	PORTB.OUTCLR = 0x03;
	PORTB.OUTSET = (addr & 0x03);
	
	//!CS�A�T�[�g
	PORTB.OUTCLR = (cs & 0x03) << 2;
	
	//�f�[�^�o�X����͐ݒ�
	PORTA.DIRCLR = 0xFF;
	
	//!RD�A�T�[�g
	PORTE.OUTCLR = 0x02;
	
	_delay_us(20);
	
	//�f�[�^�ǂݎ��
	uint8_t ret = PORTA.IN;
		
	//!RD�l�Q�[�g
	PORTE.OUTSET = 0x02;

	//!CS�l�Q�[�g
	PORTB.OUTSET = (cs & 0x03) << 2;

	//�f�[�^�o�X���o�͐ݒ�
	PORTA.DIRSET = 0xFF;
	
	_delay_us(WAIT_US);
	
	return ret;
}