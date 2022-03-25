/*
 * SysExProcessor.h
 *
 * Created: 2022/03/24 20:44:14
 *  Author: Owner
 */ 


#ifndef SYSEXPROCESSOR_H_
#define SYSEXPROCESSOR_H_

#include <avr/io.h>
#include "VoiceAssigner.h"
#include "ParamXchanger.h"


void SEP_Process(uint8_t *data,uint8_t size);


#endif /* SYSEXPROCESSOR_H_ */