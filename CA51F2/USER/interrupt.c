#ifndef _INTERRUPT_C_
#define _INTERRUPT_C_

#include "ca51f_config.h"

#include "delay.h"
#include "uart.h"
#include "system_clock.h"
#include "rtc.h"	
#include "conturol_user.h"
#include "key.h"
#include "music.h"
#include "led.h"

#include "ts_configuration.h"
#include "ts_def.h"
#include "ts_api.h"
#include "ts_service.h"

#if DEBUG
#include "i2c.h"		
void I2C_ISR(void);
#endif
void INT8_ISR (void) interrupt 13 	 
{
//    static unsigned int xdata  = 0;
	if(RTCIF & RTC_MF)			//毫秒中断	   时间为 (RTMSS+1)*128*Trtc, 
	{
		RTCIF = RTC_MF;	
        TS_MS_ISR();
        
		if(TS_LongKeyTimer)
		{
			TS_LongKeyTimer--;		
		}
        Key_Scan();
        
        
        if(Flag.Dimming) LED_Dimming();
	}

	if(RTCIF & RTC_HF)			//半秒中断
	{
		RTCIF = RTC_HF;	
		TS_HS_ISR();
        
        Flag.Flicker ^= 1;  //半秒翻转
        
        if(!(Flag.SetAlarm1 | Flag.SetAlarm2)) sj ^= SEG_Sec;//未设置闹钟时秒闪烁
        if((Flag.Flicker)&&(Flag.TrueAlarm1))                //日出1S闪烁
        {
            Flag.Alarm_Timer++;
            sj ^= SEG_Alarm1;
        }
        if((Flag.Flicker)&&(Flag.TrueAlarm2))                //日落1S闪烁
        {
            Flag.Alarm_Timer++;
            sj ^= SEG_Alarm2;
        }
        if((Flag.Alarm_Timer % 4) && Flag.TrueAlarm1) //日出2S进行一次递增 
        {
            if(PWM_DATA_Table.W < 1000)
            {
                PWM_DATA_Table.W++;
                Flag.Update = 1;
            } 
        }
        if((Flag.Alarm_Timer % 4) && Flag.TrueAlarm2) //日落2S进行一次递减
        {
            if(PWM_DATA_Table.W >= 2)
            {
                PWM_DATA_Table.W--;
                Flag.Update = 1;
            } 
        }
        
        if(!RTCS) Flag.TimerMin= 1;  //每分钟扫描一次
        
        Timer.Min  = RTCM;
        if(Flag.TimerOut_Counter)      //设置超时处理
        {
            Flag.TimerOut_Counter--;
            if(Flag.TimerOut_Counter == 0)
            {
                Flag.TimerOut = 1;
                Flag.SetHour = 0;
                Flag.SetAlarm1 = 0;
                Flag.SetAlarm2 = 0;
            }
        }
        
        
        //未进入设置时进行刷新显示
        if(!Flag.SetUp)
        {
            if(Flag.Hour12)
            {
                if((RTCH & 0x1F) >= 12) sj = (sj & 0xFA)|SEG_PM;
                else                    sj = (sj & 0xFA)|SEG_AM;
                if((RTCH  & 0x1F) == 0) Timer.Hour = 12;
                if(((RTCH & 0x1F) <= 12)&&((RTCH & 0x1F) >= 1)) Timer.Hour = RTCH;
                if((RTCH  & 0x1F) >12) Timer.Hour = (RTCH & 0x1F)-12;
            }
            else
            {
                sj &= 0xFA;       //清零AM,PM
                Timer.Hour = RTCH;
            }
            if(Timer.Hour >= 10)
                seg_display(SEG0,NUM_TAB[Timer.Hour/10]);
            else
                seg_display(SEG0,0x00);
            seg_display(SEG1,NUM_TAB[Timer.Hour%10]);            
            seg_display(SEG2,NUM_TAB[Timer.Min/10]);
            seg_display(SEG3,NUM_TAB[Timer.Min%10]);
            seg_display(SEG4,sj);
        }    
	}

    if(RTCIF & RTC_AF)           //闹钟中断
	{
        RTCIF = RTC_AF;
        
    }
}

void INT0_ISR (void) interrupt 0
{
    
    
}

void INT2_ISR (void) interrupt 7
{
    if(EPIF & 0x01) //判断外部中断2中断标志
    {
        EPIF = 0x01; //中断标志写1清0
//        if(P6 & 0x80)
//        {
//            PWCON ｜=0x08; //退出STOP后，必须把LDO设置回高功率模式
//            EPCON = (1<<7) | 55; //设置为下降沿触发,等待掉电
//        }
//        else
//        {
//            Stop();
//        }
           P11^= 1; 
    }
}

void INT3_ISR (void) interrupt 8
{	
    
	if(TKIF != 0)
	{
         
		TS_ISR();
        
	}
}
void INT6_ISR(void) interrupt 11 
{
#if DEBUG
	if(I2CFLG & I2CF)		
	{
		I2C_ISR();
	}
#endif
}
#endif