/*
 * LED.c
 *
 * Created: 24-1-2025 12:21:05
 *  Author: timde
 */ 
#include <avr/io.h>
#include <stdbool.h>
#include "ultrasoonMode.h"

#define INTERVAL 500
#define LED_LEFT PORTB5
#define LED_RIGHT PORTB3

uint32_t currentMillisLED = 0;
uint32_t previousMillisLED = 0;

volatile _Bool startLeftBlink = 0;
volatile _Bool startRightBlink = 0;
_Bool ledLeft = 0;
_Bool ledRight = 0;

void ledBlinker(void){
	currentMillisLED = ms;
	if(currentMillisLED - previousMillisLED >= INTERVAL){
		previousMillisLED = currentMillisLED;
		if(startLeftBlink){
			if(ledLeft == false){
				ledLeft = true;
			}else{
				ledLeft = false;
			}
		}
		if(startRightBlink){
			if(ledRight == false){
				ledRight = true;
			}else{
				ledRight = false;
			}
		}
	}
	
	if(ledRight){
		PORTB |= (1<<LED_RIGHT);
	}else{
		PORTB &= ~(1<<LED_RIGHT);
	}
	
	if(ledLeft){
		PORTD |= (1<<LED_LEFT);
	}else{
		PORTD &= ~(1<<LED_LEFT);
	}
}

void startLeftLedBlink(void){
	startLeftBlink = true;
	startRightBlink = false;
	ledRight = false;
}

void startRightLedBlink(void){
	startLeftBlink = false;
	startRightBlink = true;
	ledLeft = false;
}

void stopBlink(void){
	startLeftBlink = false;
	startRightBlink = false;
	ledLeft = false;
	ledRight = false;
}