/*
 * RhythmCtrl.h
 *
 * Created: 2022/03/22 12:36:14
 *  Author: Owner
 */ 


#ifndef RHYTHMCTRL_H_
#define RHYTHMCTRL_H_

#include "RegCtrl.h"
#include "CommonStructs.h"
enum RhythmInstrument_t {
	BD = 0x01,
	SD = 0x02,
	TC = 0x04,
	HH = 0x08,
	TOM = 0x10,
	RIM = 0x20
};

void Rhythm_Key(uint8_t dump,enum RhythmInstrument_t inst);

void Rhythm_SetTotalLevel(uint8_t tl);

void Rhythm_SetInstLevel(enum RhythmInstrument_t inst,enum Pan_t pan,uint8_t tl);


#endif /* RHYTHMCTRL_H_ */