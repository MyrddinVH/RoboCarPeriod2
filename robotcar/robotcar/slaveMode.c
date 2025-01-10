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

volatile uint8_t slaveSpeed = 70;
volatile _Bool Forward = false;
volatile _Bool Left	   = false;			 //    MRL
volatile _Bool Right   = false;		  //PC76543210

void slaveMode(void){

	uint8_t sensor_left = PINC & (1 << PORTC0);   // Read left sensor
	uint8_t sensor_center = PINC & (1 << PORTC2); // Read center sensor
	uint8_t sensor_right = PINC & (1 << PORTC1);  // Read right sensor
	
	if(!sensor_center && sensor_left && sensor_right){
		Forward = true;
		Left = false;
		Right = false;
	}else if(sensor_center && !sensor_left && sensor_right){
		Forward = false;
		Left = true;
		Right = false;
	}else if(sensor_center && sensor_left && !sensor_right){
		Forward = false;
		Left = false;
		Right = true;
	}else{
		Forward = false;
		Left = false;
		Right = false;
	}
	
	if(Forward){
		motorForward(slaveSpeed, slaveSpeed);
	}else if(Left){
		tankTurnLeft(slaveSpeed);
	}else if(Right){
		tankTurnRight(slaveSpeed);
	}
}