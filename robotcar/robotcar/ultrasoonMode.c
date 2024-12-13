/*
 * ultrasoonMode.c
 *
 * Created: 29-11-2024 09:20:00
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

uint16_t measure_distance(void);

void initHCSR04(){
	DDRD |= (1<<PORTD4); //set PD4 as output
	DDRB &= ~(1<<PORTB1); //set PB1 as trigger
	
	DDRB |= (1<<DDB5);
	PORTB |= (1<<PORTB5);
	
	PORTD &= ~(1 << PORTD4); //trigger is set to low by default
}

void UltrasoonLoop(){
	uint16_t distance = measure_distance();
	_delay_ms(60);
	if(distance < 50){
		PORTB |= (1<<PORTB5);
	}
	else{
		PORTB &= ~(1<<PORTB5);
	}
}

uint16_t measure_distance(void){
	uint16_t pulseWidth = 0;
	
	//send a 10 microseconds pulse
	PORTD |= (1 << PORTD4);
	_delay_us(10);
	PORTD &= (1<<PORTD4);
	
	while(!(PINB & (1 << PORTB1))); //wait for the echo pin to become high
	
	TCNT1 = 0; //reset the timer
	TCCR1B = (1 << CS11); //start the timer with prescaler 8
	
	while (PINB & (1 << PORTB1)) {
		if (TCNT1 > 60000) { // Timeout (~30ms)
			TCCR1B = 0; // Stop Timer1
			return 0; // Return 0 to indicate timeout
		}
	}
	
	TCCR1B = 0; // Stop Timer1
	pulseWidth = TCNT1; // Read the Timer1 counter value
	
	return pulseWidth / 58; // returns the distance in CM
}