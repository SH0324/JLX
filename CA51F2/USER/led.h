#ifndef _LED_H_
#define _LED_H_

#include "ca51f_config.h"


#define PWM_off 0ul
#define PWM_min 50ul
#define PWM_typ 300ul
#define PWM_max 1000ul
#define PWM_div 1000ul

typedef struct
{
    unsigned char Step; 
    unsigned int B;
    unsigned int C;
    unsigned int W;
} PWM_DATA_s;

extern PWM_DATA_s xdata PWM_DATA_Table;


void LED_Init(void);
void LED_Dimming(void);  //无极调光
void PWM_Set(void);  //更新PWM数据
#endif


