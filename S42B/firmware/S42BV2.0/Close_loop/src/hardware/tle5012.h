#ifndef __TLE5012_H
#define __TLE5012_H


#include "mydef.h"

#define SPI_TX_OFF   {GPIOA->CRL&=0x0FFFFFFF;GPIOA->CRL|=0x40000000;}
#define SPI_TX_ON    {GPIOA->CRL&=0x0FFFFFFF;GPIOA->CRL|=0xB0000000;}   

#define	TLE012_CS   PAout(4) //	

#define CAL         PAin(15)
#define CLOSE       PBin(3)
#define SET1        PBin(10)
#define SET2        PBin(11)

#define IN1         PBout(6)
#define IN2         PBout(7)
#define IN3         PBout(8)
#define IN4         PBout(9)

#define IN1_HIGH    true
#define IN2_HIGH    true
#define IN3_HIGH    true
#define IN4_HIGH    true
    
#define IN1_LOW     false
#define IN2_LOW     false
#define IN3_LOW     false
#define IN4_LOW     false
    
void tle5012b_init(void);
void Motor_init(void);
void SetModeCheck(void);
void Output(int32_t theta,uint8_t effort);
int16_t Mod(int32_t xMod,int16_t mMod);
void OneStep(void);
int fputc(int c,FILE *stream); 
int fgetc(FILE *stream); 
void SerialCheck(void);
uint16_t ReadValue(uint16_t RegValue);
void WriteValue(uint16_t RegAdd,uint16_t RegValue);
uint16_t ReadState(void);
uint16_t ReadAngle(void);
void CalibrateEncoder(void);




#endif

