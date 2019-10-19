#ifndef _music_h_
#define _music_h_

#include "conturol_user.h"

//#define MLD_BSY (P6 & 0x40)   //****************************************************

#define MLD_DAT_Clr()  P32 = 0
#define MLD_DAT_Set()  P32 = 1

#define MLD_SCK_Clr()  P33 = 0
#define MLD_SCK_Set()  P33 = 1

sbit MLD_BSY = P4^5;

void music_init(void);
void music_cmd(unsigned char cmd);
void volume_control(unsigned char volume);
void music_stop(void);
void Alarm2_play(void);
void Alarm1_play(void);

#endif