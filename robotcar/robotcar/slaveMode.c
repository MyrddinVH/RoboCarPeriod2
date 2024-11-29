/*
 * slaveMode.c
 *
 * Created: 29-11-2024 09:20:25
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

void slaveMode(){
	//PB3 = right
	//PB4 = middle
	//PB5 = left
	
	_Bool forward;
	_Bool left;
	_Bool right;
	int slaveMaskForward = 0b00101000;
	int slaveMaskLeft = 0b00011000;
	int slaveMaskRight = 0b00110000;
	
	if((PINB & slaveMaskForward) == 0x28){
		forward = true;
		left = false;
		right = false;
	}
	
	if((PINB & slaveMaskLeft) == 0x18){
		forward = false;
		left = true;
		right = false;
	}
	
	if((PINB & slaveMaskRight) == 0x30){
		forward = false;
		left = false;
		right = true;
	}
	
	if(forward){
		motorForward(20);
	}
	
	if(left){
		tankTurnLeft(20);
	}
	
	if(right){
		tankTurnRight(20);
	}
}
