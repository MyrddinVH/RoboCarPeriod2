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
#include <avr/interrupt.h>
#include "motorControl.h"
#include "ultrasoonMode.h"

#define SLAVE_SPEED 50

uint8_t slaveSpeed = SLAVE_SPEED;
 _Bool Forward = false;
 _Bool Left	   = false;
 _Bool Right   = false;		  


void slaveMode(void){

	_Bool sensorLeft   = PINC & (1 << PORTC0);   // Read left sensor
	_Bool sensorCenter = PINC & (1 << PORTC2);   // Read center sensor
	_Bool sensorRight  = PINC & (1 << PORTC1);   // Read right sensor
	
	//check wich way the car needs to turn or just go straight
	if(!sensorCenter && sensorLeft && sensorRight){
		Forward = true;
		Left = false;
		Right = false;
	}else if(sensorCenter && !sensorLeft && sensorRight){
		Forward = false;
		Left = true;
		Right = false;
	}else if(sensorCenter && !sensorRight && sensorLeft){
		Forward = false;
		Left = false;
		Right = true;
	}
	
	//get a distance from the ultrasonic sensors to make sure it doesn't collide with the car in front
	pulseTimer();
	if(distancePB1 != 0 || distancePB2 != 0){
		if(distancePB1 <= 5 || distancePB2 <= 5){
			slaveSpeed = 0;
		}else{
			slaveSpeed = SLAVE_SPEED;
		}
	}else{
		slaveSpeed = SLAVE_SPEED;
	}
	
	//decide wich way it needs to go at what speed
	if(Forward){
		motorForward(slaveSpeed, slaveSpeed);
	}else if(Left){
		tankTurnLeft(slaveSpeed);
	}else if(Right){
		tankTurnRight(slaveSpeed);
	}
}