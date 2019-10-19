#include "lcd.h"

/***********************************************************************************
��������LCD_init
����˵����LCD�Ĵ�����ʼ��
���������  len  LCDʱ��Դѡ��
		   dmod	��������ѡ��
		   bias	ƫѹ����
		   ldrv	������ѹ�ȼ�����
		   lxdiv LCDʱ�ӷ�Ƶϵ��
����ֵ��	��
***********************************************************************************/
void LCD_init(LEN_TypeDef len,DMOD_TypeDef dmod,BIAS_TypeDef bias,LDRV_TypeDef ldrv,unsigned int lxdiv)
{
	LXDIVH = (unsigned char)(lxdiv>>8);
	LXDIVL = (unsigned char)(lxdiv);	
	LXCFG =	 DMOD(dmod) | BIAS(bias) | LDRV(ldrv);
	LXCON =  LEN(len) | LMOD(LMOD_lcd);	 
}
/***********************************************************************************
��������LED_init
����˵����LED�Ĵ�����ʼ��
��������� len	LCDʱ��Դѡ��
		 comhv	COM��Ч��ƽ����
		 seghv	SEG��Ч��ƽ����
		 lxdiv 	LEDʱ�ӷ�Ƶϵ��
����ֵ��	��						
***********************************************************************************/
void SEG_init(LEN_TypeDef len,COMHV_TypeDef comhv,SEGHV_TypeDef seghv,LDRV_TypeDef ldrv,unsigned int lxdiv)
{
	LXDIVH = (unsigned char)(lxdiv>>8);
	LXDIVL = (unsigned char)(lxdiv);	
	LXCFG =	 COMHV(comhv) | SEGHV(seghv) | BLNK(0)|LDRV(ldrv);
	LXCON =  LEN(len) | LMOD(LMOD_led);	 
}
/***********************************************************************************
��������LCD_LED_WriteLram
����˵����д�����ݵ���ʾ����
��������� 	laddr	��ʾ�����ַ
		    ldata	��ʾ��������
����ֵ��	��						
***********************************************************************************/
void LCD_WriteLram(unsigned char laddr, unsigned char ldata)
{
	INDEX = laddr;
	LXDAT = ldata;
}

/***********************************************************************************
��������LCD_LED_ReadLram
����˵��������ʾ�����ȡ����
��������� 	laddr		��ʾ�����ַ
����ֵ��	��ʾ��������			
***********************************************************************************/
unsigned char LCD_ReadLram(unsigned char laddr)
{
	INDEX = laddr;
	return LXDAT;
}
/*********************************************************************************************************************/