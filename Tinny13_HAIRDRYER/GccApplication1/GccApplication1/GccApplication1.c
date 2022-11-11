#include "main.h"


 char flag_culler = 0;
 int ADC_value=0;
							ISR(ADC_vect)
							{
								ADC_value = (ADC/4);
								OCR0A = ADC_value;
								ADCSRA |= (1<<ADSC);
							}
int main(void)
{
	

    DDRB  &=~  (1<<ENABLE_CULLER); // настройка порта для входа сигнала куллера
    PORTB &=~  (1<<ENABLE_CULLER); // настройка порта для входа сигнала куллера
	
	DDRB  |= (1<<IRFZ44N);         // настройка порта ШИМ  куллера
	PORTB &=~(1<<IRFZ44N);         // настройка порта ШИМ  куллера
	
	
	
	//PB2 IN ADC 
	DDRB  &=~ (1<<2);// ADC
    PORTB &=~ (1<<2);// ADC
	
	
	
	ADCSRA |= ((1<<ADEN)|(1<<ADIE)|(1<<ADPS2));
	ADMUX  &=~ (1<<REFS0);
	ADMUX  |=  (1<<0);
	ADCSRA |= (1<<ADSC);
	 
 
	

	asm("sei");
	
    while(1)
    {
		
		
	if (((PINB&(1<<ENABLE_CULLER))==0) && (flag_culler == 0))
    {
		 
		flag_culler = 1;
		 TCCR0B |= (1 << CS01);
		 TCCR0A |= (1 << WGM01) | (1 << WGM00);
		 TCCR0A |= (1 << COM0A1);;
	}
	 if ((!(PINB&(1<<ENABLE_CULLER))==0) && (flag_culler == 1))
	 {
		 
	     
		  TCCR0B &=~ (1 << CS01  );
		  TCCR0A &=~ (1 << WGM01 );
		  TCCR0A &=~ (1 << WGM00 );
		  TCCR0A &=~ (1 << COM0A1);
		  flag_culler = 0;
		  PORTB &=~(1<<IRFZ44N); 
	 }
       
    
	
	
	}
}