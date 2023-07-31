#include "App.h"

int main(){

	sei();          //Global interrupts enable
    Reg_int();      //Initialize registers
    _delay_ms(10);  //wait
	
	App();          //Application Start

	return 0;
}
