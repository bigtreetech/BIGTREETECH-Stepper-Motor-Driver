
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 



uint8_t OLED_GRAM[128][8];


void OLED_Refresh_Gram(void)
{
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    
		OLED_WR_Byte (0x00,OLED_CMD);      
		OLED_WR_Byte (0x10,OLED_CMD);      
		for(n=0;n<128;n++)
		OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}
#if OLED_MODE==1

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



void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{	
	uint8_t i;	
    if(cmd)    
        OLED_RS_H; 
    else 
        OLED_RS_L;
	OLED_CS_L;		  
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_L;
		if(dat&0x80)OLED_SDIN_H;
		else OLED_SDIN_L;
		OLED_SCLK_H;
		dat<<=1;   
	}				 
	OLED_CS_H;		  
	OLED_RS_H;   	  
} 
#endif	     

void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X14,OLED_CMD);  
	OLED_WR_Byte(0XAF,OLED_CMD);  
}
    
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X10,OLED_CMD);  
	OLED_WR_Byte(0XAE,OLED_CMD);  
}		   			 
	  
void OLED_Clear(void)  
{  
	uint8_t i,n;  
	for(i=0;i<8;i++)
	for(n=0;n<128;n++)
	OLED_GRAM[n][i]=0x00;  
	OLED_Refresh_Gram();
}

void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t)
{
	uint8_t pos,bx,temp=0;
	if(x>127||y>63)return;
	pos=7-y/8;		
	bx=y%8;			
	temp=1<<(7-bx);	
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}
	  
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot)  
{  
	uint8_t x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();
}

void OLED_ShowChar(uint8_t x,uint8_t y,char chr,uint8_t size,uint8_t mode)
{      			    
	uint8_t temp,t,t1;
	uint8_t y0=y;
	chr=chr-' ';			   
    for(t=0;t<size;t++)
    {   
		if(size==16)//temp=oled_asc2_1206[chr][t];  
		//else
		 temp=oled_asc2_1608[chr][t];		                           
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
	OLED_Refresh_Gram();	
}

uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//
//x,y :	 
//len :
//size:
//mode:	0,;1,
//num:(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
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

void OLED_ShowString(uint8_t x,uint8_t y,const char *p)
{
#define MAX_CHAR_POSX 120
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

/*
void OLED_Showword(uint8_t x,uint8_t y,uint8_t *num,uint8_t mode)
{
	uint8_t t,t1,t2;
	uint8_t temp;
	uint8_t y0=y;
//	t=*num;
	for(t=0;t<50;t++)	
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
						x++;			
						if(x>=127) return;	
						break;				
					}
				}
			}//
		
		}
	}	
		OLED_Refresh_Gram();
}
*/

//SSD1306					    
void OLED_Init(void)
{ 	 
    
	OLED_RST_L;			  		//
	LL_mDelay(100);
	OLED_RST_H; 
	OLED_WR_Byte(0xAE,OLED_CMD);//
	OLED_WR_Byte(0xD5,OLED_CMD);//,
	OLED_WR_Byte(80,OLED_CMD);  //
	OLED_WR_Byte(0xA8,OLED_CMD);//
	OLED_WR_Byte(0X3F,OLED_CMD);//(1/64) 
	OLED_WR_Byte(0xD3,OLED_CMD);//
	OLED_WR_Byte(0X00,OLED_CMD);//

	OLED_WR_Byte(0x40,OLED_CMD);// [5:0]
												    
	OLED_WR_Byte(0x8D,OLED_CMD);//
	OLED_WR_Byte(0x14,OLED_CMD);//bit2，
	OLED_WR_Byte(0x20,OLED_CMD);//
	OLED_WR_Byte(0x02,OLED_CMD);//[1:0],;;1
	OLED_WR_Byte(0xA1,OLED_CMD);//,bit0:0,0->0;1,0->127;
	OLED_WR_Byte(0xC0,OLED_CMD);//;bit3[N-;N:
	OLED_WR_Byte(0xDA,OLED_CMD);//
	OLED_WR_Byte(0x12,OLED_CMD);//[5:4]
		 
	OLED_WR_Byte(0x81,OLED_CMD);//
	OLED_WR_Byte(0xEF,OLED_CMD);//1~255; 
	OLED_WR_Byte(0xD9,OLED_CMD);//
	OLED_WR_Byte(0xf1,OLED_CMD);//[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB,OLED_CMD);// 
	OLED_WR_Byte(0x30,OLED_CMD);//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	OLED_WR_Byte(0xA4,OLED_CMD);//;bit0:1,;0,
	OLED_WR_Byte(0xA6,OLED_CMD);//;bit0:1,;0,	    						   
	OLED_WR_Byte(0xAF,OLED_CMD);//
	LL_mDelay(100);
	OLED_Clear();
}  





























