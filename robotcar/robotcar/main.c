/*
 * robotcar.c
 *
 * Created: 22-11-2024 09:46:49
 * Author : Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "motorControl.h"
#include "remoteControl.h"
#include "slaveMode.h"
#include "ultrasoonMode.h"
#include "timeSaving.h"
#include "modeSwitch.h"
#include "LED.h"

volatile _Bool modeSwitch = false;

ISR(PCINT0_vect){
	if((PINB & (1<<PINB4)) == 0){
		modeSwitch = true;
	}
}

int main(void){

    DDRD |= (1<<DDD5) | (1<<DDD7) | (1<<DDD6) | (1<<DDD2);

	DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3);
	DDRB &= ~(1<<DDB4);
	
	DDRC &= ~((1<<DDC0) | (1<<DDC1) | (1<<DDC2));
	
	PORTB |= (1<<PORTB4);
	
	// PWM setup
	TCCR0A |= (1<<WGM00);
	TCCR0B |= (1<<CS02) | (1<<CS00);
	
	// Set Compare Output Mode for both channels A and B
	TCCR0A |= (1<<COM0A1)  | (1<<COM0B1) ;
	
	// mode switch interupt setup
	PCMSK0 |= (1<<PCINT4);
	PCICR |= (1<<PCIE0);
	sei();

	// Initial speed set
	OCR0A = 0;
	OCR0B = 0;
	
    lcd_init(LCD_ON_DISPLAY);
    lcd_backlight(1);
	initHCSR04();
	initDebugger();
	millis_init();
	LCD_read_data();
	
	lcd_clrscr();
	_delay_ms(20);
	lcd_gotoxy(3,0);
	_delay_ms(20);
	lcd_puts("REMOTE");
	_delay_ms(20);
	LCD_time_call();
	
			
    while (1){
		if(modeSwitch){
			modeSwitcher();
			modeSwitch = false;
		}		
		modeChecker();
		ledBlinker();
		LCD_time();	
	}

}

