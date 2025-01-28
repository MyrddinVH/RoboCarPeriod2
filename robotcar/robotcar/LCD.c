/*
 * LCD.c
 *
 * Created: 29-11-2024 09:19:27
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 

#include "millis.h"
#include "ultrasoonMode.h"
#include <time.h> 
#include <avr/eeprom.h>
#include <util/delay.h>

int LCDminutes = 0;
int LCDhours = 0;
int timeChange= 1;

uint32_t nextmillis = 60000;
uint32_t currentTime = 0;

void LCD_time(){
	time_Handler();
	LCD_Showtime_standard(LCDhours, LCDminutes);
}

void LCD_time_call(){
	LCD_Showtime_call(LCDhours, LCDminutes);
}

void time_Handler(){
	currentTime = ms;
	if (currentTime > nextmillis){
		LCDminutes += 1;
		nextmillis += 60000;
		timeChange = 1;
		//eeprom_write_byte(minutes, 0X20);
	}
	if (LCDminutes == 60){
		LCDhours += 1;
		LCDminutes = 0;
		nextmillis += 60000;
		timeChange = 1;
		//eeprom_write_byte(hours, 0X21);
	}
}


void LCD_Showtime_standard(int hours, int minutes){
	if (timeChange == 1){
		_delay_ms(20);
		lcd_gotoxy(4,1);
		_delay_ms(20);
		variableLCD(hours);
		_delay_ms(20);
		lcd_gotoxy(6,1);
		_delay_ms(20);
		lcd_puts(":");
		_delay_ms(20);
		lcd_gotoxy(8,1);
		_delay_ms(20);
		variableLCD(minutes);
		timeChange = 0;		
	}
};
void LCD_Showtime_call(int hours, int minutes){
		_delay_ms(20);
		lcd_gotoxy(4,1);
		_delay_ms(20);
		variableLCD(hours);
		_delay_ms(20);
		lcd_gotoxy(6,1);
		_delay_ms(20);
		lcd_puts(":");
		_delay_ms(20);
		lcd_gotoxy(8,1);
		_delay_ms(20);
		variableLCD(minutes);
		timeChange = 0;		
};