#ifndef __TIME_H
#define __TIME_H

#include "mydef.h"



void TIM2_Cap_Init(u16 arr,u16 psc);
void TIM4_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);//	 
//void TIM3_Init(u16 arr,u16 psc);//
void TIM3_Init(void);
void TIM1_Init(uint16_t Arr,uint16_t Psc);//
void SetT1Pwm1(uint16_t Duty);

void TIM_Init(void);
void Pulse_Control(u16 cycle, u16 pulse_num);

#endif





