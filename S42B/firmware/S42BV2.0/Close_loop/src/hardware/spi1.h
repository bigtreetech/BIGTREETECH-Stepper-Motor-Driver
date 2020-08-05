#ifndef __SPI1_H
#define __SPI1_H
#include "mydef.h"


//  
#define SPI_SPEED_2   0
#define SPI_SPEED_8   1
#define SPI_SPEED_16  2
#define SPI_SPEED_256 3

void SPI1_Init(void);
void SPI1_SetSpeed(u8 SpeedSet);
u8 SPI1_ReadWriteByte(u8 TxData);




#endif


