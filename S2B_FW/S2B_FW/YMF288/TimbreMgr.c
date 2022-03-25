/*
 * TimbreMgr.c
 *
 * Created: 2022/03/23 11:24:09
 *  Author: Owner
 */ 

#include "TimbreMgr.h"

uint8_t timbre_ram[38 * 24];

void Timbre_RAM_Write(uint8_t *from,uint8_t pgm);
void Timbre_EEPROM_Write(uint8_t *from,uint8_t pgm);

void Timbre_ROM_Read(uint8_t *to,uint8_t pgm);
void Timbre_RAM_Read(uint8_t *to,uint8_t pgm);
void Timbre_EEPROM_Read(uint8_t *to,uint8_t pgm);

void Timbre_Read(uint8_t *to,enum TimbreArea_t area,uint8_t pgm){
	switch(area){
		case ROM:
			Timbre_ROM_Read(to,pgm);
			break;
		case RAM:
			Timbre_RAM_Read(to,pgm);
			break;
		case EEPROM:
			Timbre_EEPROM_Read(to,pgm);
			break;
	}
	return;
}

void Timbre_Write(enum TimbreArea_t area, uint8_t *from,uint8_t pgm){
	switch(area){
		case ROM:
			//prohibited
			break;
		case RAM:
			Timbre_RAM_Write(from,pgm);
			break;
		case EEPROM:
			Timbre_EEPROM_Write(from,pgm);
			break;
	}
	return;
}


void Timbre_RAM_Write(uint8_t *from,uint8_t pgm){
	memcpy(&timbre_ram[38 * pgm],from,38);
}

void Timbre_EEPROM_Write(uint8_t *from,uint8_t pgm){
	eeprom_busy_wait();
	eeprom_write_block(from,(void *)(38 * pgm),38);
}

void Timbre_ROM_Read(uint8_t *to,uint8_t pgm){

}

void Timbre_RAM_Read(uint8_t *to,uint8_t pgm){
	memcpy(to,&timbre_ram[38 * pgm],38);
}

void Timbre_EEPROM_Read(uint8_t *to,uint8_t pgm){
	eeprom_busy_wait();
	eeprom_read_block(to,(void *)(38 * pgm),38);
}
