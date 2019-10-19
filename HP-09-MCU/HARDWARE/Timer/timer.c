#include "timer.h"
#include "key.h"
#include "control_user.h"

TIMER_S  Timer  =  {0,0,0};
//TMC定时器约4ms
void INT3_ISR (void) interrupt 5
{
    if(TMCON & TMF)   
	 {
	    TMCON |=TMF;  //清中断标志   
		 Key_Scan();   //按键扫描
	}
}

void TIM0_ISR (void) interrupt 1
{
    TL0  = T1MS;       //重装初值
    TH0  = T1MS>>8;
    TF0  = 0;      //清标志
   
    Timer.mSec++;      //基础时间计数
    if(Timer.mSec == 1000)
    {
        Timer.mSec = 0;
        Timer.Sec++;
        
    }
    if(Timer.Sec == 60) //1分钟
    {
        Timer.Sec = 0;
        Flag.Timer--;

    }
    if(Flag.Timer == 0)  //到定是时间，清零各标志
    {
        Flag.Power = 0;
        Flag.Timer = 0;
        TF0  = 0;      //清标志
        TR0  = 0;
        ET0  = 0;      //关T0中断
    }
}

void Timer_Init(void)
{
    TMOD = 0x01;   //定时器016位模式
    TL0  = T1MS;   //初值
    TH0  = T1MS>>8;
    TF0  = 0;      //清标志
    ET0  = 1;      //T0中断
    TR0  = 0;      //不启动，定时开始再启动
    
    
    CKCON |= ILCKE;    //打开IRCL时钟
	TMCON  = TME(1);   //TMC使能
    TMSNU  = 0;        //约4MS
    INT3EN = 1;        //开TMC中断
    EA     = 1;        //开总中断
}
