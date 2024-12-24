/*
 * ultrasoonMode.c
 *
 * Created: 29-11-2024 09:20:00
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "Debugger.h"
#include "ultrasoonMode.h"
#include "millis.h"
#include "motorControl.h"
#include <time.h> 
#include <avr/interrupt.h>

#define STOP_DISTANCE 100
#define TURN_TIME 750
#define SPEED_ULTRASOON 70

enum driveDirection{forward, turnLeft, turnRight};
enum driveDirection directionToDrive;


unsigned long pulseIn(volatile uint8_t *port, uint8_t pin, uint8_t state, unsigned long timeout_us);
void pulseTimer();

// uint32_t timeToTurn = 3000;
uint32_t previousTurnMillis = 0;
uint32_t currentTurnMillis = 0;

uint32_t previousmillis = 0;
// unsigned long currentmillis = 0;
uint32_t interval = 60;
uint32_t distancePB1 = 0;
uint32_t distancePB2 = 0;
volatile uint32_t ms = 0;

bool objectDetected = false;



int sensorToRead = 1;


void initHCSR04(){
	DDRD |= (1<<PORTD4); //set PD4 as output
	DDRB &= ~(1<<PORTB1); //set PB1 as trigger
	DDRB &= ~(1<<PORTB2);

	PORTD &= ~(1 << PORTD4); //trigger is set to low by default
	usart0_transmitStr("ultrasoon initialized");
}


void pulseTimer(){
	unsigned long currentmillis = millis();
	
 	if(currentmillis - previousmillis >= interval){
 		sendPulse();
		previousmillis = currentmillis;
 	}
}

void sendPulse(){
		PORTD |= (1 << PORTD4);
		_delay_us(10);
		PORTD &= ~(1<<PORTD4);
	
		switch(sensorToRead){
			case 1:
			distancePB1 = pulseIn(&PINB, PORTB1, 1, 30000);
			distancePB1 = distancePB1 / 10;
			char temp[50];
// 			sprintf(temp, "%d", distancePB1);
// 			usart0_transmitStr("sensor on PB1");
// 			usart0_transmitStr("\n");
// 			usart0_transmitStr(temp);
// 			usart0_transmitStr("\n");
			sensorToRead = 2;
			break;
			case 2:
			distancePB2 = pulseIn(&PINB, PORTB2, 1, 30000);
			distancePB2 = distancePB2 / 10;
// 			sprintf(temp, "%d", distancePB2);
// 			usart0_transmitStr("sensor on pb2");
// 			usart0_transmitStr("\n");
// 			usart0_transmitStr(temp);
// 			usart0_transmitStr("\n");
			sensorToRead = 1;
			break;
			default:
			sensorToRead = 1;
			break;
		}
}


// Function to measure the duration of a pulse on a specified pin
unsigned long pulseIn(volatile uint8_t *port, uint8_t pin, uint8_t state, unsigned long timeout_us) {
	// Set up the timeout in clock cycles
	unsigned long timeout = (F_CPU / 1000000) * timeout_us; // Convert timeout from microseconds to clock cycles
	unsigned long count = 0;
	uint8_t stateMask = state ? (1 << pin) : 0;

	// Wait for the pin to change to the desired state
	while ((*port & (1 << pin)) != stateMask) {
		if (count++ >= timeout) {
			return 0; // Timeout occurred
		}
		_delay_us(1); // Small delay to avoid excessive CPU usage
	}

	// Measure the pulse duration
	count = 0;
	while ((*port & (1 << pin)) == stateMask) {
		if (count++ >= timeout) {
			return 0; // Timeout occurred
		}
		_delay_us(1); // Increment in microsecond intervals
	}

	// Convert count to microseconds
	return count;
}

inline uint32_t millis(void)
{
	// ms is a 32-bit variable (uint32_t). This means that multiple accesses
	// are needed to read or write the value of ms. There is a chance that
	// in the middle of these multiple accesses, the ms value is written due to
	// the ISR being triggered. In order to make sure the value of ms is not
	// updated when reading it, disable interrupts while reading the value.
	cli();
	uint32_t ret = ms;
	sei();
	return ret;
}

void millis_init(void)
{
	ms = 0;
	// Configure Timer/counter 1 to generate an interrupt every millisecond
	//
	// - WGM1[3:0] = 0100 : waveform generation mode is CTC with TOP in OCR1A
	// - CS1[2:0] = 011 : 64 prescaler
	// - TOP : 24999
	//
	// T_events = T_CPU * N * (TOP + 1)
	// = 1/16 MHz * 64 * (24999 + 1)
	// = 1 ms

	TCCR1B |= (1<<WGM12);        // Set CTC mode
	TCCR1B |= (1<<CS11) | (1<<CS10); // Set prescaler to 64
	OCR1A = 249;               // Set TOP value to 24999 for 16-bit resolution

	// Timer/Counter1 Output Compare Match A Interrupt Enable
	TIMSK1 |= (1<<OCIE1A);
}

// Interrupt Service Routine that is automatically executed as soon as
// timer/counter 1 has reached its compare value
ISR(TIMER1_COMPA_vect)
{
	ms++;
}

void checkForObject(){
	if((distancePB1 > STOP_DISTANCE)  || (distancePB2 > STOP_DISTANCE) ){
		if((distancePB1 != 0) || (distancePB2 != 0)){
			objectDetected = false;
		}
	}
	else if((distancePB1 < STOP_DISTANCE) || (distancePB2 < STOP_DISTANCE)){
		if ((distancePB1 != 0) || (distancePB2 != 0)){
			objectDetected  = true;
		}
	}
}

void driver(){
	static bool turning = false; // Indicates if the car is currently turning
	static uint32_t turnStartMillis = 0; // Stores the time when the turn started

	if (!objectDetected && !turning) {
		directionToDrive = forward; // Continue forward if no object is detected
		} else if (!turning) {
		if (distancePB1 < distancePB2) {
			directionToDrive = turnLeft;
			} else if (distancePB1 > distancePB2) {
			directionToDrive = turnRight;
		}
		turning = true; // Start the turn
		turnStartMillis = millis(); // Record the start time of the turn
	}

	// Check if the car needs to stop turning
	if (turning) {
		uint32_t currentMillis = millis();
		if (currentMillis - turnStartMillis >= TURN_TIME) {
			turning = false; // Stop turning
			directionToDrive = forward; // Resume forward motion
		}
	}

	// Execute motion based on directionToDrive
	switch (directionToDrive) {
		case forward:
		motorForward(100, 100);
		break;
		case turnLeft:
		tankTurnLeft(100);
		break;
		case turnRight:
		tankTurnRight(100);
		break;
		default:
		break;
	}
}

void runUltrasoon(){
	pulseTimer();
	checkForObject();
	driver();
// 	driver2();
}

