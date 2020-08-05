/**
  ******************************************************************************
  * @file    uart.c
  * @author  dy_stm32
  * @version V1.0.0
  * @date    2016.8.1
  * @brief   
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "usart.h"
#include "gpio.h"
#include "delay.h"
#include "flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define H_ENABLE_STATUS   "Enable =%d \r\n"
#define L_ENABLE_STATUS   "!Enable =%d \r\n"
#define CCW_DIR           "Dir =%d, CCW\r\n"
#define CW_DIR            "Dir =%d, CW\r\n"
/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


//////////////////////////////////////////////////////////////////
//  
#if 1
#pragma import(__use_no_semihosting)             
//                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is  d in stdio.h. */ 
FILE __stdout;       
//  
void _sys_exit(int x) 
{ 
	x = x; 
} 
// 
int fputc(int ch, FILE *f)
{      
    USART1->DR = (u8) ch;
	while(USART_GetFlagStatus (USART1 , USART_FLAG_TC)== RESET);//   
	return ch;
}
#endif 
//end
//////////////////////////////////////////////////////////////////
//
#if 0
void usart_init(u32 pclk2,u32 bound)
{
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//
	mantissa=temp;				 //
	fraction=(temp-mantissa)*16; //	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //  
	RCC->APB2ENR|=1<<14;  // 
	GPIOA->CRH&=0XFFFFF00F;//
	GPIOA->CRH|=0X000008B0;//
		  
	RCC->APB2RSTR|=1<<14;   //
	RCC->APB2RSTR&=~(1<<14);//	   	   
 	USART1->BRR=mantissa; // 	
	
//	USART1->CR1|=1<<13;  //
//	USART1->CR1&=~(1<<12);//
//	USART1->CR2&=~(3<<12);//
//	USART1->CR1|=(1<<3);//
//	USART1->CR1|=(1<<2);//
	USART1->CR1|=0X200C;  
	
	USART1->CR1|=1<<8;		 //
	USART1->CR1|=1<<5;   //	 
	MY_NVIC_Init(3,3,USART1_IRQn,2);// 
}

#endif
/*********************************************/
void USART1_SendByte(char data)
{
    USART1->DR = (uint8_t)data;
    /*  */
    while(USART_GetFlagStatus (USART1 , USART_FLAG_TC)== RESET);// 
}


/*******************************************************************************
* : UART1_SendStr
* : 
* : data -> 
*      
*  
******************************************************************************/
void USART1_SendStr(char *str)
{
    while(*str != '\0')
    {
        USART1_SendByte(*str++); /*  */
    }   
    //*str =NULL ;
}
/**
  * @brief  System_NVIC_Priority_Configurate
  * @param  chx nvic irq Channel
  * @param  pre PreemptionPriority
  * @param  sub SubPriority
  * @retval None
  */
void System_NVIC_Priority_Configurate(uint8_t chx, uint8_t pre, uint8_t sub)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = chx;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pre;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief 	UART_BaudRate_Settings
  * @param  USARTx, baudrate
  * @retval None
  */
void UART_BaudRate_Settings(USART_TypeDef * USARTx, uint32_t baudrate)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART_DeInit(USARTx);
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USARTx, &USART_InitStructure);
}

/**
  * @brief 	UART_Configuration
  * @param  USARTx, baudrate
  * @retval None
  */
void UART_Configuration(USART_TypeDef * USARTx, uint32_t baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	if (USARTx == USART1) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO , ENABLE);
    
		GPIO_InitStructure.GPIO_Pin = UART1_TX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(UART1_TX_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = UART1_RX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(UART1_RX_GPIO_PORT, &GPIO_InitStructure);

		UART_BaudRate_Settings(USART1, baudrate);
        System_NVIC_Priority_Configurate(USART1_IRQn, 1, 3);

		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
        USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
		USART_Cmd(USART1, ENABLE);
        
		USART_ClearFlag(USART1, USART_FLAG_TC);
	}
}

void PID_Cal_value_init(void)
{
//    enmode =0;
 /**/
    s=0;
    s_1=0;
    
    s_sum=0;
    r=0;
    r_1=0;
    y=0;
    y_1=0;
    yw=0;
    e=0;
    u=0;
    dterm=0;
    wrap_count=0;
    //LL_TIM_SetCounter(TIM1,0);
    
    
    r=*(volatile uint16_t*)((ReadValue(READ_ANGLE_VALUE)>>1)*2+SAMPLING_DATA_ADDR); //
    s_sum=r;   //
    y=r;
    y_1=y;
    yw=y;  
    yw_1=yw;
    
    WRITE_REG(TIM2->CNT, 0);
    
}

void test_uart(void)
{
    if(info_report_flag ==1){
        info_report_flag =0;
    
        switch(Rx1_buff[3]){         //
            case 0xA0:
                    kp = value_Temp;
                    table1[11]=kp;
                    
                    printf("new kp = %d\r\n",kp);
            break;
            case 0xA1:
                    ki = value_Temp;
                    table1[12]=ki;
                    
                    printf("new ki = %d\r\n",ki);
                break;
            case 0xA2: kd = value_Temp;
                    table1[13]=kd;
                    
                    printf("new kd = %d\r\n",kd);
                break;
            case 0xA3:      //set Current 
                    Currents = (value_Temp/100)<<3;
                    Menu_Num2_item = Currents>>3;
            
                    table1[1]=Currents;
                    table1[2]=Menu_Num2_item;
                    
                break;                                      //
            case 0xA4:
                    enmode =0;                      //
                    PID_Cal_value_init();                   /**/
                    stepangle = 64/value_Temp;
                    //stepangle =Microstep_Set;              //
                    table1[3]=stepangle;                    //
                    switch(stepangle & 0x3e){
                        case 0x02:Menu_Num3_item =4;  break;
                        case 0x04:Menu_Num3_item =3;  break;
                        case 0x08:Menu_Num3_item =2;  break;
                        case 0x10:Menu_Num3_item =1;  break;
                        case 0x20:Menu_Num3_item =0;  break;
                        default: Menu_Num3_item =3; break;
                    }
                    table1[4]=Menu_Num3_item;
                     
                break;
            case 0xA5:
                    enmode =0;                      //
                    PID_Cal_value_init();                               //
                    if(0xaa == value_Temp){
                        Motor_ENmode_flag=0;Menu_Num4_item=1;           //
                    }else if(0x55 == value_Temp) {
                        Motor_ENmode_flag=1;Menu_Num4_item=0;
                    }
                    table1[5]=Motor_ENmode_flag;                        //
                    table1[6]=Menu_Num4_item;
                    
                break; 
            case 0xA6:                                                  //
                    if(0x11 == value_Temp){
                        Motor_Dir=1;Menu_Num5_item=0;                   //
                    }else if(0x22 == value_Temp) {
                        Motor_Dir=0;Menu_Num5_item=1;
                    }
                    table1[7]=Motor_Dir;                                //
                    table1[8]=Menu_Num5_item;
                   
                break; 
            case 0xB0: if((Rx1_buff[4]==0xaa) && (Rx1_buff[5]== 0xaa)){                     //
                   
                    printf("p --- kp =%d\r\n",kp);
                    printf("i --- ki =%d\r\n",ki);
                    printf("d --- kd =%d\r\n",kd);
                    }else{
                        USART1_SendStr("Read PID err\r\n");
                    }
                break;
            case 0xB1: if((Rx1_buff[4]==0xaa) && (Rx1_buff[5]== 0xaa)){                     //
                 
                        printf("Currents =%d mA\r\n",(Currents>>3)*100);
                    }else{
                        USART1_SendStr("Read Current err\r\n");
                    }
                break;
            case 0xB2: if((Rx1_buff[4]==0xaa) && (Rx1_buff[5]== 0xaa)){                     //
                 
                        printf("Microstep =%d -->%d Gear\r\n",64/stepangle,16384/stepangle);
                    }else{
                        USART1_SendStr("Read Microstep err\r\n");
                    }
                break;
            case 0xB3: if((Rx1_buff[4]==0xaa) && (Rx1_buff[5]== 0xaa)){                     //
                
                        if(1 == Motor_ENmode_flag)
                            printf(H_ENABLE_STATUS,Motor_ENmode_flag);
                        if (0== Motor_ENmode_flag)
                            printf(L_ENABLE_STATUS,Motor_ENmode_flag);
                    }else{
                        USART1_SendStr("Read enable err\r\n");
                    }
                break;                           
            case 0xB4: if((Rx1_buff[4]==0xaa) && (Rx1_buff[5]== 0xaa)){                     //
                   
                        if(0 == Motor_Dir)
                            printf(CCW_DIR,Motor_Dir);
                        if(1 == Motor_Dir)
                            printf(CW_DIR,Motor_Dir);
                    }else{
                        USART1_SendStr("Read Dir err\r\n");
                    }
                break;
            default: USART1_SendStr("Function Code Undefined\r\n");
                break;
        }
    }
}
void data_Process(void)
{
   if(Urat_CRC_Correct_flag){               //
        Urat_CRC_Correct_flag=0;
        if(Rx1_buff[2] ==0x05){                 //
            value_Temp = Rx1_buff[4];
            value_Temp<<=8;
            value_Temp|= Rx1_buff[5];
            if(Rx1_buff[3]>=0xA0 && Rx1_buff[3]<=0xBF){
                if((Rx1_buff[3] &0xA0)== 0xA0)
                    flash_store_flag=1;                     //
                else
                    flash_store_flag=0;
                info_report_flag =1;
                //test_uart();
            }else{
                USART1_SendStr("Function Code err\r\n");
            }
        }
        else{
            ////
            USART1_SendStr("Data Length err\r\n");
        }
        //USART_Cmd(USART1, ENABLE);
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
        USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    }
}
//
void usart_Receive_Process(void)
{
    static uint8_t t;
//    uint32_t Temporary_val=0;
    uint16_t CRC_val=0;
    if(Communications_Process_flag){
        Communications_Process_flag=0;
        if(Uart_CRC_flag ){                                   //   
            Uart_CRC_flag=0;
            for(t=2;t<Rx1_temp_num-2;t++){//8-2
                CRC_val+=Rx1_buff[t];
                if(t==Rx1_temp_num-3) CRC_val=CRC_val & 0xff;//
            } 
            if(Rx1_buff[t]==CRC_val){
                Urat_CRC_Correct_flag=1;                    //
                // OK
                //USART1_SendStr("OK\r\n");
                printf("OK\r\n");
            }
            else{
//                Uart_CRC_Error_flag=0;                      //
                //
                printf("CRC verify err\r\n");
                //USART1_SendStr("CRC verify err\r\n");
                
                //USART_Cmd(USART1, ENABLE);
                USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
                USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);   
            }
        }
        else{
            //USART_Cmd(USART1, ENABLE);
            USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
            USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
        }
    }
}



#ifdef USART1_FIFO  

/**
  * @brief  USART1_IRQHandler
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
    uint8_t _data;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)// //LL_USART_IsActiveFlag_IDLE
    {
        Rx1_buff[Receive_Count++]= USART1->DR;            //
    }
    else if(USART_GetITStatus(USART1, USART_IT_IDLE) == 1){
        
        _data = USART1->SR;                             //
        _data = USART1->DR;
                       
        //Receive_finish_flag=1;
        if((Rx1_buff[0]==0xfe)&&(Rx1_buff[1]==0xfe)&&(Rx1_buff[Receive_Count-1]==0x16))//                                
        {
            //USART_Cmd(USART1, DISABLE);
            USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
            USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);

            //Rx_Datanum==Rx_Databuff[13]+16;            //
            Rx1_temp_num=Receive_Count;                  
            Receive_Count=0;
//            Communications_flag=1;                      //
            Communications_Process_flag=1;              //
            Uart_CRC_flag=1;                            //
            
//            value_Temp = (int16_t)Rx1_buff[4];
//            value_Temp<<=8;
//            value_Temp|=(int16_t) Rx1_buff[5];
//            if((Rx1_buff[3] &0xA0)== 0xA0)
//                    flash_store_flag=1;                     //
//                else
//                    flash_store_flag=0;
//                info_report_flag =1;
        }
        else{
            Receive_Count=0;
            //
             frame_Error_flag=1;   
        }  
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);     //
}
#endif


/******************* (C) COPYRIGHT 2016 STMicroelectronics *****END OF FILE****/




