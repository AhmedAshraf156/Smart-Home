#ifndef APP_H_
#define APP_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL

#include "LCD_Deriver.h"
#include "Servo.h"
#include "Motor_Conrol.h"
#include "ultrasonic.h"

//Function Prototypes

void Reg_int();   //Initialize Registers
void App();       //Application Function

#endif