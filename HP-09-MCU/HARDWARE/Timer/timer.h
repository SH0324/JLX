#ifndef	__TIMER_H
#define	__TIMER_H

#include "ca51f5sfr.h"

#define	T1MS (65536-1340)  //670


#define TME(N)    (N<<7)    //N= 0-1
#define TMF       (1<<0)

#define IHCKE      (1<<7)
#define ILCKE      (1<<6)
 
 
//定时器计数
typedef struct
{
	  unsigned int    mSec;
	  unsigned char   Sec;
	  unsigned char   Min;
}TIMER_S;
 

extern TIMER_S  Timer;
 
void Timer_Init(void);


#endif
