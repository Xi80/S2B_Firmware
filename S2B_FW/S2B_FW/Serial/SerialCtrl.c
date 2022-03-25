/*
 * SerialCtrl.c
 *
 * Created: 2022/03/21 9:55:50
 *  Author: Owner
 */ 

#include "SerialCtrl.h"

RingBuff_t MIDIBuffer,DebugBuffer;

ISR(USARTC0_RXC_vect){
	uint8_t recv = USARTC0.DATA;
	RingBuffer_Insert(&MIDIBuffer,recv);
}

ISR(USARTD0_RXC_vect){
	uint8_t recv = USARTD0.DATA;
	RingBuffer_Insert(&DebugBuffer,recv);
}

void SerialInit_Debug(void){
	cli();
	
	PORTD.DIRSET = 0x08;
	PORTD.OUTSET = 0x08;
	
	USARTD0.BAUDCTRLA = 12;
	USARTD0.BAUDCTRLB = 2 << 4;
	
	USARTD0.CTRLC = 0x03;
	USARTD0.CTRLB = 0x18;
	USARTD0.CTRLA = 0x30;
	
	RingBuffer_InitBuffer(&DebugBuffer);
	
	xdev_out(DebugWrite);
	xdev_in(DebugRead);
	sei();
}

void SerialInit_MIDI(void){	
	cli();
	
	PORTC.DIRSET = 0x08;
	PORTC.OUTSET = 0x08;
	
	USARTC0.BAUDCTRLA = 15;
	USARTC0.BAUDCTRLB = 2 << 4;
	
	USARTC0.CTRLC = 0x03;
	USARTC0.CTRLB = 0x18;
	USARTC0.CTRLA = 0x30;
	
	RingBuffer_InitBuffer(&MIDIBuffer);
	
	sei();
}

void DebugWrite(int chr){
	while(!(USARTD0.STATUS & 0x20));
	USARTD0.DATA = chr;
	return;
}

int DebugRead(void){
	while(!RingBuffer_GetCount(&DebugBuffer));
	return RingBuffer_Remove(&DebugBuffer);
}

void MIDIWrite(int dat){
	while(!(USARTC0.STATUS & 0x20));
	USARTC0.DATA = dat;
	return;
}

int MIDIRead(void){
	if(!RingBuffer_GetCount(&MIDIBuffer))return -1;
	return RingBuffer_Remove(&MIDIBuffer);
}
