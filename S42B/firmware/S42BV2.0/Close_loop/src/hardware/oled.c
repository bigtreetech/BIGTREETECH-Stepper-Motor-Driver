#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
//#include "gpio.h"
//////////////////////////////////////////////////////////////////////////////////	

//
//
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 		   
u8 OLED_GRAM[128][8];

//		 
void OLED_Refresh_Gram(void)//
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //
		OLED_WR_Byte (0x00,OLED_CMD);      //
		OLED_WR_Byte (0x10,OLED_CMD);      //   
		for(n=0;n<128;n++)
		OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}
#if OLED_MODE==1
//
//dat:
//cmd:/ 0;1;
void OLED_WR_Byte(u8 dat,u8 cmd)
{
	DATAOUT(dat);	    
 	OLED_RS=cmd;
	OLED_CS=0;	   
	OLED_WR=0;	 
	OLED_WR=1;
	OLED_CS=1;	  
	OLED_RS=1;	 
} 	    	    
#else
//
//dat:
//cmd:
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	OLED_RS=cmd; // 
	OLED_CS=0;		  
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK=0;
		if(dat&0x80)OLED_SDIN=1;
		else OLED_SDIN=0;
		OLED_SCLK=1;
		dat<<=1;   
	}				 
	OLED_CS=1;		  
	OLED_RS=1;   	  
} 
#endif	     
//    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET 
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET 
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)
	for(n=0;n<128;n++)
	OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//
}
// 
//x:0~127
//y:0~63
//t:1  0,
///
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//.
	pos=7-y/8;		//
	bx=y%8;			//
	temp=1<<(7-bx);	//
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}
//x1,y1,x2,y2 
//<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,;1,	  
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//
}
//
//x:0~127
//y:0~63
//mode:0,;1,				 
//size: 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	chr=chr-' ';//				   
    for(t=0;t<size;t++)
    {   
		if(size==12)temp=oled_asc2_1206[chr][t];  //
		else temp=oled_asc2_1608[chr][t];		 // 	                          
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    } 
	OLED_Refresh_Gram();//	
}
//m^n
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}
//
//x,y :	 
//len :
//size:
//mode:;1,
//num:(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1;  
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}
} 
//

void OLED_ShowString(u8 x,u8 y,const char *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,16,1);	 
        x+=8;
        p++;
    }  
}	   
//
struct wordtypedef		 //  
{
	u8 Index[2];		  // 	
	u8 Msk[32];				// (16*16/8) 
};
struct wordtypedef word[]={

{{"AA"},{0x02,0x00,0x04,0x00,0x0B,0xFC,0x32,0x02,0xC2,0x22,0x22,0x12,0x13,0xE2,0x08,0x02,0x04,0x0E,0x00,0x00,0x1F,0xF0,0x00,0x02,0x00,0x01,0xFF,0xFE,0x00,0x00,0x00,0x00}},/*"?",0*/
//{{"��"},{0x20,0x08,0x24,0x10,0x22,0x60,0x21,0x80,0x26,0x41,0x39,0x32,0x02,0x04,0x0C,0x18,0xF0,0x60,0x13,0x80,0x10,0x60,0x10,0x18,0x14,0x04,0x18,0x02,0x00,0x01,0x00,0x00}},/*"?",7*/
//{{"ӭ"},{0x02,0x00,0x02,0x02,0x42,0x04,0x33,0xF8,0x00,0x04,0x00,0x02,0x3F,0xF2,0x20,0x22,0x40,0x42,0x00,0x02,0x3F,0xFE,0x20,0x42,0x20,0x22,0x3F,0xC2,0x00,0x02,0x00,0x00}},/*"?",0*/
//{{"��"},{0x02,0x01,0x02,0x01,0x42,0x02,0x22,0x04,0x1A,0x18,0x03,0xE0,0x02,0x00,0xFE,0x00,0x02,0x00,0x03,0xFC,0x0A,0x02,0x12,0x02,0x62,0x02,0x02,0x02,0x02,0x1E,0x00,0x00}},/*"?",1*/
//{{"��"},{0x00,0x00,0x1F,0xF8,0x00,0x00,0x00,0x00,0xFF,0xFF,0x02,0x00,0x04,0x00,0x18,0xFE,0xF0,0x84,0x18,0x84,0x16,0xFC,0x10,0x84,0x10,0x84,0x10,0xFE,0x10,0x00,0x00,0x00}},/*"?",2*/
};

//
//
//
void OLED_Showword(u8 x,u8 y,u8 *num,u8 mode)
{
	u8 t,t1,t2;
	u8 temp;
	u8 y0=y;
//	t=*num;
	for(t=0;t<50;t++)	//
	{
		if((*num==word[t].Index[0])&&(*(num+1)==word[t].Index[1]))//
		{
			for(t1=0;t1<32;t1++)		//
			{
				temp=word[t].Msk[t1];
				for(t2=0;t2<8;t2++)	//
				{
					if(temp&0x80)			//
						OLED_DrawPoint(x,y,1);
					else
						OLED_DrawPoint(x,y,0);
					temp<<=1;
					y++	;				//
//					if(y>=127) {return ;}		//
					if((y-y0)==16)		//
					{
						y=y0;
						x++;			//
						if(x>=127) return;	
						break;				//
					}
				}
			}//
		
		}
	}	
		OLED_Refresh_Gram();//	
}

//SSD1306					    
void OLED_Init(void)
{ 	 

    #if 1
	RCC->APB2ENR|=1<<3;    // 
	RCC->APB2ENR |=1<<2;		//

    GPIOA->CRH &=0XFFFffFF0;	// 
    GPIOA->CRH |=0X00000003;	
    GPIOA->ODR |=1<<8;		    // 	

  	GPIOB->CRH&=0X0000FFFF;//PB 
  	GPIOB->CRH|=0X33330000;	
	GPIOB->ODR|=0xF<<12;
	
	#endif
    #if 0
    	RCC->APB2ENR|=1<<3;    // 
        RCC->APB2ENR |=1<<2;		//

        GPIOB->CRL&=0X00FFFFFF;//PB6,7  
        GPIOB->CRL|=0X33000000;	 

        GPIOB->CRH&=0XFFFFFFF0;//PB8  
        GPIOB->CRH|=0X00000003;	
        GPIOB->ODR|=1<<8;
        
        GPIOA->CRH &=0XFFF00FFF;	//
        GPIOA->CRH |=0X00033000;	
        GPIOA->ODR |=1<<11;		    //	
        
    #endif
									  
	OLED_RST=0;			  		//
	delay_ms(100);
	OLED_RST=1; 
	OLED_WR_Byte(0xAE,OLED_CMD);//
	OLED_WR_Byte(0xD5,OLED_CMD);//
	OLED_WR_Byte(80,OLED_CMD);  //[3:0],;[7:4],
	OLED_WR_Byte(0xA8,OLED_CMD);//
	OLED_WR_Byte(0X3F,OLED_CMD);//(1/64) 
	OLED_WR_Byte(0xD3,OLED_CMD);//
	OLED_WR_Byte(0X00,OLED_CMD);//

	OLED_WR_Byte(0x40,OLED_CMD);// [5:0],.
													    
	OLED_WR_Byte(0x8D,OLED_CMD);//
	OLED_WR_Byte(0x14,OLED_CMD);///
	OLED_WR_Byte(0x20,OLED_CMD);//
	OLED_WR_Byte(0x02,OLED_CMD);//[1:0],;
	OLED_WR_Byte(0xA1,OLED_CMD);//,bit0:0,0->0;1,0->127;
	OLED_WR_Byte(0xC0,OLED_CMD);//;bit3:0,;1, COM[N-1]->COM0;N:
	OLED_WR_Byte(0xDA,OLED_CMD);//
	OLED_WR_Byte(0x12,OLED_CMD);//[5:4]
		 
	OLED_WR_Byte(0x81,OLED_CMD);//
	OLED_WR_Byte(0xEF,OLED_CMD);//1~255; 
	OLED_WR_Byte(0xD9,OLED_CMD);//
	OLED_WR_Byte(0xf1,OLED_CMD);//[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB,OLED_CMD);// 
	OLED_WR_Byte(0x30,OLED_CMD);//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	OLED_WR_Byte(0xA4,OLED_CMD);//;bit0:1,;0,;
	OLED_WR_Byte(0xA6,OLED_CMD);//;bit0:1,;0,	    						   
	OLED_WR_Byte(0xAF,OLED_CMD);//
	delay_ms(100);
	OLED_Clear();
}  





























