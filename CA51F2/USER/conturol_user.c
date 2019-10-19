#include "conturol_user.h"
#include "lcd.h"
#include "key.h"
#include "rtc.h"
#include "led.h"
#include "pwm.h"
#include "wdt.h"
#include "uart.h"
#include "music.h"
#include "delay.h"
#include "system_clock.h"

#include "ts_configuration.h"
#include "ts_def.h"
#include "ts_api.h"
#include "ts_service.h"

TIMER_S  xdata Timer   =  {0,0};
TIMER_S  xdata Alarm1  =  {8,22,12};
TIMER_S  xdata Alarm2  =  {6,22,12};
TIMER_S  xdata Cache   =  {0,0};

unsigned char xdata sj = 0;

code unsigned char Cache_Volume[]={0,0,0,20,20,20,40,40,40,60,60,60,80,80,80,100,100,100};
code unsigned char NUM_TAB[]=
{
	0x3F,		// 0-5f
	0x06,		// 1
	0x5B,		// 2
	0x4F,		// 3
	0x66,		// 4
	0x6D,		// 5
	0x7D,		// 6
	0x07,		// 7
	0x7F,		// 8
	0x6F,		// 9
//	0x37,		// A
//	0x7C,		// B
//	0x39,		// C
//	0x5E,		// D
//	0x79,		// E
//	0x71		// F
};

void LCD_RamClear(void)
{
	unsigned char  i;
	for(i = 0; i < 9; i++)
	{
		LCD_WriteLram(i,0x00);
	}
}


void seg_display(unsigned char laddr,unsigned char lnum)
{
    unsigned char  i;
    
    for(i=0;i<8;i++)
    {
        INDEX = i;
        if(lnum & 0x80)
            LXDAT |= laddr;
        else
            LXDAT &= ~laddr;
        lnum <<= 1;
    }
}


//void INT0_init(void)
//{
//    P67F = INPUT;//����P67Ϊ��������
//    IT0CON = 55; //ѡ��P67��Ϊ�ж�0���ţ�55ΪP67��Ӧ���������
//    EX0 = 1;     //INT0�ж�ʹ��
//    IE0 = 1;     //�ⲿ�ж�0ʹ��
//    IT0 = 1;     //����Ϊ�½����ж�
//    PX0 = 1;     //����INT0Ϊ�����ȼ�
//}

void INT2_init(void)
{
    P67F = INPUT;//����P67Ϊ��������
    INDEX = 0; //����EPCON�����ţ�0~7�ֱ��Ӧ�ⲿ�ж�2~9
//    EPCON = (0<<7) | 55; //����Ϊ�����ش����������ж�����������ţ�55��ӦP67
    EPCON = (1<<7) | 55; //����Ϊ�½��ش���
    INT2EN = ENABLE; //INT2�ж�ʹ��
    EPIE |= 0x01;    //�ⲿ�ж�2�ж�ʹ��
    EXIP |= 0x01;    //�����ȼ�
}

void Stop(void)
{
    I2CCON = 0; //�ر�I2C���ܣ���ΪI2CĬ����ʹ�ܵģ����I2C���رս��޷��ر�IRCHʱ��
    CKCON = 0; //�ر�����ʱ��
    PWCON &=0xF7; //����LDO����͹���ģʽ
    MECON |= (1<<6); //����FLASH�������˯��״̬
    while(STPSTH|STPSTL); //������ж�δ��Ӧ,�ȴ��жϱ���Ӧ
    EPCON = (0<<7) | 55; //����Ϊ�����ش����ȴ��´��ϵ�
    PCON |= 0x02; //����STOPģʽ
    _nop_();
    _nop_();
}


void sys_init(void)
{
    
    
    #ifdef LVD_RST_ENABLE
	LVDCON = 0xA7;	//����LVD��λ��ѹΪ2V
#endif
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);
#endif
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);
#endif
#ifdef UART2_EN
	Uart2_Initial(UART2_BAUTRATE);
#endif

    LED_Init();
    
#if (RTC_CLK_SELECT == XOSCL)
	GPIO_Init(P71F,P71_XOSCL_OUT_SETTING);
	GPIO_Init(P72F,P72_XOSCL_IN_SETTING);
	CKCON |= XLCKE;
	while(!(CKCON & XLSTA));
	CKSEL = CKSEL & 0x7F;
    
#else
    CKCON |= ILCKE;
	CKSEL |= 0x80;
#endif

//    CKCON |= TFCKE;   
//    CKCON |= ILCKE;
//	CKSEL |= 0x80;


    INT8EN = ENABLE;     //ʵʱ��ʱ���жϴ�

    

    RTC_init(RTCE_On,MSE_On,HSE_On);     //��ʱ�ӣ���������жϴ�
    Delay_ms(1);
    RTC_WriteHour(8);                    //����ʱ��
    RTC_WriteMinute(54);
    RTC_WriteSecond(00);
//    RTC_AlarmCfg(HCE_On,MCE_On,SCE_Off); //����ֻ�Ƚ�Сʱ���
//    RTC_SetAlaramTime(8,36,0);           //��������Ϊ12.30
    RTC_WriteWeek(0);                      //��������
    Timer.Hour = RTCH;                     //��ȡʱ��ͬ��
    Timer.Min  = RTCM;
    
    GPIO_Init(P00F,P00_COM0_SETTING);  //COM0-4
    GPIO_Init(P01F,P01_COM1_SETTING);
    GPIO_Init(P02F,P02_COM2_SETTING);
    GPIO_Init(P03F,P03_COM3_SETTING);
    GPIO_Init(P04F,P04_COM4_SETTING);
    
    GPIO_Init(P20F,P20_SEG31_SETTING);  //SEG.A-G
    GPIO_Init(P21F,P21_SEG30_SETTING);
    GPIO_Init(P22F,P22_SEG29_SETTING);
    GPIO_Init(P23F,P23_SEG28_SETTING);
    GPIO_Init(P24F,P24_SEG27_SETTING);
    GPIO_Init(P25F,P25_SEG26_SETTING);
    GPIO_Init(P26F,P26_SEG25_SETTING);
    GPIO_Init(P64F,P64_SEG14_SETTING);

    LCD_RamClear();   //�建��

    SEG_init(LEN_XOSCL,COM_H,SEG_L,LDRV_7,1);
    key_init();
    music_init();
    
//    INT0_init();
    INT2_init();
    TS_init();	
//    LXCFG |= BLNK(1);  //ȫ����˸
}


void sys_Other(void)
{
    if(Flag.Alarm1) sj |= 0x20;
    else            sj &= 0xDF;
    if(Flag.Alarm2) sj |= 0x10;
    else            sj &= 0xEF;
    if(Flag.SetUp|Flag.TimerOut)
    {
        Flag.TimerOut = 0;
        Flag.SetUp = 0;
        while(MLD_BSY == 1) music_stop();
    }  
    TS_Action();
    P11 ^= 1;
    if(TS_Key != 0)
    {
        switch(TS_Key)
        {
            //��������Ϣ
            case (K1|KEY_BREAK):
            {
                if(Flag.TrueAlarm1|Flag.TrueAlarm2)
                {
                    Flag.TimerOut_Counter = 0;
                    Flag.TrueAlarm1 = 0;
                    Flag.TrueAlarm2 = 0;
                    Flag.LedMode = 0;
                    Flag.Update = 1;
                    Flag.TimerOut = 1;  //ֹͣMusic
                }
                else
                {
                    Flag.LedMode++; 
                    Flag.Update = 1;  //K1�̰��л��ƹ⣬�ճ������¹ر�ģʽ
                }
            }break;
            case (K1|KEY_LONG_START):Flag.Dir ^= 1;Flag.Dimming = 1;	  //K1�����޼�����
                break;
            case (K1|KEY_LONG_BREAK):Flag.Dimming =0; //K1�������ֲ�������Ϣ
                break;
        }
    }
    PWM_Set();
}


void ContinuousAdj(void)
{
    static unsigned int xdata Counter_Hour = 0;
    if((Key_Up == KEY_HOLD)|(Key_Down == KEY_HOLD)) Counter_Hour++;
    if(Counter_Hour >= 2500) 
    {
        Counter_Hour = 0;
        if(Key_Up == KEY_HOLD) Key_Up = KEY_DOWN;
        else                   Key_Down = KEY_DOWN;
    }
}


