#ifndef _MAIN_C_
#define _MAIN_C_

#include "key.h"
#include "conturol_user.h"

void main(void)
{
    sys_init();
    EA = 1;         
	while(1)
	{	
        sys_Other();
        key_processinng();
        Hour_processinng();
        Alarm1_processinng();
        Alarm2_processinng();
        
        if(Flag.TimerMin&&(Flag.Alarm1|Flag.Alarm2))
        {
            Flag.TimerMin= 0;
            Alarm_processinng();
        }
	}
}
#endif
