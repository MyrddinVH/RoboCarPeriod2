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
#include "motorControl.h"

volatile uint8_t speed = 100;

void slaveMode(){
	//PC0 = left
	//PC1 = right
	//PC2 = middle
	
	_Bool forward;
	_Bool left;
	_Bool right;
	int slaveMaskForward = 0b00000100;
	int slaveMaskLeft = 0b00000001;
	int slaveMaskRight = 0b00000010;

	
	if((PINC & slaveMaskForward) == 4){
		forward = true;
		left = false;
		right = false;
	}
	
	if((PINC & slaveMaskLeft) == 1){
		forward = false;
		left = true;
		right = false;
	}
	
	if((PINC & slaveMaskRight) == 2){
		forward = false;
		left = false;
		right = true;
	}
	
	if(forward){
		motorForward(speed, speed);
	}
	
	if(left){
		tankTurnLeft(speed);
	}
	
	if(right){
		tankTurnRight(speed);
	}
}
