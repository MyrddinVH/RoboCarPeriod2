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
#include "ultrasoonMode.h"

volatile uint8_t slaveSpeed = 70;
volatile _Bool Forward = false;
volatile _Bool Left	   = false;			 //    MRL
volatile _Bool Right   = false;		  //PC76543210

void slaveMode(void){

	_Bool sensorLeft   = PINC & (1 << PORTC0);   // Read left sensor
	_Bool sensorCenter = PINC & (1 << PORTC2);   // Read center sensor
	_Bool sensorRight  = PINC & (1 << PORTC1);   // Read right sensor
	
	//check wich way the car needs to turn or just go straight
	if(!sensorCenter){
		Forward = true;
		Left = false;
		Right = false;
	}else if(sensorCenter && !sensorLeft){
		Forward = false;
		Left = true;
		Right = false;
	}else if(sensorCenter && !sensorRight){
		Forward = false;
		Left = false;
		Right = true;
	}else{
		Forward = false;
		Left = false;
		Right = false;
	}
	
	//gets a distance from the ultrasonic sensors to make sure it doesn't collide
	pulseTimer();
	if(distancePB1 >= 50 || distancePB2 >= 50){
		if(distancePB1 != 0 || distancePB2 != 0){
			slaveSpeed = 0;
		}
	}else{
		slaveSpeed = 70;
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