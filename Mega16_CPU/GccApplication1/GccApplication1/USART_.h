 
#ifndef USART__H_
#define USART__H_
#include "main.h"
void USART_ini(unsigned int speed);
void USART_transmit(unsigned char data);
void UART_Send_Str(char str[]);



#endif /* USART__H_ */