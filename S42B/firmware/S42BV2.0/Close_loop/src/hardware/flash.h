#ifndef __FLASH_H
#define __FLASH_H

#include "mydef.h"


#define STM32_FLASH_BASE        0x08000000           //Flash base addr
#define Data_Store_Arrdess      0x08017C00           //
//#define Data_Store_Arrdess      0x8007C00
#define SAMPLING_DATA_ADDR      0x08018000          //
#define STM32_memory_size       128         // Kb

uint16_t FlashReadHalfWord(uint32_t faddr);
uint8_t FlashWriteHalfWord(uint32_t faddr,uint16_t dat);
void STMFLASH_Read(uint32_t ReadAddr,uint16_t *pBuffer,uint16_t NumToRead);
void STMFLASH_Write_NoCheck(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);
void STMFLASH_Write(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);

void FlashErase32K(void);









#endif 


