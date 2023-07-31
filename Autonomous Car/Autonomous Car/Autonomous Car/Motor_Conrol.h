#ifndef LAMP_DIMMER_H_
#define LAMP_DIMMER_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "StandredMacros.h"
#include "STD.h"

void Car_Stop();      //Stop the Car
void Rotate_Right();  //Rotate Car Right
void Rotate_left();   //Rotate Car Left
void Normal_Speed();  //Move Car with Normal Speed
void init_Motor();    //Initialize Motor

#endif