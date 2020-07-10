
#ifndef __OLED_H
#define __OLED_H 

#include "main.h"



#define OLED_CMD  0	
#define OLED_DATA 1	


void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	

void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);					   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);					

void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);	
void OLED_ShowChar(uint8_t x,uint8_t y,char chr,uint8_t size,uint8_t mode);	
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,const char *p);	 		
  
uint32_t oled_pow(uint8_t m,uint8_t n);
//void OLED_Showword(uint8_t x,uint8_t y,uint8_t *num,uint8_t mode);





























#endif


























