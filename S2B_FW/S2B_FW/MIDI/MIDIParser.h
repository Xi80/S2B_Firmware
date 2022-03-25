/*
 * MIDIParser.h
 *
 * Created: 2022/03/24 8:25:38
 *  Author: Owner
 */ 


#ifndef MIDIPARSER_H_
#define MIDIPARSER_H_

#include <avr/io.h>
#include <string.h>
#include "Structs.h"

extern void (*MIDICallBack_NoteOn)(struct Note_t);
extern void (*MIDICallBack_NoteOff)(struct Note_t);

extern void (*MIDICallBack_ControlChange)(struct ControlChange_t);
extern void (*MIDICallBack_ProgramChange)(struct ProgramChange_t);

extern void (*MIDICallBack_PitchBend)(struct PitchBend_t);

extern void (*MIDICallBack_SystemExclusive)(struct SysEx_t);

void MIDI_Parse(uint8_t data);

#endif /* MIDIPARSER_H_ */