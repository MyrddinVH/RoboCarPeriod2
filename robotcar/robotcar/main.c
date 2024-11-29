/*
 * robotcar.c
 *
 * Created: 22-11-2024 09:46:49
 * Author : Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "LCD.h"
#include "motorControl.h"
#include "remoteControl.h"
#include "slaveMode.h"
#include "ultrasoonMode.h"
#include "timeSaving.h"
#include "modeSwitch.h"


int main(void){
    DDRD |= (1<<DDD5) | (1<<DDD7);
	DDRC |= (1<<DDC0);
	DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
	
    while (1){
		slaveMode();
    }
}

