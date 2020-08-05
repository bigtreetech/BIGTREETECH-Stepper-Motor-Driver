#ifndef __CAN_H
#define __CAN_H

#include "mydef.h"

//
#define CAN1_RX0_INT_ENABLE	1		//.								    
										 							 				    
uint8_t CAN1_Mode_Init(uint8_t tsjw,uint8_t tbs2,uint8_t tbs1,uint16_t brp,uint8_t mode);//
 
uint8_t CAN1_Send_Msg(uint8_t* msg,uint8_t len);						//

uint8_t CAN1_Receive_Msg(uint8_t *buf);							//






















#endif


