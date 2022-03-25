/*
 * BusCtrl.h
 *
 * Created: 2022/03/20 9:19:10
 *  Author: Owner
 */ 

#ifndef BUSCTRL_H_
#define BUSCTRL_H_

#include <avr/io.h>
#include <util/delay.h>

//���C�g��̑҂�����
#define WAIT_US	20

//�o�X�̏�����
void BusInit(void);

//�o�X�]��
void BusXfer(uint8_t cs,uint8_t addr,uint8_t data);

//�o�X�ǂݍ���
uint8_t BusRead(uint8_t cs,uint8_t addr);
#endif /* BUSCTRL_H_ */