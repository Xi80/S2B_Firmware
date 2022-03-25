/*
 * ParamXchanger.h
 *
 * Created: 2022/03/24 11:31:05
 *  Author: Owner
 */ 


#ifndef PARAMXCHANGER_H_
#define PARAMXCHANGER_H_

#include <avr/io.h>

#include "Structs.h"
#include "SysExProcessor.h"
#include "VoiceAssigner.h"
#include "../YMF288/YMF288.h"
#include "../Serial/xprintf.h"

void PX_Init(void);

void PX_NoteOn(uint8_t ch,uint8_t note,uint8_t vel);

void PX_NoteOff(uint8_t ch,uint8_t note);

void PX_ControlChange(uint8_t ch,uint8_t ctrl,uint8_t val);

void PX_ProgramChange(uint8_t ch,uint8_t pgm);

void PX_PitchBend(uint8_t ch,uint16_t val);

void PX_Drums(uint8_t note,uint8_t vel);

void PX_SetEnvelopeShape(uint8_t ch,uint8_t shape);

void PX_SetEnvelopeFreq(uint8_t id,uint16_t freq);

void PX_ReceiveTimbre(uint8_t pgm,uint8_t *data);
#endif /* PARAMXCHANGER_H_ */