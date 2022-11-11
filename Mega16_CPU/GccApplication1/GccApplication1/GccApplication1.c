#include "main.h"

 int t;
ISR(TIMER0_OVF_vect)
{
		 
		
	 
	 
SPI_MasterResive_MAX6675('0');
  UART_Send_Str("OK_!");
// 		 sendchar('7');
//SPI_MasterTransmit_74CH(SPI_MasterResive_MAX6675(0));
		
}

int main(void)
{
   USART_ini(103);
   UART_Send_Str("OK_!");
TCCR0 |= ((1<<CS02)|(1<<CS00));
TIMSK |= (1<<TOIE0);

	 DDRC  |=0b11110011; //LCD
	 PORTC |=0b00000000; //LCD
     DDRD |=(1<<1);

 LCD_Init();
 
str_lcd("LCD - ");
 
 
  init_SPI(); 
 
 
  
	asm("sei");
    while(1)
    {
 asm("nop");
 UART_Send_Str("Z");
    }
}