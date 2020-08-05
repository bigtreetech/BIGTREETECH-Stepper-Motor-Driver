#include "gpio.h"

//LED IO
void LED_Init(void)
{
 
     GPIO_InitTypeDef  GPIO_InitStructure;
        
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //
        

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->C13 
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //
     GPIO_Init(GPIOC, &GPIO_InitStructure);					 //
     GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //Pc13 

}
 
