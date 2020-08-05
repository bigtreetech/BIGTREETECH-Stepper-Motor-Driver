#include "flash.h"



//
uint8_t FlashGetStatus(void)
{
  uint32_t res;
  res=FLASH->SR;
  if(res&(1<<0))//flash busy
    return 1; 
  else if(res&(1<<2))  //Programming error
	return 2; 
  else if(res&(1<<4))  //
	return 3; 
  return 0;     
}

uint8_t FlashWaitDone(uint16_t time)
{
  uint8_t res;
  do
  {
    res=FlashGetStatus();
    if(res!=1)
	  break;
	delay_us(1);	
    time--;
  }while(time);
  if(time==0)
    res=0xff;
  return res;
}
//
uint8_t FlashErasePage(uint32_t paddr)
{
  uint8_t res=0;
  res=FlashWaitDone(0X5FFF);
  if(res==0)
  {
    FLASH->CR|=1<<1; 
    FLASH->AR=paddr; 
    FLASH->CR|=1<<6; 
    res=FlashWaitDone(0X5FFF); 
    if(res!=1) 
      FLASH->CR&=~(1<<1); 
  }
  return res;
}

//
uint8_t FlashWriteHalfWord(uint32_t faddr,uint16_t dat)
{
  uint8_t  res;
  res=FlashWaitDone(0XFF);
  if(res==0)
  {
    FLASH->CR|=1<<0;
    *(volatile uint16_t*)faddr=dat; 
    res=FlashWaitDone(0XFF);
	if(res!=1)
    {
      FLASH->CR&=~(1<<0); 
    }
  }
  return res;
}
//
uint16_t FlashReadHalfWord(uint32_t faddr)
{
  return *(volatile uint16_t*)faddr;
}
  
//
//ReadAddr:
//pBuffer:
//NumToWrite:
void STMFLASH_Read(uint32_t ReadAddr,uint16_t *pBuffer,uint16_t NumToRead)   	
{
	uint16_t i;
	for(i=0;i<NumToRead;i++)
	{
        pBuffer[i]=FlashReadHalfWord(ReadAddr);//
		ReadAddr+=2;//
	}
}
//
//WriteAddr:
//pBuffer:
//NumToWrite:
void STMFLASH_Write_NoCheck(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite)   
{ 			 		 
	uint16_t i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//
	}  
} 

//WriteAddr:
//pBuffer:
//NumToWrite:
#define STM32_FLASH_SIZE STM32_memory_size
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
uint16_t STMFLASH_BUF[STM_SECTOR_SIZE/2];//
void STMFLASH_Write(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite)	
{
	uint32_t secpos;	   //
	uint16_t secoff;	   //
	uint16_t secremain; //
 	uint16_t i;    
	uint32_t offaddr;   //
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//
	FLASH_Unlock();						//
	offaddr=WriteAddr-STM32_FLASH_BASE;		//
	secpos=offaddr/STM_SECTOR_SIZE;			//  0~63 for STM32F030
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//
	secremain=STM_SECTOR_SIZE/2-secoff;		//   
	if(NumToWrite<=secremain)secremain=NumToWrite;//
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//
		for(i=0;i<secremain;i++)//
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//  	  
		}
		if(i<secremain)//
		{
			FlashErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//
			for(i=0;i<secremain;i++)//
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//  
		}else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//
		if(NumToWrite==secremain)break;//
		else//
		{
			secpos++;				//
			secoff=0;				// 	 
		   	pBuffer+=secremain;  	
			WriteAddr+=secremain*2;	
		   	NumToWrite-=secremain;	//
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//
			else secremain=NumToWrite;//
		}	 
	};	
	FLASH_Lock();//
}


//FLASH32K
void FlashErase32K(void)
{
  FlashErasePage(0x08018000);
  FlashErasePage(0x08018400);
  FlashErasePage(0x08018800);
  FlashErasePage(0x08018C00);
  FlashErasePage(0x08019000);
  FlashErasePage(0x08019400);
  FlashErasePage(0x08019800);
  FlashErasePage(0x08019C00);
  FlashErasePage(0x0801A000);
  FlashErasePage(0x0801A400);
  FlashErasePage(0x0801A800);
  FlashErasePage(0x0801AC00);
  FlashErasePage(0x0801B000);
  FlashErasePage(0x0801B400);
  FlashErasePage(0x0801B800);
  FlashErasePage(0x0801BC00);
  FlashErasePage(0x0801C000);
  FlashErasePage(0x0801C400);
  FlashErasePage(0x0801C800);
  FlashErasePage(0x0801CC00);
  FlashErasePage(0x0801D000);
  FlashErasePage(0x0801D400);
  FlashErasePage(0x0801D800);
  FlashErasePage(0x0801DC00);
  FlashErasePage(0x0801E000);
  FlashErasePage(0x0801E400);
  FlashErasePage(0x0801E800);
  FlashErasePage(0x0801EC00);
  FlashErasePage(0x0801F000);
  FlashErasePage(0x0801F400);
  FlashErasePage(0x0801F800); 
  FlashErasePage(0x0801FC00);
}
 
 























