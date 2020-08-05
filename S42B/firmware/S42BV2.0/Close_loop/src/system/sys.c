#include "sys.h"

//
//NVIC_VectTab:
//Offset:			 
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)	 
{ 	   	 
	SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);//
	//
}
//
//NVIC_GROUP: 0-4 
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)
{
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//
	temp1<<=8;
	temp=SCB->AIRCR;  //
	temp&=0X0000F8FF; //
	temp|=0X05FA0000; //
	temp|=temp1;	   
	SCB->AIRCR=temp;  //		
}
// 
//NVIC_PreemptionPriority:
//NVIC_SubPriority       :
//NVIC_Channel           :
//NVIC_Group             : 0~4
//
//:4-7
//0:0,4
//1:1,3
//2:2,2
//3:3,1
//4:4,0
//NVIC_SubPriority NVIC_PreemptionPriority	   
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;
	u8 IPADDR=NVIC_Channel/4;//
	u8 IPOFFSET=NVIC_Channel%4;//
	IPOFFSET=IPOFFSET*8+4;//
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;//  
	if(NVIC_Channel<32)
		NVIC->ISER[0]|=1<<NVIC_Channel;//
	else
		NVIC->ISER[1]|=1<<(NVIC_Channel-32);    
	NVIC->IP[IPADDR]|=temp<<IPOFFSET;//   	    	  				   
}
//
//GPIOA~G;
//:
//GPIOx:0~6,GPIOA~G
//BITx:;
//TRIM:1;2;3
//
//
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM) 
{
	u8 EXTADDR;
	u8 EXTOFFSET;
	EXTADDR=BITx/4;//
	EXTOFFSET=(BITx%4)*4; 
	RCC->APB2ENR|=0x01;//			 
	AFIO->EXTICR[EXTADDR]&=~(0x000F<<EXTOFFSET);//
	AFIO->EXTICR[EXTADDR]|=GPIOx<<EXTOFFSET;// 
	//
	EXTI->IMR|=1<<BITx;//  line BITx
	//EXTI->EMR|=1<<BITx;//line BITx
 	if(TRIM&0x01)
		EXTI->FTSR|=1<<BITx;//line 
	if(TRIM&0x02)
		EXTI->RTSR|=1<<BITx;//line 
} 



