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

//ライト後の待ち時間
#define WAIT_US	20

//バスの初期化
void BusInit(void);

//バス転送
void BusXfer(uint8_t cs,uint8_t addr,uint8_t data);

//バス読み込み
uint8_t BusRead(uint8_t cs,uint8_t addr);
#endif /* BUSCTRL_H_ */