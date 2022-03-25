/*
 * FMCtrl.h
 *
 * Created: 2022/03/22 9:23:13
 *  Author: Owner
 */ 


#ifndef FMCTRL_H_
#define FMCTRL_H_

#include <avr/io.h>
#include "RegCtrl.h"
#include "CommonStructs.h"
#include "../Serial/xprintf.h"

void FM_Init(void);

void FM_SetDetuneMultiply(uint8_t ch,uint8_t slot,uint8_t dt,uint8_t ml);

void FM_SetTotalLevel(uint8_t ch,uint8_t slot,uint8_t tl);

void FM_SetKeyscaleAttackrate(uint8_t ch,uint8_t slot,uint8_t ks,uint8_t ar);

void FM_SetAmDecayrate(uint8_t ch,uint8_t slot,uint8_t am,uint8_t dr);

void FM_SetSustainrate(uint8_t ch,uint8_t slot,uint8_t sr);

void FM_SetSustainlevelReleaserate(uint8_t ch,uint8_t slot,uint8_t sl,uint8_t rr);

void FM_SetSSGEg(uint8_t ch,uint8_t slot,uint8_t ssgeg);

void FM_SetFNum(uint8_t ch,struct FNumber_t fnum);

void FM_SetFeedbackConnection(uint8_t ch,uint8_t fb,uint8_t cn);

void FM_SetOutputchannelAMSPMS(uint8_t ch,enum Pan_t pan,uint8_t ams,uint8_t pms);

void FM_Key(uint8_t ch,uint8_t slot);

#endif /* FMCTRL_H_ */