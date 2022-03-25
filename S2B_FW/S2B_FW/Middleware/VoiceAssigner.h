/*
 * VoiceAssigner.h
 *
 * Created: 2022/03/24 10:00:15
 *  Author: Owner
 */ 


#ifndef VOICEASSIGNER_H_
#define VOICEASSIGNER_H_

#include <avr/io.h>
#include "Structs.h"
#include "../Serial/xprintf.h"

void VA_Init(void);

uint8_t VA_AssignOn(uint8_t ch,uint8_t note);

uint8_t VA_AssignOff(uint8_t ch,uint8_t note);

struct NoteList_t VA_AssignSustain(uint8_t ch,uint8_t flag);

struct NoteList_t VA_SearchVoices(uint8_t ch);

struct NoteList_t VA_GetAssignMap(uint8_t ch);

void VA_SetAssignMap(uint8_t ch,uint8_t count,uint8_t *voice);
#endif /* VOICEASSIGNER_H_ */