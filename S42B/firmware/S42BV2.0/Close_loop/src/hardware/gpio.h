#ifndef __GPIO_H
#define __GPIO_H

#include "mydef.h"


#define led1        PCout(13)
//#define led1        PBout(0)
#define LED_F       led1^=1

#define LED_ON      1
#define LED_OFF     0


void LED_Init(void);





#endif

