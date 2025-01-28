#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <avr/io.h>
#include <avr/interrupt.h>
// Macros
//#define F_CPU 16000000UL
#include <util/delay.h>

#define USART_RX_BUFFER_SIZE (64)
#define USART_TX_BUFFER_SIZE (64)

// Buffer size checks
#define USART_RX_BUFFER_MASK (USART_RX_BUFFER_SIZE - 1)
#if (USART_RX_BUFFER_SIZE & USART_RX_BUFFER_MASK)
#error RX buffer size is not a power of 2
#endif

#define USART_TX_BUFFER_MASK (USART_TX_BUFFER_SIZE - 1)
#if (USART_TX_BUFFER_SIZE & USART_TX_BUFFER_MASK)
#error TX buffer size is not a power of 2
#endif

// Global variables (extern to be defined in the source file)
extern char USART_RxBuf[USART_RX_BUFFER_SIZE];
extern volatile unsigned char USART_RxHead;
extern volatile unsigned char USART_RxTail;
extern char USART_TxBuf[USART_TX_BUFFER_SIZE];
extern volatile unsigned char USART_TxHead;
extern volatile unsigned char USART_TxTail;

// Function prototypes
void usart0_init(void);
char usart0_receive(void);
void usart0_transmit(char data);
unsigned char usart0_nUnread(void);
void usart0_transmitStr(char *str);

#endif // BLUETOOTH_H
