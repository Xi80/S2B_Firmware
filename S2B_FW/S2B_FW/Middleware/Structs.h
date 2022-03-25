/*
 * Structs.h
 *
 * Created: 2022/03/24 10:00:45
 *  Author: Owner
 */ 


#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <avr/io.h>
#include "../YMF288/CommonStructs.h"

struct MIDIParam_t {
	uint8_t vol;
	uint8_t exp;
	uint8_t mod;
	enum Pan_t	pan;
	uint8_t pbs;
	uint16_t pb;
};

typedef struct {
	uint8_t assigned_ch;			/*���蓖�Ă��Ă���`���l��*/
	uint8_t priority;				/*�D��x*/
	uint8_t note_state;				/*��������*/
	uint8_t sustain;				/*�T�X�e�C����Ԃ�*/
	uint8_t note_number;			/*�m�[�g�i���o�[*/
	uint16_t assign_map;			/*���蓖�ĉ\�ȃ`���l��*/
}voice_param_t;



enum params_t {
	DT,
	ML,
	TL,
	KS,
	AR,
	AM,
	DR,
	SR,
	SL,
	RR,
	FB,
	AL
};

struct FMParam_t{
	enum Pan_t pan;
	uint8_t timbre[38];
};

struct SSGParam_t{
	uint8_t useEnvelope;
	uint8_t envelopeShape;
	uint16_t envelopeFreq;
};

struct RhythmVolume_t {
	uint8_t BD;
	uint8_t SD;
	uint8_t TC;
	uint8_t HH;
	uint8_t TOM;
	uint8_t RIM;
};

struct NoteList_t{
	uint8_t count;
	uint8_t noteId[18];
	uint8_t noteNumber[18];
};
#endif /* STRUCTS_H_ */