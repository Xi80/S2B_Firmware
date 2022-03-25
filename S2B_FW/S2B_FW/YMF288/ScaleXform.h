/*
 * ScaleXform.h
 *
 * Created: 2022/03/23 10:10:20
 *  Author: Owner
 */ 


#ifndef SCALEXFORM_H_
#define SCALEXFORM_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "CommonStructs.h"

struct FNumber_t Scale_GetFnumber(enum TG_t tg,uint8_t noteNumber,uint8_t pbs,uint16_t pb);


#endif /* SCALEXFORM_H_ */