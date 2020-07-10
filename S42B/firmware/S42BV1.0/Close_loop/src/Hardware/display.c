#include "display.h"
#include "oled.h"



void Oled_display(void)
{
/*******************************************************************************/
    if(Menu_update_flag == 1){
        Menu_update_flag =0;
//                OLED_Clear();                   //
        switch(Menu_Num){//界面切换
            case 0:                             //Setting menu 
                    switch(Menu_Num_item){      //
                        case 0:OLED_ShowString(0,0,"->");
                            OLED_ShowString(0,16,"  ");
                        break;
                        case 1:OLED_ShowString(0,0,"  ");
                            OLED_ShowString(0,16,"->");
                        break ;
                        default:OLED_ShowString(0,0,"->");break ;//
                    }
                    if(Calibration_flag!=0xAA){                     //
                        OLED_ShowString(16,0,"Calibration");
                        OLED_ShowString(16,16,"Exit");
                    }
                    else if(Second_Menu==1){                                           //
                            switch(Menu_Num_item){
                                case 2: OLED_ShowString(16,0," Calibrate");
                                        OLED_ShowString(16,16," Motor mA ");
                                        OLED_ShowString(16,32," Microstep");
                                        OLED_ShowString(16,48," EnablePin");
                                break;
                                case 3:
                                        OLED_ShowString(16,0," Motor mA ");
                                        OLED_ShowString(16,16," Microstep");
                                        OLED_ShowString(16,32," EnablePin");
                                        OLED_ShowString(16,48," DirPin   ");
                                break ;
                                case 4:
                                        OLED_ShowString(16,0," Microstep");
                                        OLED_ShowString(16,16," EnablePin");
                                        OLED_ShowString(16,32," DirPin   ");
                                        OLED_ShowString(16,48," Exit     ");
                                break ;
                                case 5:
                                            OLED_ShowString(16,0," EnablePin");
                                            OLED_ShowString(16,16," DirPin   ");
                                            OLED_ShowString(16,32," Exit     ");
                                            OLED_ShowString(16,48,"          ");
                                break ;
                                case 6:
                                            OLED_ShowString(16,0," DirPin   ");
                                            OLED_ShowString(16,16," Exit     ");
                                            OLED_ShowString(16,32,"          ");
//                                            OLED_ShowString(16,48,"           ");
                                break ;
                                case 7:
                                            OLED_ShowString(16,0," Exit     ");
//                                            OLED_ShowString(16,48,"           ");
//                                            OLED_ShowString(16,32,"           ");
                                            OLED_ShowString(16,16,"           ");
                                break ;
//                                case 5:
//                                        OLED_ShowString(16,0," EnablePin");
//                                        OLED_ShowString(16,16," DirPin   ");
//                                        OLED_ShowString(16,32," MotorMode");
//                                        OLED_ShowString(16,48," Exit     ");
//                                break ;
//                                case 6:
//                                        OLED_ShowString(16,0," DirPin   ");
//                                        OLED_ShowString(16,16," MotorMode");
//                                        OLED_ShowString(16,32," Exit     ");
//                                        OLED_ShowString(16,48,"           ");
//                                break ;
//                                case 7:
//                                        OLED_ShowString(16,0," MotorMode");
//                                        OLED_ShowString(16,16," Exit     ");
//                                        OLED_ShowString(16,32,"           ");
//                                       // OLED_ShowString(16,16,"        ");
//                                break ;
//                                case 8:
//                                        OLED_ShowString(16,0," Exit     ");
////                                            OLED_ShowString(16,48,"           ");
////                                            OLED_ShowString(16,32,"           ");
//                                        OLED_ShowString(16,16,"        ");
//                                break ;
                                default :break ;
                            }
                        }
                    else if(Second_Menu == 2){
                        switch(Menu_Num2_item){
                                case 0: OLED_ShowString(16,0,"0   ");//Currents
                                        OLED_ShowString(16,16,"100");
                                        OLED_ShowString(16,32,"200");
                                        OLED_ShowString(16,48,"300");
                                        //
                                        Currents_Set=0;//12.890625//0.077575
                                break;
                                case 1: Currents_Set=8;
                                        OLED_ShowString(16,0,"100");
                                        OLED_ShowString(16,16,"200");
                                        OLED_ShowString(16,32,"300");
                                        OLED_ShowString(16,48,"400");//
                                break ;
                                case 2:Currents_Set=16;
                                        OLED_ShowString(16,0,"200");
                                        OLED_ShowString(16,16,"300");
                                        OLED_ShowString(16,32,"400");
                                        OLED_ShowString(16,48,"500");
                                break ;
                                case 3:Currents_Set=24;
                                        OLED_ShowString(16,0,"300");
                                        OLED_ShowString(16,16,"400");
                                        OLED_ShowString(16,32,"500");
                                        OLED_ShowString(16,48,"600");
                                break ;
                                case 4:Currents_Set=32;
                                        OLED_ShowString(16,0,"400");
                                        OLED_ShowString(16,16,"500");
                                        OLED_ShowString(16,32,"600");
                                        OLED_ShowString(16,48,"700");
                                break ;
                                case 5:Currents_Set=40;
                                        OLED_ShowString(16,0,"500");
                                        OLED_ShowString(16,16,"600");
                                        OLED_ShowString(16,32,"700");
                                        OLED_ShowString(16,48,"800");
                                break ;
                                case 6:Currents_Set=48;
                                        OLED_ShowString(16,0,"600");
                                        OLED_ShowString(16,16,"700");
                                        OLED_ShowString(16,32,"800");
                                        OLED_ShowString(16,48,"900");
                                break ;
                                case 7:Currents_Set=56;
                                        OLED_ShowString(16,0,"700");
                                        OLED_ShowString(16,16,"800");
                                        OLED_ShowString(16,32,"900");
                                        OLED_ShowString(16,48,"1000");
                                break ;
                                case 8:Currents_Set=64;
                                        OLED_ShowString(16,0,"800");
                                        OLED_ShowString(16,16,"900");
                                        OLED_ShowString(16,32,"1000");
                                        OLED_ShowString(16,48,"1100");
                                break ;
                                case 9:Currents_Set=72;
                                        OLED_ShowString(16,0,"900");
                                        OLED_ShowString(16,16,"1000");
                                        OLED_ShowString(16,32,"1100");
                                        OLED_ShowString(16,48,"1200");
                                break ;
                                case 10:Currents_Set=80;
                                        OLED_ShowString(16,0,"1000");
                                        OLED_ShowString(16,16,"1100");
                                        OLED_ShowString(16,32,"1200");
                                        OLED_ShowString(16,48,"1300");
                                break ;
                                case 11:Currents_Set=88;
                                        OLED_ShowString(16,0,"1100");
                                        OLED_ShowString(16,16,"1200");
                                        OLED_ShowString(16,32,"1300");
                                        OLED_ShowString(16,48,"1400");
                                break ;
                                case 12:Currents_Set=96;
                                        OLED_ShowString(16,0,"1200");
                                        OLED_ShowString(16,16,"1300");
                                        OLED_ShowString(16,32,"1400");
                                        OLED_ShowString(16,48,"1500");
                                break ;
                                case 13:Currents_Set=104;
                                        OLED_ShowString(16,0,"1300");
                                        OLED_ShowString(16,16,"1400");
                                        OLED_ShowString(16,32,"1500");
                                        OLED_ShowString(16,48,"1600");
                                break ;
                                case 14:Currents_Set=112;
                                        OLED_ShowString(16,0,"1400");
                                        OLED_ShowString(16,16,"1500");
                                        OLED_ShowString(16,32,"1600");
                                        OLED_ShowString(16,48,"1700");
                                break ;
                                case 15:Currents_Set=120;
                                        OLED_ShowString(16,0,"1500");
                                        OLED_ShowString(16,16,"1600");
                                        OLED_ShowString(16,32,"1700");
                                        OLED_ShowString(16,48,"1800");
                                break ;
                                case 16:Currents_Set=128;
                                        OLED_ShowString(16,0,"1600");
                                        OLED_ShowString(16,16,"1700");
                                        OLED_ShowString(16,32,"1800");
                                        OLED_ShowString(16,48,"1900");
                                break ;
                                case 17:Currents_Set=136;
                                        OLED_ShowString(16,0,"1700");
                                        OLED_ShowString(16,16,"1800");
                                        OLED_ShowString(16,32,"1900");
                                        OLED_ShowString(16,48,"2000");
                                break ;
                                case 18:Currents_Set=144;
                                        OLED_ShowString(16,0,"1800");
                                        OLED_ShowString(16,16,"1900");
                                        OLED_ShowString(16,32,"2000");
                                        OLED_ShowString(16,48,"2100");
                                break ;
                                case 19:Currents_Set=152;
                                        OLED_ShowString(16,0,"1900");
                                        OLED_ShowString(16,16,"2000");
                                        OLED_ShowString(16,32,"2100");
                                        OLED_ShowString(16,48,"2200");
                                break ;
                                case 20:Currents_Set=160;
                                        OLED_ShowString(16,0,"2000");
                                        OLED_ShowString(16,16,"2100");
                                        OLED_ShowString(16,32,"2200");
                                        OLED_ShowString(16,48,"2300");
                                break ;
                                case 21:Currents_Set=168;
                                        OLED_ShowString(16,0,"2100");
                                        OLED_ShowString(16,16,"2200");
                                        OLED_ShowString(16,32,"2300");
                                        OLED_ShowString(16,48,"2400");
                                break ;
                                case 22:Currents_Set=176;
                                        OLED_ShowString(16,0,"2200");
                                        OLED_ShowString(16,16,"2300");
                                        OLED_ShowString(16,32,"2400");
                                        OLED_ShowString(16,48,"2500");
                                break ;
                                case 23:Currents_Set=184;
                                        OLED_ShowString(16,0,"2300");
                                        OLED_ShowString(16,16,"2400");
                                        OLED_ShowString(16,32,"2500");
                                        OLED_ShowString(16,48,"2600");
                                break ;
                                case 24:Currents_Set=192;
                                        OLED_ShowString(16,0,"2400");
                                        OLED_ShowString(16,16,"2500");
                                        OLED_ShowString(16,32,"2600");
                                        OLED_ShowString(16,48,"2700");
                                break ;
                                case 25:Currents_Set=200;
                                        OLED_ShowString(16,0,"2500");
                                        OLED_ShowString(16,16,"2600");
                                        OLED_ShowString(16,32,"2700");
                                        OLED_ShowString(16,48,"2800");
                                break ;
                                case 26:Currents_Set=208;
                                        OLED_ShowString(16,0,"2600");
                                        OLED_ShowString(16,16,"2700");
                                        OLED_ShowString(16,32,"2800");
                                        OLED_ShowString(16,48,"2900");
                                break ;
                                case 27:Currents_Set=216;
                                        OLED_ShowString(16,0,"2700");
                                        OLED_ShowString(16,16,"2800");
                                        OLED_ShowString(16,32,"2900");
                                        OLED_ShowString(16,48,"3000");
                                break ;
                                case 28:Currents_Set=224;
                                        OLED_ShowString(16,0,"2800");
                                        OLED_ShowString(16,16,"2900");
                                        OLED_ShowString(16,32,"3000");
                                        OLED_ShowString(16,48,"3100");
                                break ;
                                case 29:Currents_Set=232;
                                        OLED_ShowString(16,0,"2900");
                                        OLED_ShowString(16,16,"3000");
                                        OLED_ShowString(16,32,"3100");
                                        OLED_ShowString(16,48,"3200");
                                break ;
                                case 30:Currents_Set=240;
                                        OLED_ShowString(16,0,"3000");
                                        OLED_ShowString(16,16,"3100");
                                        OLED_ShowString(16,32,"3200");
                                        OLED_ShowString(16,48,"3300");
                                break ;
                                case 31:Currents_Set=248;
                                        OLED_ShowString(16,0,"3100");
                                        OLED_ShowString(16,16,"3200");
                                        OLED_ShowString(16,32,"3300");
                                        OLED_ShowString(16,48,"    ");
                                break ;
                                case 32:Currents_Set=255;
                                        OLED_ShowString(16,0,"3200");
                                        OLED_ShowString(16,16,"3300");
                                        OLED_ShowString(16,32,"    ");
//                                                OLED_ShowString(16,48,"1400");
                                break ;
                                case 33:Currents_Set=255;
                                        OLED_ShowString(16,0,"3300");
                                        OLED_ShowString(16,16,"    ");
//                                                OLED_ShowString(16,32,"1300");
//                                                OLED_ShowString(16,48,"1400");
                                break ;
                            default :break ;
                            }
                    }
                    else if(Second_Menu == 3){                      //Gear
                        switch(Menu_Num3_item){
                            case 0: Microstep_Set=32;                 //
                                    OLED_ShowString(16,0,"2 ");      
                                    OLED_ShowString(16,16,"4");
                                    OLED_ShowString(16,32,"8");
                                    OLED_ShowString(16,48,"16");
                            break;
                            case 1:Microstep_Set=16;
                                   OLED_ShowString(16,0,"4");
                                   OLED_ShowString(16,16,"8");
                                   OLED_ShowString(16,32,"16");
                                   OLED_ShowString(16,48,"32"); 
                            break;
                            case 2: Microstep_Set=8;
                                    OLED_ShowString(16,0,"8");
                                    OLED_ShowString(16,16,"16");
                                    OLED_ShowString(16,32,"32");
                                    OLED_ShowString(16,48,"  ");
                                break;
                            case 3: Microstep_Set=4;
                                    OLED_ShowString(16,0,"16");
                                    OLED_ShowString(16,16,"32");
                                    OLED_ShowString(16,32,"  ");
                                break;
                            case 4: Microstep_Set= 2;
                                    OLED_ShowString(16,0,"32");
                                    OLED_ShowString(16,16,"  ");
                                break;
//                            case 5: Microstep_Set= 1;
//                                    OLED_ShowString(16,0,"64");
//                                    OLED_ShowString(16,16,"  ");
//                                break;
                            default :break ;
                        }
                    }
                    else if(Second_Menu == 4){                              //enable
                        switch(Menu_Num4_item){
                            case 0: //这里要理清逻辑，使能信号已主板的使能信号为准
//                                    if( enter2_once_flag==1){             //
 //                                       enter2_once_flag =0;
 //                                       enter1_once_flag=1;
//                                        if(enmode!=0)//1
                                            Dir_Enable= 0x55;
//                                        else 
//                                            Dir_Enable=0xaa;
//                                    }
                                    OLED_ShowString(16,0,"Enable ");
                                    OLED_ShowString(16,16,"!Enable");
                                break;
                            case 1: 
//                                    if( enter1_once_flag==1 ){                         
//                                                             
//                                        enter1_once_flag=0;
//                                        enter2_once_flag=1;
//                                        if(ENIN == 0)
                                            Dir_Enable= 0xaa;                                   //
//                                        else
//                                            Dir_Enable= 0x55;    
//                                    }
                                    OLED_ShowString(16,0,"!Enable");
                                    OLED_ShowString(16,16,"       ");
                                break;
                            default :break ;
                        }
                    }
                    else if(Second_Menu == 5){                              //dir
                        switch(Menu_Num5_item){
                            case 0: if(dir2_once_flag ==1 ){
                                        dir2_once_flag=0;
                                        dir1_once_flag=1;
                                        Dir_Enable =0x11;
                                    }
                                    OLED_ShowString(16,0,"Hight CW ");
                                    OLED_ShowString(16,16,"Hight CCW");
                                break;
                            case 1: if(dir1_once_flag == 1){//
                                        dir1_once_flag=0;
                                        dir2_once_flag=1;
                                        Dir_Enable =0x22;
                                    }
                                    OLED_ShowString(16,0,"Hight CCW");
                                    OLED_ShowString(16,16,"         ");
                                break;
                            default :break ;
                        }
                    }
//                    else if(Second_Menu == 6){                              //
//                        switch(Menu_Num6_item){
//                            case 0: 
////                                    if(close_loop2_flag ==1 ){
////                                        close_loop2_flag=0;
////                                        close_loop1_flag=1;
//                                        Dir_Enable =0x33;
////                                    }
//                                    OLED_ShowString(16,0,"Loop Close");
//                                    OLED_ShowString(16,16,"Loop Open ");
//                                break;
//                            case 1: 
////                                if(close_loop1_flag == 1){//初始默认是
////                                        close_loop1_flag=0;
////                                        close_loop2_flag=1;
//                                        Dir_Enable =0x44;
////                                    }
//                                    OLED_ShowString(16,0,"Loop Open ");
//                                    OLED_ShowString(16,16,"         ");
//                                break;
//                            default :break ;
//                        }
//                    }
                    /***********************P、I、D ********************************/
                    
            break;
            case 1:OLED_ShowString(0,2,"Simp:  0000 RPM");//
                   OLED_ShowString(0,22," Err:  000.00 ");
                   OLED_ShowString(0,42," Deg:  0000.0");
            break;
            default:break ;
        }
    }
}
//
void Motor_data_dis(void)
{
    uint8_t temp[17]={0};
    //int32_t deg_temp=0;
    static int32_t e_temp=0;
    static uint16_t e_a=0,e_b=0;
    
    if(Data_update_flag ==1 && Menu_Num==1){
        Data_update_flag=0;
/*************SIMP*****************************************************/
        Motor_speed = wap2-wap1;//
        if(Motor_speed>=0)temp[8]=' ';
        else{
            temp[8]='-';
            Motor_speed = ~Motor_speed ;
            Motor_speed+=1;
        }
        Motor_speed=Motor_speed*60;//
        temp[0]=Motor_speed/1000;
        temp[1]=Motor_speed%1000/100;
        temp[2]=Motor_speed%100/10;
        temp[3]=Motor_speed%10;
/*************ERR*************************************************/
        if(e>=0){
            temp[4]=' ';
            e_temp=e;
        }else{
            temp[4]='-';
            e_temp=-e;
        }
        e_temp=e_temp*0.021972*100;
        e_a =e_temp/100;                    //
        e_b =e_temp%100;                    //
        //e_b =(e_temp -e_a) *100;        //
   
        temp[5]=e_a/100;
        temp[6]=e_a%100/10;
        temp[7]=e_a%10;
//        temp[8]='.';
        temp[9]=e_b/10;
        temp[10]=e_b%10;
/*************Deg***************************************************/
        if(yw>=0){
            temp[12]=' ';
            e_temp= yw;
        }else{
            temp[12]='-';
            e_temp=-yw;
        }
        e_temp=e_temp*360*10/16384; //
        e_a =e_temp/10;                    //
        e_b =e_temp%10;                    //
        temp[13]=e_a/1000;
        temp[14]=e_a%1000/100;
        temp[15]=e_a%100/10;
        temp[16]=e_a%10;
//        temp[8]='.';
        temp[11]=e_b%10;
/**********显示*****************************************************/ 
        OLED_ShowChar( 48, 2, temp[8], 16, 1);
        OLED_ShowChar( 56, 2, '0'+temp[0], 16, 1);
        OLED_ShowChar( 64, 2, '0'+temp[1], 16, 1);
        OLED_ShowChar( 72, 2, '0'+temp[2], 16, 1);
        OLED_ShowChar( 80, 2, '0'+temp[3], 16, 1);
        
        OLED_ShowChar( 48, 22, temp[4], 16, 1);
        OLED_ShowChar( 56, 22, '0'+temp[5], 16, 1);
        OLED_ShowChar( 64, 22, '0'+temp[6], 16, 1);
        OLED_ShowChar( 72, 22, '0'+temp[7], 16, 1);
//        OLED_ShowChar( 80, 22, temp[8], 16, 1);
        OLED_ShowChar( 88, 22, '0'+temp[9], 16, 1);
        OLED_ShowChar( 96, 22, '0'+temp[10], 16, 1);
        
        OLED_ShowChar( 48, 42, temp[12], 16, 1);
        OLED_ShowChar( 56, 42, '0'+temp[13], 16, 1);
        OLED_ShowChar( 64, 42, '0'+temp[14], 16, 1);
        OLED_ShowChar( 72, 42, '0'+temp[15], 16, 1);
        OLED_ShowChar( 80, 42, '0'+temp[16], 16, 1);
//        OLED_ShowChar( 88, 42, temp[8], 16, 1);
        OLED_ShowChar( 96, 42, '0'+temp[11], 16, 1);
    }
}























