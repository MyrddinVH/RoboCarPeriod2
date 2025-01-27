/*
 * remoteControl.c
 *
 * Created: 29-11-2024 09:20:43
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "motorControl.h"
#include "remoteControl.h"
#include "Bluetooth.h"

char recievedData;

void remoteInit(void){
	usart0_init();
	sei();
}

void remoteControl(void) {
	// Check if data is available
	if (usart0_nUnread() > 0) {
		// Read received data
		recievedData = usart0_receive();

	// Perform actions based on the received data
		switch (recievedData) {
			case 'b':
			motorForward(0,0);
			break;
			case 'a':
			tankTurnLeft(100);
			break;
			case 'd':
			tankTurnRight(100);
			break;
			case 'w':
			motorForward(100,100);
			break;
			case 's':
			motorBackward(100,100);
			break;
			default:
			// Handle invalid command if necessary
			break;
		}
	}
}