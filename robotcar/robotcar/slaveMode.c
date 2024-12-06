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

<<<<<<< HEAD
volatile uint8_t speedSlave = 40;
=======
volatile uint8_t speed = 40;
>>>>>>> slaveMode

void slaveMode(){
	//PC0 = left
	//PC1 = right
	//PC2 = middle
	
	_Bool forward;
	_Bool left;					//MRL
	_Bool right;		 //PC76543210
	int slaveMaskForward = 0b00000011;
	int slaveMaskLeft 	 = 0b00000110;
	int slaveMaskRight   = 0b00000101;

	
	if((PINC & slaveMaskForward) == 3){
		forward = true;
		left = false;
		right = false;
	}
	
	if((PINC & slaveMaskLeft) == 6){
		forward = false;
		left = true;
		right = false;
	}
	
	if((PINC & slaveMaskRight) == 5){
		forward = false;
		left = false;
		right = true;
	}
	
	if((PINC & 0b00000111) == 7){
		forward = true;
		left = false;
		right = false;
	}
	
	if(forward){
<<<<<<< HEAD
		motorForward(speedSlave,speedSlave);
	}
	
	if(left){
		tankTurnLeft(speedSlave);
	}
	
	if(right){
		tankTurnRight(speedSlave);
=======
		motorForward(speed,speed);
	}
	
	if(left){
		tankTurnRight(speed);
	}
	
	if(right){
		tankTurnRight(speed);
>>>>>>> slaveMode
	}
}
