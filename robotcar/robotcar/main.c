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
#include "LCD.h"
#include "motorControl.h"
#include "remoteControl.h"
#include "slaveMode.h"
#include "ultrasoonMode.h"
#include "timeSaving.h"
#include "modeSwitch.h"

int main(void){

    DDRD |= (1<<DDD5) | (1<<DDD7);

    DDRD |= (1<<DDD5) | (1<<DDD7) | (1<<DDD6);

	DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
	
	// PWM setup
	TCCR0A |= (1<<WGM00);
	TCCR0B |= (1<<CS02) | (1<<CS00);
	// Set Compare Output Mode for both channels A and B

	TCCR0A |= (1<<COM0A1)  | (1<<COM0B1) ;

	// Initial speed set
	OCR0A = 0;
	OCR0B = 0;
	
    lcd_init(LCD_ON_DISPLAY);
    lcd_backlight(0);
    _delay_ms(500);
    lcd_backlight(1);
    _delay_ms(500);		

    while (1){
		int test = 200;
        lcd_clrscr();
        lcd_gotoxy(0, 0);
		variableLCD(test);
        lcd_gotoxy(1, 1);
        lcd_puts("test");
        _delay_ms(1000);		
    }
}



