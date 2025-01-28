/*
 * motorControl.h
 *
 * Created: 28-11-2024 13:14:55
 *  Author: timde
 */ 


#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

void motorForward(int speed1, int speed2);
void motorBackward(int speed1, int speed2);
void tankTurnLeft(int speed);
void tankTurnRight(int speed);
void tankDirection(void);
void arrowRemove(void);
void showspeed();

#endif /* MOTORCONTROL_H_ */