/*
 * remoteControl.c
 *
 * Created: 29-11-2024 09:20:43
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "SoftSerial.h"
#include "Debugger.h"
int bluetoothspeed = 10; // initial speed, equal to lowest setting

void RemoteControlInit()
{
    DDRB &= ~(1<<DDD3);

    SoftSerialInit();
//     usart0_init();
    sei();
}
void RemoteControlLoop()
{
	    if(SoftSerialUnread() > 0)
	    {
		    char data = SoftSerialReceiveByte();

		    switch( data )
		    {

			    case '1': // stop
			    SoftSerialTransmitString("stopstopstopstopstop\n");
				motorForward(0,0);
			    break;

			    case 'w': // foreward
			    SoftSerialTransmitString("move foreward\n");
				motorForward(bluetoothspeed,bluetoothspeed);
			    break;

			    case 'a': // right
			    SoftSerialTransmitString("turn right\n");
				tankTurnRight(50);
			    break;
				
				case 'd': // left
				SoftSerialTransmitString("turn left\n");
				tankTurnLeft(50);
				break;
				
				case 's': // backwards
				SoftSerialTransmitString("move backward\n");
				motorBackward(bluetoothspeed,bluetoothspeed);
				break;
				
				case 'p': // speed 1
				SoftSerialTransmitString("speed 1 selected\n");
				bluetoothspeed = 10;
				break;
				
				case '2': // speed 2
				SoftSerialTransmitString("speed 2 selected\n");
				bluetoothspeed = 30;
				break;
				
				case '3': // speed 3
				SoftSerialTransmitString("speed 3 selected\n");
				bluetoothspeed = 50;
				break;

			    default: // prevent undefined
			    SoftSerialTransmitString("Unknown / no command\n");
			    break;
		    }
	}
}