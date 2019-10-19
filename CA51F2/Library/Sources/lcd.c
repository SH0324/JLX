#include "lcd.h"

/***********************************************************************************
函数名：LCD_init
功能说明：LCD寄存器初始化
输入参数：  len  LCD时钟源选择
		   dmod	驱动电流选择
		   bias	偏压设置
		   ldrv	驱动电压等级设置
		   lxdiv LCD时钟分频系数
返回值：	无
***********************************************************************************/
void LCD_init(LEN_TypeDef len,DMOD_TypeDef dmod,BIAS_TypeDef bias,LDRV_TypeDef ldrv,unsigned int lxdiv)
{
	LXDIVH = (unsigned char)(lxdiv>>8);
	LXDIVL = (unsigned char)(lxdiv);	
	LXCFG =	 DMOD(dmod) | BIAS(bias) | LDRV(ldrv);
	LXCON =  LEN(len) | LMOD(LMOD_lcd);	 
}
/***********************************************************************************
函数名：LED_init
功能说明：LED寄存器初始化
输入参数： len	LCD时钟源选择
		 comhv	COM有效电平设置
		 seghv	SEG有效电平设置
		 lxdiv 	LED时钟分频系数
返回值：	无						
***********************************************************************************/
void SEG_init(LEN_TypeDef len,COMHV_TypeDef comhv,SEGHV_TypeDef seghv,LDRV_TypeDef ldrv,unsigned int lxdiv)
{
	LXDIVH = (unsigned char)(lxdiv>>8);
	LXDIVL = (unsigned char)(lxdiv);	
	LXCFG =	 COMHV(comhv) | SEGHV(seghv) | BLNK(0)|LDRV(ldrv);
	LXCON =  LEN(len) | LMOD(LMOD_led);	 
}
/***********************************************************************************
函数名：LCD_LED_WriteLram
功能说明：写入数据到显示缓存
输入参数： 	laddr	显示缓存地址
		    ldata	显示缓存数据
返回值：	无						
***********************************************************************************/
void LCD_WriteLram(unsigned char laddr, unsigned char ldata)
{
	INDEX = laddr;
	LXDAT = ldata;
}

/***********************************************************************************
函数名：LCD_LED_ReadLram
功能说明：从显示缓存读取数据
输入参数： 	laddr		显示缓存地址
返回值：	显示缓存数据			
***********************************************************************************/
unsigned char LCD_ReadLram(unsigned char laddr)
{
	INDEX = laddr;
	return LXDAT;
}
/*********************************************************************************************************************/