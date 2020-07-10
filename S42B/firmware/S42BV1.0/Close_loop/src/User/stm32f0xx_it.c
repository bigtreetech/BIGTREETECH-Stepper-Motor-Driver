#include "stm32f0xx.h"
#include "stm32f0xx_it.h"


void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
} 


void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}

//
void EXTI0_1_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
    if(DIRIN==1){
        if(Motor_Dir==1){
            LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERMODE_UP);
        }
        else{
            LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERMODE_DOWN);
        }
    }
	else{
        if(Motor_Dir ==1){
            LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERMODE_DOWN);
        }
        else{
            LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERMODE_UP);
        }
    }
  }
}
//
void EXTI2_3_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_2) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
      
	if(ENIN==1)
	  enmode=1;
	else{
	  enmode=0;
      LL_TIM_OC_SetCompareCH1(TIM3,0);  
	  LL_TIM_OC_SetCompareCH2(TIM3,0);  
	}
    
    if(ENIN==0)
        enmode=1;
    else{
        enmode=0;
        LL_TIM_OC_SetCompareCH1(TIM3,0);  
        LL_TIM_OC_SetCompareCH2(TIM3,0);   
    }
  }
}


void TIM6_IRQHandler(void)
{
  if(LL_TIM_IsActiveFlag_UPDATE(TIM6) == 1)
  {
	LL_TIM_ClearFlag_UPDATE(TIM6);
	LL_IWDG_ReloadCounter(IWDG);//
    if(enmode==1)
	{
	  if(closemode==1) 
	  {    
		y=*(volatile uint16_t*)((ReadValue(READ_ANGLE_VALUE)>>1)*2+0x08008000);//
        s=LL_TIM_GetCounter(TIM1);//
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
            LED_H;
        }
        #else 
        if(u>UMAXCL)     
        {
		  u=UMAXCL;//
		  LED_H;
		}
        #endif
        else
          LED_L;
        Output(y,u);    
      }          
      else 
	  {		
		s=LL_TIM_GetCounter(TIM1);
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
      if(Data_update_Count>=5000){       //250ms
          Data_update_Count-=5000;
          Motor_speed_flag++;
          if(Motor_speed_flag>=2){
            Motor_speed_flag=0;
              
              wap1=wap2;
              wap2=wrap_count;
//              Motor_speed = wap2-wap1;//
          }
        Data_update_flag=1;           //
      }
    }
  }
}




