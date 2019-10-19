#include "conturol_user.h"

#include "system_clock.h"
#include "pwm.h"
#include "delay.h"

#include "ts_configuration.h"
#include "ts_def.h"
#include "ts_api.h"
#include "ts_service.h"


Flag_s xdata Flag = {0,1,0,0,0,1,0};  //初值
TIMER_s  xdata Timer = {0,0,0};
PWM_DATA_s xdata PWM_DATA_Table = {100,500,1000,0,0};

void LED_Init(void)
{
    GPIO_Init(P30F,PU_EN|OUTPUT);
    GPIO_Init(P31F,PU_EN|OUTPUT);
    GPIO_Init(P00F,PU_EN|OUTPUT);
    GPIO_Init(P01F,PU_EN|OUTPUT);
    GPIO_Init(P02F,PU_EN|OUTPUT);
    GPIO_Init(P03F,PU_EN|OUTPUT);
    
    GPIO_Init(P06F,PU_EN|OUTPUT);
    
    GPIO_Init(P34F,P34_PWM3_SETTING);
    PWM_init(PWM_CH3,Edge_Align,1,Toggle_Off,0,0);
    PWM_CfgDivDuty(PWM_CH3,1000,0);
    PWM_Update(PWM_CH3);
    WaitPWMUpdateComplete();
    PWM_EnContrl(PWM_CH3);
    
    
//    GPIO_Init(P07F,PD_EN|OUTPUT);
}

//void Timer_Init(void)
//{
//    TMOD = 0x01;   //定时器016位模式
//    TH0  = TH_VAL; //初值
//    TL0  = TL_VAL;
//    ET0  = 1;      //关T0中断
//    PT0  = 0;       //设置定时器0中断优先级为低优先级
//    TR0  = 0;      //不启动，定时开始再启动
//    

//}

void LED_Display(void)
{
    if(Flag.Timer > 5)
    {
        D1 = 1;
        D2 = 1;
        D3 = 1;
        D4 = 1;
        D5 = 1;
        D6 = 1;
    }
    else if(Flag.Timer > 4)
    {
        D1 = 1;
        D2 = 1;
        D3 = 1;
        D4 = 1;
        D5 = 1;
        D6 = 0;
    }
    else if(Flag.Timer > 3)
    {
        D1 = 1;
        D2 = 1;
        D3 = 1;
        D4 = 1;
        D5 = 0;
        D6 = 0;
    }
    else if(Flag.Timer > 2)
    {
        D1 = 1;
        D2 = 1;
        D3 = 1;
        D4 = 0;
        D5 = 0;
        D6 = 0;
    }
    else if(Flag.Timer > 1)
    {
        D1 = 1;
        D2 = 1;
        D3 = 0;
        D4 = 0;
        D5 = 0;
        D6 = 0;
    }
    else if(Flag.Timer > 0)
    {
        D1 = 1;
        D2 = 0;
        D3 = 0;
        D4 = 0;
        D5 = 0;
        D6 = 0;
    }
    else if(Flag.Timer == 0)
    {
        D1 = 0;
        D2 = 0;
        D3 = 0;
        D4 = 0;
        D5 = 0;
        D6 = 0;
    }
}


void PWM_Set(void)  //更新PWM数据
{
    if(Flag.Update)
    {
        Flag.Update = 0;
        PWM_CfgDivDuty(PWM_CH3,PWM_div,PWM_DATA_Table.LED_DutyDat);
        PWM_Update(PWM_CH3);
        WaitPWMUpdateComplete();
    }
}

void Adj_light(void)   //无极亮度
{
    if(Flag.Light == 0)      PWM_DATA_Table.Adj = PWM_DATA_Table.Light0;
    else if(Flag.Light == 1) PWM_DATA_Table.Adj = PWM_DATA_Table.Light1;
    else if(Flag.Light == 2) PWM_DATA_Table.Adj = PWM_DATA_Table.Light2;

    Flag.Light = 6;
}

void Assignment(void)   //赋值
{
    switch (Flag.Light)
    {
        case 0:
        {
           PWM_DATA_Table.LED_DutyDat = PWM_DATA_Table.Light0;
        }
            break;
        case 1:
        {
            PWM_DATA_Table.LED_DutyDat = PWM_DATA_Table.Light1;
        }
            break;
        case 2:
        {
           PWM_DATA_Table.LED_DutyDat = PWM_DATA_Table.Light2;
        }
            break;
        case 3:
        {
            Flag.Power = 0;
        }
            break;
        case 6:
        {
            PWM_DATA_Table.LED_DutyDat = PWM_DATA_Table.Adj;
        }
            break;
    } 
}

void LED_Dimming(void)  //无极调光
{
    if(Flag.Dir)      //方向
    {   
        if(PWM_DATA_Table.Adj > PWM_typ) PWM_DATA_Table.Adj--;
        if(PWM_DATA_Table.Adj > PWM_min) PWM_DATA_Table.Adj--;
    }
    else
    {
        if((PWM_DATA_Table.Adj > PWM_typ)&(PWM_DATA_Table.Adj < PWM_div)) 
            PWM_DATA_Table.Adj++;
        if(PWM_DATA_Table.Adj < PWM_div) PWM_DATA_Table.Adj++;
        
    }
    
    Flag.Update = 1;
}



void main_loop(void)
{
    static unsigned int k = 0;
    
    if(TS_Key != 0)
    {
        switch(TS_Key)
        {
            //电源按键消息
            case K1:                                   //K1短按产生的按键消息	
               {
                 Flag.Power ^= 1;  
                 Adj_light();
                 if(Flag.Power)
                 {
                     PWM_DATA_Table.LED_DutyDat = 50;
                     do
                    {
                        if((PWM_DATA_Table.LED_DutyDat > PWM_typ)&(PWM_DATA_Table.LED_DutyDat < PWM_div)) 
                            PWM_DATA_Table.LED_DutyDat++;
                        if(PWM_DATA_Table.LED_DutyDat < PWM_div) PWM_DATA_Table.LED_DutyDat++;
                        if(PWM_DATA_Table.LED_DutyDat > PWM_DATA_Table.Adj)
                        {
                            PWM_DATA_Table.LED_DutyDat = PWM_DATA_Table.Adj;
                        }
                        PWM_CfgDivDuty(PWM_CH3,PWM_div,PWM_DATA_Table.LED_DutyDat);
                        PWM_Update(PWM_CH3);
                        WaitPWMUpdateComplete();
                        Delay_ms(1);
                    }
		            while(PWM_DATA_Table.LED_DutyDat != PWM_DATA_Table.Adj);
                 }
                 else
                 {
                     do
                    {
                        if(PWM_DATA_Table.LED_DutyDat > PWM_typ) PWM_DATA_Table.LED_DutyDat--;
                        if(PWM_DATA_Table.LED_DutyDat > 0) PWM_DATA_Table.LED_DutyDat--;
                        if(PWM_DATA_Table.LED_DutyDat <= 0)
                        {
                            PWM_DATA_Table.LED_DutyDat = 0;
                        }
                        PWM_CfgDivDuty(PWM_CH3,PWM_div,PWM_DATA_Table.LED_DutyDat);
                        PWM_Update(PWM_CH3);
                        WaitPWMUpdateComplete();
                        Delay_ms(1);
                    }
		            while(PWM_DATA_Table.LED_DutyDat != 0);
                 }
               }             		
                break;
            //60min按键消息
            case K2:Flag.Timer1 = 6;				    //K2短按产生的按键消息
                break;
            case (K2|KEY_LONG_START):Flag.Timer1 = 0;	//K2长按开始产生的消息（长按约1秒时产生）
                break;
            //50min按键消息
            case K3:Flag.Timer1 = 5;
                break;
            case (K3|KEY_LONG_START):Flag.Timer1 = 0;
                break;
            //40min按键消息
            case K4:Flag.Timer1 = 4;
                break;
            case (K4|KEY_LONG_START):Flag.Timer1 = 0;
                break;
            //30min按键消息
            case K5:Flag.Timer1 = 3;
                break;
            case (K5|KEY_LONG_START):Flag.Timer1 = 0;
                break;
            //20min按键消息
            case K6:Flag.Timer1 = 2;
                break;
            case (K6|KEY_LONG_START):Flag.Timer1 = 0;
                break;
            //10min按键消息
            case K7:Flag.Timer1 = 1;
                break;
            case (K7|KEY_LONG_START):Flag.Timer1 = 0;
                break;
            //Light按键消息
            case (K8|KEY_BREAK):
                {
                    Flag.Light++;
                    if(Flag.Light >= 3) Flag.Light = 0;
                }									
                break;
            case (K8|KEY_LONG_START):	//K8长按开始产生的消息（长按约1秒时产生）
                {   
                    Adj_light();
                    Flag.Dimming  = 1;
                    Flag.Dir     ^= 1;
                }
                break;  
            case (K8|KEY_LONG_BREAK):	//K8长按抬起产生的消息（长按约1秒时产生）
                {
                    Flag.Dimming  = 0;
                }
        }
        if(Flag.Timer1 != Flag.Timer)
        {
            Timer.Sec  = 0;
            Timer.mSec = 0;
        }
//        if(!Flag.Timer1)
//        {
//            TR0  = 0;
//        }
//        else if((Flag.Timer)&&(!TR0))  
//        {
//            TR0  = 1;
//        }
        Flag.Update = 1;
    }
    
    
    if(Flag.Power)  //开机才获取
    { 
        k++;
        if((Flag.Dimming)&&(k >= 150 ))  //无极调光速度
        {
           k = 0;
           LED_Dimming();
        }
        if(!Flag.Dimming)  //无极调光完毕
        {
            Flag.Dimming = 0;
        }
        Assignment();      //获取PWM值
    }
    
    if(!Flag.Power)         //关机清0PWM
    {
        PWM_DATA_Table.LED_DutyDat = 0;   
        Flag.Timer1 = 0;
        Flag.Timer  = 0;
//        TR0  = 0;
    }
    PWM_Set();      //更新PWM
    LED_Display();
}


