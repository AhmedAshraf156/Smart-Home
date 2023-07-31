#ifndef LCD_DERIVER_H_
#define LCD_DERIVER_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "StandredMacros.h"
#include "STD.h"

//four bits config
#define data_bits_modes 4
//use higher 4 bits in port
#if (data_bits_modes == 4)
#define upper_ports_pins
#endif

//LCD Pins
#define EN 3
#define RW 2
#define RS 1
#define LCD_CTRL_PORT PORTC
#define LCD_CTRL_PORT_DIR DDRC
#define LCD_DATA_PORT PORTA
#define LCD_DATA_PORT_DIR DDRA

//LCD Commands
#define clear_command 0x01
#define four_bits_mode 0x02
#define two_lines_lcd_4bit 0x28
#define two_lines_lcd_8bit 0x38
#define cruser_off 0x0C
#define cruser_on 0x0E
#define set_cruser_location 0x80

//Prototypes
void lcd_sendcommand(uint8 command);
void lcd_display_char(uint8 data);
void lcd_display_string(const char *Str);
void lcd_init(void);
void lcd_clean_screan(void);
void lcd_display_string_a_rowcolumn(uint8 row,uint8 col,const char *Str);
void lcd_go_to_rowcolumn(uint8 row,uint8 col);
void lcd_into_string(int data);

#endif /* LCD_DERIVER_H_ */