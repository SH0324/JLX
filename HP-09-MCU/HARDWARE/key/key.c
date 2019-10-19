#include "key.h"
#include "pwm.h"         //����PWM����
#include "timer.h"       //����ʱ��ṹ
#include "wdt.h"
#include "control_user.h"

KEY_STATUS_e		KeyMode  = KEY_FREE;
KEY_STATUS_e		KeyLight = KEY_FREE;
KEY_STATUS_e		KeyTimer = KEY_FREE;


Flag_s xdata Flag={0,0,0,0,0,0,0,0};  //��ֵ



/************************************************************
 * ������	:	Key_Scan
 * ����˵��	:	����ɨ��
 *
 * �������	:	��
 * �������	:	��
 *
 * �޸ļ�¼	:	������������һ�α༭
 * ��������	:	SJ0324
 * ����		:	2017-7-30
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
    
	//Mode���̰�
	if((KEY_ModeDown_Counter_Old < KEYHOLD_TIME) && (KEY_ModeDown_Counter_Old > KEYDOWN_TIME))
	{
        KeyMode = KEY_DOWN;
	}
	//Mode������
	else if(KEY_ModeDown_Counter >= KEYHOLD_TIME)
	{
        Flag.Power = 0;
        Flag.Timer = 0;
        
	}
	//Light���̰�
	if((KEY_LightDown_Counter_Old < KEYHOLD_TIME) && (KEY_LightDown_Counter_Old > KEYDOWN_TIME))
	{
        KeyLight = KEY_DOWN;
	}
	//Timer���̰�
	if((KEY_TimerDown_Counter_Old < KEYHOLD_TIME) && (KEY_TimerDown_Counter_Old > KEYDOWN_TIME))
	{
        KeyTimer = KEY_DOWN;
	}
	//Timer������
	else if(KEY_TimerDown_Counter >= KEYHOLD_TIME)
	{
         Flag.Timer = 0;
         TR0  = 0;
	}
}

void main_loop(void)
{
    if(KeyMode == KEY_DOWN)   //ģʽ������
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
    if(KeyLight == KEY_DOWN)  //���ȼ�����
    {
        KeyLight = KEY_FREE;
        Update_light();
        Flag.Update = 1;
        
    }
    if(KeyTimer == KEY_DOWN)  //��ʱ�䰴��
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
    if(Flag.Power)  //�����Ż�ȡ
    {
        Assignment();      //��ȡPWMֵ
    }
    if(!Flag.Power)         //�ػ���0PWM
    {
        TR0  = 0;
        Timer.Sec  = 0;
        Timer.mSec = 0;
        Flag.Timer = 0;
        LED_C_DutyDat = 0;
        LED_W_DutyDat = 0;
        Flag.Update = 1; 
    }
    PWM_Update();      //����PWM
    

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
