#include "spi1.h"


void SPI1_Init(void)
{	 
//	RCC->APB2ENR|=1<<2;       // 	 
//	RCC->APB2ENR|=1<<12;      // 
//		   
//	//
//	GPIOA->CRL&=0X000FFFFF; 
//	GPIOA->CRL|=0XBBB00000;//PA5.6. 	    
//	GPIOA->ODR|=0X7<<5;    //PA5.6.7
//		
//	SPI1->CR1|=0<<10;//	
//	SPI1->CR1|=1<<9; //
//	SPI1->CR1|=1<<8;  

//	SPI1->CR1|=1<<2; //
//	SPI1->CR1|=0<<11;//	
//
//	SPI1->CR1|=0<<1; // 
//	//SPI1->CR1|=1<<1; // 			   
//	SPI1->CR1|=0<<0; //,CPHA=1 CPOL=1	   
//	SPI1->CR1|=7<<3; //Fsck=Fcpu/256
//	SPI1->CR1|=0<<7; //MSBfirst   
//	SPI1->CR1|=1<<6; //
//	SPI1_ReadWriteByte(0xff);//		
    
 	GPIO_InitTypeDef GPIO_InitStructure;
  	SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );// 
	//RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );// 	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);  //PB13/14/15

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //:
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//:
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;		//:
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//:
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;		//
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//
	SPI_Init(SPI1, &SPI_InitStructure);  //
 
	SPI_Cmd(SPI1, ENABLE); //
	
//	SPI2_ReadWriteByte(0xFFFF);//	     
}   
//SPI 
//SpeedSet:
//SPI_SPEED_2   2   (SPI 36M@sys 72M)
//SPI_SPEED_8   8   (SPI 9M@sys 72M)
//SPI_SPEED_16  16  (SPI 4.5M@sys 72M)
//SPI_SPEED_256 256 (SPI 281.25K@sys 72M)
void SPI1_SetSpeed(u8 SpeedSet)
{
	SPI1->CR1&=0XFFC7;//Fsck=Fcpu/256
	if(SpeedSet==SPI_SPEED_2)//
	{
		SPI1->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz	
	}else if(SpeedSet==SPI_SPEED_8)// 
	{
		SPI1->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz	
	}else if(SpeedSet==SPI_SPEED_16)//
	{
		SPI1->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
	}else			 	 //256
	{
		SPI1->CR1|=7<<3; //Fsck=Fpclk/256=281.25Khz 
	}
	SPI1->CR1|=1<<6; //	  
} 
//SPIx 
//TxData:
//
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 
	while((SPI1->SR&1<<1)==0)//	
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI1->DR=TxData;	 	  // 
	retry=0;
	while((SPI1->SR&1<<0)==0) //  
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI1->DR;          //				    
}




















