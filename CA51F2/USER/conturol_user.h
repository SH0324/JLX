#ifndef _conturol_user_h_
#define _conturol_user_h_

#include "ca51f_config.h"


#define SEG_AM		    (1<<0)
#define SEG_Sleep		(1<<1)
#define SEG_PM		    (1<<2)
#define SEG_WiFi		(1<<3)
#define SEG_Alarm2		(1<<4)
#define SEG_Alarm1		(1<<5)
#define SEG_Sec		    (1<<6)

#define SEG0 	     0x01
#define SEG1 	     0x02
#define SEG2 	     0x04
#define SEG3 	     0x08
#define SEG4 	     0x10


//定时计数
typedef struct
{
    unsigned char   Hour;     //时
	unsigned char   Min;      //分钟
    unsigned        Volume:4; //音量
}TIMER_S;


extern TIMER_S  xdata Timer;
extern TIMER_S  xdata Alarm1;
extern TIMER_S  xdata Alarm2;
extern TIMER_S  xdata Cache;


extern unsigned char xdata sj;

extern code unsigned char Cache_Volume[];
extern code unsigned char NUM_TAB[];
void LCD_RamClear(void);
void seg_display(unsigned char laddr,unsigned char lnum);
void sys_init(void);
void sys_Other(void);
void ContinuousAdj(void);
void Stop(void);
    
#endif