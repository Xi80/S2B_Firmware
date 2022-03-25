/*
 * TimbreMgr.h
 *
 * Created: 2022/03/23 11:23:58
 *  Author: Owner
 */ 


#ifndef TIMBREMGR_H_
#define TIMBREMGR_H_

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <string.h>

enum TimbreArea_t {
	ROM,
	RAM,
	EEPROM
};

void Timbre_Read(uint8_t *to,enum TimbreArea_t area,uint8_t pgm);

void Timbre_Write(enum TimbreArea_t area,uint8_t *from,uint8_t pgm);

#endif /* TIMBREMGR_H_ */