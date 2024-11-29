/*
 * Motorcontrol.c
 *
 * Created: 28-11-2024 13:14:54
 * Author : Pnhpl
 */ 

#define F_CPU (16000000UL)
#include <avr/io.h>
#include <util/delay.h>

// Snellheid gaat van 0 naar 4999 0 stillstand 4999 max
int main(void)
{
int initSpeed = 0;
 // PB0 - PB5 output, rest input gehardforced voor nu
 DDRB = 0b00111111;
 DDRD = 0b10000000;
 // Configure Timer/counter 1 to generate an interrupt approximately every second
 //
 // For this configuration, several bits can keep their reset value.
 // This means that this function only implements instructions for bits
 // that must be updated.
 // Refer to the datasheet for a description of all the bits.
 // - WGM1[3:0] = 1110 : waveform generation mode is Fast PWM with TOP in ICR1
 // - CS1[2:0] = 011 : 64 prescaler
 //
 // TOP = (F_CPU / (F_PWM * N)) - 1
 // = (16MHz / (50Hz * 64)) - 1
 // = 4999
 TCCR1A |= (1<<WGM11);
 TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
 ICR1 = 4999;
 // Set Compare Output Mode for both channels A and B

 TCCR1A |= (1<<COM1A1)  | (1<<COM1B1) ; //  zodat het 0 -> 4999 gaat voor snelheid zonder inverse 4999 -> 0

// Initial speed set
 OCR1A = 0;
 OCR1B = 0;}// Motor forward functie voor snellheid aanpassen integers van 0 -> 4999 maximaalmotorForward(int speed1, int speed2){	 PORTB = 0b00000110;
	 PORTD = 0b00000000;	 OCR1A = speed1;
	 OCR1B = speed2;	 		 }// Motor backward functie voor snellheid aanpassen integers van 0 -> 4999 maximaalmotorBackward(int speed1, int speed2){	 PORTB = 0b00000111;
	 PORTD = 0b10000000;	 OCR1A = speed1;
	 OCR1B = speed2;	 	}// Tank draai functie voor snellheid aanpassen integers van 0 -> 4999 maximaaltankDraaiLinks(int speed1, int speed2){	 PORTB = 0b00000110;
	 PORTD = 0b10000000;	 OCR1A = speed1;
	 OCR1B = speed2;}// Tank draai functie voor snellheid aanpassen integers van 0 -> 4999 maximaaltankDraaiRechts(int speed1, int speed2){	 PORTB = 0b00000111;
	 PORTD = 0b00000000;	 OCR1A = speed1;
	 OCR1B = speed2;}