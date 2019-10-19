#ifndef _control_user_h_
#define _control_user_h_

#include "ca51f_config.h"

#define PWM_off 0ul
#define PWM_min 50ul
#define PWM_typ 120ul
#define PWM_div 1000ul

#define  D1      P30   //指示灯定义
#define  D2      P31
#define  D3      P00
#define  D4      P01
#define  D5      P02
#define  D6      P03

typedef struct
{
    unsigned Power:1;
    unsigned Light:3;
    unsigned Timer:6;
    unsigned Timer1:6;
    unsigned Update:1;
    unsigned Dir:1;
    unsigned Dimming:1;
}Flag_s;

typedef struct
{
    unsigned int 	Light0; 
    unsigned int  	Light1;
    unsigned int  	Light2;
    unsigned int  	Adj;
    
    int             LED_DutyDat;
}PWM_DATA_s;

//定时器计数
typedef struct
{
	  unsigned char   mSec;
	  unsigned char   Sec;
	  unsigned char   Min;
}TIMER_s;
 

extern Flag_s xdata Flag;
extern TIMER_s  xdata Timer;
extern PWM_DATA_s xdata PWM_DATA_Table;


void LED_Init(void);
void PWM_Set(void);  //更新PWM数据
void Assignment(void);   //赋值
void LED_Dimming(void);  //无极调光
void main_loop(void);
//void Timer_Init(void);


#endif