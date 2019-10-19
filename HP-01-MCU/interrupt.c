#ifndef _INTERRUPT_C_
#define _INTERRUPT_C_

#include "ca51f_config.h"

#include "conturol_user.h"

#include "delay.h"
#include "uart.h"
#include "system_clock.h"
#include "rtc.h"	


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
    static unsigned char f = 0;
	if(RTCIF & RTC_MF)			//�����ж�	   ʱ��Ϊ (RTMSS+1)*128*Trtc, 
	{
		RTCIF = RTC_MF;		
		TS_MS_ISR();
		if(TS_LongKeyTimer)
		{
			TS_LongKeyTimer--;		
		}
        f++;
        if((Flag.Timer1 != Flag.Timer)&(f >= 20))  //��ʱָʾ�������ٶ�
        {
            f = 0;
            if(Flag.Timer1 > Flag.Timer)
            {
                Flag.Timer++;
            }
            else
            {
                Flag.Timer--;
            }
            
        }
	}
	if(RTCIF & RTC_HF)			//�����ж�
	{
		RTCIF = RTC_HF;	


        if(Flag.Timer1 != 0)
            Timer.mSec++;   //����ʱ�����

        if(Timer.mSec == 110)  //1����
        {
            Timer.mSec = 0;
            Timer.Sec++;
        }
        if(Timer.Sec == 10) //10����
        {
            Timer.Sec = 0;
            Flag.Timer1--;
            if(Flag.Timer1 == 0)  //������ʱ�䣬�������־
            {
                Flag.Power = 0;
                Flag.Update = 1;
            }
        }
		TS_HS_ISR();
	}	
}

//void TIM0_ISR (void) interrupt 1     //1ms
//{
//    TH0  = TH_VAL;  //��װ��ֵ
//    TL0  = TL_VAL;
//    
//    Timer.mSec++;   //����ʱ�����

//    if(Timer.mSec == 1000)
//    {
//        Timer.mSec = 0;
//        Timer.Sec++;
//        
//    }
//    if(Timer.Sec == 60) //10����
//    {
//        Timer.Sec = 0;
//        Flag.Timer1--;
//        if(Flag.Timer1 == 0)  //������ʱ�䣬�������־
//        {
//            Flag.Power = 0;
//            Flag.Update = 1;
//        }
//    }
//    
//}


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