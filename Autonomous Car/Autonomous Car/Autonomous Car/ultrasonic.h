#ifndef _ULTRA_H_
#define _ULTRA_H_

#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "StandredMacros.h"
#include "STD.h"


//Function Prototypes

void ultrasonic_init(void);     //initialize UltraSonic
void enable_ex_interrupt(void); //Interrupt enable
void ultra_triger(void);        //trigger Sensor
void timer0_init(void);         //initialize Timer 0

#endif
