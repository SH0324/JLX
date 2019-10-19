#ifndef _MAIN_C_
#define _MAIN_C_

#include "system_clock.h"
#include "key.h"
#include "timer.h"
#include "pwm.h"
#include "control_user.h"
#include "wdt.h"

void main(void)
{
    Sys_Clk_Set_IRCH();
    LED_Init();
    Timer_Init();
    WDT_init(WDTS_IRCH,WDRE_reset,0x0808);   //高速时钟，复位，1800，1S
    while(1)
    {
        main_loop();
        WDT_FeedDog();
    }  
}

#endif