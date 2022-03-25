/*
 * SysExProcessor.c
 *
 * Created: 2022/03/24 20:44:20
 *  Author: Owner
 */ 

#include "SysExProcessor.h"

void decode_OriginalExclusive(uint8_t *data,uint8_t size){
	xprintf("Other Exclusive\n");
	if(size < 3)return;
	if(data[0] != 0x7D)return;
	if(data[1] != 0x01)return;
	switch(data[2]){
		case 0:
			//�{�C�X�A�T�C��
			VA_SetAssignMap(data[3],data[4],&data[5]);
			break;
		case 1:
			//�~�L�T�[�ݒ�
			SSG_SetMixer((data[3] == 0)? YMF288_1 : YMF288_2,data[4]);
			break;
		case 2:
			//�G���x���[�v�g�`�ݒ�
			PX_SetEnvelopeShape(data[3],data[4]);
			break;
		case 3:
			//�G���x���[�v���g���ݒ�
			PX_SetEnvelopeFreq(data[3],data[4] | (data[5] << 7));
			break;
		case 4:
			//OPNA�{�C�X�]��
			Timbre_Write(RAM,&data[4],data[3]);
			break;
		case 5:
			//OPNA�{�C�X�ۑ�(RAM-->EEPROM)
			break;
		case 6:
			//OPNA�{�C�X�Ăяo��(EEPROM-->RAM)
			break;
		case 7:
			
			break;
		case 8:

			break;
		case 9:

			break;
		case 10:

			break;
	}
}

void SEP_Process(uint8_t *data,uint8_t size){
	const uint8_t gm_reset[] = { 0x7E, 0x7F, 0x09, 0x01 };
	const uint8_t xg_reset[] = { 0x43, 0x10, 0x4C, 0x00, 0x00, 0x7E, 0x00 };
	const uint8_t gs_reset[] = { 0x41, 0x10, 0x42, 0x12, 0x40, 0x00, 0x7F, 0x00, 0x41 };
	const uint8_t gs_mode1[] = { 0x41, 0x10, 0x42, 0x12, 0x00, 0x00, 0x7F, 0x00, 0x01 };
	
	if (!memcmp(data, gm_reset, sizeof(gm_reset))) {
		xprintf("GM Reset\n");
		return;
	}

	if (!memcmp(data, gs_reset, sizeof(gs_reset))) {
		xprintf("GS Reset\n");
		return;
	}

	if (!memcmp(data, gs_mode1, sizeof(gs_mode1))) {
		xprintf("GS Mode 1\n");
		return;
	}

	if (!memcmp(data, xg_reset, sizeof(xg_reset))) {
		xprintf("XG Reset\n");
		return;
	}
	
	decode_OriginalExclusive(data,size);
	return;
}
