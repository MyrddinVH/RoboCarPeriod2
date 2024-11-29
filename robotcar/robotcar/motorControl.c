/*
 * motorControl.c
 *
 * Created: 28-11-2024 13:13:04
 *  Author: Paul Nguyen
 */ 
#define F_CPU (16000000UL)
#include <avr/io.h>
#include <util/delay.h>

// Snellheid gaat van 0 naar 4999 0 stillstand 4999 max
// Motor forward functie voor snellheid aanpassen integers van 0 -> 4999 maximaalmotorForward(int speed1, int speed2){	PORTB = 0b00000110;
	PORTD = 0b00000000;	OCR1A = speed1;
	OCR1B = speed2;}// Motor backward functie voor snellheid aanpassen integers van 0 -> 4999 maximaalmotorBackward(int speed1, int speed2){	PORTB = 0b00000111;
	PORTD = 0b10000000;	OCR1A = 4999 - speed1;
	OCR1B = 4999 - speed2;}// Tank draai functie voor snellheid aanpassen integers van 0 -> 4999 maximaaltankDraaiLinks(int speed1, int speed2){	PORTB = 0b00000110;
	PORTD = 0b10000000;	OCR1A = 4999 - speed1;
	OCR1B = speed2;}// Tank draai functie voor snellheid aanpassen integers van 0 -> 4999 maximaaltankDraaiRechts(int speed1, int speed2){	PORTB = 0b00000111;
	PORTD = 0b00000000;	OCR1A = speed1;
	OCR1B = 4999 - speed2;}