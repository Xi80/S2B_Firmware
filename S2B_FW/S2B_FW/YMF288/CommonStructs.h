/*
 * CommonStructs.h
 *
 * Created: 2022/03/23 10:15:09
 *  Author: Owner
 */ 


#ifndef COMMONSTRUCTS_H_
#define COMMONSTRUCTS_H_

#include <avr/io.h>

enum TG_t {
	PSG,
	OPNA
};

struct FNumber_t {
	uint8_t block;
	uint16_t fNumber;
};

enum Pan_t {
	Left = 0x80,
	Center = 0xC0,
	Right = 0x40
};

#endif /* COMMONSTRUCTS_H_ */