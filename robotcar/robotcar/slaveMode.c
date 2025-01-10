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

volatile uint8_t slaveSpeed = 40;
volatile _Bool forward;
volatile _Bool left;			 //    MRL
volatile _Bool right;		  //PC76543210
volatile int slaveMaskForward = 0b00000011;
volatile int slaveMaskLeft 	  = 0b00000110;
volatile int slaveMaskRight   = 0b00000101;

void slaveMode(void){

	uint8_t sensor_left = PINC & (1 << PORTC0);   // Read left sensor
	uint8_t sensor_center = PINC & (1 << PORTC1); // Read center sensor
	uint8_t sensor_right = PINC & (1 << PORTC2);  // Read right sensor
	
	if(!sensor_center && sensor_left && sensor_right){
		forward = true;
		left = false;
		right = false;
	}else if(sensor_center && !sensor_left && sensor_right){
		forward = false;
		left = true;
		right = false;
	}else if(sensor_center && sensor_left && !sensor_right){
		forward = false;
		left = false;
		right = true;
	}else{
		motorForward(0,0);
		forward = false;
		left = false;
		right = false;
	}
	
	if(forward){
		motorForward(slaveSpeed, slaveSpeed);
	}else if(left){
		tankTurnLeft(slaveSpeed);
	}else if(right){
		tankTurnRight(slaveSpeed);
	}
}
