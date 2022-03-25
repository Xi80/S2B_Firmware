/*
 * YMF288.h
 *
 * Created: 2022/03/23 11:22:41
 *  Author: Owner
 */ 


#ifndef YMF288_H_
#define YMF288_H_

#include "FMCtrl.h"
#include "RhythmCtrl.h"
#include "ScaleXform.h"
#include "SSGCtrl.h"
#include "TimbreMgr.h"

void YMF288_Reset(void);

void YMF288_NoteOn(uint8_t id,uint8_t note,uint8_t pbs,uint8_t pb);
void YMF288_NoteOff(uint8_t id);

void YMF288_ProgramChange(uint8_t id,enum TimbreArea_t area,uint8_t pgm);
void YMF288_PitchBend(uint8_t id,uint8_t note,uint8_t pbs,uint8_t pb);

void YMF288_Pan(uint8_t id);

#endif /* YMF288_H_ */