#ifndef _I2C_C_
#define _I2C_C_

#include "ca51f_config.h"

#include "rtc.h"		
#include "system_clock.h"		

#include "ts_configuration.h"
#include "ts_def.h"
#include "ts_api.h"
#include "ts_service.h"		   
#if DEBUG
#include "i2c.h"		
void I2C_ISR(void);
#endif

#if DEBUG
#define I2C_ADDR		0xCA
unsigned char xdata TouchDebugID = '2';
unsigned char rxOffset;
unsigned char regAddr;
bit iicReadMode;
bit iicEnd;
code unsigned char *TS_INFO[]=
{
	&TouchDebugID,
	&TS_State,
	&Key_Cnt,
	&TS_RefChBaseLineData,
	&TS_RefPostData,
	&KeysFlagSN,
	&TS_BaseLineData[0],
	&TS_PostData[0],
	&TSKey_FingerThd[0],
	&TS_CH[0],
};
unsigned char *pTS_Info;
void I2C_ISR(void)
{
	unsigned char Sta_Temp;
					
	Sta_Temp = I2CSTA;			
	
	if(Sta_Temp == 0x60)			   //接收到从机地址+写位
	{			
		rxOffset = 0xff;
		iicReadMode = 0;
		I2CCON |= AAK(1);			
	}
	else if(Sta_Temp == 0x80)			   
	{					
		if(iicReadMode)	 				//发送一字节数据
		{
			rxOffset++;
			I2CDAT = *(pTS_Info+rxOffset);			
		}
		else									//接收到一字节数据
		{				
			if(rxOffset == 0xff) 		//地址
			{
				regAddr=I2CDAT;	 
				pTS_Info = TS_INFO[regAddr];
				rxOffset=0;
				I2CCON |= AAK(1);
			}
			else				   		//数据
			{
				*(pTS_Info+rxOffset) = I2CDAT;
				rxOffset++;	
				I2CCON |= AAK(1);		
			}
		}	
	}
	else if(Sta_Temp==0xA8)				//接收到从机地址+读位，发送ACK信号
	{								
		I2CDAT = *(pTS_Info+rxOffset);
		iicReadMode = 1;
	}
	else if(Sta_Temp == 0x88)	
	{
	}
	I2CFLG  |= I2CF;
}
void Debug_init(void)
{
#ifdef I2C_SELECT_P36_P37
	I2CIOS = 0;
	GPIO_Init(P36F,P36_I2C_SDA_SETTING);
	GPIO_Init(P37F,P37_I2C_SCL_SETTING);	
#elif defined I2C_SELECT_P30_P31
	I2CIOS = 1;
	GPIO_Init(P30F,P30_I2C_SDA_SETTING);
	GPIO_Init(P31F,P31_I2C_SCL_SETTING);
#elif defined I2C_SELECT_P66_P67
	I2CIOS = 2;
	GPIO_Init(P66F,P66_I2C_SDA_SETTING);
	GPIO_Init(P67F,P67_I2C_SCL_SETTING);
#elif defined I2C_SELECT_P61_P60
	I2CIOS = 3;
	GPIO_Init(P66F,P61_I2C_SDA_SETTING);
	GPIO_Init(P67F,P60_I2C_SCL_SETTING);
#endif
	I2CCON = I2CE(1) | I2CIE(1) | STA(0) | STP(0)| CKHD(0) | AAK(1)| CBSE(0) | STFE(0);		
	I2CADR = (I2C_ADDR>>1);
	
	INT6EN = 1;
	EXIP |= (1<<4);			//优先级设置为最高
}
#endif
#endif
