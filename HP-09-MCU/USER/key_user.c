#include "key_user.h"
#include "control_user.h"
#include "pwm.h"


Flag_s xdata Flag={0,0,0,0,0,0,0,0,0,1,0,0,0};  //初值


void SYS_init(void)  //系统初始化
{
    LED_Init();
    TS_init();	
    EA = 1;
}

void Key_Scan(void)   //按键扫描
{
    TS_Action();
#if SUPPORT_KEY
#if GENERATE_TS_KEY_EN
    if(TS_Key != 0)
    {
        switch(TS_Key)
        {
            //单按键消息
            case (K2|KEY_BREAK):	  //K2短按松手产生的按键消息
            {
                
            }
                break;
            case (K1|KEY_BREAK):      //K1短按松手产生的按键消息
            {
                
            }
                break;
            case (K1|KEY_LONG_START):	//K1长按开始产生的消息（长按约1秒时产生）
            {
                
            }
                break;
            case (K2|KEY_LONG_START):	//K2长按开始产生的消息（长按约1秒时产生）
            {   
                
            }
                break;  
            case (K2|KEY_LONG_BREAK):	//K2长按抬起产生的消息（长按约1秒时产生）
            {
                
            }
        }
    }
#endif
#endif
}

void main_loop(void)
{
    static unsigned char k = 0;
    Key_Scan();     //按键扫描
    if(Flag.Power)  //开机
    {
        if(Flag.Dimming)  //无极调光
        {
            k++;
            if(k >= 60)   //变化时间
            {
                k = 0;
                LED_Dimming();  
            }
        }
        if(!Flag.Dimming)  //无极调光完毕
        {
            Flag.Dimming = 0;
        }
        Assignment();      //获取PWM值
    }
    if(!Flag.Power)         //关机
    {
        LED_C_DutyDat = LED_W_DutyDat = 0;
    }
    PWM_Update();      //更新PWM
}


