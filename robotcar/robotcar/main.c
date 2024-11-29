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
<<<<<<< HEAD
    DDRD |= (1<<DDD5) | (1<<DDD7);
	DDRC |= (1<<DDC0);
	DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
	
=======
	
	// PWM setup
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	ICR1 = 4999;
	TCCR1A |= (1<<COM1A1)  | (1<<COM1B1) ;
	OCR1A = 0;
	OCR1B = 0;
			
>>>>>>> motorControl
    while (1){
		slaveMode();
    }
}

