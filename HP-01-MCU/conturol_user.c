#include "conturol_user.h"

#include "system_clock.h"
#include "pwm.h"
#include "delay.h"

#include "ts_configuration.h"
#include "ts_def.h"
#include "ts_api.h"
#include "ts_service.h"


Flag_s xdata Flag = {0,1,0,0,0,1,0};  //��ֵ
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
//    TMOD = 0x01;   //��ʱ��016λģʽ
//    TH0  = TH_VAL; //��ֵ
//    TL0  = TL_VAL;
//    ET0  = 1;      //��T0�ж�
//    PT0  = 0;       //���ö�ʱ��0�ж����ȼ�Ϊ�����ȼ�
//    TR0  = 0;      //����������ʱ��ʼ������
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


void PWM_Set(void)  //����PWM����
{
    if(Flag.Update)
    {
        Flag.Update = 0;
        PWM_CfgDivDuty(PWM_CH3,PWM_div,PWM_DATA_Table.LED_DutyDat);
        PWM_Update(PWM_CH3);
        WaitPWMUpdateComplete();
    }
}

void Adj_light(void)   //�޼�����
{
    if(Flag.Light == 0)      PWM_DATA_Table.Adj = PWM_DATA_Table.Light0;
    else if(Flag.Light == 1) PWM_DATA_Table.Adj = PWM_DATA_Table.Light1;
    else if(Flag.Light == 2) PWM_DATA_Table.Adj = PWM_DATA_Table.Light2;

    Flag.Light = 6;
}

void Assignment(void)   //��ֵ
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

void LED_Dimming(void)  //�޼�����
{
    if(Flag.Dir)      //����
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
            //��Դ������Ϣ
            case K1:                                   //K1�̰������İ�����Ϣ	
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
            //60min������Ϣ
            case K2:Flag.Timer1 = 6;				    //K2�̰������İ�����Ϣ
                break;
            case (K2|KEY_LONG_START):Flag.Timer1 = 0;	//K2������ʼ��������Ϣ������Լ1��ʱ������
                break;
            //50min������Ϣ
            case K3:Flag.Timer1 = 5;
                break;
            case (K3|KEY_LONG_START):Flag.Timer1 = 0;
                break;
            //40min������Ϣ
            case K4:Flag.Timer1 = 4;
                break;
            case (K4|KEY_LONG_START):Flag.Timer1 = 0;
                break;
            //30min������Ϣ
            case K5:Flag.Timer1 = 3;
                break;
            case (K5|KEY_LONG_START):Flag.Timer1 = 0;
                break;
            //20min������Ϣ
            case K6:Flag.Timer1 = 2;
                break;
            case (K6|KEY_LONG_START):Flag.Timer1 = 0;
                break;
            //10min������Ϣ
            case K7:Flag.Timer1 = 1;
                break;
            case (K7|KEY_LONG_START):Flag.Timer1 = 0;
                break;
            //Light������Ϣ
            case (K8|KEY_BREAK):
                {
                    Flag.Light++;
                    if(Flag.Light >= 3) Flag.Light = 0;
                }									
                break;
            case (K8|KEY_LONG_START):	//K8������ʼ��������Ϣ������Լ1��ʱ������
                {   
                    Adj_light();
                    Flag.Dimming  = 1;
                    Flag.Dir     ^= 1;
                }
                break;  
            case (K8|KEY_LONG_BREAK):	//K8����̧���������Ϣ������Լ1��ʱ������
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
    
    
    if(Flag.Power)  //�����Ż�ȡ
    { 
        k++;
        if((Flag.Dimming)&&(k >= 150 ))  //�޼������ٶ�
        {
           k = 0;
           LED_Dimming();
        }
        if(!Flag.Dimming)  //�޼��������
        {
            Flag.Dimming = 0;
        }
        Assignment();      //��ȡPWMֵ
    }
    
    if(!Flag.Power)         //�ػ���0PWM
    {
        PWM_DATA_Table.LED_DutyDat = 0;   
        Flag.Timer1 = 0;
        Flag.Timer  = 0;
//        TR0  = 0;
    }
    PWM_Set();      //����PWM
    LED_Display();
}


