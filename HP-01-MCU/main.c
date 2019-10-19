#ifndef _MAIN_C_
#define _MAIN_C_

#include "delay.h"
#include "uart.h"
#include "system_clock.h"
#include "rtc.h"	
#include "pwm.h"	
#include "adc.h"
#include "conturol_user.h"

#include "ts_configuration.h"
#include "ts_def.h"
#include "ts_api.h"
#include "ts_service.h"

unsigned char read_inner_trim(void)				
{
	unsigned char value;
	FSCMD = 0x80;	
	PTSH = 0x00;				
	PTSL = 0x24;      
	FSCMD = 0x81;						
	value = FSDAT;
	FSCMD = 0;
	return value;
}
void SystemInit(void)
{
//    Sys_Clk_Set_IRCH();
//    Sys_Clk_Set_PLL(6);
#ifdef LVD_RST_ENABLE
	LVDCON = 0x80;	
	Delay_50us(1);
	LVDCON = 0xc2;	
	LVDCON |= 0x20;	
#endif
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	
#endif
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);
#endif
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);
#endif
#ifdef UART2_EN
	Uart2_Initial(UART2_BAUTRATE);
#endif
	
//	ADCFGH = (ADCFGH&0xC0) | VTRIM(read_inner_trim());	//加载ADC内部基准校准值
    
    LED_Init();
//    Timer_Init();
}
void main(void)
{
	SystemInit();
    
	EA = 1;
    
	TS_init();	
    
	while(1)
	{			
		TS_Action();
        main_loop();
	}
}
#endif
