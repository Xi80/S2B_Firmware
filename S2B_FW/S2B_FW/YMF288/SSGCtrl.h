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
//�y�����g���̐ݒ�
void SSG_SetMelodyFreq(uint8_t ch,struct FNumber_t fnum);

//�m�C�Y�����g���̐ݒ�
void SSG_SetNoiseFreq(enum YMF288_ChipSelect_t cs,struct FNumber_t fnum);

//�G���x���[�v���g���̐ݒ�
void SSG_SetEnvelopeFreq(enum YMF288_ChipSelect_t cs,struct FNumber_t fnum);

//�~�L�T�[�̐ݒ�
void SSG_SetMixer(enum YMF288_ChipSelect_t cs,uint8_t mix);

//���ʃR���g���[����DAC
void SSG_SetVolume(uint8_t ch,uint8_t useEnvelope,uint8_t vol);

//�G���x���[�v�̌`��R���g���[��
void SSG_SetEnvelopeShape(enum YMF288_ChipSelect_t cs,uint8_t shape);

#endif /* SSGCTRL_H_ */