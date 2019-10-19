#ifndef _SYSTEM_CLOCK_C_
#define _SYSTEM_CLOCK_C_

#include "system_clock.h"

void Sys_Clk_Set_IRCH(void)
{
	CKCON |= IHCKE;
	CKSEL = (CKSEL&0xF8) | CKSEL_IRCH;		
}
void Sys_Clk_Set_PLL(unsigned char Multiple)	
{
	static bit NeedTrim = 1;
	unsigned char ck_bak;
	unsigned char temp;
	if(Multiple < 2 || Multiple > 8) return;
	if(NeedTrim)
	{		
		LOCK  = 0x2B;	
		FSCMD = 0x80;	
		PTSH = 0x00;				
		PTSL = 0x10;        			
		FSCMD = 0x81;						
		temp = FSDAT;
		IHCFGH = temp;
		temp = FSDAT;
		IHCFGL = temp;
		FSCMD = 0;
		LOCK = 0xAA;

		ck_bak = CKCON;
		CKCON |= ILCKE|IHCKE|TFCKE;
		VCKDH = 0XAF;
		VCKDL = 0XC7;
		RCCON = MODE(2) | MSEX(0) | CKSS(10);
		while(RCCON&0xC0);	
		
		RCTAGH = RCMSLH;
		RCTAGL = RCMSLL;
		PLLCON = PLLON(1) | MULFT(Multiple-2);
		while(!(PLLCON & PLSTA));
		CKSEL = (CKSEL&0xF8) | CKSEL_PLL;		
		
		IHCFGH=0X07;
		IHCFGL=0XFF;				
		RCCON = MODE(3) | MSEX(0) | CKSS(10);
		while(RCCON&0xC0);		
	}
	else
	{
		PLLCON = PLLON(1) | MULFT(Multiple-2);
		while(!(PLLCON & PLSTA));
		CKSEL = (CKSEL&0xF8) | CKSEL_PLL;				
	}
	if(NeedTrim)
	{
		CKCON = ck_bak | IHCKE;
		NeedTrim = 0;
	}	
}
void Sys_Clk_Set_IRCL(void)
{
	CKCON |= ILCKE;
	CKSEL = (CKSEL&0xF8) | CKSEL_IRCL;
}
void Sys_Clk_Set_XOSCL(void)
{
	GPIO_Init(P71F,P71_XOSCL_OUT_SETTING);
	GPIO_Init(P72F,P72_XOSCL_IN_SETTING);
	CKCON |= XLCKE;
	while(!(CKCON & XLSTA));
	CKSEL = (CKSEL&0xF8) | CKSEL_XOSCL;		
}

void Sys_Clk_Set_XOSCH(void)
{
	GPIO_Init(P74F,P74_XOSCH_IN_SETTING);
	GPIO_Init(P73F,P73_XOSCH_OUT_SETTING);
	CKCON |= XHCKE;
	while(!(CKCON & XHSTA));
	CKSEL = (CKSEL&0xF8) | CKSEL_XOSCH;		
}
void Sys_Clk_Set_TFRC(void)
{
	CKCON |= TFCKE;
	CKSEL = (CKSEL&0xF8) | CKSEL_TFRC;		
}
void Calibration_IL_Targ__IH_Ref(unsigned long int frequency)		//以IH为参考时钟
{
	RCTAGH =   ((frequency*450)/36864)/256;
	RCTAGL =   ((frequency*450)/36864)%256;
 
	VCKDH = 45000/256;
	VCKDL = 45000%256;

	ILCFGH = 0;
	ILCFGL = 0xFF;
	RCCON = MODE(3) | MSEX(0) | CKSS(6);
	while(RCCON&0xC0);	
}

#endif
