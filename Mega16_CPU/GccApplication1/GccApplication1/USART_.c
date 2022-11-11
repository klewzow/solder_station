#include "USART_.h"
void USART_ini(unsigned int speed)
{
	UBRRH = (unsigned char) (speed>>8);
	UBRRL = (unsigned char) (speed);
	
	
	UCSRB |= (1<<RXEN)|(1<<TXEN);						 // �������� ����� � �������� USART
	//UCSRB |= (1<<RXCIE);								 // ��������� ���������� ��� ������ (�� ���������)
	UCSRA |= (1<<U2X);									 // �������� �������� ���
	UCSRC |= (1<<URSEL)|(1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0); // ���������� ������ � �������� UCSRC = 1,
	// ����������� ����� UNSEL = 0
	// �� ���������� �������� �������� UPM1=0, UPM0=0
	// 2 ����  ���� USBS = 1
	// 8-�� ������  ������� UCSZ1=1, UCSZ0=1
	
}
void USART_transmit(unsigned char data) // �������� �����
{
	while (!(UCSRA&(1<<UDRE)));
	UDR =  data;
	
}
void UART_Send_Str(char str[])
{
	unsigned char i = 0;

	while (str[i]!='\0')
	{
		USART_transmit(str[i]);
		i++;
	}
}