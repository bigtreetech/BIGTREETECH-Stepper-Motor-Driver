#include "can.h"

uint8_t CAN1_Mode_Init(uint8_t tsjw,uint8_t tbs2,uint8_t tbs1,uint16_t brp,uint8_t mode)
{

    GPIO_InitTypeDef        GPIO_InitStructure; 
    CAN_InitTypeDef         CAN_InitStructure;
    CAN_FilterInitTypeDef   CAN_FilterInitStructure;
#if CAN1_RX0_INT_ENABLE 
   	NVIC_InitTypeDef  NVIC_InitStructure;
#endif
    //
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO, ENABLE);//	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//	
	
    //GPIO
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//
    
    GPIO_Init(GPIOA, &GPIO_InitStructure);//PA11,PA12
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//
    GPIO_Init(GPIOA, &GPIO_InitStructure);//PA11,PA12
    
	
	  //
//	  GPIO_PinRemapConfig( GPIO_Remap1_CAN1,  ENABLE); //GPIOA11CAN1
	  
  	//CAN
   	CAN_InitStructure.CAN_TTCM=DISABLE;	//   
  	CAN_InitStructure.CAN_ABOM=DISABLE;	//	  
  	CAN_InitStructure.CAN_AWUM=DISABLE;//(CAN->MCR SLEEP位)
  	CAN_InitStructure.CAN_NART=ENABLE;	// 
  	CAN_InitStructure.CAN_RFLM=DISABLE;	//,  
  	CAN_InitStructure.CAN_TXFP=DISABLE;	// 
  	CAN_InitStructure.CAN_Mode= mode;	 // 
  	CAN_InitStructure.CAN_SJW=tsjw;	//(Tsjw) tsjw+1 CAN_SJW_1tq~CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1=tbs1; //Tbs1CAN_BS1_1tq ~CAN_BS1_16tq
  	CAN_InitStructure.CAN_BS2=tbs2;//Tbs2CAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler=brp;  //(Fdiv)为brp+1	
  	CAN_Init(CAN1, &CAN_InitStructure);   // CAN1 
    
		//
 	CAN_FilterInitStructure.CAN_FilterNumber=0;	  //0
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32 ID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32 MASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;// 0 FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //0
  	CAN_FilterInit(&CAN_FilterInitStructure);//
		
#if CAN1_RX0_INT_ENABLE
	
  	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // 1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // 0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
    
    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//.		    
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);//
    
#endif
	return 0;
}   
 
#if CAN1_RX0_INT_ENABLE	//
//			    
void USB_LP_CAN1_RX0_IRQHandler(void)
{   static int i=0;
  	CanRxMsg RxMessage;
    NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);//
    CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);//
	
    CAN_Receive(CAN1, 0, &RxMessage);
    //
    
	for(i=0;i<8;i++)
        printf("rxbuf[%d]:%#x\r\n",i,RxMessage.Data[i]);
    
    CAN_FIFORelease(CAN1,CAN_FIFO0);//
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);//
}
#endif

//
//len:()				     
//msg:,.
//:0,;
//		 ,;
uint8_t CAN1_Send_Msg(uint8_t* msg,uint8_t len)
{	
  uint8_t mbox;
  uint16_t i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x12;	 // 
  TxMessage.ExtId=0x12;	 // 
  TxMessage.IDE=0;		  // 
  TxMessage.RTR=0;		  // 
  TxMessage.DLC=len;							 // 
  for(i=0;i<len;i++)
  TxMessage.Data[i]=msg[i];				 //           
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  i=0;
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//
  if(i>=0XFFF)return 1;
  return 0;		

}
//
//buf:;	 
//
//		 ;
uint8_t CAN1_Receive_Msg(uint8_t *buf)
{		   		   
 	uint32_t i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		// 
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//	
    for(i=0;i<RxMessage.DLC;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}




















