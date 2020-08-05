/**
  ******************************************************************************
  * @file    main.c
  * @author  Vsion yang
  * @version V1.0.0
  * @date    2019.8.5
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
#include "mydef.h"
#include "gpio.h"
#include "usart.h"
#include "oled.h"
//#include "spi.h"
#include "spi1.h"
#include "time.h"
#include "exit.h"
#include "key.h"
#include "can.h"
#include "display.h"
#include "flash.h"
#include "tle5012.h"
#include "iwdg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ENCLOSE_LOOP            //
#define ENCOLSE_LOOP_CONFIG     //
//#define ENFLASH_TEST            // 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//
int16_t kp=30;     
int16_t ki=10;  
int16_t kd=250; 

//
const uint8_t LPFA=125; 
const uint8_t LPFB=3;

int32_t s=0;//
int32_t s_1=0;
int32_t s_sum=0;//
int32_t r=0;//
int32_t r_1=0;
uint8_t dir=1;//
int16_t y=0;//
int16_t y_1=0;
int32_t yw=0;//
int32_t yw_1=0;
int16_t advance=0;//
int32_t wrap_count=0;//
int32_t e=0;//
int32_t iterm=0;//
int32_t dterm=0;//
int16_t u=0;//
int32_t stepnumber=0;//
uint8_t stepangle=0;//

uint16_t hccount=0;//
uint8_t closemode;//
uint8_t enmode=0;//

uint16_t Calibration_flag=0;      //
uint8_t Menu_Num =0;             //
uint8_t Menu_Num_item=0;         //
uint8_t Menu_move_num=0;         //
volatile uint8_t Menu_update_flag=1;      //
volatile uint8_t Data_update_flag =1; //
volatile uint16_t Data_update_Count =0; //

uint8_t CalibrateEncoder_finish_flag=0; //
uint8_t Second_Calibrate_flag=0;        //
uint8_t Second_Menu=0;                  //
uint8_t Menu_Num2_item=0;               //  
uint8_t Menu_Num3_item=0;               //
uint8_t Menu_Num4_item=0;               //  
uint8_t Menu_Num5_item=0;               // 
uint8_t Menu_Num6_item=0;               // 

int16_t Motor_speed =0;
int16_t wap1=0;
int16_t wap2=0;
uint8_t Motor_speed_flag=0; 

uint8_t Currents=0;                 //
uint8_t Currents_Set=0;
uint8_t Microstep_Set=0;            //->
uint8_t Microstep=0;                //->
uint8_t Dir_Enable=0x00;           // 
                                    //!ENABLE = 
                                    //ENABLE = 
uint8_t Motor_Dir=0;               //

uint8_t Motor_Enable=0;            //
uint8_t Motor_mode=0;              // 
volatile uint8_t Motor_ENmode_flag=0; //
volatile uint8_t enter1_once_flag =1;    //
volatile uint8_t enter2_once_flag =0;

volatile uint8_t dir1_once_flag =1;      //
volatile uint8_t dir2_once_flag =0;
volatile uint8_t close_loop1_flag =1;      //
volatile uint8_t close_loop2_flag =0;

volatile uint8_t flash_store_flag=0;    //
uint16_t table1[14];                    //
volatile uint8_t Reset_status_flag=0;                    //

uint8_t Rx1_buff[9];
uint8_t Receive_Count=0;                //    
uint8_t Rx1_temp_num=0;                 //
uint8_t Receive_finish_flag=0;          //

volatile uint8_t  Communications_Process_flag=0;     //
volatile uint8_t  Uart_CRC_flag=0;                   //  
volatile uint8_t  frame_Error_flag=0;                //
volatile uint8_t  Urat_CRC_Correct_flag=0;           //
volatile uint8_t  info_report_flag=0;
//uint8_t Receive_statu=0x00;
volatile int16_t value_Temp=0;
uint8_t Receiv_pluse =0;

/* Private function prototypes -----------------------------------------------*/
uint16_t table[]={'1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','0'};

/* Private functions ---------------------------------------------------------*/
void flash_test(void);
void restart_init(void);
//
//2019-10-21 
//2019-10-22 
//2019-10-23 
//2019-10-28 
//2019-10-29 
//2019-11-02 
//2019-11-04  
//2019-11-07 
//2019-11-11 
//2019-11-15  
//2019-11-18 
//2019-11-19 
//2020-01-03 
//2020-01-16 
//2020-04-20 
//2020-04-29 
 

/**
  * @brief  main program
  * @param  None
  * @retval None
  */
int main(void)
{
	static uint8_t res = 0;
//    static uint8_t key=0,i=1;
//	u16 temp;
    uint8_t canbufTx[]="12345678";
//    uint8_t canbufRx[8]={0};
    
//    uint8_t k3_flag = 0,;
//    uint8_t k4_flag = 0;
//    uint8_t mode=1;//
    
    System_Clock_Init();            //
    delay_init(72);					// 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
	LED_Init();					                    //
	OLED_Init();					                //
    OLED_ShowString(0,0,"Oled Init...OK");
    delay_ms(100);   
    Key_init();                                     //
    
#ifdef ENFLASH_TEST    
    flash_test();                            //flash  
#endif
//    SetModeCheck();                          //
//       while(1);
#ifdef ENCOLSE_LOOP_CONFIG
    OLED_Clear();                             //
    OLED_ShowString(0,0,"Close Loop Model");

    tle5012b_init();            //
    Motor_init();               //
    TIM3_Init();                            //PWM  
    
    FLASH_Unlock();
    Calibration_flag = FlashReadHalfWord(Data_Store_Arrdess);
    FLASH_Lock();
    if((Calibration_flag>>8) == 0xAA){
        OLED_ShowString(0,25,"  Calibration  ");
        OLED_ShowString(40,45,"  OK!");
        delay_ms(500);
        //
        OLED_Clear();   //
        OLED_ShowString(0,2,"Simp:  0000 RPM");//
        OLED_ShowString(0,22," Err:  000.00 ");
        OLED_ShowString(0,42," Deg:  0000.0");
        Menu_Num_item=2;                                        //
        Second_Menu=1;                                          //
        Menu_update_flag=0;                                     //
        Menu_Num=1;                                             //   
        Reset_status_flag=1;                                    //
//        Menu_Num2_item=8;                                       //
        //Motor_Enable = enmode;                                //
/*****************************************************/

        STMFLASH_Read(Data_Store_Arrdess,table1,14);            //
        SetModeCheck();                 //

        Currents=table1[1];             //
        Menu_Num2_item =table1[2];
        
        stepangle=table1[3];             //
        Menu_Num3_item=table1[4];        //
        
        Motor_ENmode_flag =table1[5];    //
        Menu_Num4_item= table1[6];  
        
        Motor_Dir =table1[7];            //
        Menu_Num5_item =table1[8];
        
//        Motor_Dir =table1[9];           //
//        Menu_Num5_item =table1[10];

        kp = table1[11];                //Kp
        ki = table1[12];                //Ki
        kd = table1[13];                //Kd
    }
    else{//
        OLED_ShowString(48,16,"NOT");
        OLED_ShowString(16,32,"Calibration");
        OLED_ShowString(0,48,"Please calibrate");
        delay_ms(500);
        //
        OLED_Clear();
        OLED_ShowString(0,0,"->");

        while(1){
            KeyScan();
            Oled_display();
        }            
    }

    EXTIX_Init();                       //
    NVIC_EnableIRQ(EXTI1_IRQn);         //
    UART_Configuration(USART1, UART1_DEFAULT_BAUDRATE);     //
    CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_5tq,6,CAN_Mode_LoopBack);// 
    res=CAN1_Send_Msg(canbufTx,8);                      //
    delay_ms(100);
    if(res){                                            //
        printf("CAN1 Transport fail!\r\n");
    }
    else{
        printf("CAN1 Transport OK!\r\n");
    }
    TIM2_Cap_Init(0xFFFF,0);          //
    TIM4_Init(7200-1, 0);             //
#endif    
//    IWDG_Init(4,625);                 //
 	while(1) 
    {
    #ifdef ENCLOSE_LOOP 
/**************************************************************/
        if(Motor_ENmode_flag ==1){
            if(ENIN==1) {                            //
                restart_init();                // 
//                Reset_status_flag=0;
//                enmode=1;                
            } 
            else{
                Reset_status_flag++;     //0++
                enmode=0; //
            }    
        }
        if(Motor_ENmode_flag ==0){
            if(ENIN==0){
                restart_init(); //   
//                Reset_status_flag=0;
//                enmode=1;
            }
            else{
                Reset_status_flag++;     //0++
                enmode=0; //
            }
        }
/*******************************************************************/
        if(Reset_status_flag == 1){       //
            enmode=0;
            Reset_status_flag ++;           //1++            
            PID_Cal_value_init();           //
                
            wap1=0;
            wap2=0;
            Data_update_flag=1;//
        }else{
            if(Reset_status_flag>3)
                Reset_status_flag--;
        }
        
        usart_Receive_Process();                        //
        data_Process();
        test_uart();
        
        if(frame_Error_flag){
            frame_Error_flag =0;
            USART1_SendStr("Frame Err!\r\n");   
        }
        if(flash_store_flag ==1){
            flash_store_flag =0;

            //USART_Cmd(USART1, DISABLE);
            USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
            USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);
            
            STMFLASH_Write(Data_Store_Arrdess,table1,14);//
            
            //USART_Cmd(USART1, ENABLE);
            USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
            USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
            
            //Reset_status_flag=1;
            //restart_init();
        }
        KeyScan();                                      //
        Oled_display();                                 //
        Motor_data_dis();                               //
/*************************************************************************************************/
#endif
#if 0
        if(KEY_Select==0){
			delay_ms(10);
			if(KEY_Select==0){
                if(k3_flag == 0){
                    k3_flag =1;
                    led1=!led1;			//
                    res=CAN1_Send_Msg(canbufTx,8);//
                    if(res)
                        printf("CAN1 Transport fail!\r\n");
                    else
                        printf("OK!\r\n");
                }
			}
		}
        else if(KEY_Confirm==0){
			delay_ms(10);
			if(KEY_Confirm==0){
                if(k4_flag == 0){
                    k4_flag =1; 
                    mode=!mode;
                    CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_5tq,6,mode);	//
                     
                    if(mode==0)//
                    {
                        printf("Nnormal Mode \r\n");	    
                    }else //
                    {
                        printf("LoopBack Mode\r\n");
                    }                    
                    led1=1;			//off
                    delay_ms(200);
                    led1=0;			//on
                    delay_ms(200);
                    led1=1;			//off
                    delay_ms(200);
                    led1=0;			//on
                    delay_ms(200);
                }
            }
		}
        else{
            k3_flag = 0;
            k4_flag = 0;
        }
        key=CAN1_Receive_Msg(canbufRx);
		if(key)//
		{	
            printf("CAN Receive: ");	
 			for(i=0;i<key;i++){		
                printf("%x ",canbufRx[i]);
 			}
            printf("\r\n");
		}
        key=0;
#endif
	}
}
//
void restart_init(void)
{
    //
    if(Reset_status_flag !=0 ){
        CLEAR_BIT(TIM2->CR1, TIM_CR1_CEN); 
        PID_Cal_value_init();           //
        SET_BIT(TIM2->CR1, TIM_CR1_CEN);
    }
    enmode=1;
    Reset_status_flag=0;
}
#ifdef ENFLASH_TEST 
void flash_test(void)
{
    static char t=0;
    STMFLASH_Write(Data_Store_Arrdess,table,16);
    delay_ms(10);
    FLASH_Unlock();						//
    STMFLASH_Read(Data_Store_Arrdess,table1,16);
    FLASH_Lock();//
     printf("flash Read: ");	
    for(t=0;t<16;t++){		
        printf("%c ",table1[t]);
    }
    while(1);
}
#endif























/******************* (C) COPYRIGHT 2016 STMicroelectronics *****END OF FILE****/
