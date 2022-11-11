 

#ifndef SPI__H_
#define SPI__H_
 #include "main.h"
#define DDR_74CH            DDRB
#define PORT_74CH           PORTB
#define MOSI_74CH           5
#define MISO_74CH           6
#define SCK_74CH            7
#define SS_74CH			    3


#define DDR_MAX6675            DDRB
#define PORT_MAX6675          PORTB
#define SS_MAX6675		    2
#define EN_CH_MAX6675  (PORT_MAX6675 |= (1<<SS_MAX6675))
#define DIS_CH_MAX6675 (PORT_MAX6675 &=~ (1<<SS_MAX6675))




#define EN_CH_74CH  (PORT_74CH |=  (1<<SS_74CH))
#define DIS_CH_74CH (PORT_74CH &=~ (1<<SS_74CH))

void init_SPI(void);
void SPI_MasterTransmit_74CH(char cpi_data);
char SPI_MasterResive_MAX6675(char cpi_data);



#endif  