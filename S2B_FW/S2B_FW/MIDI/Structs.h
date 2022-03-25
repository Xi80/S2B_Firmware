/*
 * Structs.h
 *
 * Created: 2022/03/24 8:20:55
 *  Author: Owner
 */ 


#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <avr/io.h>

struct Note_t{
	uint8_t channel;
	uint8_t noteNunber;
	uint8_t velocity;
};

struct ProgramChange_t{
	uint8_t channel;
	uint8_t value;
};

struct ControlChange_t{
	uint8_t channel;
	uint8_t ccNumber;
	uint8_t value;
};

struct PitchBend_t{
	uint8_t channel;
	uint16_t value;
};

struct SysEx_t{
	uint8_t length;
	uint8_t value[64];
};

#endif /* STRUCTS_H_ */