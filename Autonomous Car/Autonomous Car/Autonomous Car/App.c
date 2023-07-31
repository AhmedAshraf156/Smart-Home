#include "App.h"

extern distance;      //Variable take output of Sensor

void Reg_int()        //Initialize Registers
{
	init_servo();     //Initialization of servo motor
	lcd_init();       //Initialization of LCD
	init_Motor();     //Initialization of Motors
	ultrasonic_init();//Initialization of UltraSonic Sensor
	setbit(DDRD,5);   //out of servo
	setbit(DDRD,7);   //out of Osc 1
    ultra_triger();   //Trigger Sensor
	_delay_ms(200);   //Wait till It Get the First Distance Value

}

void App()            //Application Function
{
	while (1)
	{
		ultra_triger();           //take a reading
	    _delay_ms(30);
		
		if (distance<100)
		{
			position_pos();       //rotate sensor right
			ultra_triger();       //take a reading
			_delay_ms(300);
			if (distance<100)     //if obstacle
			{
				position_neg();   //rotate sensor left
				ultra_triger();   //take a reading
				_delay_ms(300);
			    if (distance<100)  //if obstacle
			    {
					lcd_clean_screan();
					lcd_display_string("Car Stuck !");
					lcd_go_to_rowcolumn(1,0);
					lcd_display_string("Press Reset But");
					Car_Stop();    //stop the car
					return 0;
			    }
				else               //if no obstacle
				{
					lcd_clean_screan();
					lcd_display_string("Rotating left");
					Rotate_left(); //rotate the car left
					lcd_clean_screan();
					lcd_display_string("Go Forward");
					position_zero();
				}
			}
			else
			{
				lcd_clean_screan();  
				lcd_display_string("Rotating Right");
				Rotate_Right();   //rotate the car right
				lcd_clean_screan();
				lcd_display_string("Go Forward");
				position_zero();
			}
		}
        else    //continue moving
		{
			Normal_Speed(); 
		}
	}
}