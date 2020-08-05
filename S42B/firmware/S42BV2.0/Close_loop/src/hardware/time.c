#include "time.h"
#include "gpio.h"
#include "iwdg.h"


void TIM2_Cap_Init(u16 arr,u16 psc)
{	 
    TIM_DeInit(TIM2);
    
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//    TIM_ICInitTypeDef  TIM2_ICInitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;
    
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; // 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //
  
    TIM_ARRPreloadConfig(TIM2,DISABLE);              //
//    TIM_ETRClockMode1Config(TIM2, TIM_ExtTRGPSC_OFF,  TIM_ExtTRGPolarity_NonInverted,0);
    TIM2->SMCR |= 1<<14;                        //
//    TIM2->SMCR &= ~(1<<15);                     // 
//    TIM2->SMCR &= ~(3<<12);                     // 
//    TIM2->SMCR &= ~(0xF<<8);
    
    TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 7);
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Reset);
    TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Disable);              //
    
//
//	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	 
//  	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//
//  	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //
//  	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //, 
//  	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000  
//  	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
#if 0
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;  //
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //
	NVIC_Init(&NVIC_InitStructure);  // 

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);// 
#endif
    TIM_SetCounter(TIM2 , 0);
    TIM_Cmd(TIM2,ENABLE ); 	//
}


//u8  TIM2CH1_CAPTURE_STA=0;	//		    				
//u16	TIM2CH1_CAPTURE_VAL;	//
// 
//	 
//void TIM2_IRQHandler(void)
//{ 
//    static uint16_t overflow=0;
//// 	if((TIM2CH1_CAPTURE_STA&0X80)==0)//	
////	{	  
////		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
////		{	    
////            led2=!led2;
//            Receiv_pluse = TIM2->CNT;
//            overflow++ ;                      
//            if(overflow>=5){                     //
//                
//                overflow=0;
//            }
//            printf("overflow = %d , Receiv_pluse = %d\r\n",overflow,Receiv_pluse);
////			if(TIM2CH1_CAPTURE_STA&0X40)//
////			{
////				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//
////				{
////					TIM2CH1_CAPTURE_STA|=0X80;//
////					TIM2CH1_CAPTURE_VAL=0XFFFF;
////				}else TIM2CH1_CAPTURE_STA++;
////			}	 
////		}
////	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//
////		{	
////			if(TIM2CH1_CAPTURE_STA&0X40)		// 		
////			{	  			
////				TIM2CH1_CAPTURE_STA|=0X80;		//
////				TIM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);
////		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 
////			}else  								//,
////			{
////				TIM2CH1_CAPTURE_STA=0;			//
////				TIM2CH1_CAPTURE_VAL=0;
////	 			TIM_SetCounter(TIM2,0);
////				TIM2CH1_CAPTURE_STA|=0X40;		//
////		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 
////			}		    
////		}			     	    					   
//// 	}
//    TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //
//}



//
//void TIM1_Init(uint16_t Arr,uint16_t Psc)
//{
////    GPIO_InitTypeDef            GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
////	TIM_OCInitTypeDef           TIM_OCInitStructure;
//	NVIC_InitTypeDef            NVIC_InitStructure;

//	   
////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

////   // 	GPIOB.1	  	GPIOB.0
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
////	GPIO_Init(GPIOA, &GPIO_InitStructure);//
//	
//   //
//    TIM_DeInit(TIM1);
//	TIM_TimeBaseStructure.TIM_Period = Arr; //
//	TIM_TimeBaseStructure.TIM_Prescaler =Psc; //  72000/7200=10K
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //

//	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

//	
////    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2; //
////    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //
////    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //  
////	 //
////    TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High; //
////    TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;//
////    TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; //
////    TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//
////	// TIM_OC1Init(TIM8,&TIM_OCInitStructure); //
//    
////    TIM_SelectMasterSlaveMode(TIM1 ,TIM_MasterSlaveMode_Enable);
////    TIM_SelectOutputTrigger(TIM1 ,TIM_TRGOSource_Update);

////    TIM_OC4Init(TIM1, &TIM_OCInitStructure);    
////    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
//        
////    TIM_OC2Init(TIM8, &TIM_OCInitStructure);  // OC2
////    TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //

//    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
////    TIM_CtrlPWMOutputs(TIM1, ENABLE); //
////    TIM_Cmd(TIM1, ENABLE);  //
//    TIM_ITConfig(TIM1,  TIM_IT_Update, ENABLE);
//}

void SetT1Pwm1(uint16_t Duty)
{
    TIM1 ->CCR4 = Duty; 
}

void TIM3_Init(void)
{
    
   	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef  GPIO_InitStruct;
//    GPIO_AFIODeInit();
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);// 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //
	
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);    //
    
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;			
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);	

    
   	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1; //
	TIM_TimeBaseInitStruct.TIM_Period = 256;		//
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; //
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);

//	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);//	
	TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Disable);//	
//	TIM_SelectInputTrigger(TIM3,TIM_TS_ITR1);//

    TIM_ARRPreloadConfig(TIM3,DISABLE);              //
    
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//
	TIM_OCInitStruct.TIM_Pulse = 3;//
    
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
    TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);//

	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//
    
//    TIM_ARRPreloadConfig(TIM3,ENABLE);              //
    TIM_CtrlPWMOutputs(TIM3, ENABLE);               //
	TIM_Cmd(TIM3,ENABLE);                           //
}
//
void TIM4_Init(u16 arr,u16 psc)
{	 
//	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//
		
	// TIM4	 
	TIM_TimeBaseStructure.TIM_Period = arr; // 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //
     
	//
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //
	NVIC_Init(&NVIC_InitStructure);  // 
//	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);// 
	
    TIM_Cmd(TIM4,ENABLE ); 	//
}
//	 
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){	    
//            led1=!led1;
        IWDG_Feed();//
        if(enmode==1)
        {
          //SET_BIT(TIM3->CR1, TIM_CR1_CEN);
          if(closemode==1) 
          {    
            y=*(volatile uint16_t*)((ReadValue(READ_ANGLE_VALUE)>>1)*2+0x08008000);//
            s=TIM_GetCounter(TIM2);//
            if(s-s_1<-32768)
              s_sum+=stepangle*65536;
            else if(s-s_1>32768)
              s_sum-=stepangle*65536;
            r=s_sum+stepangle*s;//
            s_1=s;
            
            if(y-y_1>8192) 
              wrap_count--;      
            else if(y-y_1<-8192) 
              wrap_count++; 
            yw=y+16384*wrap_count;//            
            e=r-yw;//
            if(e>1638)//
              e=1638;
            else if(e<-1638)
              e=-1638;
            iterm+=ki*e/32;//
            if(iterm>UMAXSUM)//
              iterm=UMAXSUM;
            else if(iterm<-UMAXSUM) 
              iterm=-UMAXSUM; 
        
               
            dterm=LPFA*dterm/128-LPFB*kd*(yw-yw_1)/8;//
            u=(kp*e+iterm+dterm)/128;//
            
            advance=(yw-yw_1)*1.5f;//
            y_1=y;  
            yw_1=yw;
        
            if(u>0)            
            {
              if(advance>68)//
                advance=68;
              else if(advance<0)
                advance=0; 		  
              y+=(82+advance);//
            }
            else if(u<0)
            {
              if(advance<-68)
                advance=-68; 
              else if(advance>0)
                advance=0; 
              y-=(82-advance);
              u=-u;
            }
            //
            #if 1
            if(u>Currents){
                u=Currents;//
                led1 = LED_ON;
            }
            #else 
            if(u>UMAXCL)     
            {
              u=UMAXCL;
              LED_H;
            }
            #endif
            else
              led1 = LED_OFF;
            Output(y,u);    
          }          
          else 
          {		
            s=TIM_GetCounter(TIM2);
            if(s-s_1<-32768)
              s_sum+=stepangle*65536;
            else if(s-s_1>32768)
              s_sum-=stepangle*65536;
            r=s_sum+stepangle*s;
            s_1=s;
            
            if(r==r_1)
            {
              hccount++;
              if(hccount>=1000)
                hccount=1000;
            }
            else
              hccount=0;
            
            if(hccount>=1000)//
              Output(r,UMAXOP/2);
            else
              Output(r,UMAXOP);
            r_1=r;
          }
         
          Data_update_Count++;
          if(Data_update_Count>=5000){       
              Data_update_Count-=5000;
              Motor_speed_flag++;
              if(Motor_speed_flag>=2){
                Motor_speed_flag=0;
                  
                  wap1=wap2;
                  wap2=wrap_count;
    //              Motor_speed = wap2-wap1;//
              }
            Data_update_flag=1;           
          }
        }
      }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //
}


//void  TIM1_UP_IRQHandler(void)
//{
//    if(TIM_GetITStatus(TIM1,TIM_IT_Update)!= RESET){
//        TIM_ClearITPendingBit(TIM1 ,TIM_IT_Update);
//        TIM_Cmd(TIM1, DISABLE);                     //
//        TIM1->CNT = 0;                              //
//    }
//}
//void TIM_Init(void)
//{	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	TIM_OCInitTypeDef TIM_OCInitStruct;
//	GPIO_InitTypeDef  GPIO_InitStruct;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3,ENABLE);   //
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);						  //	

////	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);	

//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;			
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStruct);	
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
//	GPIO_Init(GPIOA,&GPIO_InitStruct); 

//	//
//	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//
//	TIM_TimeBaseInitStruct.TIM_Prescaler = 7199;				//
//	TIM_TimeBaseInitStruct.TIM_Period = 99; 					
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);	

//	TIM_SelectOnePulseMode(TIM2,TIM_OPMode_Single);		 //	  
//	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_OC1Ref); //OC1REF signal is used as the trigger output (TRGO).

//	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);	 //
//	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;		 //
//	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;	//
//	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;		//
//	TIM_OCInitStruct.TIM_Pulse = 20;		//
//	TIM_OC1Init(TIM2,&TIM_OCInitStruct);		
//	TIM_Cmd(TIM2,DISABLE); //Disable the TIM Counter

//	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//
//	TIM_TimeBaseInitStruct.TIM_Prescaler = 719; //
//	TIM_TimeBaseInitStruct.TIM_Period = 29;		//
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);

//	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);//	
//	TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);//	
//	TIM_SelectInputTrigger(TIM3,TIM_TS_ITR1);//

//	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);//
//	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;//
//	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//
//	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//
//	TIM_OCInitStruct.TIM_Pulse = 15;//
//	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
//	TIM_Cmd(TIM3,ENABLE);//
//}

/*********************************************************

*********************************************************/
void Pulse_Control(u16 cycle, u16 pulse_num)
{
	u16 arr3 = 0;
	u32 time = 0;
	if(pulse_num)
	{ 
		time = cycle * pulse_num / 100;
		arr3 = cycle / 10;             
		TIM_SetAutoreload(TIM2, time + 19);
		TIM_SetAutoreload(TIM3, arr3 - 1);
		TIM_SetCompare1(TIM3,arr3 / 2); 
		TIM_Cmd(TIM2,ENABLE);
       
	}
}
