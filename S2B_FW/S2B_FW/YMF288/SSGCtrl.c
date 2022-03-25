/*
* SSGCtrl.c
*
* Created: 2022/03/20 10:19:36
*  Author: Owner
*/

#include "SSGCtrl.h"

//�y�����g���̐ݒ�
void SSG_SetMelodyFreq(uint8_t ch,struct FNumber_t fnum){
	if(ch > 2){
		RegWrite(YMF288_2,SSG,(ch - 3) << 1,(uint8_t)(fnum.fNumber & 0x00FF));
		RegWrite(YMF288_2,SSG,((ch - 3) << 1) + 1,(uint8_t)((fnum.fNumber >> 8) & 0x0F));
	} else {
		RegWrite(YMF288_1,SSG,(ch) << 1,(uint8_t)(fnum.fNumber & 0x00FF));
		RegWrite(YMF288_1,SSG,((ch) << 1) + 1,(uint8_t)((fnum.fNumber >> 8) & 0x0F));		
	}
}

//�m�C�Y�����g���̐ݒ�
void SSG_SetNoiseFreq(enum YMF288_ChipSelect_t cs,struct FNumber_t fnum)
{
	RegWrite(cs,SSG,0x06,(uint8_t)(fnum.fNumber & 0x00FF));
}

//�G���x���[�v���g���̐ݒ�
void SSG_SetEnvelopeFreq(enum YMF288_ChipSelect_t cs,struct FNumber_t fnum)
{
	RegWrite(cs,SSG,0x0B,(uint8_t)(fnum.fNumber & 0x00FF));
	RegWrite(cs,SSG,0x0C,(uint8_t)((fnum.fNumber & 0xFF00) >> 8));
}

//�~�L�T�[�̐ݒ�
void SSG_SetMixer(enum YMF288_ChipSelect_t cs,uint8_t mix)
{
	RegWrite(cs,SSG,0x07,mix);
}

//���ʃR���g���[����DAC
void SSG_SetVolume(uint8_t ch,uint8_t useEnvelope,uint8_t vol)
{
	if(ch > 2){
		RegWrite(YMF288_2,SSG,(ch - 3) + 0x08,(useEnvelope)? 0x10 : vol);
	} else {
		RegWrite(YMF288_1,SSG,(ch) + 0x08,(useEnvelope)? 0x10 : vol);
	}
}

//�G���x���[�v�̌`��R���g���[��
void SSG_SetEnvelopeShape(enum YMF288_ChipSelect_t cs,uint8_t shape)
{
	RegWrite(cs,SSG,0x0D,shape);
}
