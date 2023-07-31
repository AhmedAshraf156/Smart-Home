#include "LCD_Deriver.h"


void lcd_init(void){
	setbit(DDRC,RS);
	setbit(DDRC,RW);
	setbit(DDRC,EN);
#if (data_bits_modes == 4)
 #ifdef upper_ports_pins
      DDRA |= 0xF0;                           //work on 4bit in micro controller
 #else
      DDRA |=0x0F;
 #endif
    lcd_sendcommand(four_bits_mode);     //work on 4bit in micro controller
	lcd_sendcommand(two_lines_lcd_4bit); //use two lines + 4 bits data

#elif (data_bits_modes==8)		
DDRA |=0xFF;                              //work on 8bits in micro controller
lcd_sendcommand(two_lines_lcd_8bit);	  //use two lines + 8 bits data
#endif
//optional
   lcd_sendcommand(clear_command);        //clear screen
   lcd_sendcommand(cruser_off);  //set cruser of
}

void lcd_sendcommand(uint8 command){
	clearbit(PORTC,RS);    //send command to LCD RS=0
	clearbit(PORTC,RW);
    setbit(PORTC,EN);	   //EN=1
    _delay_ms(1);
   
    #if (data_bits_modes==4)  //out is the 4 most significant bits only
     #ifdef upper_ports_pins // out the highest 4 bits of the required command to the data bus D4 --> D7 
	 PORTA = (command & 0xF0);
	 #else                         //needed recap
	 PORTA = ((command>>4)&0x0F);
     #endif
	_delay_ms(1);
	clearbit(PORTC,EN); //EN=0
	_delay_ms(1);
	setbit(PORTC,EN);
	_delay_ms(1);
	                      
	#ifdef upper_ports_pins // out the lowest 4 bits of the required command to the data bus D4 --> D7 
	PORTA = (command << 4) & 0xF0;
	#else
	PORTA = (command & 0x0F);
	#endif
	_delay_ms(1);                /* delay for processing Tdsw = 100ns */
	clearbit(PORTC,EN);          /* disable LCD E=0 */
	_delay_ms(1);                /* delay for processing Th = 13ns */
	#elif (data_bits_modes == 8)
	PORTA = command;              /* out the required data to the data bus D0 --> D7 */
	_delay_ms(1);                /* delay for processing Tdsw = 100ns */
	clearbit(PORTC,EN);           /* disable LCD E=0 */
	_delay_ms(1);                /* delay for processing Th = 13ns */
	#endif
}

void lcd_display_char(uint8 data){
	setbit(PORTC,RS);         //Write data to LCD RS=1
	clearbit(PORTC,RW);
	setbit(PORTC,EN);	      //EN=1
	_delay_ms(1);
	
	#if (data_bits_modes==4)  //out is the 4 most significant bits only
	#ifdef upper_ports_pins   // out the highest 4 bits of the required command to the data bus D4 --> D7
	PORTA = (data & 0xF0);
	#else
	PORTA = ((data>>4)&0x0F); //can be |0x00?
	#endif
	_delay_ms(1);
	clearbit(PORTC,EN);       //EN=0
	_delay_ms(1);
	setbit(PORTC,EN);
	_delay_ms(1);
	
	#ifdef upper_ports_pins       // out the lowest 4 bits of the required command to the data bus D4 --> D7
	PORTA = (data << 4) & 0xF0;
	#else
	PORTA = (data & 0x0F);
	#endif
	_delay_ms(1);                /* delay for processing Tdsw = 100ns */
	clearbit(PORTC,EN);          /* disable LCD E=0 */
	_delay_ms(1);               /* delay for processing Th = 13ns */
	#elif (data_bits_modes == 8)
	PORTA = data;                 /* out the required data to the data bus D0 --> D7 */
	_delay_ms(1);                /* delay for processing Tdsw = 100ns */
	clearbit(PORTC,EN);           /* disable LCD E=0 */
	_delay_ms(1);                /* delay for processing Th = 13ns */
	#endif
}

void lcd_display_string(const Int8 *Str){
	uint8 i=0;
	while(Str[i] !='\0')         //not equal null
	{
		lcd_display_char(Str[i]);
		i++;
	}
}

void lcd_into_string(int32 data){
	Int8 buff[16];            //string to hold ascii result
	itoa(data,buff,10);       //10 for decimal
	lcd_display_string(buff); // display output
}

void lcd_clean_screan(){
	
	lcd_sendcommand(clear_command);  //clear display
	
}

void lcd_go_to_rowcolumn(uint8 row,uint8 col){
   uint8 address;
  //Get which addres you want depend on row
switch(row){
	case 0: 
	address=col;
	break;
	case 1:
	address=col+0x40;
	break;
}
/* to write to a specific address in the LCD 
we need to apply the corresponding command 0b10000000+Address */
lcd_sendcommand(address + set_cruser_location);	
}

void lcd_display_string_a_rowcolumn(uint8 row,uint8 col,const Int8 *Str){
	lcd_go_to_rowcolumn(row,col); //go to required location
	lcd_display_string(Str);      //lcd display string
}
