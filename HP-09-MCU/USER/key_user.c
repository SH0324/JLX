#include "key_user.h"
#include "control_user.h"
#include "pwm.h"


Flag_s xdata Flag={0,0,0,0,0,0,0,0,0,1,0,0,0};  //��ֵ


void SYS_init(void)  //ϵͳ��ʼ��
{
    LED_Init();
    TS_init();	
    EA = 1;
}

void Key_Scan(void)   //����ɨ��
{
    TS_Action();
#if SUPPORT_KEY
#if GENERATE_TS_KEY_EN
    if(TS_Key != 0)
    {
        switch(TS_Key)
        {
            //��������Ϣ
            case (K2|KEY_BREAK):	  //K2�̰����ֲ����İ�����Ϣ
            {
                
            }
                break;
            case (K1|KEY_BREAK):      //K1�̰����ֲ����İ�����Ϣ
            {
                
            }
                break;
            case (K1|KEY_LONG_START):	//K1������ʼ��������Ϣ������Լ1��ʱ������
            {
                
            }
                break;
            case (K2|KEY_LONG_START):	//K2������ʼ��������Ϣ������Լ1��ʱ������
            {   
                
            }
                break;  
            case (K2|KEY_LONG_BREAK):	//K2����̧���������Ϣ������Լ1��ʱ������
            {
                
            }
        }
    }
#endif
#endif
}

void main_loop(void)
{
    static unsigned char k = 0;
    Key_Scan();     //����ɨ��
    if(Flag.Power)  //����
    {
        if(Flag.Dimming)  //�޼�����
        {
            k++;
            if(k >= 60)   //�仯ʱ��
            {
                k = 0;
                LED_Dimming();  
            }
        }
        if(!Flag.Dimming)  //�޼��������
        {
            Flag.Dimming = 0;
        }
        Assignment();      //��ȡPWMֵ
    }
    if(!Flag.Power)         //�ػ�
    {
        LED_C_DutyDat = LED_W_DutyDat = 0;
    }
    PWM_Update();      //����PWM
}


