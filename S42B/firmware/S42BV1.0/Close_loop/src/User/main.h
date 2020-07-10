#ifndef __MAIN_H__
#define __MAIN_H__


#include "stm32f0xx_ll_iwdg.h"
#include "stm32f0xx_ll_crs.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_dma.h"
#include "stm32f0xx_ll_spi.h"
#include "stm32f0xx_ll_tim.h"
#include "stm32f0xx_ll_usart.h"
#include "stm32f0xx_ll_gpio.h"
#include "math.h"
#include "stdio.h"



#define MISO_Pin LL_GPIO_PIN_6
#define MISO_GPIO_Port GPIOA
#define MOSI_Pin LL_GPIO_PIN_7
#define MOSI_GPIO_Port GPIOA
#define CAL_Pin LL_GPIO_PIN_0
#define CAL_GPIO_Port GPIOA
#define CLOSE_Pin LL_GPIO_PIN_1
#define CLOSE_GPIO_Port GPIOA
#define SET2_Pin LL_GPIO_PIN_2
#define SET2_GPIO_Port GPIOA
#define SET1_Pin LL_GPIO_PIN_3
#define SET1_GPIO_Port GPIOA
#define CLKIN_Pin LL_GPIO_PIN_0
#define CLKIN_GPIO_Port GPIOB
#define CLKIN_EXTI_IRQn EXTI0_1_IRQn
#define DIRIN_Pin LL_GPIO_PIN_1
#define DIRIN_GPIO_Port GPIOB
#define DIRIN_EXTI_IRQn EXTI0_1_IRQn
#define ENIN_Pin LL_GPIO_PIN_2
#define ENIN_GPIO_Port GPIOB
#define ENIN_EXTI_IRQn EXTI2_3_IRQn
#define LED_Pin LL_GPIO_PIN_11  
#define LED_GPIO_Port GPIOB
#define PWM1_Pin LL_GPIO_PIN_4
#define PWM1_GPIO_Port GPIOB
#define PWM2_Pin LL_GPIO_PIN_5
#define PWM2_GPIO_Port GPIOB
#define IN1_Pin LL_GPIO_PIN_6
#define IN1_GPIO_Port GPIOB
#define IN2_Pin LL_GPIO_PIN_7
#define IN2_GPIO_Port GPIOB
#define IN3_Pin LL_GPIO_PIN_8
#define IN3_GPIO_Port GPIOB
#define IN4_Pin LL_GPIO_PIN_9
#define IN4_GPIO_Port GPIOB
#define NSS_Pin LL_GPIO_PIN_4
#define NSS_GPIO_Port GPIOA

#define KEY_Select_Pin          LL_GPIO_PIN_15      //
#define KEY_Select_GPIO_Port    GPIOA               
#define KEY_Back_Pin            LL_GPIO_PIN_11      //
#define KEY_Back_GPIO_Port      GPIOA  
#define KEY_Confirm_Pin         LL_GPIO_PIN_8       //
#define KEY_Confirm_GPIO_Port    GPIOA 

//------------------------------			   
#define OLED_CS_Pin             LL_GPIO_PIN_12		//
#define OLED_CS_GPIO_Port       GPIOB
#define OLED_RST_Pin            LL_GPIO_PIN_13 		//
#define OLED_RST_GPIO_Port      GPIOC
#define OLED_RS_Pin             LL_GPIO_PIN_13		//
#define OLED_RS_GPIO_Port       GPIOB

#define OLED_SCLK_Pin           LL_GPIO_PIN_15		//
#define OLED_SCLK_GPIO_Port     GPIOB
#define OLED_SDIN_Pin           LL_GPIO_PIN_14	    //
#define OLED_SDIN_GPIO_Port     GPIOB


#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif



#define CAL     LL_GPIO_IsInputPinSet(CAL_GPIO_Port,  CAL_Pin) 
#define CLOSE   LL_GPIO_IsInputPinSet(CLOSE_GPIO_Port, CLOSE_Pin) 
#define SET1    LL_GPIO_IsInputPinSet(SET1_GPIO_Port, SET1_Pin) 
#define SET2    LL_GPIO_IsInputPinSet(SET2_GPIO_Port, SET2_Pin)
#define ENIN    LL_GPIO_IsInputPinSet(ENIN_GPIO_Port, ENIN_Pin)
#define DIRIN   LL_GPIO_IsInputPinSet(DIRIN_GPIO_Port,DIRIN_Pin)

/**************Key_Pin************************/

#define KEY_Select      LL_GPIO_IsInputPinSet(KEY_Select_GPIO_Port,KEY_Select_Pin)
#define KEY_Back        LL_GPIO_IsInputPinSet(KEY_Back_GPIO_Port,KEY_Back_Pin)
#define KEY_Confirm     LL_GPIO_IsInputPinSet(KEY_Confirm_GPIO_Port,KEY_Confirm_Pin)

#define LED_H     LL_GPIO_SetOutputPin(LED_GPIO_Port, LED_Pin)  
#define LED_L     LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin) 
#define LED_F     LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin)
#define IN1_HIGH  LL_GPIO_SetOutputPin(IN1_GPIO_Port, IN1_Pin) 
#define IN1_LOW   LL_GPIO_ResetOutputPin(IN1_GPIO_Port, IN1_Pin)
#define IN2_HIGH  LL_GPIO_SetOutputPin(IN2_GPIO_Port, IN2_Pin) 
#define IN2_LOW   LL_GPIO_ResetOutputPin(IN2_GPIO_Port, IN2_Pin)
#define IN3_HIGH  LL_GPIO_SetOutputPin(IN3_GPIO_Port, IN3_Pin) 
#define IN3_LOW   LL_GPIO_ResetOutputPin(IN3_GPIO_Port, IN3_Pin)
#define IN4_HIGH  LL_GPIO_SetOutputPin(IN4_GPIO_Port, IN4_Pin) 
#define IN4_LOW   LL_GPIO_ResetOutputPin(IN4_GPIO_Port, IN4_Pin)

#define NSS_H   LL_GPIO_SetOutputPin(NSS_GPIO_Port, NSS_Pin)  
#define NSS_L   LL_GPIO_ResetOutputPin(NSS_GPIO_Port, NSS_Pin) 

#define SPI_TX_OD  LL_GPIO_SetPinOutputType(MOSI_GPIO_Port, MOSI_Pin, LL_GPIO_OUTPUT_OPENDRAIN)
#define SPI_TX_PP  LL_GPIO_SetPinOutputType(MOSI_GPIO_Port, MOSI_Pin, LL_GPIO_OUTPUT_PUSHPULL)

/*******************OLED output Defined****************************/
#define OLED_CS_H       LL_GPIO_SetOutputPin(OLED_CS_GPIO_Port, OLED_CS_Pin)  		//
#define OLED_CS_L       LL_GPIO_ResetOutputPin(OLED_CS_GPIO_Port, OLED_CS_Pin)

#define OLED_RST_H      LL_GPIO_SetOutputPin(OLED_RST_GPIO_Port,OLED_RST_Pin) 		//
#define OLED_RST_L      LL_GPIO_ResetOutputPin(OLED_RST_GPIO_Port,OLED_RST_Pin) 	//

#define OLED_RS_H       LL_GPIO_SetOutputPin(OLED_RS_GPIO_Port,OLED_RS_Pin)		//
#define OLED_RS_L       LL_GPIO_ResetOutputPin(OLED_RS_GPIO_Port,OLED_RS_Pin)		//

#define OLED_SCLK_H     LL_GPIO_SetOutputPin(OLED_SCLK_GPIO_Port,OLED_SCLK_Pin)		//
#define OLED_SCLK_L     LL_GPIO_ResetOutputPin(OLED_SCLK_GPIO_Port,OLED_SCLK_Pin)		//

#define OLED_SDIN_H     LL_GPIO_SetOutputPin(OLED_SDIN_GPIO_Port,OLED_SDIN_Pin)	    //
#define OLED_SDIN_L     LL_GPIO_ResetOutputPin(OLED_SDIN_GPIO_Port,OLED_SDIN_Pin)		//


/* SPI command for TLE5012 */
#define READ_STATUS				0x8001			//8000
#define READ_ANGLE_VALUE		0x8021			//8020
#define READ_SPEED_VALUE		0x8031			//8030

#define WRITE_MOD1_VALUE		0x5060			//0_1010_0_000110_0001
#define MOD1_VALUE	0x0001

#define WRITE_MOD2_VALUE		0x5080			//0_1010_0_001000_0001
#define MOD2_VALUE	0x0800

#define WRITE_MOD3_VALUE		0x5091			//0_1010_0_001001_0001
#define MOD3_VALUE	0x0000

#define WRITE_MOD4_VALUE		0x50E0			//0_1010_0_001110_0001
#define MOD4_VALUE	0x0098						//9bit 512

#define WRITE_IFAB_VALUE		0x50B1
#define IFAB_VALUE 0x000D
/* Functionality mode */
#define REFERESH_ANGLE		0

#define UMAXCL   62    //
#define UMAXOP   160    //
#define UMAXSUM  25600  //


extern int16_t kp;     
extern int16_t ki;
extern int16_t kd;

extern const uint8_t LPFA; 
extern const uint8_t LPFB;


extern int32_t s;
extern int32_t s_1;
extern int32_t s_sum;
extern int32_t r;   
extern int32_t r_1;   
extern uint8_t dir; 
extern int16_t y;   
extern int16_t y_1;
extern int32_t yw;  
extern int32_t yw_1;
extern int16_t advance;
extern int32_t wrap_count; 
extern int32_t e;  
extern int32_t iterm;
extern int32_t dterm;
extern int16_t u;     
extern int32_t stepnumber;
extern uint8_t stepangle;

extern uint16_t hccount;
extern uint8_t closemode;
extern uint8_t enmode;

extern uint8_t Currents;          //800ma
extern uint8_t Microstep;            //4->4096
extern uint8_t Motor_Dir;                  //

extern volatile uint8_t Menu_update_flag;      //
extern volatile uint8_t Data_update_flag;  
extern volatile uint16_t Data_update_Count;
extern uint8_t Menu_Num ;             //
extern uint8_t Menu_Num_item;         //
extern uint8_t Menu_move_num;         //

extern uint8_t CalibrateEncoder_finish_flag; //
extern uint8_t Second_Calibrate_flag; //
extern uint8_t Second_Menu;           //
extern uint8_t Menu_Num2_item;        //  
extern uint8_t Menu_Num3_item;        //
extern uint8_t Menu_Num4_item;        //
extern uint8_t Menu_Num5_item;        // 
extern uint8_t Menu_Num6_item;        // 
extern uint8_t Calibration_flag;      //
extern int16_t Motor_speed ;
extern int16_t wap1;
extern int16_t wap2;
extern uint8_t Motor_speed_flag;

extern volatile uint8_t flash_store_flag;
extern uint16_t table1[14];                    //

extern uint8_t Rx1_buff[8];
extern uint8_t Receive_Count;
extern uint8_t Rx1_temp_num;                       
extern uint8_t Receive_finish_flag;          //
extern volatile uint8_t  Communications_Process_flag;     //
extern volatile uint8_t  Uart_CRC_flag;                   //  
extern volatile uint8_t  frame_Error_flag;                //
extern volatile uint8_t  Urat_CRC_Correct_flag;           //
extern int16_t value_Temp;
extern uint8_t Currents_Set;
extern uint8_t Microstep_Set;            //4->4096

extern uint8_t Dir_Enable;           //
extern uint8_t Motor_Dir;                  //
extern uint8_t Motor_Enable;               //
extern uint8_t Motor_mode;              //
extern volatile uint8_t Motor_ENmode_flag; //
extern volatile uint8_t enter1_once_flag ;    //
extern volatile uint8_t enter2_once_flag ;
extern volatile uint8_t dir1_once_flag ;      //
extern volatile uint8_t dir2_once_flag ;
extern volatile uint8_t close_loop1_flag ;      //
extern volatile uint8_t close_loop2_flag ;

extern void Output(int32_t theta,uint8_t effort);
extern uint16_t ReadValue(uint16_t RegValue);
extern uint16_t ReadAngle(void);


#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif 
