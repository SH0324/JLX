#ifndef _control_user_h_
#define _control_user_h_

#include "ca51f5_config.h"

#define PWM_off 0L
#define PWM_min 50L
#define PWM_typ 100L
#define PWM_max 500L


#define  D1      P06
#define  D2      P07
#define  D3      P03

typedef struct 
{
    unsigned int 	Light0; 
    unsigned int  	Light1;
    unsigned int 	Light2; 
    unsigned int  	Light3;
    
}Mode_s;

typedef struct
{
	/* 调整参数结构 */
	Mode_s Mode0,Mode1,Mode2;

} PWM_DATA_s;

extern PWM_DATA_s xdata PWM_DATA_Table;
extern unsigned int  xdata LED_C_DutyDat;  //冷光 Cold
extern unsigned int xdata LED_W_DutyDat;   //暖光 Warm

void LED_Init(void);
void Read_light(void);    
void Update_light(void);
void LED_Off(void);   //关闭LED
void PWM_Update(void);  //更新PWM数据
void Assignment(void);   //赋值
    
#endif