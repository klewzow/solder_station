#include "main.h"

#ifndef LCD_H_
#define LCD_H_


//---------------------DEFINE LCD--------------------------------------------
#define  P_ORT_DDR DDRC
#define  P_ORT     PORTC  // #7 #6 #5 #4 /--4bit #0-RS   #1-RW(или GND)  #2-E

//---------------------DEFINE LCD--------------------------------------------

 
 
  void int_string_lcd(int a);
void LCD_Init();
void lcd_clear(void);
void setPos(unsigned char x, unsigned char y);
void sendchar(unsigned char x);
void str_lcd(char str_1[]);


#endif /* LCD_H_ */