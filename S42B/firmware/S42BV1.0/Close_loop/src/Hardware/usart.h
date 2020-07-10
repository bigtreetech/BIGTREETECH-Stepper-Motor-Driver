#ifndef __USART_H
#define __USART_H


#include "main.h"

void PID_Cal_value_init(void);
void MX_USART1_UART_Init(void);
void usart_Receive_Process(void);
//void SerialCheck(void);
void USART1_IRQHandler(void);
void UART1_SendByte(uint8_t data);
uint8_t UART1_ReceiveByte(void);
void UART1_SendStr(char *str);
void Uart_Data_Conversion(int16_t Conversion_value,uint8_t num);

#endif


