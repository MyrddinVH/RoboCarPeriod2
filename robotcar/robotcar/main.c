/*
 * robotcar.c
 *
 * Created: 22-11-2024 09:46:49
 * Author : Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "LCD.h"
#include "motorControl.h"
#include "remoteControl.h"
#include "slaveMode.h"
#include "ultrasoon.h"
#include "timeSaving.h"


int main(void){
    DDRD = 0x3C;
	DDRC = 0x1;
	DDRB = 0x32;
    while (1){
		
    }
}

