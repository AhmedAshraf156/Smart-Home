#ifndef TIMER_H_
#define TIMER_H_

#include "StandredMacros.h"
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL

//Function Prototypes

void init_servo(void);           //initialize timer value
void position_zero(void);        //Function to lock the door
void position_pos(void);         //Function to unlock the door
void position_neg(void);         //Function to unlock the door


#endif 