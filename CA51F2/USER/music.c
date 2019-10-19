#include "music.h"
#include "delay.h"

void music_init(void)
{
    GPIO_Init(P45F,INPUT|PU_EN);   //Music
    GPIO_Init(P33F,OUTPUT|PD_EN);
    GPIO_Init(P32F,OUTPUT|PD_EN);
    
//    GPIO_Init(P10F,INPUT|PU_EN);
//    GPIO_Init(P11F,INPUT|PU_EN);
}

void music_cmd(unsigned char cmd)
{
    unsigned char i;
    MLD_SCK_Set();
    Delay_ms(5);
    for(i=0;i<8;i++)
    {
        MLD_SCK_Clr();
        if((cmd & 0x80))
        {
            MLD_DAT_Set();
        }
        else
        {
            MLD_DAT_Clr();
        }
        Delay_50us(9);
        MLD_SCK_Set();
        Delay_50us(9);
        cmd <<= 1;
    }
    MLD_SCK_Clr();
    MLD_DAT_Clr();
}


void Alarm1_play(void)
{
    music_cmd(0x02);
}

void Alarm2_play(void)
{
    music_cmd(0x01);
}

void music_stop(void)
{
    music_cmd(0x00);
}

void volume_control(unsigned char volume)
{
    music_cmd(volume | 0xE0);
}