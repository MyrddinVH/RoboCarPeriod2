#ifndef SOFTSERIAL_H_
#define SOFTSERIAL_H_

/* Prototypes */
void RemoteControlInit(void);
void RemoteControlLoop(void);
void SoftSerialInit(void);
char SoftSerialReceiveByte(void);
void SoftSerialTransmitByte(char data);
void SoftSerialReceiveString(char *str);
void SoftSerialTransmitString(char *str);
unsigned char SoftSerialUnread(void);

#endif /* SOFTSERIAL_H_ */