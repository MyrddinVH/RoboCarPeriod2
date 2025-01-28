/*
 * remoteControl.c
 *
 * Created: 29-11-2024 09:20:43
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "motorControl.h"
#include "Bluetooth.h"

char recievedData;
volatile int remoteSpeed = 100;

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
			case '1': // set speed 1 (80)
				remoteSpeed = 80;
				break;
			case '2': // set speed 2 (150)
				remoteSpeed = 150;
				break;
			case '3': // set speed 3 (255)
				remoteSpeed = 255;
				break;
			case 'b': //stop  
				motorForward(0,0);
				break;
			case 'd': // right
				tankTurnLeft(remoteSpeed);
				break;
			case 'a': //left
				tankTurnRight(remoteSpeed);
				break;
			case 'w': //forward
				motorForward(remoteSpeed,remoteSpeed);
				break;
			case 's': //backward
				motorBackward(remoteSpeed,remoteSpeed);
				break;
			default:
				break;
		}
	}
}