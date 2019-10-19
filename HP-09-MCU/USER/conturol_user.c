#include "control_user.h"
#include "pwm.h"   //初始化、赋值
#include "key.h"   //状态标志

unsigned int xdata LED_C_DutyDat = 0;  //冷光 Cold
unsigned int xdata LED_W_DutyDat = 0;  //暖光 Warm


PWM_DATA_s xdata PWM_DATA_Table = 
{ 
	//亮度1         亮度2
	{ 462L ,  154L ,246L ,82L},  //模式0  C = W  780 ,  192
    
	{ 250L ,  498L },  //模式1  C  ,W = 0
	{ 250L ,  480L }   //模式2  W  ,C = 0
};

void LED_Init(void) 
{
    PWM4_init(PWMIE_off,CKS_SYS,Toggle_Off,0);  
	PWM5_init(PWMIE_off,CKS_SYS,Toggle_Off,0);
    PWM4_CfgDivDuty(PWM_max,0);
    PWM5_CfgDivDuty(PWM_max,0);

    PWM_Enable(PWM_CH4);     //使能PWM
    PWM_Enable(PWM_CH5);
    GPIO_Init(P04F,P04_PWM4_SETTING);      
	GPIO_Init(P05F,P05_PWM5_SETTING);//PD_EN|OUTPUT|
    
    GPIO_Init(P00F,PU_EN|INPUT);
    GPIO_Init(P01F,PU_EN|INPUT);
    GPIO_Init(P02F,PU_EN|INPUT);

    GPIO_Init(P03F,PU_EN|OUTPUT);
    GPIO_Init(P06F,PU_EN|OUTPUT);
    GPIO_Init(P07F,PU_EN|OUTPUT);
    
    GPIO_Init(P32F,PD_EN|OUTPUT);
    P32 = 0;
}

void Read_light(void)  //读取亮度
{
    if(Flag.mode == 0) 
    {   
        Flag.Light = Flag.Light0;
    }
    else if(Flag.mode == 1) 
    {   
        Flag.Light = Flag.Light1;
    }
    else if(Flag.mode == 2) 
    {   
        Flag.Light = Flag.Light2;
    }
}


void Update_light(void)  //更新亮度
{
    if(Flag.mode == 0) 
    {   
        Flag.Light0 ^= 1;
        Flag.Light   = Flag.Light0;
    }
    else if(Flag.mode == 1) 
    {   
        Flag.Light1 ^= 1;
        Flag.Light   = Flag.Light1;
    }
    else if(Flag.mode == 2) 
    {   
        Flag.Light2 ^= 1;
        Flag.Light   = Flag.Light2;
    }
}

void LED_Off(void)   //关闭全部
{
    PWM4_CfgDivDuty(PWM_max,0);
    PWM5_CfgDivDuty(PWM_max,0);
}
 
void PWM_Update(void)  //更新PWM数据
{
    if(Flag.Update)
    {
        Flag.Update = 0;
        PWM4_CfgDivDuty(PWM_max,LED_C_DutyDat);
        PWM5_CfgDivDuty(PWM_max,LED_W_DutyDat);
        
    }
}

void Assignment(void)   //赋值
{
    switch (Flag.mode)
    {
        case 1:
        {
            PWM_Enable(PWM_CH4);
            PWM_Enable(PWM_CH5);
            if(Flag.Light == 0)
            {
                LED_C_DutyDat = PWM_DATA_Table.Mode0.Light0;
                LED_W_DutyDat = PWM_DATA_Table.Mode0.Light1;
            }
            else
            {
                LED_C_DutyDat = PWM_DATA_Table.Mode0.Light2;
                LED_W_DutyDat = PWM_DATA_Table.Mode0.Light3;
            }
                
        }
            break;
        case 0:
        {
            PWM_Enable(PWM_CH4);
            PWM_Disable(PWM_CH5);
            if(Flag.Light == 0)      LED_C_DutyDat = PWM_DATA_Table.Mode1.Light1;
            else                     LED_C_DutyDat = PWM_DATA_Table.Mode1.Light0;
            LED_W_DutyDat = 0;
        }
            break;
        case 2:
        {
            PWM_Disable(PWM_CH4);
            PWM_Enable(PWM_CH5);
            if(Flag.Light == 0)      LED_W_DutyDat = PWM_DATA_Table.Mode2.Light1;
            else                     LED_W_DutyDat = PWM_DATA_Table.Mode2.Light0;
            LED_C_DutyDat = 0;
        }
            break;
        case 3:
        {
            Flag.Power = 0;

            LED_C_DutyDat = 0;
            LED_W_DutyDat = 0;

            
        }
            break;
    } 
}



