 #include "LCD_.h"
 void INIT_LCD_PORT(void)
 {
	 P_ORT_DDR   = 0b11110011; //LCD
	 P_ORT       = 0b00000000; //LCD
	 
 }
 
 #define  E1   P_ORT |=  (1<<1);
 #define  E0   P_ORT &=~ (1<<1);
 
 #define  RS1  P_ORT |=  (1<<0);
 #define  RS0  P_ORT &=~ (1<<0);
 
 // RS = 0 когда идет комманда 
 // RS = 1 когда идет Данные  
 

 void higthByte(unsigned char a)
 {
	 
	 a<<=4;
	  E1;
	 _delay_us(50);
	 P_ORT &=~ 0b11110000 ;
	 P_ORT |=a;
	
	 _delay_us(50);
	 E0;
	_delay_us(50);
 }
 void sendhalfbyte(unsigned char b_yte)
 {
	 
	 b_yte <<=4;
	  E1;
    _delay_us(50);
	
	 P_ORT &=~ 0b11110000;
	 P_ORT |=b_yte;
	 _delay_us(50);
	  E0;
	_delay_us(50);
 }
 void sendbyte(unsigned char x,unsigned char mode )
 {
	 if(mode == 0){RS0;}
	 else { RS1;}
	 unsigned char hc=0;
	 hc = x>>4;
	 higthByte(hc);
	 higthByte(x);
 }
				 void LCD_Init()
				 {
					 INIT_LCD_PORT();
					 
					 _delay_ms(16);
					 higthByte(0b00000011);
					 _delay_ms(5);
					 higthByte(0b00000011);
					 _delay_us(120);
					 higthByte(0b00000011);
					 _delay_ms(1);
					 higthByte(0b0000010);
					 _delay_ms(1);
					 sendbyte(0b00101000, 0);
					 _delay_ms(1);
					 sendbyte(0b00001000, 0);
					 _delay_ms(1);
					 sendbyte(0b00000001, 0);
					 _delay_ms(1);
					 sendbyte(0b00000011, 0);
					 _delay_ms(1);
					 sendbyte(0b00001100, 0);
				 }
 void lcd_clear(void)
 {
	 sendbyte(0b00000001,0);
 }
 void setPos(unsigned char x, unsigned char y)
 {
	 char adress=0;
	 adress = (0x40*y+x)|0b10000000;
	 sendbyte(adress,0);
 }
 void sendchar(unsigned char x)
 {
	 sendbyte(x,1);
 }
 
 void str_lcd(char str_1[])
 {
	 
 
	 for (char n=0; (char)str_1[n]!='\0'; n++)
	 {
		 sendchar((char)str_1[n] );
	 }
	 
 }
 void itoa_str_lcd(unsigned int a)
 {
	 char c[16];
 
	 sprintf(c, "%d\n",a);
	 str_lcd(c);
 };
 
 
 

