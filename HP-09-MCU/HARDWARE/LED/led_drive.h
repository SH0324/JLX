#ifndef _LED_DRIVE_H
#define _LED_DRIVE_H

#include "ca51f5sfr.h"

#define  D1      P03
#define  D2      P07
#define  D3      P06

#define  PWM_DivDat  1000UL

#define  PWM100       999UL
#define  PWM72        720UL
#define  PWM65        650UL
#define  PWM42        420UL

extern  unsigned int LED_H_DutyDat;
extern  unsigned int LED_W_DutyDat;

void LED_Init(void);

#endif										
