/*
* RegCtrl.h
*
* Created: 2022/03/20 9:48:18
*  Author: Owner
*/


#ifndef REGCTRL_H_
#define REGCTRL_H_

#include "BusCtrl.h"
#include "../Serial/xprintf.h"

enum YMF288_ChipSelect_t{
	YMF288_1 = 1,
	YMF288_2 = 2,
	BOTH = 3
};

enum YMF288_AccessSelect_t{
	SSG = 0,
	FM0 = 1,
	FM1 = 2
};

//レジスタ書き込み
void RegWrite(enum YMF288_ChipSelect_t cs,enum YMF288_AccessSelect_t as,uint8_t addr,uint8_t data);

//レジスタ読み込み
uint8_t RegRead(enum YMF288_ChipSelect_t cs,enum YMF288_AccessSelect_t as,uint8_t addr);

#endif /* REGCTRL_H_ */