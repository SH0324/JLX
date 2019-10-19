#ifndef _WDT_C_
#define _WDT_C_

#include "wdt.h"

/*****************************************************************************
函数名：WDT_init
功能描述：初始化看门狗
输入参数：wdts		看门狗时钟源设置
		 wdre		看门狗模式设置
		 wdtch		看门狗时间设置
返回值： 无
******************************************************************************/
void WDT_init(WDTS_TypeDef wdts,WDRE_TypeDef wdre,unsigned int wdtvh)
{
	WDCON = WDTS(wdts) | WDRE(wdre);
	WDVTHH = (unsigned char)(wdtvh>>8);
	WDVTHL = (unsigned char)(wdtvh);	
}

/*****************************************************************************
函数名：WDT_FeedDog
功能描述：刷新看门狗
输入参数：无
返回值： 无
******************************************************************************/
void WDT_FeedDog(void)
{
	WDFLG = 0xA5;
}

#endif