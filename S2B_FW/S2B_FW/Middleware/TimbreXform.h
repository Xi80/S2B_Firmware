/*
 * TimbreXform.h
 *
 * Created: 2022/03/24 18:53:04
 *  Author: Owner
 */ 


#ifndef TIMBREXFORM_H_
#define TIMBREXFORM_H_


#include "Structs.h"
#include <avr/io.h>
#include <string.h>
void TX_XformToStruct(struct FMParam_t *to,uint8_t *timbre);

void TX_XformToArray(uint8_t *to,struct FMParam_t *timbre);
#endif /* TIMBREXFORM_H_ */