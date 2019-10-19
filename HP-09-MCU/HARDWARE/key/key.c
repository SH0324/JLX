#include "key.h"
#include "pwm.h"         //控制PWM开关
#include "timer.h"       //清零时间结构
#include "wdt.h"
#include "control_user.h"

KEY_STATUS_e		KeyMode  = KEY_FREE;
KEY_STATUS_e		KeyLight = KEY_FREE;
KEY_STATUS_e		KeyTimer = KEY_FREE;


Flag_s xdata Flag={0,0,0,0,0,0,0,0};  //初值



/************************************************************
 * 函数名	:	Key_Scan
 * 功能说明	:	按键扫描
 *
 * 输入参数	:	无
 * 输出参数	:	无
 *
 * 修改记录	:	新增函数，第一次编辑
 * 历次作者	:	SJ0324
 * 日期		:	2017-7-30
*************************************************************/	
void Key_Scan(void)
{
	static unsigned int KEY_ModeDown_Counter = 0,		KEY_LightDown_Counter = 0,		KEY_TimerDown_Counter = 0;
	static unsigned int KEY_ModeDown_Counter_Old = 0,	KEY_LightDown_Counter_Old = 0,	KEY_TimerDown_Counter_Old = 0;
	if(!KEY_Mode)
	{
		_nop_();
		if(!KEY_Mode)
		{
			KEY_ModeDown_Counter++;
		}
	}
	else
	{
		KEY_ModeDown_Counter_Old = KEY_ModeDown_Counter;
		KEY_ModeDown_Counter = 0;
	}
	if(!KEY_Light)
	{
		_nop_();
		if(!KEY_Light)
		{
			KEY_LightDown_Counter++;
		}
	}
	else
	{
		KEY_LightDown_Counter_Old = KEY_LightDown_Counter;
		KEY_LightDown_Counter = 0;
	}
	if(!KEY_Timer)
	{
			_nop_();
		if(!KEY_Timer)
		{
			KEY_TimerDown_Counter++;
		}
	}
	else
	{
		KEY_TimerDown_Counter_Old = KEY_TimerDown_Counter;
		KEY_TimerDown_Counter = 0;
	}
    
	//Mode键短按
	if((KEY_ModeDown_Counter_Old < KEYHOLD_TIME) && (KEY_ModeDown_Counter_Old > KEYDOWN_TIME))
	{
        KeyMode = KEY_DOWN;
	}
	//Mode键长按
	else if(KEY_ModeDown_Counter >= KEYHOLD_TIME)
	{
        Flag.Power = 0;
        Flag.Timer = 0;
        
	}
	//Light键短按
	if((KEY_LightDown_Counter_Old < KEYHOLD_TIME) && (KEY_LightDown_Counter_Old > KEYDOWN_TIME))
	{
        KeyLight = KEY_DOWN;
	}
	//Timer键短按
	if((KEY_TimerDown_Counter_Old < KEYHOLD_TIME) && (KEY_TimerDown_Counter_Old > KEYDOWN_TIME))
	{
        KeyTimer = KEY_DOWN;
	}
	//Timer键长按
	else if(KEY_TimerDown_Counter >= KEYHOLD_TIME)
	{
         Flag.Timer = 0;
         TR0  = 0;
	}
}

void main_loop(void)
{
    if(KeyMode == KEY_DOWN)   //模式键按下
    { 
        KeyMode = KEY_FREE;
        Flag.mode++;
        if(Flag.mode >= 4) Flag.mode = 0;
        if(!Flag.Power)
        {
            Flag.mode   = 0;
            Flag.Power  = 1;  
        }
        Read_light();
        Flag.Update = 1;

    }
    if(KeyLight == KEY_DOWN)  //亮度键按下
    {
        KeyLight = KEY_FREE;
        Update_light();
        Flag.Update = 1;
        
    }
    if(KeyTimer == KEY_DOWN)  //定时间按下
    {
        KeyTimer = KEY_FREE;
        WDT_FeedDog();
        
        if(Flag.Power)
        {
            TR0  = 0;
            Timer.Sec  = 0;
            Timer.mSec = 0;
            Flag.Timer += 30;
            if(Flag.Timer >= 120) Flag.Timer = 0; 
            if(Flag.Timer)  
            {
                TR0  = 1;
            }
           
        }
        Flag.Update = 1;
        
    }
    if(Flag.Power)  //开机才获取
    {
        Assignment();      //获取PWM值
    }
    if(!Flag.Power)         //关机清0PWM
    {
        TR0  = 0;
        Timer.Sec  = 0;
        Timer.mSec = 0;
        Flag.Timer = 0;
        LED_C_DutyDat = 0;
        LED_W_DutyDat = 0;
        Flag.Update = 1; 
    }
    PWM_Update();      //更新PWM
    

    if(Flag.Timer > 60)
    {
        D1 = 0;
        D2 = 0;
        D3 = 0;
    }
    else if(Flag.Timer > 30)
    {
        D1 = 0;
        D2 = 0;
        D3 = 1;
    }
    else if(Flag.Timer > 0)
    {
        D1 = 0;
        D2 = 1;
        D3 = 1;
    }
    else
    {
        D1 = 1;
        D2 = 1;
        D3 = 1;
    }
}
