#include "system_clock.h"

#include "ca51f5sfr.h"

void Sys_Clk_Set_IRCH(void)
{
 	CKCON |= IHCKE;
 	CKCON = (CKCON&0xFE) | CKSEL_IRCH;		
}
void Sys_Clk_Set_IRCL(void)
{
 	CKCON |= ILCKE;
 	CKCON = (CKCON&0xFE) | CKSEL_IRCL;		
}

