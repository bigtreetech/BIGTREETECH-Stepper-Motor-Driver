/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H

/**
  ******************************************************************************
  * @file    uart.h
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

#include "mydef.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//USART Define 
#define USART1_FIFO      


#ifdef  USART1_FIFO
// UARTx default baudrate
    #define UART1_DEFAULT_BAUDRATE		38400
// UARTx gpio interfaces
    #define UART1_TX_GPIO_PORT			GPIOA
    #define UART1_TX_GPIO_PIN			GPIO_Pin_9
    #define UART1_RX_GPIO_PORT			GPIOA
    #define UART1_RX_GPIO_PIN			GPIO_Pin_10
#endif 


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void System_NVIC_Priority_Configurate(uint8_t chx, uint8_t pre, uint8_t sub);
void UART_BaudRate_Settings(USART_TypeDef * USARTx, uint32_t baudrate);
void UART_Configuration(USART_TypeDef * USARTx, uint32_t baudrate);


void USART1_IRQHandler(void);


/* Private functions ---------------------------------------------------------*/



void usart_init(u32 pclk2,u32 bound);//
void usart_putchar(u8 ch);//
void PID_Cal_value_init(void);
void usart_Receive_Process(void);
void USART1_SendStr(char *str);
void data_Process(void);
void test_uart (void );
#endif

 // __UART_H
/******************* (C) COPYRIGHT 2016 STMicroelectronics *****END OF FILE****/
