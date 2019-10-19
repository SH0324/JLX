#ifndef _CLOCK_C_
#define _CLOCK_C_

#include "clock.h"

//TIMER_S  Timer   =  {0,0,0,0};
//TIMER_S  Alarm1  =  {0,0,0,0};
//TIMER_S  Alarm2  =  {0,0,0,0};
//TIMER_S  Cache   =  {0,0,0,0};

//void Time_Conversion(void)
//{
//    if(hour >= 12) PM;
//    else           AM;

//    if(hour == 0) 12;
//    if((hour <= 12)&&(hour >= 1)) hour;
//    if(hour >12) hour-12;
//}

//void Key_Scan(void)	//按键检测函数
//{
//	if(Set_key == 0)	//设置按键处理：统计设置键按下次数、定位光标及其闪烁位置及定时器起停控制
//	{
//		Delay_ms(5);	//设置键消抖
//		if(Set_key == 0)
//		{				
//00while( !Set_key );		//按键松手检测			
//			Flag_set = 1;			//置位设置键按下标志
//			Num_set++;				//统计设置键按下的次数
//			Flag_Alarm = 0;			//清零闹钟标志位以关闭蜂鸣器
//			CmdWrite_LCD1602(0x0f);	//打开LCD1602光标闪烁
//			
//			miao = DateRead_DS12C887(0);//读取DS12C887的秒值
//			fen = DateRead_DS12C887(2);	//读取DS12C887的分值
//			shi = DateRead_DS12C887(4);	//读取DS12C887的时值

//			switch(Num_set)	//定位光标闪烁位置
//			{
//				case 1: CmdWrite_LCD1602(0x80+11);	break;	//设置键按下1次，光标在秒的个位闪烁
//				case 2: CmdWrite_LCD1602(0x80+8);	break;	//设置键按下2次，光标在分的个位闪烁
//				case 3: CmdWrite_LCD1602(0x80+5);	break;	//设置键按下3次，光标在时的个位闪烁
//				default: Num_set=0; 	Flag_set=0;			//其他情况则清零设置键按下的次数及标志位						 
//						 CmdWrite_LCD1602(0x0c);	break;	//关闭光标闪烁
//			}		
//		}		
//	}
//	
//	if(Add_key == 0)	//加键及其处理
//	{
//			Flag_Alarm = 0;		//清零闹钟标志位以关闭蜂鸣器
//			switch(Num_set)		//根据设置键按下的次数决定程序流程
//			{
//				case 1: miao++; if(miao == 60)	miao = 0; 	//设置键按下一次，则处理秒加
//						NumberDisp_LCD1602(10,0,miao);		//刷新秒的显示
//						DateWrite_DS12C887(0,miao);			//创新把秒写入DS12C887
//						CmdWrite_LCD1602(0x80+11);	break; 	//重新定位光标闪烁的位置
//				case 2: fen++;  if(fen == 60)	fen = 0;	//设置键按下二次，则处理分加
//						NumberDisp_LCD1602(7,0,fen);		//刷新分的显示
//						DateWrite_DS12C887(2,fen);			//创新把分写入DS12C887
//						CmdWrite_LCD1602(0x80+8);	break; 	//重新定位光标闪烁的位置
//				case 3: shi++;  if(shi == 24)	shi = 0; 	//设置键按下三次，则处理时加
//						NumberDisp_LCD1602(4,0,shi);		//刷新时的显示
//						DateWrite_DS12C887(4,shi);			//创新把时写入DS12C887
//						CmdWrite_LCD1602(0x80+5);	break; 	//重新定位光标闪烁的位置
//				default: 	break;							//其他情况则不作处理
//			}
//		}		
//	}
//	
//	if(Dec_key == 0)	//减键及其处理
//	{
//			Flag_Alarm = 0;		//清零闹钟标志位以关闭蜂鸣器
//			switch(Num_set)
//			{
//				case 1: if(miao == 0)  miao = 60; miao--;	//设置键按下一次，则处理秒减
//						NumberDisp_LCD1602(10,0,miao);		//刷新秒的显示
//						DateWrite_DS12C887(0,miao);			//创新把秒写入DS12C887
//						CmdWrite_LCD1602(0x80+11);	break; 	//重新定位光标闪烁的位置
//				case 2: if(fen == 0)   fen = 60;  fen--;	//设置键按下二次，则处理分减
//						NumberDisp_LCD1602(7,0,fen);		//刷新分的显示
//						DateWrite_DS12C887(2,fen);			//创新把分写入DS12C887
//						CmdWrite_LCD1602(0x80+8);	break; 	//重新定位光标闪烁的位置
//				case 3: if(shi == 0)   shi = 24;  shi--; 	//设置键按下三次，则处理时减
//						NumberDisp_LCD1602(4,0,shi);		//刷新时的显示
//						DateWrite_DS12C887(4,shi);			//创新把时写入DS12C887
//						CmdWrite_LCD1602(0x80+5);	break; 	//重新定位光标闪烁的位置
//				default: 	break;	//其他情况则不作处理
//			}
//		}		
//	}
//	
//	//设置键未按下时，则在LCD1602刷新DS12C887的时间日期显示
//	if(!Flag_set)	DateRefresh_LCD1602();
//	
//	//根据闹钟时间是否到来的中断标志位决定开启与关闭蜂鸣器
//	if(Flag_Alarm)	Buzzer = 0;	//闹钟时间到则开启蜂鸣器
//	else  			Buzzer = 1; //否则关闭蜂鸣器
//}

//void TIM0_ISR (void) interrupt 1
//{
//    TL0  = T1MS;       //重装初值
//    TH0  = T1MS>>8;
//   
//    Timer.mSec++;      //基础时间计数1ms
//    if(Timer.mSec == 1000)
//    {
//        Timer.mSec = 0;
//        Timer.Sec++;
//        
//    }
//    if(Timer.Sec == 60) //秒
//    {
//        Timer.Sec = 0;
//        Timer.Min++;
//        Flag.Timer--;

//    }
//	if(Timer.Min == 60)//分
//    {
//        Timer.Min = 0;
//        Timer.Hour++;
//        
//    }
//	if(Timer.Hour == 24)//时
//    {
//        Timer.Hour = 0;
//    }
//}

//void Timer_Init(void)
//{
//    TMOD = 0x01;   //定时器016位模式
//    TL0  = T1MS;   //初值
//    TH0  = T1MS>>8;
//    TF0  = 0;      //清标志
//    ET0  = 1;      //开T0中断
//    TR0  = 0;      //不启动，定时开始再启动
//    
//    
//    CKCON |= ILCKE;    //打开IRCL时钟
//	TMCON  = TME(1);   //TMC使能
//    TMSNU  = 0;        //约4MS
//    INT3EN = 1;        //开TMC中断
//    EA     = 1;        //开总中断
//}


#endif