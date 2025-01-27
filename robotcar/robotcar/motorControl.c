/*
 * motorControl.c
 *
 * Created: 28-11-2024 13:13:04
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU (16000000UL)
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "LCD.h"
#include "LED.h"

_Bool forwardcalled = 0;
_Bool backwardcalled = 0;
_Bool leftcalled = 0;
_Bool rightcalled = 0;


// Motor forward functie voor snellheid aanpassen integers van 0 -> 255 maximaalvoid motorForward(int speed1, int speed2){	PORTB &= ~(1<<PORTB0); // PortB bit 0 uitzetten
	PORTD &= ~(1<<PORTD7); // PortB bit 7 uitzetten	OCR0A = speed1;
	OCR0B = speed2;	if (forwardcalled == 0){
			backwardcalled = 0;
			leftcalled = 0;
			rightcalled = 0;
			forwardcalled = 1;
			tankDirection();	
	}	stopBlink();}// Motor backward functie voor snellheid aanpassen integers van 0 -> 255 maximaalvoid motorBackward(int speed1, int speed2){	PORTB |= (1<<PORTB0); // PortB bit 0 aanzetten
	PORTD |= (1<<PORTD7); // PortB bit 7 aanzetten	OCR0A = 255 - speed1;
	OCR0B = 255 - speed2;	if (backwardcalled == 0){
			forwardcalled = 0;
			leftcalled = 0;
			rightcalled = 0;
			backwardcalled = 1;
			tankDirection();
	}	stopBlink();}// Tank draai functie voor snellheid aanpassen integers van 0 -> 255 maximaalvoid tankTurnLeft(int speed){	PORTB &= ~(1<<PORTB0);
	PORTD |= (1<<PORTD7);	OCR0A = speed;
	OCR0B = 255 - speed;	if (leftcalled == 0){
			forwardcalled = 0;
			rightcalled = 0;
			backwardcalled = 0;	
			leftcalled = 1;
			tankDirection();
	}	startLeftLedBlink();}// Tank draai functie voor snellheid aanpassen integers van 0 -> 255 maximaalvoid tankTurnRight(int speed){	PORTB |= (1<<PORTB0);
	PORTD &= ~(1<<PORTD7);	OCR0A = 255 - speed;
	OCR0B = speed;	if (rightcalled == 0){
			forwardcalled = 0;
			backwardcalled = 0;
			leftcalled = 0;
			rightcalled = 1;
			tankDirection();
	}		startRightLedBlink();}

void tankDirection(void){			// Local function to show direction
	if (forwardcalled == 1){
		arrowRemove();
		lcd_gotoxy(1,1);		_delay_ms(20);		lcd_puts("V");		
	}
	if (backwardcalled == 1){
		arrowRemove();
		lcd_gotoxy(1,0);		_delay_ms(20);		lcd_puts("^");	
	}
	if (leftcalled == 1){
		arrowRemove();
		lcd_gotoxy(0,1);		_delay_ms(20);		lcd_puts("<");
	}
	if (rightcalled == 1){
		arrowRemove();
		lcd_gotoxy(2,1);		_delay_ms(20);		lcd_puts(">");	
	}			
}

void arrowRemove(void){
		lcd_gotoxy(1,0);		_delay_ms(20);		lcd_puts(" ");
		_delay_ms(20);
		lcd_gotoxy(1,1);		_delay_ms(20);		lcd_puts(" ");
		_delay_ms(20);
		lcd_gotoxy(0,1);		_delay_ms(20);		lcd_puts(" ");
		_delay_ms(20);
		lcd_gotoxy(2,1);		_delay_ms(20);		lcd_puts(" ");
		_delay_ms(20);						
}