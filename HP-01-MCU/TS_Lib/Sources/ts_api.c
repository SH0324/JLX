#ifndef _TK_API_C_
#define _TK_API_C_

#include "rtc.h"		
#include "system_clock.h"		
#include "uart.h"

#include "adc.h"
#include "delay.h"

#include "ts_configuration.h"
#include "ts_def.h"
#include "ts_api.h"
#include "ts_service.h"		   

void Debug_init(void);
void Debug_ParamLoad(void);
#if TK_SENSITIVE_AUTO_TRIM_EN
void TK_TouchThdTrim(unsigned char ch);
#endif
#if SUPPORT_KEY
code unsigned int TS_KEY_CH_INFO_SEQ[][2]=
{
	KEY_SEQ
};
#if TK_SENSITIVE_AUTO_TRIM_EN
code unsigned int TK_BASELINE_VALUE_INFO_SEQ[]=
{
	TK_BASELINE_VALUE_SEQ
};
#endif
#endif
#if SUPPORT_WHEEL_SLIDER
code unsigned char TS_WHEEL_SLIDER_CH_SEQ[]=
{
	WHEEL_SLIDER0_SEQ,
};
code unsigned char WHEEL_SLIDER0_MAX_MIN_TAB[]={WHEEL_SLIDER0_CH_MIN_RATE};
#else
code unsigned char WHEEL_SLIDER0_MAX_MIN_TAB[1]={0};
#endif	
#if SUPPORT_KEY	
code TYPE_SN MASK_TAB[]=
{
	0x000001,
#if (KEY_CH_COUNT > 1)
	0x000002,
#endif
#if (KEY_CH_COUNT > 2)
	0x000004,
#endif
#if (KEY_CH_COUNT > 3)
	0x000008,
#endif
#if (KEY_CH_COUNT > 4)
	0x000010,
#endif
#if (KEY_CH_COUNT > 5)
	0x000020,
#endif
#if (KEY_CH_COUNT > 6)
	0x000040,
#endif
#if (KEY_CH_COUNT > 7)
	0x000080,
#endif
#if (KEY_CH_COUNT > 8)
	0x000100,
#endif
#if (KEY_CH_COUNT > 9)
	0x000200,
#endif
#if (KEY_CH_COUNT > 10)
	0x000400,
#endif
#if (KEY_CH_COUNT > 11)
	0x000800,
#endif
#if (KEY_CH_COUNT > 12)
	0x001000,
#endif
#if (KEY_CH_COUNT > 13)
	0x002000,
#endif
#if (KEY_CH_COUNT > 14)
	0x004000,
#endif
#if (KEY_CH_COUNT > 15)
	0x008000,
#endif
#if (KEY_CH_COUNT > 16)
	0x010000,
#endif
#if (KEY_CH_COUNT > 17)
	0x020000,
#endif
#if (KEY_CH_COUNT > 18)
	0x040000,
#endif
#if (KEY_CH_COUNT > 19)
	0x080000,
#endif

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
		if(TSWheelSlider_TouchConfirmTimer)
		{
			TSWheelSlider_TouchConfirmTimer--;
		}
#endif
#if SUPPORT_COVER_PANAL_AFTER_POWERON
		if(PanalCoverJudgeTimer) PanalCoverJudgeTimer--;
#endif
		if(PowerDetTimer) PowerDetTimer--;
	}	
}
void TS_HS_ISR (void)
{
#if SUPPORT_KEY
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
	unsigned char i;
	for(i = 0; i < KEY_CH_COUNT; i++)
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
	if(TSWheelSlider_LongTouchLimitTimer)
	{
		TSWheelSlider_LongTouchLimitTimer--;
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
}
void TS_ISR (void)
{	
	unsigned char index_copy,i;
	WORD_UNION TS_Data[6];
	if(TLFLG & (TLERR|TLKOV|TLLOV))
	{
		TLFLG |= TLERR|TLKOV|TLLOV;
	}
	index_copy = INDEX;
	for(i = 0; i < 6; i++)
	{
		if(TKIF & (1<<i))
		{
			TKIF = (1<<i);	
			INDEX = i;
			TS_Data[i].bVal[0] = TKMSH;
			TS_Data[i].bVal[1] = TKMSL;
		}
	}
	for(i = 0; i < 6; i++)
	{
		if(TS_Index+i == TS_Cnt)
		{
#if (TS_ACQ_TIMES == 1)
			TS_RefChRawData = TS_Data[i].wVal;	
#else
			TS_RefDataSum += TS_Data[i].wVal;	
#endif
			break;
		}
#if (TS_ACQ_TIMES == 1)
		TS_RawData[TS_Index+i] = TS_Data[i].wVal;	
#else
		TS_DataSum[TS_Index+i] += TS_Data[i].wVal;	
#endif
	}
	if(TS_Index+6 > TS_Cnt)
	{
#if (TS_ACQ_TIMES == 1)
		TS_CycleScanDoneFlag = 1;	
#else
		TS_Acq_Counter++;
		if(TS_Acq_Counter >= TS_ACQ_TIMES)
		{
			for(i = 0; i < TS_Cnt; i++)
			{
				TS_RawData[i] = TS_DataSum[i];
				TS_DataSum[i] = 0;
			}
			TS_RefChRawData = TS_RefDataSum;
			TS_RefDataSum = 0;
			TS_CycleScanDoneFlag = 1;		
			TS_Acq_Counter = 0;
		}	
#endif		
		TS_Index = 0;
	}
	else 
	{
		TS_Index += 6;
	}
	TS_ScanStart();	
	INDEX = index_copy;
}
void TS_DataFiltering(void)
{
	unsigned char i;
#if (FILTER_COUNT > 1)
	unsigned char j,k;
	unsigned int Temp;
	unsigned int  xdata TS_FilterTemp[FILTER_COUNT];	
#endif
	for(i = 0; i < TS_Cnt; i++)
	{
#if (FILTER_COUNT == 1)
		TS_PostData[i] = TS_RawData[i];
#else
		TS_FilterPosIdx[i]++;
		if(TS_FilterPosIdx[i] >= FILTER_COUNT) 
		{
			TS_FilterPosIdx[i] = 0;
		}
		INT3EN = 0;
		TS_FilterBuf[i][TS_FilterPosIdx[i]] = TS_RawData[i];
		INT3EN = 1; 
	 	for(j = 0; j < FILTER_COUNT; j++)
		{
			TS_FilterTemp[j]= TS_FilterBuf[i][j];
		}
		for(j = 0; j < (FILTER_COUNT/2 + 1); j++)
		{
			for(k = 0; k < FILTER_COUNT-1-j; k++)
			{
				if(TS_FilterTemp[k] > TS_FilterTemp[k+1])
				{
					Temp = TS_FilterTemp[k];
					TS_FilterTemp[k] = TS_FilterTemp[k+1];
					TS_FilterTemp[k+1] = Temp;
				}
			}
		}
#if (FILTER_COUNT%2)
		TS_PostData[i] = TS_FilterTemp[FILTER_COUNT/2];
#else
		TS_PostData[i] = (TS_FilterTemp[FILTER_COUNT/2-1] + TS_FilterTemp[FILTER_COUNT/2])/2;
#endif		
#endif		
 	}		
}
unsigned char Get_VDDCH_ADC_Value(void)
{
	unsigned char adcon_v, adcfgl_v, adcfgh_v;
	if(ADCON & AST(1)) 
	{
		while(!(ADCON & ADIF));
	}
	adcon_v = ADCON;
	adcfgl_v = ADCFGL;
	adcfgh_v = ADCFGH;
	
	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(0);	
	ADCFGH = AOPS(0) | (ADCFGH&0x3F);	
	ADCFGL = ACKD(4) | ADCHS(9);		
	ADCON |= AST(1);
		
	while(!(ADCON & ADIF));
	ADCON |= ADIF;
	
	ADCON  = adcon_v;
	ADCFGL = adcfgl_v;
	ADCFGH = adcfgh_v;	
	
	return ADCDH;
}
void PowerDetectProc(void)
{
	if(!PowerDetTimer)
	{
		PowerDetTimer = 3;
		PowerDetBufIdx++;
		if(PowerDetBufIdx >= POWER_DET_BUF_SIZE)
		{
			PowerDetBufIdx = 0;
		}
		PowerDetectBuf[PowerDetBufIdx] = Get_VDDCH_ADC_Value();
	}
}
bit PowerJumpOrFallJudge(void)
{
	unsigned char ref_value,crt_value,delta;
	unsigned char PowerDetectCnt;
	
	PowerDetectCnt = 0;
	while(1)
	{
		if(PowerDetBufIdx == (POWER_DET_BUF_SIZE-1)) 
		{
			ref_value = PowerDetectBuf[0];
		}
		else
		{
			ref_value = PowerDetectBuf[PowerDetBufIdx + 1];
		}
		crt_value = Get_VDDCH_ADC_Value();
		if(ref_value > crt_value)
		{
			delta = ref_value - crt_value;
		}
		else
		{
			delta = crt_value - ref_value;
		}
		if(delta > 12)			//约对应300mv
		{
			PowerDetectCnt++;
			if(PowerDetectCnt < 3)
			{
				PowerDetTimer = 3;
				while(PowerDetTimer);
				PowerDetectProc();
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}
}

void TS_RunInit(void)
{
	unsigned char i,j;
	static unsigned char TS_ScanTimes=0;
	if(TS_Init_Step == 0)
	{
#if (TS_ACQ_TIMES > 1)
		for(i = 0; i < TS_Cnt; i++)
		{	
			TS_DataSum[i] = 0;
		}
		TS_Acq_Counter = 0;
#endif
		TS_Index = 0;
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
				TS_Index = 0;
				TS_ScanStart();						
				return;
			}
			TS_RefCHBaseLineAdjuTimer = 0;
			for(i = 0; i < TS_Cnt; i++)
			{	
				for(j = 0; j < FILTER_COUNT; j++)
				{
					TS_FilterBuf[i][j] = TS_RawData[i];
				}
				TS_FilterPosIdx[i] = 0;
				TS_BaseLineData[i] = TS_RawData[i];			
				TS_FirstAreaData[i] = TS_RawData[i]; 
				
#if (SUPPORT_KEY && SUPPORT_WHEEL_SLIDER)
				if(i < KEY_CH_COUNT)
				{
#if TK_SENSITIVE_AUTO_TRIM_EN
					TK_TouchThdTrim(i);
#else
					TSKey_FingerThd[i] = TS_KEY_CH_INFO_SEQ[i][1];
#endif
					TS_AreaConfirmTimerSet(i,AREA_PNOISE);
				}
				else
				{
					TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
				}
#elif SUPPORT_KEY
#if TK_SENSITIVE_AUTO_TRIM_EN
				TK_TouchThdTrim(i);
#else
				TSKey_FingerThd[i] = TS_KEY_CH_INFO_SEQ[i][1];
#endif
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);				
#elif SUPPORT_WHEEL_SLIDER
				TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
#endif
			}	
			
			PowerDetectBuf[0] = Get_VDDCH_ADC_Value();
			for(i = 1; i < POWER_DET_BUF_SIZE; i++)
			{
				PowerDetectBuf[i] = PowerDetectBuf[0];
			}
			PowerDetBufIdx = 0;
			
#if (DEBUG)
			Debug_ParamLoad();
#endif		
			TS_State = TS_DEAL;	
			TS_Index = 0;
			TS_ScanStart();							
		}
	}
}
#if TK_SHARE_LED_EN
void TKLED_Set(unsigned char ch,unsigned char mode)
{
	unsigned char real_ch,idx,mask_bit;
	switch(mode)
	{
		case LED_ON:
		case LED_OFF:
			real_ch = TS_KEY_CH_INFO_SEQ[ch][0];
			idx = real_ch>>3;
			mask_bit = (real_ch&0x07);
			INDEX = idx;
			if(mode == LED_ON)
			{
				TLDAT |= 1<<mask_bit;
			}
			else
			{
				TLDAT &= ~(1<<mask_bit);
			}
			break;
		case LED_ALL_OFF:
			INDEX = 0;
			TLDAT = 0;
			INDEX = 1;
			TLDAT = 0;
			INDEX = 2;
			TLDAT = 0;
			break;
	}
}
void TKLED_Update(void)
{

	static TYPE_SN xdata PrevTKSN = 0;
	unsigned char i;
	if(PrevTKSN == KeysFlagSN) return;
	for(i = 0; i < KEY_CH_COUNT; i++)
	{
		if(KeysFlagSN & MASK_TAB[i])
		{
			TKLED_Set(i,LED_ON);
		}
		else
		{
			TKLED_Set(i,LED_OFF);
		}
	}
	PrevTKSN = KeysFlagSN;
}
#endif
#if TK_SENSITIVE_AUTO_TRIM_EN
void TK_TouchThdTrim(unsigned char ch)
{
	unsigned int b1,b2,th1,c;
	unsigned long int cal_tmp1;
	unsigned int cal_tmp2;
		
	b1 = TK_BASELINE_VALUE_INFO_SEQ[ch];
	th1 = TS_KEY_CH_INFO_SEQ[ch][1];
	b2 = TS_BaseLineData[ch];
	cal_tmp1 = ((unsigned long int)b1*(unsigned long int)b2);
	c = (unsigned int)(cal_tmp1/(b1-th1)) - b2;
	cal_tmp2 = (unsigned int)(cal_tmp1/(b1+c));
 	TSKey_FingerThd[ch] = b2 - cal_tmp2;
}
#endif
#if SUPPORT_ANTI_WATER_FUNCTION
unsigned char AntiWaterModeGetMaxDeltaCh(void)
{
	unsigned char i;
	unsigned long int CalcTemp1;
	unsigned int CalcTemp2,CalcTemp3;
	int Delta;
	int max_delta;
	char max_index;
	max_delta = 0;
	for(i = 0; i < KEY_CH_COUNT; i++)
	{
		if(i == 0)
		{
			Delta = (int)TS_BaseLineData[i] - (int)TS_PostData[i];
		}
		else
		{
			CalcTemp1 = 	(unsigned long int)TS_PostData[i] * (unsigned long int)TS_BaseLineData[0];
			CalcTemp2 =  	(unsigned int)(CalcTemp1/TS_BaseLineData[i]);
			CalcTemp3 = 	TS_PostData[i] + TS_BaseLineData[0] - CalcTemp2;
			CalcTemp2 = 	(unsigned int)(CalcTemp1/CalcTemp3);	
			Delta 		= 	(int)TS_BaseLineData[0] - (int)CalcTemp2;						
		}
		if(max_delta < Delta)
		{
			max_delta = Delta;
			max_index = i;
		}
	}
	return max_index;
}
#endif
#if SUPPORT_KEY
void TSKey_DataDeal(void)
{
	unsigned char i;
	unsigned char  TouchArea,NowArea;		

#if SUPPORT_COVER_PANAL_AFTER_POWERON
	unsigned char PanalToggleCount = 0;
#endif
	for(i = 0; i < KEY_CH_COUNT; i++)
	{	
#if SUPPORT_ANTI_WATER_FUNCTION
		if(KeyPressedFlag)
		{
			if(PressedKeyIndex != i)
			{
				TS_FirstAreaData[i] = TS_BaseLineData[i];
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);		
				continue;		
			}
		}
#endif
		TouchArea = TS_GetDataArea(i,TS_FirstAreaData[i],NOISE_THRESHOLD,(bit)(PreKeysFlagSN & MASK_TAB[i]));
		NowArea   = TS_GetDataArea(i,TS_PostData[i],NOISE_THRESHOLD,(bit)(PreKeysFlagSN & MASK_TAB[i]));
		
		if((NowArea != AREA_PNOISE)&&(NowArea != AREA_NNOISE))
		{
			TS_StableFlag = 0;		
		}
#if SUPPORT_COVER_PANAL_AFTER_POWERON
		if((NowArea == AREA_PNOISE_PLUS) || (NowArea == AREA_FINGER_TOUCH))
		{
			PanalToggleCount++;
		}
#endif
		if(TouchArea == AREA_FINGER_TOUCH)
		{
			if(NowArea == AREA_FINGER_TOUCH)
			{
				if(!(PreKeysFlagSN & MASK_TAB[i]))
				{
					if(!TS_AreaConfirmTimer[i])
					{		
						PreKeysFlagSN |= MASK_TAB[i];		
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
						TSKey_LongTouchLimitTimer[i] = FINGER_LONG_TOUCH_TIME_LIMIT;
#endif
						TS_AreaConfirmTimer[i] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;	
					}
				}
				else
				{	
#if SUPPORT_ANTI_WATER_FUNCTION		
					if(i != AntiWaterModeGetMaxDeltaCh())
					{
						goto ANTI_WATER_MODE_KEY_RELEASE;
					}
#endif
					TS_AreaConfirmTimer[i] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
					if(!TSKey_LongTouchLimitTimer[i])
					{
						PreKeysFlagSN &= ~MASK_TAB[i];
						TS_FirstAreaData[i] = TS_PostData[i];
						TS_BaseLineData[i] 	= TS_PostData[i];
#if TK_SENSITIVE_AUTO_TRIM_EN
						TK_TouchThdTrim(i);
#endif
						TS_AreaConfirmTimerSet(i,AREA_PNOISE);		
#if SUPPORT_ANTI_WATER_FUNCTION
						KeyPressedFlag = 0;
						break;
#endif						
					}							
#endif					
				}				
			}
			else
			{
				if(PreKeysFlagSN & MASK_TAB[i]) 
				{
					if(!TS_AreaConfirmTimer[i])
					{
#if SUPPORT_ANTI_WATER_FUNCTION
ANTI_WATER_MODE_KEY_RELEASE:						
						KeyPressedFlag = 0;
#endif
						PreKeysFlagSN &= ~MASK_TAB[i];

						TS_FirstAreaData[i] = TS_BaseLineData[i];
						TS_AreaConfirmTimerSet(i,AREA_PNOISE);
#if SUPPORT_ANTI_WATER_FUNCTION
						break;
#endif
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
		if(PreKeysFlagSN != 0) 
		{
			TS_FirstAreaData[i] = TS_BaseLineData[i];
			TS_AreaConfirmTimerSet(i,AREA_PNOISE);		
			continue;			
		}
		if(TS_AreaDeviateDetection(TS_FirstAreaData[i],TS_PostData[i],NOISE_THRESHOLD))	   //判断偏差是否在允许范围内
		{	
			if(!TS_AreaConfirmTimer[i])
			{
				TS_FirstAreaData[i] = TS_PostData[i];
				TS_BaseLineData[i] 	= TS_PostData[i];

#if TK_SENSITIVE_AUTO_TRIM_EN
				TK_TouchThdTrim(i);
#endif
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);	
			}	
		}
		else
		{
			TS_FirstAreaData[i] = TS_PostData[i];	
			TS_AreaConfirmTimerSet(i,NowArea);		
		}
	}	 	
#if SUPPORT_ANTI_WATER_FUNCTION
	if(KeysFlagSN == 0)
	{
		if(PreKeysFlagSN != 0)
		{
			PressedKeyIndex = AntiWaterModeGetMaxDeltaCh();
			PreKeysFlagSN = MASK_TAB[PressedKeyIndex];
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
			TSKey_LongTouchLimitTimer[PressedKeyIndex] = FINGER_LONG_TOUCH_TIME_LIMIT;
#endif
			TS_AreaConfirmTimer[PressedKeyIndex] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;	
			KeyPressedFlag = 1;
		}
	}
#endif
#if SUPPORT_COVER_PANAL_AFTER_POWERON
	if(!PanalCoverJudgeFlag)
	{
		if(PreKeysFlagSN != 0)
		{
			if(KeysFlagSN == 0)
			{
				PanalCoverJudgeFlag = 1;
				PanalCoverJudgeTimer = PANAL_COVER_JUDGE_TIME; 		
			}
			else
			{
				if((PanalToggleCount >= JUDGE_TK_NUM)||(PowerJumpOrFallJudge()))
				{
					PreKeysFlagSN = 0;
					PanalCoverJudgeFlag = 0;
					TS_BaseLineForceUpdate();
				}
				KeysFlagSN  = PreKeysFlagSN;
			}
		}
		else
		{
			KeysFlagSN  = PreKeysFlagSN;
		}
	}
	else
	{
		if(!PanalCoverJudgeTimer)
		{
			PanalCoverJudgeFlag = 0;
			KeysFlagSN = PreKeysFlagSN;
		}
		else
		{
			if((PanalToggleCount >= JUDGE_TK_NUM)||(PowerJumpOrFallJudge()))
			{
				PreKeysFlagSN = 0;
				PanalCoverJudgeFlag = 0;
				TS_BaseLineForceUpdate();
			}			
		}
	}
#else
	if((PreKeysFlagSN != 0)&&(KeysFlagSN == 0))
	{
		if(PowerJumpOrFallJudge())
		{
			PreKeysFlagSN = 0;
			
#if SUPPORT_ANTI_WATER_FUNCTION
			KeyPressedFlag = 0;
#endif
			TS_BaseLineForceUpdate();		
		}
	}
	KeysFlagSN  = PreKeysFlagSN;

#endif
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
	unsigned char i;
	unsigned int   Delta,Position;
	bit WheelSliderTogFlag = 0;
	TS_BaseCh = KEY_CH_COUNT; 
	if(!W_S_RefChSet)
	{
		W_S_RefChSet = 1;		
		SetWheelSliderRefCh(WHEEL_SLIDER0_CH_COUNT);
	}
	
#if PRINT_WHEEL_SLIDER_DATA_EN
	TK_Debug_UartPutChar(0xaa);
	for(i = TS_BaseCh; i < TS_BaseCh + WHEEL_SLIDER0_CH_COUNT; i++)
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
#endif
#if (WHEEL_OR_SLIDER_DEF0	== SLIDER)
	Position = SliderTouchJudge(WHEEL_SLIDER0_CH_COUNT,WHEEL_SLIDER0_TOUCH_THD);
#elif (WHEEL_OR_SLIDER_DEF0	== WHEEL)
	Position = WheelTouchJudge(WHEEL_SLIDER0_CH_COUNT,WHEEL_SLIDER0_TOUCH_THD);
#endif
	if(Position != -1)
	{
		TS_StableFlag = 0;
	}
	if(WheelSliderState == WHEEL_SLIDER_NO_TOUCH)
	{
		if(!WheelSliderTouchFlag)
		{
			if(Position != -1)
			{
				WheelSliderTouchFlag = 1;	
				TSWheelSlider_TouchConfirmTimer = WHEEL_SLIDER_TOUCH_CONFIRM_TIME;				
			}
			else
			{
				for(i = TS_BaseCh; i < TS_BaseCh + WHEEL_SLIDER0_CH_COUNT; i++)
				{						
					if(TS_FirstAreaData[i] > TS_PostData[i]) 
					{
						Delta 	= TS_FirstAreaData[i] - TS_PostData[i];
					}
					else
					{
						Delta 	= TS_PostData[i] - TS_FirstAreaData[i];
					}					
					if(Delta <= WHEEL_SLIDER0_NOISE_THD) 
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
				if(!TSWheelSlider_TouchConfirmTimer)
				{
						WheelSliderState = WHEEL_SLIDER_TOUCH;	
#if (WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT > 0)
						TSWheelSlider_LongTouchLimitTimer = WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT;
#endif
				}	
			}
			else
			{
				WheelSliderTouchFlag = 0;
				for(i = TS_BaseCh; i < TS_BaseCh + WHEEL_SLIDER0_CH_COUNT; i++)
				{
					TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
				}
			}
		}				
	}
	else if(WheelSliderState == WHEEL_SLIDER_TOUCH)
	{		
#if (WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT > 0)
		if(!TSWheelSlider_LongTouchLimitTimer)
		{
			for(i = TS_BaseCh; i < TS_BaseCh + WHEEL_SLIDER0_CH_COUNT; i++)
			{
				TS_FirstAreaData[i] = TS_PostData[i];
				TS_BaseLineData[i] 	= TS_PostData[i];
			}
			WheelSliderTouchFlag = 0;
			goto WHEEL_SLIDER_RELEASE;
		}
#endif
		if(WheelSliderTouchFlag)
		{
			if(Position == -1)	
			{
				WheelSliderTouchFlag = 0;
				TSWheelSlider_TouchConfirmTimer = WHEEL_SLIDER_TOUCH_RELEASE_CONFIRM_TIME;		
			}
		}
		else						 
		{
			if(Position == -1)	
			{
				if(!TSWheelSlider_TouchConfirmTimer)
				{
WHEEL_SLIDER_RELEASE:
					WheelSliderState = WHEEL_SLIDER_NO_TOUCH;	
					WheelSliderCapRateFilter = 0;
					WheelSliderPosition = -1;
					for(i = TS_BaseCh; i < TS_BaseCh + WHEEL_SLIDER0_CH_COUNT; i++)
					{
						TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
					}
				}
			}
			else
			{
				WheelSliderTouchFlag = 1;				
			}
		}		
	}		
	if(WheelSliderState == WHEEL_SLIDER_TOUCH)
	{
		if(Position != -1)
		{
			WheelSliderPosition = Position;
		}	
#if PRINT_WHEEL_SLIDER_POSITION_EN
		TK_Debug_UartPutChar(WheelSliderPosition/100+0x30);		
		TK_Debug_UartPutChar((WheelSliderPosition%100)/10+0x30);		
		TK_Debug_UartPutChar((WheelSliderPosition%10)+0x30);	

		TK_Debug_UartPutChar('\r');	
		TK_Debug_UartPutChar('\n');	
#endif
#if PRINT_WHEEL_SLIDER_RATE_EN
		{
			unsigned char DeltaRate;
			DeltaRate = WheelSliderCapRateFilter/4;
			TK_Debug_UartPutChar(WheelSliderMaxIdx + 0x30);	
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
		WheelSliderPosition = -1;	
	}

	if(WheelSliderPosition != -1)
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

	RTCON = RTCE(1) | MSE(1) | HSE(1) | SCE(0) | MCE(0) | HCE(0);
	RTMSS = 0;
	
	INT8EN = 1;			
	
	TS_IO_init();
	
	
	TKCFG = TKDIV(TKDIV_VAL)|TKTMS(TKTMS_VAL);		
#if (TK_CHARGE_REF_SELECT == SOURCE_VDD)
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|TWKE(0)|VRS(VRS_VAL);
	TKPWC = TKPC(TK_PC_VAL)|VDS(0)|VIRS(0)|TKPWS(0)|TKCVS(0);		
#elif (TK_CHARGE_REF_SELECT == SOURCE_INNER) 
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|TWKE(0)|VRS(0);
	TKPWC = TKPC(TK_PC_VAL)|VDS(VDS_VAL)|VIRS(VIRS_VAL)|TKPWS(1)|TKCVS(1);		
#endif
 	

#if TK_SHARE_LED_EN
	INDEX = 0;
	TLEN 	= 0xFF;
	TLDAT = 0x00;
	INDEX = 1;
	TLEN 	= 0xFF;
	TLDAT = 0x00;
	INDEX = 2;
	TLEN 	= 0xFF;
	TLDAT = 0x00;

	TLCON = TLEIE(0)|TLKIE(0)|TLLIE(0)|TLLVS(0)|TLPOL(0);
	TLCKS = TLCKS(2);

	TLCNTKH = 0x00;		
	TLCNTKL = 0x20;

	TLCNTLH = LED_DRV_CNT/256;		
	TLCNTLL = LED_DRV_CNT%256;

	TLCNTD = 0;
#ifdef LED_COM_SEL_P00	
	TLCOMS = 0x01;
	P00C 	|= 0x80;
	P00F 	 = 6;
#elif defined LED_COM_SEL_P01
	TLCOMS = 0x02;
	P01C  |= 0x80;
	P01F   = 6;
#elif defined LED_COM_SEL_P02
	TLCOMS = 0x03;
	P02C  |= 0x80;
	P02F   = 6;
#elif defined LED_COM_SEL_P03
	TLCOMS = 0x04;
	P03C  |= 0x80;
	P03F   = 6;
#elif defined LED_COM_SEL_P04
	TLCOMS = 0x05;
	P04C  |= 0x80;
	P04F   = 6;
#endif
#endif
	INT3EN = 1; 
	
	TS_CycleScanDoneFlag = 0;
#if SUPPORT_KEY
	KeysFlagSN = 0;
	PreKeysFlagSN = 0;
#endif	
	ActiveTouchType = 0;
#if SUPPORT_COVER_PANAL_AFTER_POWERON
	PanalCoverJudgeFlag = 0;
#endif
#if SUPPORT_TOUCH_SLEEP_MODE
	EnterStopScanTimer = ENTER_STOP_MODE_TIME;
  TS_SleepEn = 1;
#endif
#if SUPPORT_WHEEL_SLIDER
	W_S_RefChSet = 0;

	WheelSliderState = WHEEL_SLIDER_NO_TOUCH;
	WheelSliderTouchFlag = 0;
	WheelSliderPosition = -1;		
	WheelSliderCapRateFilter = 0;
#endif
	TS_State = TS_INIT;
	TS_Init_Step = 0;
	
	PowerDetTimer = 0;

#if SUPPORT_KEY	
#if GENERATE_TS_KEY_EN
	TK_State = TK_STATE_RELEASE;
	TS_Key = 0;
#endif
#endif
}

void TS_Action(void)
{	
	switch(TS_State)
	{
		case TS_INIT:
			TS_RunInit();			
			break;
		case TS_DEAL:		
			if(TS_CycleScanDoneFlag)
			{			
				TS_CycleScanDoneFlag = 0;		
				PowerDetectProc();
				TS_DataFiltering();
				TS_StableFlag = 1;
#if SUPPORT_KEY	
				if(ActiveTouchType != 2)
				{
					TSKey_DataDeal();	
				}
#endif
#if (DEBUG)
				Debug_ParamLoad();
#endif		
#if SUPPORT_WHEEL_SLIDER
				if(ActiveTouchType != 1)
				{
					TS_WheelSliderDeal();
				}
#endif				
#if SUPPORT_TOUCH_SLEEP_MODE
				if(!TS_StableFlag || !TS_SleepEn || (PCON & BIT2))	// 在仿真模式不进入STOP模式
				{
					EnterStopScanTimer = ENTER_STOP_MODE_TIME;
				}			
				if(!EnterStopScanTimer&&TS_SleepEn)
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
#if TK_SHARE_LED_EN
	TKLED_Update();
#endif
#if GENERATE_TS_KEY_EN
	TS_GetKey();
#endif
#endif
}
#if SUPPORT_TOUCH_SLEEP_MODE
void TS_SleepScanStart(void)
{	
	unsigned char i;	
	for(i = 0; i < 6; i++)					
	{
		INDEX = i;
		if(TS_Index + i < TS_Cnt)
		{
			TKCHS = MPOL(0) | NPOL(1) | TKCHS((TS_CH[TS_Index+i])+1); 
		}
		else
		{
			TKCHS = 0; 
		}
	}
	TKCON |= TKST(1);	
}
void TS_EnterSleepMode(void)
{
//省电模式参数配置
	#define STOP_TKDIV_VAL			0
	#define STOP_TKTMS_VAL			8		//放电时间
	#define STOP_VRS_VAL				7			//比较器阈值	
	unsigned char TS_AcqCnt = 0,i;
	unsigned int xdata WakeUp_PThdVal[OPENED_TS_COUNT];
	unsigned int xdata WakeUp_NThdVal[OPENED_TS_COUNT];	
	WORD_UNION TS_Data;
	
	Sys_Clk_Set_TFRC();
#if (SYSCLK_SRC == PLL)
	PLLCON = 0;
#endif	
	
	TKCON = 0;
	TKIF = 0x3F;
	
#if TK_SHARE_LED_EN
	INDEX = 0;
	TLEN 	= 0x00;
	TLDAT = 0x00;
	INDEX = 1;
	TLEN 	= 0x00;
	TLDAT = 0x00;
	INDEX = 2;
	TLEN 	= 0x00;
	TLDAT = 0x00;
#endif
	
	RTCON &=  ~(MSE(1) | HSE(1));
	RTCIF = RTC_MF | RTC_HF;	
	
	TKCON = (TKCON&0xF8) | VRS(STOP_VRS_VAL);
	TKCON &= ~TKIE(1);
	TKCON |= TMEN(1);
	TKCFG = TKDIV(STOP_TKDIV_VAL)|TKTMS(STOP_TKTMS_VAL);		

#if (OPENED_TS_COUNT%6 == 0)
	TKMTS = (SLEEP_MODE_SCAN_INTERVAL_TIME*6)/(OPENED_TS_COUNT);
#else
	TKMTS = (SLEEP_MODE_SCAN_INTERVAL_TIME)/((OPENED_TS_COUNT/6)+1);
#endif
	
	TKPWC = TKPC(1)|VDS(0)|VIRS(0)|TKPWS(0)|TKCVS(0);		//省电设为VDD充电
	
#ifdef LVD_RST_ENABLE
	LVDCON = 0;	
#endif		
	I2CCON = 0;
	CKCON = 0;
	MECON |= BIT6;	
	PWCON = PWCON&(~0x08);	

	TS_Index = 0;
	TS_SleepScanStart();
	while(1)
	{
		EA = 0;
		PCON |= (1<<1);
		_nop_();
		_nop_();
		EA = 1;
		if(TKIF != 0)
		{
			for(i = 0; i < 6; i++)
			{
				if(TKIF & (1<<i))
				{
					TKIF = (1<<i);	
					INDEX = i;
					TS_Data.bVal[0] = TKMSH;
					TS_Data.bVal[1] = TKMSL;
					if(TS_AcqCnt == 2)
					{
						WakeUp_PThdVal[TS_Index+i] = TS_Data.wVal - SLEEP_TOUTH_THD;
						WakeUp_NThdVal[TS_Index+i] = TS_Data.wVal + SLEEP_TOUTH_THD;
					}
					else if(TS_AcqCnt > 2)
					{
						if((TS_Data.wVal <= WakeUp_PThdVal[TS_Index+i])||(TS_Data.wVal >= WakeUp_NThdVal[TS_Index+i]))
						{
							goto SLEEP_EXIT;			
						}
					}
				}
			}
			if(TS_Index+6 < TS_Cnt)
			{
				TS_Index += 6;
			}
			else 
			{
				TS_Index = 0;
				TS_AcqCnt++;
			}
			TS_SleepScanStart();	
		}
	}
SLEEP_EXIT:
	TKCON = 0;
	TKIF = 0x3F;
	PWCON |= 0x08;	
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);
#elif (SYSCLK_SRC == IRCH)	
	Sys_Clk_Set_IRCH();
#endif

	TKCFG = TKDIV(TKDIV_VAL)|TKTMS(TKTMS_VAL);		
#if (TK_CHARGE_REF_SELECT == SOURCE_VDD)
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|TWKE(0)|VRS(VRS_VAL);
	TKPWC = TKPC(TK_PC_VAL)|VDS(0)|VIRS(0)|TKPWS(0)|TKCVS(0);		
#elif (TK_CHARGE_REF_SELECT == SOURCE_INNER) 
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|TWKE(0)|VRS(0);
	TKPWC = TKPC(TK_PC_VAL)|VDS(VDS_VAL)|VIRS(VIRS_VAL)|TKPWS(1)|TKCVS(1);		
#endif
#if TK_SHARE_LED_EN
	INDEX = 0;
	TLEN 	= 0xFF;
	INDEX = 1;
	TLEN 	= 0xFF;
	INDEX = 2;
	TLEN 	= 0xFF;
#endif
	RTCON |= HSE(1)|MSE(1);
	TS_Index = 0;
	TS_ScanStart();
	EnterStopScanTimer = ENTER_STOP_MODE_TIME;
#ifdef LVD_RST_ENABLE
	{
		bit ea;
		ea = EA;
		EA = 0;
		LVDCON = 0x80;	
		Delay_50us(1);
		LVDCON = 0xc2;	
		LVDCON |= 0x20;	
		EA = ea;		
	}
	LVDCON = 0xC3;	//设置LVD复位电压为2V
#endif							
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
	K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K20
};
#if GENERATE_DOUBLE_KEY_EN
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
#endif
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
#if GENERATE_DOUBLE_KEY_EN
	T_TogKeyInfo KeyInfo;
	TS_GetTogKeyInfor(&KeyInfo);
#else
	static unsigned char KeyidxBak;
	unsigned char i;
#endif
	TS_Key = 0;	
	if(TK_State == TK_STATE_RELEASE)
	{
#if GENERATE_DOUBLE_KEY_EN
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
#else
		if(KeysFlagSN != 0)
		{
			for(i = 0; i < KEY_CH_COUNT; i++)
			{
				if(KeysFlagSN & MASK_TAB[i])
				{
					KeyidxBak = i;
					KeyBak = TS_KEY_TAB[i];
					break;
				}		
			}				
			TS_Key = KeyBak;
			LongFlag = 0;
			TS_LongKeyTimer = TS_LONG_START_TIME;
			TK_State = TK_STATE_SINGLE_KEY_PRESS;		
		}
#endif
	}
	else if(TK_State == TK_STATE_SINGLE_KEY_PRESS)
	{
#if GENERATE_DOUBLE_KEY_EN	
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
#else
		if(KeysFlagSN & MASK_TAB[KeyidxBak])
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
#endif
	}
#if GENERATE_DOUBLE_KEY_EN	
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
#endif
#if PRINT_TS_KEY_EN
	if(TS_Key != 0)
	{
		if((TS_Key & 0xFF00) == 0)
		{
#if GENERATE_DOUBLE_KEY_EN	
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
#endif
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
/*********************************************************************************************************************/

/*********************************************************************************************************************/
#endif