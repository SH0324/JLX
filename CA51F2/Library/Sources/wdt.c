#ifndef _WDT_C_
#define _WDT_C_

#include "wdt.h"

/*****************************************************************************
???:WDT_init
????:??????
????:wdts		????????
					wdre		???????
					wdtch		???????
???: ?
******************************************************************************/
void WDT_init(WDTS_TypeDef wdts,WDRE_TypeDef wdre,unsigned int wdtvh)
{
	WDCON = WDTS(wdts) | WDRE(wdre);
	WDVTHH = (unsigned char)(wdtvh>>8);
	WDVTHL = (unsigned char)(wdtvh);	
}

/*****************************************************************************
???:WDT_FeedDog
????:?????
????:?
???: ?
******************************************************************************/
void WDT_FeedDog(void)
{
	WDFLG = 0xA5;
}

#endif