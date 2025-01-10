#ifndef DEBUGGER_H_
#define DEBUGGER_H_

void usart0_init(void);
char usart0_receive(void);
void usart0_transmit(char data);
unsigned char usart0_nUnread(void);
void usart0_transmitStr(char *str);
void debugBufferChecker();
void initDebugger();

#endif