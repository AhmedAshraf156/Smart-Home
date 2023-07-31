#include "ultrasonic.h"

uint8_t sensor_working=0;
uint8_t rising_edge=0;
uint32_t timer_counter=0;
uint32_t distance;
//uint8_t distance_str[10];

void timer0_init(void)  //initialize Timer 0
{
	TCCR0 =  0x00;      //Disable Timer 0
	setbit(TCCR0,0);    //Setting pre scaler /1
	TCNT0 = 0x00;       // Initializing the timer with zero 
	setbit(TIMSK,0);    // Timer overflow interrupt enable
}

void ultrasonic_init(void)  //initialize UltraSonic
{
    setbit(DDRD,0);       // output trigger
    clearbit(DDRD,3);     // input of echo
    setbit(PORTD,3);
    enable_ex_interrupt();//Interrupt enable
    timer0_init();        //initialize Timer 0
}

void enable_ex_interrupt(void)   //Interrupt enable
{
  MCUCR |= (1<<ISC10);   		// Trigger INT1 on any logic change.
  GICR  |= (1<<INT1);			// Enable INT1 interrupts.
}

void ultra_triger(void){     //trigger Sensor
  if(!sensor_working){
    setbit(PORTD,0);    //trigger for 15 micro sec
	_delay_us(15);
    clearbit(PORTD,0);
    sensor_working=1;   // can't trigger till current operation end
  }
}

ISR(INT1_vect){
  if(sensor_working==1){
    if(rising_edge==0){
      TCNT0=0x00;
      rising_edge=1;
      timer_counter=0;
    }
  else{
    distance=(timer_counter*256+TCNT0)/466;
    /*lcd_go_to_rowcolumn(1,0);
  	itoa(distance,distance_str,10);
  	strcat(distance_str, " cm ");
  	lcd_display_string(distance_str);*/
	  _delay_ms(40);
    timer_counter=0;
    rising_edge=0;
  }
}}

ISR(TIMER0_OVF_vect){
    timer_counter++;
    if(timer_counter >730){
      TCNT0=0x00;
      sensor_working=0;
      rising_edge=0;
      timer_counter=0;
    }
}
