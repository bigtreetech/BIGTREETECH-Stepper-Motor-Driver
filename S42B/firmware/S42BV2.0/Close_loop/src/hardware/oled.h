#ifndef __OLED_H
#define __OLED_H

#include "mydef.h"
#include "stdlib.h"

//
//0:
//1:
//#define OLED_MODE 0

//------------------------------			   
#define OLED_CS  PBout(12)		//
#define OLED_RST PAout(8) 		//
#define OLED_RS  PBout(13)		//

//#define OLED_SCLK  PAout(11)		///(D0)
//#define OLED_SDIN  PAout(12)	    ////(D1)
////PC0~7
//#define DATAOUT(x) GPIOC->ODR=(GPIOC->ODR&0xff00)|(x&0x00FF); //
  
// 
#define OLED_SCLK PBout(15)		//(D0)
#define OLED_SDIN PBout(14)		//(D1)
		     
#define OLED_CMD  0	//
#define OLED_DATA 1	//

//
void OLED_WR_Byte(u8 dat,u8 cmd);	//    

void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);							//		   
							   		    
void OLED_Init(void);									//
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);					//

void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);			//
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);	//
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);	//
void OLED_ShowString(u8 x,u8 y,const char *p);	 		//
  
u32 oled_pow(u8 m,u8 n);//
void OLED_Showword(u8 x,u8 y,u8 *num,u8 mode);




#endif
