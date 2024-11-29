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
	
	// PWM setup
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	ICR1 = 4999;
	TCCR1A |= (1<<COM1A1)  | (1<<COM1B1) ;
	OCR1A = 0;
	OCR1B = 0;
			
    while (1){
		
    }
}

