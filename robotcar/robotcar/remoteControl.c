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

void remoteControl()
{
    DDRB = (1<<DDB5);

    SoftSerialInit();
    usart0_init();
    sei();

    SoftSerialTransmitString("\r\nSoftSerial demo\r\n");

    while (1)
    {
	    if(SoftSerialUnread() > 0)
	    {
		    char data = SoftSerialReceiveByte();

		    switch( data )
		    {

			    case '1': // stop
			    usart0_transmitStr("stopstopstopstopstop\n");
			    break;

			    case 'w': // foreward
			    SoftSerialTransmitString("move foreward\n");
			    break;

			    case 'a': // right
			    SoftSerialTransmitString("turn right\n");
			    break;
				
				case 'd': // left
				SoftSerialTransmitString("turn left");
				break;
				
				case 's' // backwards
				SoftSerialTransmitString("move backward");
				break;
				
				case 'p' // speed 1
				SoftSerialTransmitString("speed 1 selected");
				break;
				
				case '2' // speed 2
				SoftSerialTransmitString("speed 2 selected");
				break;
				
				case '3' // speed 3
				SoftSerialTransmitString("speed 3 selected");
				break;

			    default: // prevent undefined
			    SoftSerialTransmitString("Unknown command\r\n");
			    break;
		    }

	    }
    }
}