#ifndef __key_h_
#define __key_h_

#include "ca51f5_config.h"

//宏定义
#define KEYDOWN_TIME	1u         //短按时间
#define	KEYHOLD_TIME	255u       //长按时间
//#define KEYDOWN_TIME 2u
//#define KEYHOLD_TIME 50u

//自定义按键
#define KEY_Mode 		  P00
#define KEY_Light 		  P01
#define KEY_Timer 		  P02

typedef struct 
{
    unsigned Power:2;
    
    unsigned Update:1;
    unsigned Light:1; 

    unsigned Light0:1;
    unsigned Light1:1; 
    unsigned Light2:1;
    unsigned Timer:7;
    unsigned mode:2;
}Flag_s;

typedef enum
{
    KEY_FREE   = 0,
    KEY_DOWN   = 1,
    KEY_HOLD   = 2,
    KEY_HOLD_S = 3
}KEY_STATUS_e;

extern Flag_s xdata Flag;
extern KEY_STATUS_e		KeyMode;
extern KEY_STATUS_e		KeyLight;
extern KEY_STATUS_e		KeyTimer;

void SYS_init(void);
void Key_Scan(void);    //按键扫描
void main_loop(void);


#endif