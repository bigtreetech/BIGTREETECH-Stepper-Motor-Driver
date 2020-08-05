#include "delay.h"
unsigned int fac_us,fac_ms;

//
//    

void stm32_SysClock72M(u8 PLL)//
{
	unsigned char temp=0;
	RCC->CR=0X00000083;//,
    #if 0
        RCC->CR|=0X00010000;// 
        while(!(RCC->CR>>17));//
	#endif
    #if 1
        while(!(RCC->CR&0x02));//
    #endif
    RCC->CFGR=0X00000400;//
    #if 0                // 
        PLL-=2;				 
    #endif
	RCC->CFGR|=PLL<<18;   //~21
	RCC->CFGR|=1<<16;		//
	FLASH->ACR|=0X32;		//
	RCC->CR|=0X01000000;	//
	while(!(RCC->CR>>25));	//
	RCC->CFGR|=0X00000002;	//
	while(temp!=0x02)		//
	{
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}
}

void delay_init(u8 SYSCLK)//
{
	
	SysTick->CTRL&=0xfffffffb;//
	fac_us=SYSCLK/8;
	fac_ms=fac_us*1000;
}

void delay_us(u32 nus)//
{
	u32 temp;
//	delay_Init(72);//
	SysTick->LOAD=nus*fac_us;
	SysTick->VAL=0x00;//
	SysTick->CTRL=0x01;//
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL=0x00;
	SysTick->VAL=0x00;
}

void delay_ms(u32 nms)//
{
	u32 temp;
//	delay_Init(72);//
	SysTick->LOAD=nms*fac_ms;
	SysTick->VAL=0x00;//
	SysTick->CTRL=0x01;//
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL=0x00;
	SysTick->VAL=0x00;
}

void System_Clock_Init(void)
{
    SystemInit();
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
	
 	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
}







