#include "key.h"
#include "conturol_user.h"
#include "uart.h"
#include "rtc.h"
#include "music.h"
#include "lcd.h"
#include "led.h"

#include "ts_configuration.h"
#include "ts_def.h"
#include "ts_api.h"
#include "ts_service.h"

KEY_STATUS_e xdata Key_Alarm1  = KEY_FREE;
KEY_STATUS_e xdata Key_Alarm2  = KEY_FREE;
KEY_STATUS_e xdata Key_Up      = KEY_FREE;
KEY_STATUS_e xdata Key_Down    = KEY_FREE;
KEY_STATUS_e xdata Key_Hour    = KEY_FREE;
KEY_STATUS_e xdata Key_Light   = KEY_FREE;
KEY_STATUS_e xdata Key_Touch   = KEY_FREE;

Flag_s xdata Flag={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //初值

//u8 xdata music_x;

void key_init(void)    //按键IO初始化
{
    GPIO_Init(P27F,INPUT|PU_EN);
    GPIO_Init(P17F,INPUT|PU_EN);
    GPIO_Init(P16F,INPUT|PU_EN);
    GPIO_Init(P44F,INPUT|PU_EN);
    GPIO_Init(P43F,INPUT|PU_EN);
    GPIO_Init(P42F,INPUT|PU_EN);
    GPIO_Init(P40F,INPUT|PU_EN);
}


void Key_Scan(void)   //按键扫描
{
	static unsigned int xdata KEY_Alarm1_Down_Counter = 0,	KEY_Alarm2_Down_Counter = 0,	KEY_Up_Down_Counter = 0,	KEY_Down_Counter = 0,	 KEY_Hour_Down_Counter = 0,    KEY_Light_Down_Counter = 0,    KEY_Touch_Down_Counter = 0;
	static unsigned int xdata KEY_Alarm1_Down_Counter_Old = 0,KEY_Alarm2_Down_Counter_Old = 0,KEY_Up_Down_Counter_Old = 0,KEY_Down_Counter_Old = 0,KEY_Hour_Down_Counter_Old = 0,KEY_Light_Down_Counter_Old = 0,KEY_Touch_Down_Counter_Old = 0;
	
	if(!KEYAlarm1)
	{
		_nop_();
		if(!KEYAlarm1)
		{
			KEY_Alarm1_Down_Counter++;
		}
	}
	else
	{
		KEY_Alarm1_Down_Counter_Old = KEY_Alarm1_Down_Counter;
		KEY_Alarm1_Down_Counter = 0;
	}
	if(!KEYAlarm2)
	{
		_nop_();
		if(!KEYAlarm2)
		{
			KEY_Alarm2_Down_Counter++;
		}
	}
	else
	{
		KEY_Alarm2_Down_Counter_Old = KEY_Alarm2_Down_Counter;
		KEY_Alarm2_Down_Counter = 0;
	}
	if(!KEYUp)
	{
		_nop_();
		if(!KEYUp)
		{
			KEY_Up_Down_Counter++;
		}
	}
	else
	{
		KEY_Up_Down_Counter_Old = KEY_Up_Down_Counter;
		KEY_Up_Down_Counter = 0;
	}
	if(!KEYDown)
	{
		_nop_();
		if(!KEYDown)
		{
			KEY_Down_Counter++;
		}
	}
	else
	{
		KEY_Down_Counter_Old = KEY_Down_Counter;
		KEY_Down_Counter = 0;
	}
	if(!KEYHour)
	{
			_nop_();
		if(!KEYHour)
		{
			KEY_Hour_Down_Counter++;
		}
	}
	else
	{
		KEY_Hour_Down_Counter_Old = KEY_Hour_Down_Counter;
		KEY_Hour_Down_Counter = 0;
	}
	if(!KEYLight)
	{
			_nop_();
		if(!KEYLight)
		{
			KEY_Light_Down_Counter++;
		}
	}
	else
	{
		KEY_Light_Down_Counter_Old = KEY_Light_Down_Counter;
		KEY_Light_Down_Counter = 0;
	}
    if(!KEYTouch)
	{
			_nop_();
		if(!KEYTouch)
		{
			KEY_Touch_Down_Counter++;
		}
	}
	else
	{
		KEY_Touch_Down_Counter_Old = KEY_Touch_Down_Counter;
		KEY_Touch_Down_Counter = 0;
        if(Key_Touch == KEY_HOLD)
        {
            Key_Touch = KEY_HOLD_S;
        }  
	}


	//Alarm1键短按松手
	if((KEY_Alarm1_Down_Counter_Old < KEYHOLD_TIME) && (KEY_Alarm1_Down_Counter_Old > KEYDOWN_TIME))
	{
        Key_Alarm1 = KEY_DOWN;
        if(Flag.SetAlarm1)
		{
			Flag.SetAlarm1++;
            Flag.TimerOut_Counter = 20;
		}
		else
		{
			Flag.Alarm1 ^= 1;
		}
	}
	//Alarm1键长按
	else if(KEY_Alarm1_Down_Counter >= KEYHOLD_TIME)
	{
//        Key_Alarm1 = KEY_HOLD;
        Flag.SetAlarm1 = 1;
        Flag.TimerOut_Counter = 20;
	}

	//Alarm2键短按
	if((KEY_Alarm2_Down_Counter_Old < KEYHOLD_TIME) && (KEY_Alarm2_Down_Counter_Old > KEYDOWN_TIME))
	{
        Key_Alarm2 = KEY_DOWN;
        if(Flag.SetAlarm2)
		{
			Flag.SetAlarm2++;
//            if(Flag.SetAlarm2 == 3)Alarm2_play();
//            if(Flag.SetAlarm2 == 0)music_stop();
            Flag.TimerOut_Counter = 20;
		}
		else
		{
			Flag.Alarm2 ^= 1;
		}
	}
	//Alarm2键长按
	else if(KEY_Alarm2_Down_Counter >= KEYHOLD_TIME)
	{
//        Key_Alarm2 = KEY_HOLD;
        Flag.SetAlarm2 = 1;
        Flag.TimerOut_Counter = 20;
	}

	//Up键短按
	if((KEY_Up_Down_Counter_Old < KEYHOLD_TIME) && (KEY_Up_Down_Counter_Old > KEYDOWN_TIME))
	{
        Key_Up = KEY_DOWN;
        Flag.TimerOut_Counter = 20;
	}
	//Up键长按
	else if(KEY_Up_Down_Counter >= KEYHOLD_TIME)
	{
        Key_Up = KEY_HOLD;
        Flag.TimerOut_Counter = 20; 
	}

	//Down键短按
	if((KEY_Down_Counter_Old < KEYHOLD_TIME) && (KEY_Down_Counter_Old > KEYDOWN_TIME))
	{
        Key_Down = KEY_DOWN;
        Flag.TimerOut_Counter = 20;
	}
	//Down键长按
	else if(KEY_Down_Counter >= KEYHOLD_TIME)
	{
        Key_Down = KEY_HOLD;
        Flag.TimerOut_Counter = 20;
	}

	//Hour键短按
	if((KEY_Hour_Down_Counter_Old < KEYHOLD_TIME) && (KEY_Hour_Down_Counter_Old > KEYDOWN_TIME))
	{
//        Key_Hour = KEY_DOWN;
        if(Flag.SetHour)
		{
			Flag.SetHour++;
            Flag.TimerOut_Counter = 20;
		}
		else
		{
			Flag.Hour12 ^= 1;
		}
		if(Flag.SetHour >= 3)
		{
			Flag.SetHour = 0;
		}       
	}
	//Hour键长按
	else if(KEY_Hour_Down_Counter >= KEYHOLD_TIME)
	{
        Key_Hour = KEY_HOLD;
        Flag.SetHour = 1;
        Flag.TimerOut_Counter = 20;
	}

	//Light键短按
	if((KEY_Light_Down_Counter_Old < KEYHOLD_TIME) && (KEY_Light_Down_Counter_Old > KEYDOWN_TIME))
	{
        Key_Light = KEY_DOWN;
	}
	//Light键长按
//	else if(KEY_Light_Down_Counter >= KEYHOLD_TIME)
//	{
//        Key_Light = KEY_HOLD;
//	}
	//Touch键短按
	if((KEY_Touch_Down_Counter_Old < KEYHOLD_TIME) && (KEY_Touch_Down_Counter_Old > KEYDOWN_TIME))
	{
//        Key_Touch = KEY_DOWN;
        if(Flag.TrueAlarm1|Flag.TrueAlarm2)
        {
            Flag.Alarm_Timer = 0; //关闭闹钟计时
            Flag.TrueAlarm1 = 0;  //清零闹钟运行标志
            Flag.TrueAlarm2 = 0;
            Flag.LedMode = 0;     //关闭LED
            Flag.Update = 1;      //更新LED数据
            Flag.TimerOut = 1;    //停止Music
        }
        else
        {
            Flag.LedMode++;   //切换灯光
            Flag.Update = 1;  //K1短按切换灯光，日出日落下关闭模式
        }
        
	}
    if(KEY_Touch_Down_Counter == KEYHOLD_TIME)    //长按开始
	{
        Flag.Dir ^= 1;  //无极调光方向
	}
    if(KEY_Touch_Down_Counter_Old >= KEYHOLD_TIME)    //长按结束
	{
//        Key_Touch = KEY_HOLD_S;
        Flag.Dimming =0;  //无极调光完毕
	}
	//Touch键长按
	else if(KEY_Touch_Down_Counter >= KEYHOLD_TIME)
	{
        Key_Touch = KEY_HOLD;
        Flag.Dimming = 1;  //开始无极调光
	}
}



void key_processinng(void)     //按键处理
{
//	if(Key_Alarm1 == KEY_DOWN)
//	{
//        Key_Alarm1 = KEY_FREE;
//        
//	}
//	if(Key_Alarm1 == KEY_HOLD)
//	{
//        Key_Alarm1 = KEY_FREE;
//	}
//	if(Key_Alarm2 == KEY_DOWN)
//	{
//        Key_Alarm2 = KEY_FREE;
//        
//	}
//	if(Key_Alarm2 == KEY_HOLD)
//	{
//        Key_Alarm2 = KEY_FREE;
//	}
//	if(Key_Up == KEY_DOWN)
//	{
//        Key_Up = KEY_FREE;
//	}
//	if(Key_Down == KEY_DOWN)
//	{
//        Key_Down = KEY_FREE;	
//	}
//	if(Key_Hour == KEY_DOWN)
//	{
//        Key_Hour = KEY_FREE;		
//	}
//	if(Key_Hour == KEY_HOLD)
//	{
//        Key_Hour = KEY_FREE;
//	}
	if(Key_Light == KEY_DOWN)
	{
		Key_Light = KEY_FREE;
        Flag.HourLight++;
		if(Flag.HourLight >= 3) Flag.HourLight = 0;
        if(Flag.HourLight == 0)      SEG_init(LEN_XOSCL,COM_H,SEG_L,LDRV_7,1);  //数码管亮度100%
        else if(Flag.HourLight == 1) SEG_init(LEN_XOSCL,COM_H,SEG_L,LDRV_1,1);  //数码管亮度30%
        else                         SEG_init(LEN_DISABLE,COM_L,SEG_H,LDRV_7,1); //数码管亮度0%
	}
//	if(Key_Touch == KEY_DOWN)
//	{
//        Key_Touch = KEY_FREE;
//	}  
}
//-------时钟设置-------------------------------------------
void Hour_processinng(void)
{
    while(Flag.SetHour != 0)
    {
        Timer.Hour = RTCH;
        Timer.Min  = RTCM;
        ContinuousAdj();
        sj |= SEG_Sec;
        if(Key_Up == KEY_DOWN)
        {
            Key_Up = KEY_FREE;
            switch(Flag.SetHour)
			{
				case 1: Timer.Hour++; if(Timer.Hour == 24)	Timer.Hour = 0;
						RTC_WriteHour(Timer.Hour);
                        break;
				case 2: Timer.Min++;  if(Timer.Min == 60)	Timer.Min = 0;	
						RTC_WriteMinute(Timer.Min );	
                        break;
				default: 	break;							//其他情况则不作处理
			}
            Flag.Flicker = 1;    //防止数码管调节时不显示
        }
        if(Key_Down == KEY_DOWN)
        {
            Key_Down = KEY_FREE;
            switch(Flag.SetHour)
			{
				case 1: if(Timer.Hour == 0)	Timer.Hour = 24;Timer.Hour--;
						RTC_WriteHour(Timer.Hour); 
                        break;
				case 2: if(Timer.Min == 0)	Timer.Min = 60;	Timer.Min--;
						RTC_WriteMinute(Timer.Min );	
                        break;
				default: 	break;							//其他情况则不作处理
			} 
            Flag.Flicker = 1;   //防止数码管调节时不显示
        } 
        Cache = Timer;//*************************************************************************
        if(Flag.Hour12)    //如果12小时制打开，进行转换显示
        {
            if(Timer.Hour >= 12) sj = (sj & 0xFA)|SEG_PM;
            else                 sj = (sj & 0xFA)|SEG_AM;
            if(Timer.Hour == 0) Cache.Hour = 12;
            if((Timer.Hour <= 12)&&(Timer.Hour >= 1)) Cache.Hour = Timer.Hour;
            if(Timer.Hour >12) Cache.Hour = Timer.Hour-12;
        }
        else
        {
            sj &= 0xFA;       //清零AM,PM
        }
        if(Flag.Flicker && (Flag.SetHour == 1))  //小时闪烁
        {
            if(Cache.Hour >= 10)
            seg_display(SEG0,NUM_TAB[Cache.Hour/10]);
            else
                seg_display(SEG0,DISABLE);
            seg_display(SEG1,NUM_TAB[Cache.Hour%10]);
        }
        else if(Flag.SetHour == 1)
        {
            seg_display(SEG0,DISABLE);
            seg_display(SEG1,DISABLE);
        }
        if(Flag.Flicker && (Flag.SetHour == 2))  //分钟闪烁
        {
            if(Cache.Hour >= 10)
            seg_display(SEG0,NUM_TAB[Cache.Hour/10]);
            else
                seg_display(SEG0,DISABLE);
            seg_display(SEG1,NUM_TAB[Cache.Hour%10]);
            seg_display(SEG2,NUM_TAB[Cache.Min/10]);
            seg_display(SEG3,NUM_TAB[Cache.Min%10]);
        }
        else if(Flag.SetHour == 2)
        {
            seg_display(SEG2,DISABLE);
            seg_display(SEG3,DISABLE);
        }
        seg_display(SEG4,sj);
        Flag.SetUp = 1;
    }
}
//-------闹钟1设置-------------------------------------------
void Alarm1_processinng(void)
{
    while(Flag.SetAlarm1 != 0)
    {
        ContinuousAdj();
        if(Key_Alarm1 == KEY_DOWN)
        {
            Key_Alarm1 = KEY_FREE;
            if(Flag.SetAlarm1 == 3)
                while(MLD_BSY == 0) Alarm1_play();
        }
        if(Key_Up == KEY_DOWN)
        {
            Key_Up = KEY_FREE;
            switch(Flag.SetAlarm1)
			{
				case 1: Alarm1.Hour++; if(Alarm1.Hour == 24) Alarm1.Hour = 0;
                        break;
				case 2: Alarm1.Min++;  if(Alarm1.Min == 60)  Alarm1.Min  = 0;	
                        break;
                case 3: if(Alarm1.Volume != 15) Alarm1.Volume += 3;
						volume_control(Alarm1.Volume);       //写入音量
                        while(MLD_BSY == 0) Alarm1_play();   //等待Music打开                  
                        break;
				default: 	break;							//其他情况则不作处理
			}
            Flag.Flicker = 1;
        }
        if(Key_Down == KEY_DOWN)
        {
            Key_Down = KEY_FREE;
            switch(Flag.SetAlarm1)
			{
				case 1:  if(Alarm1.Hour == 0) Alarm1.Hour = 24; Alarm1.Hour--;
                        break;
				case 2:   if(Alarm1.Min == 0) Alarm1.Min  = 60; Alarm1.Min--;
                        break;
                case 3: if(Alarm1.Volume > 0) Alarm1.Volume -= 3;
						if(Alarm1.Volume == 0) music_stop();
                        else 
                        {
                            volume_control(Alarm1.Volume);
                            while(MLD_BSY == 0) Alarm1_play();
                        }
                        break;
			}
            Flag.Flicker = 1;
        }
        
        Cache = Alarm1;
        
        if(Cache.Min >= 30)
        {
            Cache.Hour++;
            Cache.Min -= 30;
        }
        else Cache.Min += 30;
   
        
        if(Flag.Flicker && (Flag.SetAlarm1 == 1))
        {
            if(Flag.Hour12)
            {
                if(Cache.Hour >= 12) sj = (sj & 0xFA)|SEG_PM;
                else                  sj = (sj & 0xFA)|SEG_AM;
                if(Cache.Hour == 0) Cache.Hour = 12;
                if(Cache.Hour >12) Cache.Hour -= 12;
            }
            else
            {
                sj &= 0xFA;       //清零AM,PM
            }
            if(Cache.Hour >= 10)
            seg_display(SEG0,NUM_TAB[Cache.Hour/10]);
            else
                seg_display(SEG0,DISABLE);
            seg_display(SEG1,NUM_TAB[Cache.Hour%10]);
            seg_display(SEG2,NUM_TAB[Cache.Min/10]);
            seg_display(SEG3,NUM_TAB[Cache.Min%10]); 
        }
        else if(Flag.SetAlarm1 == 1)
        {
            seg_display(SEG0,DISABLE);
            seg_display(SEG1,DISABLE); 
        }
        if(Flag.Flicker && (Flag.SetAlarm1 == 2))
        {
            if(Cache.Hour >= 10)
            seg_display(SEG0,NUM_TAB[Cache.Hour/10]);
            else
                seg_display(SEG0,DISABLE);
            seg_display(SEG1,NUM_TAB[Cache.Hour%10]);
            seg_display(SEG2,NUM_TAB[Cache.Min/10]);
            seg_display(SEG3,NUM_TAB[Cache.Min%10]);  
        }
        else if(Flag.SetAlarm1 == 2)
        {
            seg_display(SEG2,DISABLE);
            seg_display(SEG3,DISABLE); 
        }
        sj |= SEG_Sec;
        if(Flag.SetAlarm1 == 3)
        {
            seg_display(SEG0,0x40);
            if(Cache_Volume[Alarm1.Volume] == 100)
                seg_display(SEG1,NUM_TAB[Cache_Volume[Alarm1.Volume]/100]); 
            else
                seg_display(SEG1,DISABLE); 
            seg_display(SEG2,NUM_TAB[Cache_Volume[Alarm1.Volume]/10%10]);
            seg_display(SEG3,NUM_TAB[Cache_Volume[Alarm1.Volume]%10]); 
            sj &= ~SEG_Sec;
        }
        seg_display(SEG4,sj);
        Flag.Alarm1 = 1;
        Flag.SetUp = 1;
    }
}

//-------闹钟2设置-------------------------------------------
void Alarm2_processinng(void)
{
    while(Flag.SetAlarm2 != 0)
    {
        ContinuousAdj();
        if(Key_Alarm2 == KEY_DOWN)
        {
            Key_Alarm2 = KEY_FREE;
            if(Flag.SetAlarm2 == 3)
                while(MLD_BSY == 0) Alarm2_play();
        }
        if(Key_Up == KEY_DOWN)
        {
            Key_Up = KEY_FREE;
            switch(Flag.SetAlarm2)
			{
				case 1: Alarm2.Hour++; if(Alarm2.Hour == 24) Alarm2.Hour = 0;
                        break;
				case 2: Alarm2.Min++;  if(Alarm2.Min == 60)  Alarm2.Min  = 0;	
                        break;
                case 3: if(Alarm2.Volume != 15) Alarm2.Volume += 3;
						volume_control(Alarm2.Volume);
                        while(MLD_BSY == 0) Alarm2_play();                   
                        break;
				default: 	break;							//其他情况则不作处理
			}
            Flag.Flicker = 1;
        }
        if(Key_Down == KEY_DOWN)
        {
            Key_Down = KEY_FREE;
            switch(Flag.SetAlarm2)
			{
				case 1:  if(Alarm2.Hour == 0) Alarm2.Hour = 24; Alarm2.Hour--;
                        break;
				case 2:   if(Alarm2.Min == 0)  Alarm2.Min  = 60; Alarm2.Min--;
                        break;
                case 3: if(Alarm2.Volume > 0) Alarm2.Volume -= 3;
						if(Alarm2.Volume == 0) music_stop();
                        else 
                        {
                            volume_control(Alarm2.Volume);
                            while(MLD_BSY == 0) Alarm2_play();
                        }
                        break;
				default: 	break;							//其他情况则不作处理
			}
            Flag.Flicker = 1;
        }
        
        Cache = Alarm2;
        
        if(Cache.Min >= 30)
        {
            Cache.Hour++;
            Cache.Min -= 30;
        }
        else Cache.Min += 30;
           
        
        if(Flag.Flicker && (Flag.SetAlarm2 == 1))
        {
            if(Flag.Hour12)
            {
                if(Cache.Hour >= 12) sj = (sj & 0xFA)|SEG_PM;
                else                  sj = (sj & 0xFA)|SEG_AM;
                if(Cache.Hour == 0) Cache.Hour = 12;
                if(Cache.Hour >12) Cache.Hour -= 12;
            }
            else
            {
                sj &= 0xFA;       //清零AM,PM
            }
            if(Cache.Hour >= 10)
            seg_display(SEG0,NUM_TAB[Cache.Hour/10]);
            else
                seg_display(SEG0,DISABLE);
            seg_display(SEG1,NUM_TAB[Cache.Hour%10]);
            seg_display(SEG2,NUM_TAB[Cache.Min/10]);
            seg_display(SEG3,NUM_TAB[Cache.Min%10]);  
        }
        else if(Flag.SetAlarm2 == 1)
        {
            seg_display(SEG0,DISABLE);
            seg_display(SEG1,DISABLE); 
        }
        if(Flag.Flicker && (Flag.SetAlarm2 == 2))
        {
            if(Cache.Hour >= 10)
            seg_display(SEG0,NUM_TAB[Cache.Hour/10]);
            else
                seg_display(SEG0,DISABLE);
            seg_display(SEG1,NUM_TAB[Cache.Hour%10]);
            seg_display(SEG2,NUM_TAB[Cache.Min/10]);
            seg_display(SEG3,NUM_TAB[Cache.Min%10]); 
        }
        else if(Flag.SetAlarm2 == 2)
        {
            seg_display(SEG2,DISABLE);
            seg_display(SEG3,DISABLE); 
        }
        sj |= SEG_Sec;
        if(Flag.SetAlarm2 == 3)
        {
            seg_display(SEG0,0x40);
            if(Cache_Volume[Alarm2.Volume] == 100)
                seg_display(SEG1,NUM_TAB[Cache_Volume[Alarm2.Volume]/100]); 
            else
                seg_display(SEG1,DISABLE); 
            seg_display(SEG2,NUM_TAB[Cache_Volume[Alarm2.Volume]/10%10]);
            seg_display(SEG3,NUM_TAB[Cache_Volume[Alarm2.Volume]%10]); 
            sj &= ~SEG_Sec;
        }
        seg_display(SEG4,sj);
        Flag.Alarm2 = 1;
        Flag.SetUp = 1;
    }
}

void Alarm_processinng(void)     //闹钟处理
{
    if(Flag.Alarm1 &&(Timer.Hour == Alarm1.Hour)&&(Timer.Min == Alarm1.Min))
    {
        if(!Flag.TrueAlarm1)
        {
            Flag.Alarm_Timer = 0;
            Flag.TrueAlarm2 = 0;
            Flag.TrueAlarm1 = 1;
            PWM_DATA_Table.W = 0;
            Flag.LedMode = 1;
        }
    }
    if(Flag.Alarm2 &&(Timer.Hour == Alarm2.Hour)&&(Timer.Min == Alarm2.Min))
    {
        if(!Flag.TrueAlarm2)
        {
            Flag.Alarm_Timer = 0;
            Flag.TrueAlarm1 = 0;
            Flag.TrueAlarm2 = 1;
            PWM_DATA_Table.W = 1000;
            Flag.LedMode = 1;
        }
    }
    
    if(Flag.TrueAlarm1&&(Flag.Alarm_Timer == 1800))     //日出闹钟时间到3600
    {
        PWM_DATA_Table.B = 1000;
        Flag.LedMode = 3;
        Flag.Update = 1;
        if(Alarm1.Volume == 0)  //音量为0时关闭
            music_stop();
        else                   //否则写入对应音量并开始播放
        {
            volume_control(Alarm1.Volume);
            while(MLD_BSY == 0) Alarm1_play();
        }
    }
    if(Flag.TrueAlarm2&&(Flag.Alarm_Timer == 1800))     //日落闹钟时间到3600
    {
        PWM_DATA_Table.W = 800;
        Flag.LedMode = 0;
        Flag.Update = 1;
        if(Alarm2.Volume == 0)  //音量为0时关闭
            music_stop();
        else                   //否则写入对应音量并开始播放
        {
            volume_control(Alarm2.Volume);
            while(MLD_BSY == 0) Alarm2_play();
        }
    }
}