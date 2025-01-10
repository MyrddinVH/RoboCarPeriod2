/*
* modeSwitch.c
*
* Created: 29-11-2024 10:15:01
*  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "slaveMode.h"
#include "ultrasoonMode.h"
#include "remoteControl.h"
#include "Debugger.h"

enum modeNames {REMOTE,SLAVE,AUTO};
volatile uint8_t mode = REMOTE;
int previousmode = 0;

void modeSwitcher(void){
	switch (mode){
		case REMOTE:
		mode = SLAVE;
		lcd_clrscr();
		lcd_gotoxy(5,0);
		usart0_transmitStr("remote");
		lcd_puts("REMOTE");
		break;
		case SLAVE:
		mode = AUTO;
		lcd_clrscr();
		lcd_gotoxy(5,0);
		usart0_transmitStr("slave");
		lcd_puts("SLAVE");
		break;
		case AUTO:
		mode = REMOTE;
		lcd_clrscr();
		lcd_gotoxy(5,0);
		usart0_transmitStr("auto");
		lcd_puts("AUTO");
		break;
	}
}

void modeChecker(void){
	if(mode == REMOTE){
		remoteControl();
	}else if(mode == SLAVE){
		slaveMode();
	}else if(mode == AUTO){
		runUltrasoon();
	}
}