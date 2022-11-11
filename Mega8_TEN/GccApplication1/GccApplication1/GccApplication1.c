#include "main.h"


#define PORT__ZERRO_CROSS          PORTD
#define DDR__ZERRO_CROSS           DDRD
#define INPUT_PIN_ZERRO_CROSS      2

#define PORT_SEMISTOR              PORTD
#define DDR_SEMISTOR               DDRD
#define PIN_SEMISTOR               3  

 char b1_PORTC  =0;
 char b2_PORTD  =0;
 char t ;
char collect_a_bit(void)
{
	
	
	
 
   b1_PORTC = (PINC);
   b1_PORTC &=~ (1<<6); 
   b1_PORTC &=~ (1<<7); 
  // b2_PORTD  = (PIND>>6);
   b2_PORTD  = (PIND<<6);
 
  	b1_PORTC |= b2_PORTD;
	return b1_PORTC;
}

unsigned char semi_slou = 0;			   // 245 max min 116 устанавливает задержку семистра
unsigned char CONTROLL_CLOSE = 1;          // первое или второе страбатывание таймера семистра

ISR(INT0_vect)
{
 semi_slou = collect_a_bit(); 
 PORTB = semi_slou;
 if (semi_slou == 0)
 {
	 asm("nop");
 }
 else
 {
	 TCNT2 = semi_slou;	              // При открытии семистра выставить значение в счетчик
     TCCR2  |= (1<<1)|(1<<2);         // Запустить Таймер2
     GICR   &=~  (1<<INT0);           // Запретитть прерывание INT0
 } 	 
}

ISR(TIMER2_COMP_vect)
 {
	 
	switch(CONTROLL_CLOSE)
	{
		case  1: 
		           PORT_SEMISTOR  |= (1<<PIN_SEMISTOR);           // Открыть семистор
		           CONTROLL_CLOSE ++;
		           TCNT2  = 0xff;       
		break;
		
		case  2 :
		           TCCR2 &=~ (1<<2);								 // Остановить Таймер2
				   TCCR2 &=~ (1<<1);
				   GICR   |=  (1<<INT0);						 	 // Разрешить прерывание INT0
                   PORT_SEMISTOR  &=~ (1<<PIN_SEMISTOR);             // Закрыть семистор
                   CONTROLL_CLOSE --;
				   
				 
		break;
	 }
 }	 






int main(void)
{
		DDR__ZERRO_CROSS    &=~  (1<<INPUT_PIN_ZERRO_CROSS);     // Вход детектора нуля
		PORT__ZERRO_CROSS   &=~   (1<<INPUT_PIN_ZERRO_CROSS);    // Вход детектора нуля
		
		DDR_SEMISTOR       |=   (1<<PIN_SEMISTOR);				// Выход задержки семистра
		PORT_SEMISTOR      &=~  (1<<PIN_SEMISTOR);				// Выход задержки семистра
		DDRC  |= 0x00;
		PORTC |= 0x00;
		
		MCUCR  &=~ (1<<ISC00);    // Настройка прерываний INT
		MCUCR  |=  (1<<ISC01);    // Настройка прерываний INT
		GICR   |=  (1<<INT0);     // Настройка прерываний INT
		
		DDRB = 0xFF;              // test
		TCCR2 |= (1<<WGM21) ;
		TIMSK |= (1<<OCIE2);
	
 
 
   asm("sei");
   while(1)
    {
        asm("nop");
    }
}