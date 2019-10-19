#include "led.h"
#include "pwm.h"
#include "key.h"

PWM_DATA_s xdata PWM_DATA_Table = {1,800,800,800};

void LED_Init(void)
{
    
    GPIO_Init(P50F,P50_PWM0_SETTING);  //B蓝色
    GPIO_Init(P51F,P51_PWM1_SETTING);  //C冷色
    GPIO_Init(P52F,P52_PWM2_SETTING);  //W暖色
    
    PWM_init(PWM_CH0,Edge_Align,CKS_SYS,Toggle_Off,0,Complementary_Off);
    PWM_CfgDivDuty(PWM_CH0,PWM_div,PWM_off);
    
    PWM_init(PWM_CH1,Edge_Align,CKS_SYS,Toggle_Off,0,Complementary_Off);
    PWM_CfgDivDuty(PWM_CH1,PWM_div,PWM_off);
    
    PWM_init(PWM_CH2,Edge_Align,CKS_SYS,Toggle_Off,0,Complementary_Off);
    PWM_CfgDivDuty(PWM_CH2,PWM_div,PWM_off);
    
    PWM_EnContrl(PWM_CH0);
    PWM_EnContrl(PWM_CH1);
    PWM_EnContrl(PWM_CH2);

    GPIO_Init(P61F,PD_EN|OUTPUT);
    P61(0);
}

void LED_Dimming(void)  //无极调光
{
    if(Flag.Dir)      //方向
    {   switch(Flag.LedMode)  
        {
        	case 1:
            {
                if(PWM_DATA_Table.W > PWM_typ) PWM_DATA_Table.W--;
                if(PWM_DATA_Table.W > PWM_min) PWM_DATA_Table.W--;
            }
        		break;
        	case 2:
            {
                if(PWM_DATA_Table.C > PWM_typ) PWM_DATA_Table.C--;
                if(PWM_DATA_Table.C > PWM_min) PWM_DATA_Table.C--;
            }
        		break;
            case 3:
            {
                if(PWM_DATA_Table.B > PWM_typ) PWM_DATA_Table.B--;
                if(PWM_DATA_Table.B > PWM_min) PWM_DATA_Table.B--;
            }
        		break;
        	default:
        		break;
        }
    }
    else
    {
        switch(Flag.LedMode)  
        {
        	case 1:
            {
                if((PWM_DATA_Table.W > PWM_typ)&(PWM_DATA_Table.W < PWM_div)) 
                    PWM_DATA_Table.W++;
                if(PWM_DATA_Table.W < PWM_div) PWM_DATA_Table.W++;
            }
        		break;
        	case 2:
            {
                if((PWM_DATA_Table.C > PWM_typ)&(PWM_DATA_Table.C < PWM_div)) 
                    PWM_DATA_Table.C++;
                if(PWM_DATA_Table.C < PWM_div) PWM_DATA_Table.C++;
            }
        		break;
            case 3:
            {
                if((PWM_DATA_Table.B > PWM_typ)&(PWM_DATA_Table.B < PWM_div)) 
                    PWM_DATA_Table.B++;
                if(PWM_DATA_Table.B < PWM_div) PWM_DATA_Table.B++;
            }
        		break;
        	default:
        		break;
        }   
    }
    
    Flag.Update = 1;
}

void PWM_Set(void)  //更新PWM数据
{
    if(Flag.Update)
    {
        Flag.Update = 0;
        switch(Flag.LedMode)  
        {
        	case 1:
            {
                PWM_CfgDuty(PWM_CH0,PWM_off);
                PWM_CfgDuty(PWM_CH1,PWM_off);
                PWM_CfgDuty(PWM_CH2,PWM_DATA_Table.W);
            }
        		break;
        	case 2:
            {
                PWM_CfgDuty(PWM_CH0,PWM_off);
                PWM_CfgDuty(PWM_CH1,PWM_DATA_Table.C);
                PWM_CfgDuty(PWM_CH2,PWM_off);
            }
        		break;
            case 3:
            {
                PWM_CfgDuty(PWM_CH0,PWM_DATA_Table.B);
                PWM_CfgDuty(PWM_CH1,PWM_off);
                PWM_CfgDuty(PWM_CH2,PWM_off);
            }
        		break;
        	default:
            {
                PWM_CfgDuty(PWM_CH0,PWM_off);
                PWM_CfgDuty(PWM_CH1,PWM_off);
                PWM_CfgDuty(PWM_CH2,PWM_off);
            }
        		break;
        }   
    }
}
