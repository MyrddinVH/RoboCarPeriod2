/*
 * ultrasoonMode.h
 *
 * Created: 29-11-2024 09:21:42
 *  Author: Huub Bouwman, Myrddin van Hallem, Tim de Kuijper and Paul Nguyen
 */ 


#ifndef ULTRASOONMODE_H_
#define ULTRASOONMODE_H_

// #include "millis.h"
void initHCSR04();
void sendPulse();
uint32_t millis(void);
void millis_init(void);
void checkForObject();
void runUltrasoon();
void pulseTimer(void);
extern _Bool objectDetected;

#endif /* ULTRASOONMODE_H_ */