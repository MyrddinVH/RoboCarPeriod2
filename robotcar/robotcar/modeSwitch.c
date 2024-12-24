/*
 * modeSwitch.c
 *
 * Created: 29-11-2024 10:15:01
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "slaveMode.h"
#include "ultrasoonMode.h"
#include "remoteControl.h"

enum modeNames { REMOTE,
				 SLAVE,
				 AUTO  };
volatile uint8_t mode = REMOTE;

ISR(PCINT0_vect){
	if((PINB & (1<<PINB7)) == 0){
		modeSwitcher();
	}
}


void modeSwitcher(){
	switch (mode){
		case REMOTE:
			mode = SLAVE;
			break;
		case SLAVE:
			mode = AUTO;
			break;
		case AUTO:
			mode = REMOTE;
			break;
	}
}

void modeChecker(){
	if(mode == REMOTE){
		remoteControl();
	}else if(mode == SLAVE){
		slaveMode();
	}else if(mode == AUTO){
// 		ultrasoonMode();
	}
}