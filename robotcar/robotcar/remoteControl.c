/*
 * remoteControl.c
 *
 * Created: 29-11-2024 09:20:43
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftSerial.h>
#include <Debugger.h>

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

			    case '1':
			    //PINB = (1<<PINB5);
			    //PINB |= (1<<PINB0);
			    usart0_transmitStr("it workss\n");
			    break;

			    case 'h':
			    SoftSerialTransmitString("hello world!\r\n");
			    break;

			    case 'H':
			    SoftSerialTransmitString("HELLO WORLD!\r\n");
			    break;

			    default:
			    SoftSerialTransmitString("Unknown command\r\n");
			    break;
		    }

	    }
    }
}