#ifndef _KEY_H_
#define _KEY_H_

#include "ca51f_config.h"

//宏定义
#define KEYDOWN_TIME	1u         //短按时间
#define	KEYHOLD_TIME	255u       //长按时间
//#define KEYDOWN_TIME 2u
//#define KEYHOLD_TIME 50u

//自定义按键
sbit KEYAlarm1	=  P2^7;     //日出模式键
sbit KEYAlarm2 	=  P1^7;     //日落模式键
sbit KEYUp 		=  P1^6;     //上调键
sbit KEYDown 	=  P4^4;     //下调键
sbit KEYHour 	=  P4^3;     //时钟键
sbit KEYLight   =  P4^2;     //时钟显示亮度键
sbit KEYTouch   =  P4^0;     //时钟显示亮度键

typedef struct 
{
    unsigned Alarm1:1;     //日出标志
    unsigned Alarm2:1;     //日落标志
    unsigned TrueAlarm1:1; //日出忙标志
    unsigned TrueAlarm2:1; //日落忙标志
    unsigned HourLight:2;  //时钟亮度标志
    unsigned Hour12:1;     //12小时制标志
    unsigned SetHour:2;    //设置时钟标志
    unsigned SetAlarm1:2;  //设置日出标志
    unsigned SetAlarm2:2;  //设置日落标志
    unsigned Hour1:1;      //
    unsigned TimerOut_Counter:5; //超时退出计数
    unsigned TimerOut:1;   //超时退出标志 
    unsigned TimerMin:1;   //每分标记一次
    unsigned Flicker:1;    //闪烁标志
    
    unsigned SetUp:1;    //闪烁标志

    unsigned Light0:1;
    unsigned Light1:1; 
    unsigned Light2:1;
    unsigned LedMode:2;
    unsigned Dimming:1;
    unsigned Dir:1;
    unsigned Update:1;
    
    unsigned int Alarm_Timer;
    
}Flag_s;

typedef enum
{
    KEY_FREE   = 0,   //空闲
    KEY_DOWN   = 1,   //按下
    KEY_HOLD   = 2,   //长按
    KEY_HOLD_S = 3
}KEY_STATUS_e;

extern KEY_STATUS_e xdata Key_Alarm1;
extern KEY_STATUS_e xdata Key_Alarm2;
extern KEY_STATUS_e	xdata Key_Up;
extern KEY_STATUS_e	xdata Key_Down;
extern KEY_STATUS_e	xdata Key_Hour;
extern KEY_STATUS_e	xdata Key_Light;
extern KEY_STATUS_e xdata Key_Touch;

extern Flag_s xdata Flag;

//extern u8 xdata music_x;

void key_init(void);
void Key_Scan(void);    //按键扫描
void key_processinng(void);
void Hour_processinng(void);
void Alarm1_processinng(void);
void Alarm2_processinng(void);
void Alarm_processinng(void);     //闹钟处理    
#endif


