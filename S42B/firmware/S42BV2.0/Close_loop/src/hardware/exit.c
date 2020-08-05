#include "exit.h"


////////////////////////////////////////////////////////////////////////////////// 	  
 
 
//
//
void EXTIX_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    #if 1
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;				 //-->PA.1 
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //
     GPIO_Init(GPIOA, &GPIO_InitStructure);					 //.10
    
        //GPIOA.1	  
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
    #else
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_11;				 //PB.11 
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //
     GPIO_Init(GPIOB, &GPIO_InitStructure);					 //
        //GPIOA.1	  
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
    #endif

   	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	// 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//
  	NVIC_Init(&NVIC_InitStructure);  	  //
 
}

 //
void EXTI1_IRQHandler(void)
{

     if(DIRIN==1){
        if(Motor_Dir==1){
            TIM_CounterModeConfig(TIM2,  TIM_CounterMode_Up);
        }
        else{
            TIM_CounterModeConfig(TIM2,TIM_CounterMode_Down);
        }
    }
	else{
        if(Motor_Dir ==1){
            TIM_CounterModeConfig(TIM2,TIM_CounterMode_Down);
        }
        else{
            TIM_CounterModeConfig(TIM2,TIM_CounterMode_Up);
        }
    }
	EXTI_ClearITPendingBit(EXTI_Line1);  //
}

