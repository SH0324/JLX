#ifndef _TK_API_C_
#define _TK_API_C_

#include "rtc.h"		
#include "system_clock.h"		
#include "uart.h"

#include "delay.h"

#include "ts_configuration.h"
#include "ts_def.h"
#include "ts_api.h"
#include "ts_service.h"	

void Debug_init(void);
#if SUPPORT_KEY
code unsigned int TS_KEY_CH_INFO_SEQ[][2]=
{
	KEY_SEQ
};
#endif
#if SUPPORT_WHEEL_SLIDER
code unsigned char TS_WHEEL_SLIDER_CH_SEQ[]=
{
#if (WHEEL_SLIDER_COUNT > 0)
	WHEEL_SLIDER0_SEQ,
#endif
#if (WHEEL_SLIDER_COUNT > 1)
	WHEEL_SLIDER1_SEQ,
#endif
#if (WHEEL_SLIDER_COUNT > 2)
	WHEEL_SLIDER2_SEQ,
#endif
#if (WHEEL_SLIDER_COUNT > 3)
	WHEEL_SLIDER3_SEQ
#endif
};
code unsigned char WHEEL_SLIDER0_MAX_MIN_TAB[]={WHEEL_SLIDER0_CH_MIN_RATE};
#if (WHEEL_SLIDER_COUNT > 1)
code unsigned char WHEEL_SLIDER1_MAX_MIN_TAB[]={WHEEL_SLIDER1_CH_MIN_RATE};
#endif
#if (WHEEL_SLIDER_COUNT > 2)
code unsigned char WHEEL_SLIDER2_MAX_MIN_TAB[]={WHEEL_SLIDER2_CH_MIN_RATE};
#endif
#if (WHEEL_SLIDER_COUNT > 3)
code unsigned char WHEEL_SLIDER3_MAX_MIN_TAB[]={WHEEL_SLIDER3_CH_MIN_RATE};
#endif
code unsigned char *WHEEL_SLIDER_MIN_RATE[]=
{
	WHEEL_SLIDER0_MAX_MIN_TAB,
#if (WHEEL_SLIDER_COUNT > 1)
	WHEEL_SLIDER1_MAX_MIN_TAB,
#endif
#if (WHEEL_SLIDER_COUNT > 2)
	WHEEL_SLIDER2_MAX_MIN_TAB,
#endif
#if (WHEEL_SLIDER_COUNT > 3)
	WHEEL_SLIDER3_MAX_MIN_TAB,
#endif
};
code unsigned char WHEEL_SLIDER_TOUCH_THD[]=
{
	WHEEL_SLIDER0_TOUCH_THD,
#if (WHEEL_SLIDER_COUNT > 1)
	WHEEL_SLIDER1_TOUCH_THD,
#endif
#if (WHEEL_SLIDER_COUNT > 2)
	WHEEL_SLIDER2_TOUCH_THD,
#endif
#if (WHEEL_SLIDER_COUNT > 3)
	WHEEL_SLIDER3_TOUCH_THD,
#endif	
};
code unsigned char SLIDER_CH_COUNT[]=
{
	WHEEL_SLIDER0_CH_COUNT,
#if (WHEEL_SLIDER_COUNT > 1)
	WHEEL_SLIDER1_CH_COUNT,
#endif
#if (WHEEL_SLIDER_COUNT > 2)
	WHEEL_SLIDER2_CH_COUNT,
#endif	
#if (WHEEL_SLIDER_COUNT > 3)
	WHEEL_SLIDER3_CH_COUNT,
#endif	
};
code unsigned char WHEEL_OR_SLIDER_DEF[]=
{
	WHEEL_OR_SLIDER_DEF0,
#if (WHEEL_SLIDER_COUNT > 1)
	WHEEL_OR_SLIDER_DEF1,
#endif
#if (WHEEL_SLIDER_COUNT > 2)
	WHEEL_OR_SLIDER_DEF2,
#endif	
#if (WHEEL_SLIDER_COUNT > 3)
	WHEEL_OR_SLIDER_DEF3,
#endif	
};
code unsigned char WHEEL_SLIDER_NOISE_THD[]=
{
	WHEEL_SLIDER0_NOISE_THD,
#if (WHEEL_SLIDER_COUNT > 1)
	WHEEL_SLIDER1_NOISE_THD,
#endif
#if (WHEEL_SLIDER_COUNT > 2)
	WHEEL_SLIDER2_NOISE_THD,
#endif	
#if (WHEEL_SLIDER_COUNT > 3)
	WHEEL_SLIDER3_NOISE_THD,
#endif	
};
#else
code unsigned char TS_WHEEL_SLIDER_CH_SEQ[]={0};
code unsigned char *WHEEL_SLIDER_MIN_RATE[]={0};
code unsigned char WHEEL_SLIDER_TOUCH_THD[]={0};
code unsigned char SLIDER_CH_COUNT[]={0};
code unsigned char WHEEL_OR_SLIDER_DEF[]={0};
code unsigned char WHEEL_SLIDER_NOISE_THD[]={0};
#endif	
#if SUPPORT_KEY	
code unsigned long int MASK_TAB[24]=
{
	0x000001,
	0x000002,
	0x000004,
	0x000008,
	0x000010,
	0x000020,
	0x000040,
	0x000080,
	0x000100,
	0x000200,
	0x000400,
	0x000800,
	0x001000,
	0x002000,
	0x004000,
	0x008000,
	0x010000,
	0x020000,
	0x040000,
	0x080000,
	0x100000,
	0x200000,
	0x400000,
	0x800000,
};
code unsigned char AREA_CONFIRM_TIME_TAB[]=
{
	FINGER_TOUCH_CONFIRM_TIME,
	AREA_PNOISE_PLUS_CONFIRM_TIME,
	AREA_PNOISE_CONFIRM_TIME,
	AREA_NNOISE_CONFIRM_TIME,
	AREA_OVERLOW_CONFIRM_TIME,
};
#else
code unsigned char AREA_CONFIRM_TIME_TAB[1]={0};
code unsigned long int MASK_TAB[1]={0};
#endif
void TS_MS_ISR (void)
{
	static unsigned char xdata ms_cnt = 0;
	unsigned char i;
 
	ms_cnt++;
	if(ms_cnt >= 4)
	{
		ms_cnt = 0;
		for(i = 0; i < TS_Cnt; i++)
		{
			if(TS_AreaConfirmTimer[i])
			{
				TS_AreaConfirmTimer[i]--;
			}
		}
#if SUPPORT_WHEEL_SLIDER	
		for(i = 0; i < WHEEL_SLIDER_COUNT; i++)
		{
			if(TSWheelSlider_TouchConfirmTimer[i])
			{
				TSWheelSlider_TouchConfirmTimer[i]--;
			}
		}	
#endif
	}	
}
void TS_HS_ISR (void)
{
	unsigned char i;
#if SUPPORT_KEY
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
	for(i = 0; i < Key_Cnt; i++)
	{
		if(TSKey_LongTouchLimitTimer[i])
		{
			TSKey_LongTouchLimitTimer[i]--;
		}
	}		
#endif
#endif
#if SUPPORT_WHEEL_SLIDER	
#if (WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT > 0)
	for(i = 0; i < WHEEL_SLIDER_COUNT; i++)
	{
		if(TSWheelSlider_LongTouchLimitTimer[i])
		{
			TSWheelSlider_LongTouchLimitTimer[i]--;
		}
	}
#endif
#endif
	if(TS_RefCHBaseLineAdjuTimer)
	{
		TS_RefCHBaseLineAdjuTimer--;
	}	
	if(EnterStopScanTimer)
	{
		EnterStopScanTimer--;
	}	
	if(TS_ForbidTimer)
	{
		TS_ForbidTimer--;
	}
}
void TS_ISR (void)
{	
	unsigned char index_copy;
	unsigned int TKMS_Sum;
	WORD_UNION TS_Data;
	unsigned char i;
	index_copy = INDEX;
	TKIF = 0x3F; 
	TKMS_Sum = 0;
	for(i=0;i<TS_AcqTimes;i++)
	{
		INDEX = i;
		TS_Data.bVal[0] = TKMSH;
		TS_Data.bVal[1] = TKMSL;
		TKMS_Sum += TS_Data.wVal;
	}	
	if(TS_Index >= TS_Cnt)
	{
		TS_RefChRawData = TKMS_Sum;
	}
	else
	{
		TS_RawData[TS_Index] = TKMS_Sum;
		TS_CfgPinFunc(TS_Index,OUTPUT);
	}
	TS_Index++;
	if(TS_Index > TS_Cnt)
	{
		TS_CycleScanDoneFlag = 1;	
	}
	else
	{
		TS_ScanContinue();	
	}
	INDEX = index_copy;
}
void TS_RunInit(void)
{
	unsigned char i;
	static unsigned char TS_ScanTimes=0;
	if(TS_Init_Step == 0)
	{
		TS_AcqCnt = 0;
		TS_ScanStart();	
		TS_Init_Step = 1;		
		TS_ScanTimes = 50;	
	}
	else if(TS_Init_Step == 1)
	{
		if(TS_CycleScanDoneFlag)
		{
			TS_CycleScanDoneFlag = 0;
			if(--TS_ScanTimes)
			{
				TS_ScanStart();						
				return;
			}
			TS_RefCHBaseLineAdjuTimer = 0;
			TS_ForbidTimer = 0;
			for(i = 0; i < TS_Cnt; i++)
			{	
#if (SUPPORT_KEY && SUPPORT_WHEEL_SLIDER)
				if(i < Key_Cnt)
				{
					TSKey_FingerThd[i] = TS_KEY_CH_INFO_SEQ[i][1];
					TS_AreaConfirmTimerSet(i,AREA_PNOISE);
				}
				else
				{
					TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
				}
#elif SUPPORT_KEY
				TSKey_FingerThd[i] = TS_KEY_CH_INFO_SEQ[i][1];
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);				
#elif SUPPORT_WHEEL_SLIDER
				TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
#endif

				TS_FilterBuf[i] = TS_RawData[i]*FilterCount;
				TS_BaseLineData[i] = TS_RawData[i];			
				TS_FirstAreaData[i] = TS_RawData[i]; 
			}	
			TS_RefChBaseLineData  = TS_RefChRawData;	
			TS_RefFilterBuf = TS_RefChRawData*FilterCount;
		
			TS_State = TS_DEAL;	
			TS_ScanStart();							
		}
	}
}

#if SUPPORT_KEY
void TSKey_DataDeal(void)
{
	unsigned char i;
	unsigned char  TouchArea,NowArea;		
	
	for(i = 0; i < Key_Cnt; i++)
	{								
		TouchArea = TS_GetDataArea(i,TS_FirstAreaData[i]);
		NowArea   = TS_GetDataArea(i,TS_PostData[i]);

		if((NowArea != AREA_PNOISE)&&(NowArea != AREA_NNOISE))
		{
			TS_StableFlag = 0;
		}
		if(TouchArea == AREA_FINGER_TOUCH)
		{
			if(NowArea == AREA_FINGER_TOUCH)
			{
				if(!(KeysFlagSN & MASK_TAB[i]))
				{
					if(!TS_AreaConfirmTimer[i])
					{		
						KeysFlagSN |= MASK_TAB[i];		
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
						TSKey_LongTouchLimitTimer[i] = FINGER_LONG_TOUCH_TIME_LIMIT;
#endif
						TS_AreaConfirmTimer[i] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;	
					}
				}
				else
				{	
					TS_AreaConfirmTimer[i] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
					if(!TSKey_LongTouchLimitTimer[i])
					{
						KeysFlagSN &= ~MASK_TAB[i];
						TS_FirstAreaData[i] = TS_PostData[i];
						TS_BaseLineData[i] 	= TS_PostData[i];
						TS_AreaConfirmTimerSet(i,AREA_PNOISE);			
					}							
#endif					
				}				
			}
			else
			{
				if(KeysFlagSN & MASK_TAB[i]) 
				{
					if(!TS_AreaConfirmTimer[i])
					{
						KeysFlagSN &= ~MASK_TAB[i];
						TS_FirstAreaData[i] = TS_PostData[i];
						TS_AreaConfirmTimerSet(i,NowArea);
					}					
				}			
				else
				{
					TS_FirstAreaData[i] = TS_PostData[i];
					TS_AreaConfirmTimerSet(i,NowArea);
				}	
			}	
			continue;						
		}	
		else
		{
			if(NowArea == AREA_FINGER_TOUCH)
			{
				TS_FirstAreaData[i] = TS_PostData[i];
				TS_AreaConfirmTimerSet(i,AREA_FINGER_TOUCH);
				continue;		
			}	
		}
		if(KeysFlagSN != 0) 
		{
			TS_FirstAreaData[i] = TS_BaseLineData[i];
			TS_AreaConfirmTimerSet(i,AREA_PNOISE);		
			continue;			
		}
		if(TS_AreaDeviateDetection(i,TS_FirstAreaData[i],TS_PostData[i]))	   //判断偏差是否在允许范围内
		{	
			if(!TS_AreaConfirmTimer[i])
			{
				TS_FirstAreaData[i] = TS_PostData[i];
				TS_BaseLineData[i] 	= TS_PostData[i];
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);	
			}		
		}
		else
		{
			TS_FirstAreaData[i] = TS_PostData[i];	
			TS_AreaConfirmTimerSet(i,NowArea);				
		}
	}	 	
	if(KeysFlagSN != 0) 
	{
		ActiveTouchType = 1;
	}
	else
	{
		ActiveTouchType = 0;
	}
}
#endif
#if SUPPORT_WHEEL_SLIDER
void TS_WheelSliderDeal(void)
{
	unsigned char num,i;
	unsigned int   Delta,Position;
	bit WheelSliderTogFlag = 0;
	if(!W_S_RefChSet)
	{
		W_S_RefChSet = 1;		
		SetWheelSliderRefCh(WHEEL_SLIDER_COUNT);
	}
	TS_BaseCh = Key_Cnt; 
	for(num = 0; num < WHEEL_SLIDER_COUNT; num++)
	{
#if PRINT_WHEEL_SLIDER_DATA_EN
		if(num == PRINT_WHEEL_SLIDER_NUM)
		{
			TK_Debug_UartPutChar(0xaa);
			for(i = TS_BaseCh; i < TS_BaseCh + SLIDER_CH_COUNT[num]; i++)
			{						
				if(TS_BaseLineData[i] > TS_PostData[i])
				{
					Delta = (int)TS_BaseLineData[i] - (int)TS_PostData[i];	
				}
				else
				{
					Delta = 0;
				}						
				TK_Debug_UartPutChar(i);
				TK_Debug_UartPutChar(TS_PostData[i]>>8);
				TK_Debug_UartPutChar(TS_PostData[i]);			
				TK_Debug_UartPutChar(TS_BaseLineData[i]>>8);
				TK_Debug_UartPutChar(TS_BaseLineData[i]);	
				TK_Debug_UartPutChar(Delta>>8);	
				TK_Debug_UartPutChar(Delta);								
			}				
		}
#endif
		if((ActiveWheelSliderNum != num) && (ActiveWheelSliderNum != 0xFF))
		{
			TS_BaseCh += SLIDER_CH_COUNT[num];
			continue;
		}
		Position = WheelSliderTouchJudge(num);
		if(Position != -1)
		{
			TS_StableFlag = 0;
		}
		if(WheelSliderState[num] == WHEEL_SLIDER_NO_TOUCH)
		{
			if(!WheelSliderTouchFlag[num])
			{
				if(Position != -1)
				{
					WheelSliderTouchFlag[num] = 1;	
					TSWheelSlider_TouchConfirmTimer[num] = WHEEL_SLIDER_TOUCH_CONFIRM_TIME;				
				}
				else
				{
					for(i = TS_BaseCh; i < TS_BaseCh + SLIDER_CH_COUNT[num]; i++)
					{						
						if(TS_FirstAreaData[i] > TS_PostData[i]) 
						{
							Delta 	= TS_FirstAreaData[i] - TS_PostData[i];
						}
						else
						{
							Delta 	= TS_PostData[i] - TS_FirstAreaData[i];
						}					
						if(Delta <= WHEEL_SLIDER_NOISE_THD[num]) 
						{
							if(!TS_AreaConfirmTimer[i])
							{
								TS_FirstAreaData[i] = TS_PostData[i];
 								TS_BaseLineData[i] 	= TS_PostData[i];
								TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
							}							
						}
						else
						{
							TS_FirstAreaData[i] = TS_PostData[i];
							TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
						}
					}
				}			
			}	
			else
			{	
				if(Position != -1)
				{
					if(!TSWheelSlider_TouchConfirmTimer[num])
					{
						WheelSliderState[num] = WHEEL_SLIDER_TOUCH;	
						ActiveWheelSliderNum = num;
#if (WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT > 0)
						TSWheelSlider_LongTouchLimitTimer[num] = WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT;
#endif
					}	
				}
				else
				{
					WheelSliderTouchFlag[num] = 0;
					for(i = TS_BaseCh; i < TS_BaseCh + SLIDER_CH_COUNT[num]; i++)
					{
						TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
					}
				}
			}				
		}
		else if(WheelSliderState[num] == WHEEL_SLIDER_TOUCH)
		{		
#if (WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT > 0)
			if(!TSWheelSlider_LongTouchLimitTimer[num])
			{
				for(i = TS_BaseCh; i < TS_BaseCh + SLIDER_CH_COUNT[num]; i++)
				{
					TS_FirstAreaData[i] = TS_PostData[i];
 					TS_BaseLineData[i] 	= TS_PostData[i];
				}
				WheelSliderTouchFlag[num] = 0;
				goto WHEEL_SLIDER_RELEASE;
			}
#endif
			if(WheelSliderTouchFlag[num])
			{
				if(Position == -1)	
				{
					WheelSliderTouchFlag[num] = 0;
					TSWheelSlider_TouchConfirmTimer[num] = WHEEL_SLIDER_TOUCH_RELEASE_CONFIRM_TIME;		
				}
			}
			else						 
			{
				if(Position == -1)	
				{
					if(!TSWheelSlider_TouchConfirmTimer[num])
					{
WHEEL_SLIDER_RELEASE:
						WheelSliderState[num] = WHEEL_SLIDER_NO_TOUCH;	
						WheelSliderCapRateFilter[num] = 0;
						WheelSliderPosition[num] = -1;
						ActiveWheelSliderNum = 0xFF;
						for(i = TS_BaseCh; i < TS_BaseCh + SLIDER_CH_COUNT[num]; i++)
						{
							TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
						}
					}
				}
				else
				{
					WheelSliderTouchFlag[num] = 1;				
				}
			}		
		}		
		if(WheelSliderState[num] == WHEEL_SLIDER_TOUCH)
		{
			if(Position != -1)
			{
				WheelSliderPosition[num] = Position;
			}	
#if PRINT_WHEEL_SLIDER_POSITION_EN
			TK_Debug_UartPutChar(num + 0x30);	
			TK_Debug_UartPutChar(' ');
			
			TK_Debug_UartPutChar(WheelSliderPosition[num]/100+0x30);		
			TK_Debug_UartPutChar((WheelSliderPosition[num]%100)/10+0x30);		
			TK_Debug_UartPutChar((WheelSliderPosition[num]%10)+0x30);	

			TK_Debug_UartPutChar('\r');	
			TK_Debug_UartPutChar('\n');	
#endif
#if PRINT_WHEEL_SLIDER_RATE_EN
			if(num == PRINT_WHEEL_SLIDER_NUM)
			{
				unsigned char DeltaRate;
				DeltaRate = WheelSliderCapRateFilter[num]/4;
				TK_Debug_UartPutChar(WheelSliderMaxIdx[num] + 0x30);	
				TK_Debug_UartPutChar(' ');
				
				TK_Debug_UartPutChar(DeltaRate/100+0x30);		
				TK_Debug_UartPutChar((DeltaRate%100)/10+0x30);		
				TK_Debug_UartPutChar((DeltaRate%10)+0x30);	
				TK_Debug_UartPutChar('\r');	
				TK_Debug_UartPutChar('\n');					
			}

#endif
		}
		else
		{
			WheelSliderPosition[num] = -1;
		}
		if(WheelSliderPosition[num] != -1)
		{
			WheelSliderTogFlag = 1;
		}
		TS_BaseCh += SLIDER_CH_COUNT[num];
	}
	if(WheelSliderTogFlag)
	{
		ActiveTouchType = 2;
	}
	else
	{
		ActiveTouchType = 0;
	}
}
#endif
void TS_init(void)
{
	unsigned char i,ch_idx;
#if (DEBUG)
	Debug_init();
#endif
	TS_Cnt 		= OPENED_TS_COUNT;
	Key_Cnt 	= KEY_CH_COUNT;
	ch_idx = 0;
	for(i = 0;i < OPENED_TS_COUNT; i++)
	{
#if (SUPPORT_KEY && SUPPORT_WHEEL_SLIDER)
		if(i < KEY_CH_COUNT)
		{
			TS_CH[ch_idx++] = TS_KEY_CH_INFO_SEQ[i][0];
		}
		else
		{
			TS_CH[ch_idx++] = TS_WHEEL_SLIDER_CH_SEQ[i-KEY_CH_COUNT];
		}
#elif SUPPORT_KEY
		TS_CH[ch_idx++] = TS_KEY_CH_INFO_SEQ[i][0];
#elif SUPPORT_WHEEL_SLIDER
		TS_CH[ch_idx++] = TS_WHEEL_SLIDER_CH_SEQ[i];
#endif
	}
	
#if (RTC_CLK_SELECT == IRCL)
	CKCON |= ILCKE;
	CKSEL |= RTCKS(1);
#elif (RTC_CLK_SELECT == XOSCL)	
	CKCON |= XLCKE;
	while(!(CKCON & XLSTA));
#endif

	RTC_init(RTCE_On,MSE_On,HSE_On);
	RTC_SetRTMSS(0);

	INT8EN = 1;			
	
	TS_IO_init();
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|TWKE(0)|VRS(VRS_VAL);
	TKCFG = TKDIV(TKDIV_VAL)|TKTMS(TKTMS_VAL);		
	INT3EN = 1; 
	
	TS_CycleScanDoneFlag = 0;
#if SUPPORT_KEY
	KeysFlagSN = 0;
#endif	
	ActiveTouchType = 0;
	
#if SUPPORT_TOUCH_SLEEP_MODE
	EnterStopScanTimer = ENTER_STOP_MODE_TIME;
  TS_SleepEn = 1;
#endif
#if SUPPORT_WHEEL_SLIDER
	W_S_RefChSet = 0;
	for(i = 0; i < WHEEL_SLIDER_COUNT; i++)
	{
		WheelSliderState[i] = WHEEL_SLIDER_NO_TOUCH;
		WheelSliderTouchFlag[i] = 0;
		WheelSliderPosition[i] = -1;
		WheelSliderCapRateFilter[i] = 0;		
	}
	ActiveWheelSliderNum = 0xFF;
#endif
	TS_State = TS_INIT;
	TS_Init_Step = 0;
	
	TS_AcqTimes 									= TS_ACQ_TIMES;
	FilterCount 									= FILTER_COUNT;
	
#if SUPPORT_KEY	
#if GENERATE_TS_KEY_EN
	TK_State = TK_STATE_RELEASE;
	TS_Key = 0;
#endif
#endif
}

void TS_Action(void)
{
#if SUPPORT_TOUCH_SLEEP_MODE
	bit EnterStopFlag = 0;
#endif
	switch(TS_State)
	{
		case TS_INIT:
			TS_RunInit();			
			break;
		case TS_DEAL:		
			if(TS_CycleScanDoneFlag)
			{			
				TS_CycleScanDoneFlag = 0;
#if SUPPORT_KEY	
				TS_CheckRefCh();
#endif
				TS_DataFiltering();
#if SUPPORT_TOUCH_SLEEP_MODE
				if(EnterStopScanTimer)
#endif
				{
					TS_Index = 0;
					TS_ScanStart();									
				}
#if SUPPORT_TOUCH_SLEEP_MODE
				else
				{
					EnterStopFlag = 1;
				}
#endif
				if(!TS_ForbidTimer)
				{
					TS_StableFlag = 1;
#if SUPPORT_KEY	
					if(ActiveTouchType != 2)
					{
						TSKey_DataDeal();	
					}
#endif
				}
#if SUPPORT_WHEEL_SLIDER
				if(ActiveTouchType != 1)
				{
					TS_WheelSliderDeal();
				}
#endif				
#if SUPPORT_TOUCH_SLEEP_MODE
				if(!TS_StableFlag || !TS_SleepEn || TS_ForbidTimer)
				{
					EnterStopScanTimer = ENTER_STOP_MODE_TIME;
				}			
				if(EnterStopFlag&&TS_SleepEn)
				{
#if ENTER_SLEEP_PRINT_EN
					TK_Debug_UartPutChar('s');	
					TK_Debug_UartPutChar('l');	
					TK_Debug_UartPutChar('e');	
					TK_Debug_UartPutChar('e');	
					TK_Debug_UartPutChar('p');	
					TK_Debug_UartPutChar('\r');	
					TK_Debug_UartPutChar('\n');		
					Delay_ms(1);
#endif
					TS_EnterSleepMode();		
#if ENTER_SLEEP_PRINT_EN					
					TK_Debug_UartPutChar('e');	
					TK_Debug_UartPutChar('x');	
					TK_Debug_UartPutChar('i');	
					TK_Debug_UartPutChar('t');	
					TK_Debug_UartPutChar('\r');	
					TK_Debug_UartPutChar('\n');		
#endif
				}
#endif										
			}
			break;
		default:
			break;
	}
#if SUPPORT_KEY	
#if GENERATE_TS_KEY_EN
	TS_GetKey();
#endif
#endif
}
#if SUPPORT_TOUCH_SLEEP_MODE
void TS_EnterSleepMode(void)
{
//省电模式参数配置
	#define STOP_TKDIV_VAL			0
	#define STOP_TKTMS_VAL			4		//放电时间
	#define STOP_VRS_VAL				7			//比较器阈值	
	unsigned char TS_AcqCnt = 0,i;
	unsigned int xdata WakeUp_PThdVal[OPENED_TS_COUNT];
	unsigned int xdata WakeUp_NThdVal[OPENED_TS_COUNT];	
	WORD_UNION TS_Data;
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_IRCH();
	PLLCON = 0;
#endif	
	P30F = P30F | PU_EN;
	P31F = P31F | PU_EN;
	RTCON &=  ~(MSE(1) | HSE(1));
	RTCIF = RTC_MF | RTC_HF;	
	
	TKCON = (TKCON&0xF8) | VRS(STOP_VRS_VAL);
	TKCON &= ~TKIE(1);
	TKCON |= TMEN(1);
	TKCFG = TKDIV(STOP_TKDIV_VAL)|TKTMS(STOP_TKTMS_VAL);		
	TKMTS = SLEEP_MODE_SCAN_INTERVAL_TIME/(OPENED_TS_COUNT);

#ifdef LVD_RST_ENABLE
	LVDCON = 0;	
#endif		
	I2CCON = 0;
	CKCON = 0;
		
	MECON |= BIT6;
	
	TKIF = 0x3F;
	
	PWCON = PWCON&(~0x08);	
	
	for(i=0;i<6;i++)
	{
		INDEX = i;
		TKCHS = 0;
	}
	TS_IO_init();
	
	TS_Index = 0;
	INDEX = 0;
	TKCHS = MPOL(0)|NPOL(0)|TKCHS((TS_CH[TS_Index])+1);
	TS_CfgPinFunc(TS_Index,4);
	TKCON |= TKST(1);
	while(1)
	{
		if(!(PCON & BIT2))	// 在仿真模式不进入STOP模式
		{
			PCON |= (1<<1);
		}
		_nop_();
		_nop_();
		if(TKIF != 0)
		{
			TKIF = 0x3F;	
			INDEX = 0;
			TS_Data.bVal[0] = TKMSH;
			TS_Data.bVal[1] = TKMSL;

			if(TS_AcqCnt == 2)
			{
				WakeUp_PThdVal[TS_Index] = TS_Data.wVal - SLEEP_TOUTH_THD;
				WakeUp_NThdVal[TS_Index] = TS_Data.wVal + SLEEP_TOUTH_THD;
			}
			else if(TS_AcqCnt > 2)
			{
				if((TS_Data.wVal <= WakeUp_PThdVal[TS_Index])||(TS_Data.wVal >= WakeUp_NThdVal[TS_Index]))
				{
					break;			
				}
			}
 			TS_CfgPinFunc(TS_Index,OUTPUT);
			TS_Index++;
			if(TS_Index >= OPENED_TS_COUNT)
			{
				TS_Index = 0;
				if(TS_AcqCnt < 0xff)
				{
					TS_AcqCnt++;
				}	
			}
			TS_CfgPinFunc(TS_Index,4);
			INDEX = 0;
			TKCHS = MPOL(0)|NPOL(0)|TKCHS((TS_CH[TS_Index])+1);
			TKCON |= TKST(1);
		}
	}
	PWCON |= 0x08;	
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);
#endif
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|TWKE(0)|VRS(VRS_VAL);
	TKCFG = TKDIV(TKDIV_VAL)|TKTMS(TKTMS_VAL);	

	RTCON |= HSE(1)|MSE(1);
	TS_CfgPinFunc(TS_Index,OUTPUT);
	TS_ScanStart();
	EnterStopScanTimer = ENTER_STOP_MODE_TIME;
	#ifdef LVD_RST_ENABLE
	LVDCON = 0xC3;	//设置LVD复位电压为2V
	#endif							
	P30F = P30F & (~PU_EN);
	P31F = P31F & (~PU_EN);	
}
#endif
/*********************************************************************************************************************/
#if SUPPORT_KEY	
#if GENERATE_TS_KEY_EN
typedef struct 
{	
	unsigned char 	TogKeyNum;
	unsigned char 	TogKeyList[2];
}
T_TogKeyInfo;
code unsigned char TS_KEY_TAB[]=
{
	K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K20,K21,K22,K23,K24
};
void TS_GetTogKeyInfor(T_TogKeyInfo *pKeyInfo)
{
	unsigned char i,index;
	pKeyInfo->TogKeyNum = 0;
	index = 0;
	for(i = 0; i < KEY_CH_COUNT; i++)
	{
		if(KeysFlagSN & MASK_TAB[i])
		{
			pKeyInfo->TogKeyNum++;
			
			if(pKeyInfo->TogKeyNum <= 2)
			{
				pKeyInfo->TogKeyList[index++] = TS_KEY_TAB[i];
			}
		}
	}
}
#if PRINT_TS_KEY_EN
void Hex2CharPrint(unsigned int integar)
{
	unsigned char CharBuf[4];
	unsigned char i, temp;
	for(i = 0; i < 4; i++)
	{
		temp = (unsigned char)(integar&0x0F);
		if(temp >= 0x0A)
		{
			CharBuf[i] = (temp - 0x0A) + 'A';
		}
		else
		{
			CharBuf[i] = temp + '0';
		}
		integar >>= 4;
	}
	TK_Debug_UartPutChar('0');	
	TK_Debug_UartPutChar('x');	
	TK_Debug_UartPutChar(CharBuf[2]);
	TK_Debug_UartPutChar(CharBuf[1]);
	TK_Debug_UartPutChar(CharBuf[0]);
}
#endif
void TS_GetKey(void)
{
	static unsigned int KeyBak;	
	static bit LongFlag;
	T_TogKeyInfo KeyInfo;
	TS_Key = 0;
	TS_GetTogKeyInfor(&KeyInfo);
		
	if(TK_State == TK_STATE_RELEASE)
	{
		if(KeyInfo.TogKeyNum != 0)
		{			
			if(KeyInfo.TogKeyNum == 1)
			{
				KeyBak = (unsigned int)KeyInfo.TogKeyList[0];
				TK_State = TK_STATE_SINGLE_KEY_PRESS;				
			}
			else if(KeyInfo.TogKeyNum == 2)
			{
				KeyBak = ((unsigned int)KeyInfo.TogKeyList[0]<<5)|(unsigned int)KeyInfo.TogKeyList[1];
				TK_State = TK_STATE_DOUBLE_KEY_PRESS;
			}
			TS_Key = KeyBak;
			LongFlag = 0;
			TS_LongKeyTimer = TS_LONG_START_TIME;
		}
	}
	else if(TK_State == TK_STATE_SINGLE_KEY_PRESS)
	{
		if(KeyInfo.TogKeyNum == 1)
		{
			if(KeyBak == (unsigned int)KeyInfo.TogKeyList[0])
			{
				if(!TS_LongKeyTimer)
				{
					if(!LongFlag)
					{
						LongFlag = 1;
						TS_Key = KeyBak | KEY_LONG_START;
					}
					else
					{
						TS_Key = KeyBak | KEY_LONG;
					}
					TS_LongKeyTimer = TS_LONG_TIME;
				}				
			}
			else 
			{
				if(!LongFlag)
				{
					TS_Key = KeyBak | KEY_BREAK;
				}
				else
				{
					TS_Key = KeyBak | KEY_LONG_BREAK;
				}
				TK_State = TK_STATE_RELEASE;
			}
		}
		else if(KeyInfo.TogKeyNum == 2)
		{
			KeyBak = ((unsigned int)KeyInfo.TogKeyList[0]<<5) | (unsigned int)KeyInfo.TogKeyList[1];
			TK_State = TK_STATE_DOUBLE_KEY_PRESS;
			TS_Key = KeyBak;
			LongFlag = 0;
			TS_LongKeyTimer = TS_LONG_START_TIME;
		}
		else if(KeyInfo.TogKeyNum == 0)
		{
			if(!LongFlag)
			{
				TS_Key = KeyBak | KEY_BREAK;
			}
			else
			{
				TS_Key = KeyBak | KEY_LONG_BREAK;
			}
			TK_State = TK_STATE_RELEASE;
		}
	}
	else if(TK_State == TK_STATE_DOUBLE_KEY_PRESS)
	{
		if(KeyInfo.TogKeyNum == 2)
		{
			if(KeyBak == ((unsigned int)KeyInfo.TogKeyList[0]<<5)|(unsigned int)KeyInfo.TogKeyList[1])
			{
				if(!TS_LongKeyTimer)
				{
					if(!LongFlag)
					{
						LongFlag = 1;
						TS_Key = KeyBak | KEY_LONG_START;
					}
					else
					{
						TS_Key = KeyBak | KEY_LONG;
					}
					TS_LongKeyTimer = TS_LONG_TIME;
				}					
			}
		}
		else if(KeyInfo.TogKeyNum == 0)
		{
			if(!LongFlag)
			{
				TS_Key = KeyBak | KEY_BREAK;
			}
			else
			{
				TS_Key = KeyBak | KEY_LONG_BREAK;
			}
			TK_State = TK_STATE_RELEASE;		
		}
	}
#if PRINT_TS_KEY_EN
	if(TS_Key != 0)
	{
		if((TS_Key & 0xFF00) == 0)
		{
			if(TS_Key > 0x1F)
			{
				TK_Debug_UartPutChar('d');	
				TK_Debug_UartPutChar('o');	
				TK_Debug_UartPutChar('u');	
				TK_Debug_UartPutChar('b');	
				TK_Debug_UartPutChar('l');	
				TK_Debug_UartPutChar('e');			
			}
			else
			{
				TK_Debug_UartPutChar('s');	
				TK_Debug_UartPutChar('i');	
				TK_Debug_UartPutChar('n');	
				TK_Debug_UartPutChar('g');	
				TK_Debug_UartPutChar('l');	
				TK_Debug_UartPutChar('e');		
			}
			TK_Debug_UartPutChar(' ');	
			TK_Debug_UartPutChar('k');	
			TK_Debug_UartPutChar('e');	
			TK_Debug_UartPutChar('y');	
			TK_Debug_UartPutChar(' ');	
			TK_Debug_UartPutChar('=');	
			TK_Debug_UartPutChar(' ');	
			Hex2CharPrint(TS_Key);
			TK_Debug_UartPutChar('\r');	
			TK_Debug_UartPutChar('\n');	
		}
		else if(TS_Key & KEY_BREAK)
		{
			TK_Debug_UartPutChar('k');	
			TK_Debug_UartPutChar('e');	
			TK_Debug_UartPutChar('y');	
			TK_Debug_UartPutChar(' ');	
			TK_Debug_UartPutChar('u');	
			TK_Debug_UartPutChar('p');	
			TK_Debug_UartPutChar('\r');	
			TK_Debug_UartPutChar('\n');				
		}
		else if(TS_Key & KEY_LONG_START)
		{
			TK_Debug_UartPutChar('l');	
			TK_Debug_UartPutChar('o');	
			TK_Debug_UartPutChar('n');	
			TK_Debug_UartPutChar('g');	
			TK_Debug_UartPutChar(' ');	
			TK_Debug_UartPutChar('s');	
			TK_Debug_UartPutChar('t');	
			TK_Debug_UartPutChar('a');	
			TK_Debug_UartPutChar('r');	
			TK_Debug_UartPutChar('t');	
			TK_Debug_UartPutChar('\r');	
			TK_Debug_UartPutChar('\n');			
		}
		else if(TS_Key & KEY_LONG)
		{
			TK_Debug_UartPutChar('l');	
			TK_Debug_UartPutChar('o');	
			TK_Debug_UartPutChar('n');	
			TK_Debug_UartPutChar('g');	
			TK_Debug_UartPutChar('\r');	
			TK_Debug_UartPutChar('\n');			
		}
	}
#endif
}
#endif
#endif

#endif