// /*
//  * millis.c
//  *
//  * Created: 20/12/2024 09:46:07
//  *  Author: Myrdd
//  */ 
// 
// #define F_CPU (16000000UL)
// #include <avr/io.h>
// #include <avr/interrupt.h>
// volatile uint32_t ms = 0;
// 
// void millis_init(void)
// {
// 	ms = 0;
// 	// Configure Timer/counter 1 to generate an interrupt every millisecond
// 	//
// 	// - WGM1[3:0] = 0100 : waveform generation mode is CTC with TOP in OCR1A
// 	// - CS1[2:0] = 011 : 64 prescaler
// 	// - TOP : 24999
// 	//
// 	// T_events = T_CPU * N * (TOP + 1)
// 	// = 1/16 MHz * 64 * (24999 + 1)
// 	// = 1 ms
// 
// 	TCCR1B |= (1<<WGM12);        // Set CTC mode
// 	TCCR1B |= (1<<CS11) | (1<<CS10); // Set prescaler to 64
// 	OCR1A = 249;               // Set TOP value to 24999 for 16-bit resolution
// 
// 	// Timer/Counter1 Output Compare Match A Interrupt Enable
// 	TIMSK1 |= (1<<OCIE1A);
// }
// 
// // Interrupt Service Routine that is automatically executed as soon as
// // timer/counter 1 has reached its compare value
// ISR(TIMER1_COMPA_vect)
// {
// 	ms++;
// }
// 
// inline uint32_t millis(void)
// {
// 	// ms is a 32-bit variable (uint32_t). This means that multiple accesses
// 	// are needed to read or write the value of ms. There is a chance that
// 	// in the middle of these multiple accesses, the ms value is written due to
// 	// the ISR being triggered. In order to make sure the value of ms is not
// 	// updated when reading it, disable interrupts while reading the value.
// 	cli();
// 	uint32_t ret = ms;
// 	sei();
// 	return ret;
// }
// int millis_main(void)
// {
// 	// Initialize the millisecond counter
// 	millis_init();
// 	// Global interrupt enable
// 	sei();
// 	uint32_t previousmillis = 0;
// 	uint32_t currentmillis = 0;
// 	uint32_t interval = 1000;
// 	while(1)
// 	{
// 		// Get the current millis
// 		currentmillis = millis();
// 		// Has 'interval' time passed since the last time we checked?
// 		if((currentmillis - previousmillis) >= interval)
// 		{
// 			// Yes, 'interval' time has passed
// 			// Save the current millis
// 			previousmillis = currentmillis;
// 			// Toggle the LED
// 			PORTB ^= (1<<PORTB5);
// 		}
// 	}
// }