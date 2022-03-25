/*
* SSGCtrl.h
*
* Created: 2022/03/20 10:06:19
*  Author: Owner
*/


#ifndef SSGCTRL_H_
#define SSGCTRL_H_

#include "RegCtrl.h"
#include "CommonStructs.h"
//楽音周波数の設定
void SSG_SetMelodyFreq(uint8_t ch,struct FNumber_t fnum);

//ノイズ音周波数の設定
void SSG_SetNoiseFreq(enum YMF288_ChipSelect_t cs,struct FNumber_t fnum);

//エンベロープ周波数の設定
void SSG_SetEnvelopeFreq(enum YMF288_ChipSelect_t cs,struct FNumber_t fnum);

//ミキサーの設定
void SSG_SetMixer(enum YMF288_ChipSelect_t cs,uint8_t mix);

//音量コントロールとDAC
void SSG_SetVolume(uint8_t ch,uint8_t useEnvelope,uint8_t vol);

//エンベロープの形状コントロール
void SSG_SetEnvelopeShape(enum YMF288_ChipSelect_t cs,uint8_t shape);

#endif /* SSGCTRL_H_ */