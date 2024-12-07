/*
 * motorControl.c
 *
 * Created: 28-11-2024 13:13:04
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU (16000000UL)
#include <avr/io.h>
#include <util/delay.h>
// Motor forward functie voor snellheid aanpassen integers van 0 -> 255 maximaalmotorForward(int speed1, int speed2){	PORTB &= ~(1<<PORTB0); // PortB bit 0 uitzetten
	PORTD &= ~(1<<PORTD7); // PortB bit 7 uitzetten	OCR0A = speed1;
	OCR0B = speed2;}// Motor backward functie voor snellheid aanpassen integers van 0 -> 255 maximaalmotorBackward(int speed1, int speed2){	PORTB |= (1<<PORTB0); // PortB bit 0 aanzetten
	PORTD |= (1<<PORTD7); // PortB bit 7 aanzetten	OCR0A = 255 - speed1;
	OCR0B = 255 - speed2;}// Tank draai functie voor snellheid aanpassen integers van 0 -> 255 maximaaltankTurnLeft(int speed){	PORTB &= ~(1<<PORTB0);
	PORTD |= (1<<PORTD7);	OCR0A = 255 - speed;
	OCR0B = speed;}// Tank draai functie voor snellheid aanpassen integers van 0 -> 255 maximaaltankTurnRight(int speed){	PORTB |= (1<<PORTB0);
	PORTD &= ~(1<<PORTD7);	OCR0A = speed;
	OCR0B = 255 - speed;}
