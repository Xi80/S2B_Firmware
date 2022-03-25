/*
 * SerialCtrl.h
 *
 * Created: 2022/03/21 9:51:49
 *  Author: Owner
 */ 


#ifndef SERIALCTRL_H_
#define SERIALCTRL_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "xprintf.h"
#include "ringbuff.h"

void SerialInit_Debug(void);

void SerialInit_MIDI(void);

void DebugWrite(int chr);

int DebugRead(void);

void MIDIWrite(int dat);

int MIDIRead(void);

#endif /* SERIALCTRL_H_ */