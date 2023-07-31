#include "Motor_Conrol.h"
 
void init_Motor()  //initialize OCS (0) For Motors
{
    /*setbit(TCCR2,WGM20);  //fast PWM mode
    setbit(TCCR2,WGM20);  //fast PWM mode
    setbit(TCCR2,COM21);  //Clear OC0 on compare match, set OC0 at BOTTOM,
    setbit(TCCR2,CS20);   //clk / 1 (From prescaler)
	OCR2=(127);*/
    
	setbit(DDRB,2);
    setbit(DDRB,4);
	clearbit(PORTB,2);   //initially Car is Stopped
	clearbit(PORTB,4);   //initially Car is Stopped
}

void Rotate_Right()    //Rotate Car Right
{
    //OCR2=(1);
	setbit(PORTB,2);
	clearbit(PORTB,4);
	_delay_ms(2000);   //wait till car Rotate
	Normal_Speed();
}

void Rotate_left()     //Rotate Car Left
{
	//OCR2=(254);
	setbit(PORTB,4);
	clearbit(PORTB,2);
    _delay_ms(2000);    //Wait till car rotate
    Normal_Speed();
}
 
void Normal_Speed()    //Move Car with Normal Speed;
{
    //OCR2=(127);		
    setbit(PORTB,2);
    setbit(PORTB,4);
} 


void Car_Stop()         //Stop the Car
{
	//OCR2=(127);
	clearbit(PORTB,2);
	clearbit(PORTB,4);
}