#ifndef _key_user_h_
#define _key_user_h_

#include "ca51f5_config.h"

#define KEYDOWN_TIME 2u
#define KEYHOLD_TIME 50u

typedef struct 
{
    unsigned Dir:1; 
    unsigned Power:1;
    unsigned Light:3; 
    unsigned Update:1;
    unsigned Dimming:1; 
    unsigned Light0:3;
    unsigned Light1:2; 
    unsigned Light2:2;
    unsigned mode:2;
    unsigned R_Flag:2;
    unsigned G_Flag:2;
    unsigned B_Flag:2;
    unsigned color:1;
}Flag_s;

typedef enum
{
    KEY_FREE   = 0,
    KEY_DOWN   = 1,
    KEY_HOLD   = 2,
    KEY_HOLD_S = 3
}KEY_STATUS_e;

extern Flag_s xdata Flag;

void SYS_init(void);
void Key_Scan(void);    //°´¼üÉ¨Ãè
void main_loop(void);

#endif