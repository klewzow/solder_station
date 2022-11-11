#include "SPI_.h"

void init_SPI(void)
{
  		DDR_74CH  |=  ((1<<MOSI_74CH)|(1<<SS_74CH)|(1<<SCK_74CH));					 // Ножки SPI На выход
		DDR_74CH  &=~ (1<<MISO_74CH);												 // MOSI на вход
  		PORT_74CH &=~ ((1<<MOSI_74CH)&~(1<<SS_74CH)&~(1<<SCK_74CH)&~(1<<MISO_74CH)); // Низкий уровень
		
		DDR_MAX6675  |= (1<<SS_MAX6675);
		PORT_MAX6675 |= (1<<SS_MAX6675);
		  
		  
		SPCR |= ((1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPR1));						// Включим шину SPI устройство мастер делитель SPR0
		SPSR |= (1<<SPI2X);										            	// удвоение частоты делитель на 8	
		
}
	 unsigned char Spi_Send_Byte(unsigned char x)
	 {
		 SPDR = x;
		 while(!(SPSR & (1<<SPIF)))
		 ;
		 // USART_transmit(SPDR);
		 return SPDR;
	 }
 
	void SPI_MasterTransmit_74CH(char cpi_data) // передача байта
	{
		
		Spi_Send_Byte(cpi_data);			       
	    EN_CH_74CH;						  // чипселект или сигнал о выводе
		DIS_CH_74CH;					  // чипселект или сигнал о выводе
	}
	
 
  
 uint16_t   result_MAX6675 = 0;
 char b,c ;
char SPI_MasterResive_MAX6675(char cpi_data) // прием байта
		{
			result_MAX6675=0;
			 
			 // 0000 0000 0000 0000
			 // xx11 1111 1111 1xxx       
			     DIS_CH_MAX6675;
                 b  = Spi_Send_Byte(0);
			     c  = Spi_Send_Byte(0);
				  EN_CH_MAX6675;
			      USART_transmit(b);
				  USART_transmit(c);
			 
				 
	 
	   
	     return  result_MAX6675;			
			
	 
		}
	
	
	
	
	
	
	
