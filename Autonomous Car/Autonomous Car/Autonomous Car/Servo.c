#include "Servo.h"

void init_servo(void)       //initialize timer value
{
	setbit(TCCR1A,COM1A1);  //  Clear OC1A/OC1B on compare match, set OC1A at BOTTOM (non-inverting mode)
	setbit(TCCR1A,WGM11);   //  Set fast PWM with the TOP in ICR1
	setbit(TCCR1B,WGM12);   //  Set fast PWM with the TOP in ICR1
    setbit(TCCR1B,WGM13);   //  Set fast PWM with the TOP in ICR1
	setbit(TCCR1B,CS11);    //  Pre scaler / 8
    ICR1=20000;             //20msec timer Periodic Time
	position_zero();        //initial position is zero
}

void position_zero(void)      //Function to lock the door
{
	OCR1A = 1500;             //1.5msec   0 degree
	_delay_ms(5000);          //Wait till servo rotate
}

void position_pos(void)        //Function to unlock the door
{ 
	OCR1A = 2000;              //2msec  +90 degree
	_delay_ms(5000);           //Wait till servo rotate
}

void position_neg(void)      //Function to lock the door
{
	OCR1A = 1000;            //1msec  -90 degree
	_delay_ms(5000);         //Wait till servo rotate
}
