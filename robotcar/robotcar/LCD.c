/*
 * LCD.c
 *
 * Created: 29-11-2024 09:19:27
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 

#include "millis.h"
#include <time.h> 
#include <avr/eeprom.h>


int minutes = 0;
int hours = 0;
int timeChange= 0;

uint32_t nextmillis = 0;
uint32_t currentMillis = 0;

void LCD_time(){
	time_Handler();
	LCD_Showtime();
}

void time_Handler(){
	currentMillis = millis();
	if (currentMillis == nextmillis){
		minutes += 1;
		nextmillis += 60000;
		timeChange = 1;
		eeprom_write_byte(0X20, minutes);
	}
	if (minutes == 60){
		hours += 1;
		minutes = 0;
		nextmillis += 60000;
		timeChange = 1;
		eeprom_write_byte(0X21, hours);
	}
}


void LCD_Showtime(int hours, int minutes){
	if (timeChange == 1){
		lcd_gotoxy(3,1);
		_delay_ms(20);
		lcd_puts("%d:%d", hours,minutes);
		timeChange = 0;		
	}
};