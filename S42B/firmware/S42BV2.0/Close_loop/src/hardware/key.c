#include "key.h"
#include "gpio.h"
#include "oled.h"
#include "tle5012.h"

uint8_t KEY_Select_flag=0;       //
uint8_t KEY_Back_flag=0;         //
uint8_t KEY_Confirm_flag=0;      //

uint8_t Enter_exit_flag =0;      //
uint8_t enter_num=0; 


void Key_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	//
    
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 //
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //
     GPIO_Init(GPIOB, &GPIO_InitStructure);					 //
    
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //
     GPIO_Init(GPIOA, &GPIO_InitStructure);					 //

}


void Key_test(void)
{
    if(KEY_Select == 0){
        delay_ms(10);
        if(KEY_Select==0){
           if(KEY_Select_flag ==0){//
                KEY_Select_flag=1;
                 led1 = !led1;  
            } 
        }
    }else if(KEY_Back == 0){
            delay_ms(10);
            if(KEY_Back==0){
                if(KEY_Back_flag ==0){//
                KEY_Back_flag=1;
                 led1 = !led1;  
            } 
        }
    }else if(KEY_Confirm == 0){
        delay_ms(10);
        if(KEY_Confirm==0){
           if(KEY_Confirm_flag ==0){//
                KEY_Confirm_flag=1;
                 led1 = !led1;  
            } 
        }
    }else
    {
        KEY_Select_flag=0;       //
        KEY_Back_flag=0;         //
        KEY_Confirm_flag=0;
    }
    
}

//
void KeyScan(void)
{
    if(KEY_Select == 0){        //
        delay_ms(10);
        if(KEY_Select == 0){
            if(Menu_Num ==0){//
                if(KEY_Select_flag ==0){//
                    KEY_Select_flag=1;
                    Menu_update_flag=1;                 //
                    
                    if((Calibration_flag>>8)!=0xAA){         //
                        Menu_Num_item++;                //
                        if(Menu_Num_item>1)             //
                            Menu_Num_item=0;
                    }
                    else if(Second_Menu==1){
                            Menu_Num_item++;                //
                            if(Menu_Num_item>MENU_NUM){            //
                                Menu_Num_item =2;
                        }
                    }
                    else if(Second_Menu==2){                //
                            Menu_Num2_item++;
                            if(Menu_Num2_item>33)
                                Menu_Num2_item=0;
                    }
                    else if(Second_Menu==3){                //
                            Menu_Num3_item++;
                            if(Menu_Num3_item>4)
                                Menu_Num3_item=0;
                    }
                    else if(Second_Menu==4){                //
                            Menu_Num4_item++;
                            if(Menu_Num4_item>1)
                                Menu_Num4_item=0;
                    }
                    else if(Second_Menu==5){                //
                            Menu_Num5_item++;
                            if(Menu_Num5_item>1)
                                Menu_Num5_item=0;
                    }
//                    else if(Second_Menu==6){                //
//                            Menu_Num6_item++;
//                            if(Menu_Num6_item>1)
//                                Menu_Num6_item=0;
//                    }
                }
            }
        }
    }else if(KEY_Back == 0){
        delay_ms(10);
        if(KEY_Back == 0){
            if(KEY_Back_flag ==0){
                KEY_Back_flag=1;
                Menu_update_flag=1;         //
                OLED_Clear();                   //
                //
                if(Enter_exit_flag == 1){
                    Enter_exit_flag=0;
                    Menu_Num=0;                         //
                    Menu_Num_item=2;                    //
                    Second_Menu=1;
                    //break;
                }else {
                    Menu_Num++;
                    if(Menu_Num >1 ){
                        Menu_Num=0;
                    }
                }
            }
        }
    }else if(KEY_Confirm == 0){
        delay_ms(10);
        if(KEY_Confirm == 0){
            if(KEY_Confirm_flag ==0){
                KEY_Confirm_flag=1;
                switch(Menu_Num){
                    case 0:     
                        switch(Menu_Num_item){                  //
                            case 0:
                                    SetModeCheck();             //
//                                    CalibrateEncoder_finish_flag=1; //
//                                    // 
//                                    flash_store_flag =1;            //
//                                    table1[0] =0xAA;
//                                    Calibration_flag =0xAA;    //
//                                    Second_Menu=1;             // 
//                            
//                                    OLED_Clear();   //
//                                    OLED_ShowString(0,0,"->Calibrate");
//                                    OLED_ShowString(0,16,"  Motor mA");
//                                    OLED_ShowString(0,32,"  Microstep");
//                                    OLED_ShowString(0,48,"  EnablePin");
//                                    Menu_Num_item=2;                                //
                            break;
                            case 1: Enter_exit_flag=1;    //
                                    Menu_Num=1;           //
                                    Menu_update_flag=1;   //
                                    OLED_Clear();         //
                            break ;
                            case 2: 
                                    TIM_Cmd(TIM2,DISABLE);
                                    enmode=0;                       ////
 //                                   NVIC_DisableIRQ(EXTI0_IRQn);
                                    NVIC_DisableIRQ(EXTI1_IRQn);//
                                    Second_Calibrate_flag=1;                        //

                                    SetModeCheck();             //
//                                    NVIC_EnableIRQ(EXTI0_IRQn);
                                    NVIC_EnableIRQ(EXTI1_IRQn);
                                    TIM_Cmd(TIM2,ENABLE);
                                    //enmode=1;                       ////
                                    Second_Menu=1;              //
                                break ;
                            case 3:
                                    OLED_Clear();   //
                                    Menu_update_flag=1;   //
                                    enter_num++;
                                    if(enter_num==1)
                                        Second_Menu=2;        //
                                    if(enter_num==2){
                                        enter_num=0;
                                        Second_Menu=1;
                                        //
                                        //
                                        Currents= Currents_Set;//
                                        flash_store_flag =1;
                                        table1[1]=Currents;
                                        table1[2]=Menu_Num2_item;
                                    }
                                break ;
                            case 4: OLED_Clear();   //
                                    Menu_update_flag=1;   //
                                    enter_num++;
                                    if(enter_num==1)
                                        Second_Menu=3;        //
                                    if(enter_num==2){
                                        enter_num=0;
                                        Second_Menu=1;
                                        enmode =0;                      //
                                        PID_Cal_value_init();           /**/
                                        //Reset_status_flag=0xff;
                                        //
                                        stepangle =Microstep_Set;   //
                                        
                                        flash_store_flag =1;        //
                                        table1[3]=stepangle;        //
                                        table1[4]=Menu_Num3_item;
                                    }
                                break ;
                            case 5: OLED_Clear();   //
                                    Menu_update_flag=1;   //
                                    enter_num++;
                                    if(enter_num==1)
                                        Second_Menu=4;        //
                                    if(enter_num==2){
                                        enter_num=0;
                                        Second_Menu=1;
                                        enmode =0;                          //
                                        PID_Cal_value_init();               //
                                        //
                                        if(Dir_Enable == 0xaa ){
                                            //enmode =1;
                                          Motor_ENmode_flag=0;
                                        }else if(Dir_Enable == 0x55  ){
                                            Motor_ENmode_flag=1;
                                            //enmode =0;
                                        }
                                        if(Dir_Enable==0x55 || Dir_Enable ==0xAA){
                                            Dir_Enable =0;
                                            flash_store_flag =1;//
                                            table1[5]=Motor_ENmode_flag;        //
                                            table1[6]=Menu_Num4_item;
                                            
                                        }
                                    }
                                break ;
                            case 6: OLED_Clear();   //
                                    Menu_update_flag=1;   //
                                    enter_num++;
                                    if(enter_num==1)
                                        Second_Menu=5;        //
                                    if(enter_num==2){
                                        enter_num=0;
                                        Second_Menu=1;
                                        
                                        //
                                        //Dir_Enable  ;
                                        if(Dir_Enable ==0x11){
                                            Motor_Dir =1;
                                        }else if(Dir_Enable == 0x22){
                                            Motor_Dir=0;
                                        }
                                        //if(Dir_Enable ==0x11 || Dir_Enable==0x22){
                                            Dir_Enable=0;
                                        //}
                                        flash_store_flag =1;//
                                        table1[7]=Motor_Dir;                    //
                                        table1[8]=Menu_Num5_item;
                                    }
                                break ;
                                    
//                            case 7:OLED_Clear();   //
//                                    Menu_update_flag=1;   //
//                                    enter_num++;
//                                    if(enter_num==1)
//                                        Second_Menu=6;        //
//                                    if(enter_num==2){
//                                        enter_num=0;
//                                        Second_Menu=1;
//                                        //
//                                        //Dir_Enable  
//                                        if(Dir_Enable ==0x33){
//                                            Motor_mode =0;
//                                            closemode=1;        //
//                                        }else if(Dir_Enable == 0x44){
//                                            Motor_mode=1;
//                                            closemode=0;        //
//                                        }
//                                        
//                                        Dir_Enable=0;
////                                        flash_store_flag =1;        //
////                                        table1[9]=Motor_mode;        //
////                                        table1[10]=Menu_Num6_item;
//                                    }
//                                break ;
                            case 7:Enter_exit_flag=1;    //
                                    Menu_Num=1;           //  
                                    Menu_update_flag=1;   //
                                    OLED_Clear();         //
                                break ;
                            default:break ;
                        }
                    break ;
//                            case 1: Enter_exit_flag=1;    //
//                                
//                            break ;
                }
            }
        }
    }else{
        KEY_Select_flag=0;       //
        KEY_Back_flag=0;         //
        KEY_Confirm_flag=0;
    }
}









