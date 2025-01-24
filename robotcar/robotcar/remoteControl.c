/*
 * remoteControl.c
 *
 * Created: 29-11-2024 09:20:43
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "motorControl.h"
#include "SoftSerial.h"

#define BLESPEED 100

enum directionBLE{forwardBLE, leftBLE, rightBLE, backwardBLE, stopBLE};
enum directionBLE directionToDriveBLE;

void initRemoteControl(){
	SoftSerialInit();
	sei();
	usart0_transmitStr("remote control initialized\n");
}

void remoteControl(){
	//hier komt de code in, getest met de debugger
	if(SoftSerialUnread() > 0){
		//hier komt de code niet
		usart0_transmitStr("test\n");
		char data = SoftSerialReceiveByte();
		
		switch (data){
			case 'w':
			directionToDriveBLE = forwardBLE;
			usart0_transmitStr("w\n");
			break;
			
			case 'a':
			directionToDriveBLE = leftBLE;
			usart0_transmitStr("a\n");
			break;
			
			case 's': 
			directionToDriveBLE = backwardBLE;
			usart0_transmitStr("s\n");
			break;
			
			case 'd':
			directionToDriveBLE = rightBLE;
			usart0_transmitStr("d\n");
			break;
			
			case 'b':
			directionToDriveBLE = stopBLE;
			usart0_transmitStr("b\n");
			break;
			
			default:
			directionToDriveBLE = stopBLE;
			usart0_transmitStr("default\n");
			break;
		}
	}
	
	switch (directionToDriveBLE){
		case forwardBLE:
		motorForward(BLESPEED,BLESPEED);
		break;
		case leftBLE:
		tankTurnLeft(BLESPEED);
		break;
		case rightBLE:
		tankTurnRight(BLESPEED);
		break;
		case backwardBLE:
		motorBackward(BLESPEED, BLESPEED);
		break;
		case stopBLE:
		motorForward(0,0);
		break;
		default:
		motorForward(0,0);
		break;
	}
}