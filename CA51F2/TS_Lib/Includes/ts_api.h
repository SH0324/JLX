#ifndef _TS_API_H
#define _TS_API_H

#ifdef _TK_API_C_
/***************************************************************************************************************/
/***************************************************************************************************************/											
TSState_T 	  xdata TS_State;
unsigned  long int xdata KeysFlagSN;	
unsigned int  TS_Key;	
unsigned int 	TS_LongKeyTimer;
unsigned char TK_State;	

bit TS_CycleScanDoneFlag;
unsigned char xdata 	TS_Cnt;			
unsigned char xdata 	Key_Cnt;		
unsigned int  xdata 	TS_RefChBaseLineData;
unsigned int  xdata 	TS_RefChRawData;					  
unsigned int 	xdata 	TS_RawData[OPENED_TS_COUNT];
unsigned int 	xdata 	TS_RefPostData;
unsigned int 	xdata 	TS_BaseLineData[OPENED_TS_COUNT];
unsigned int 	xdata 	TS_FirstAreaData[OPENED_TS_COUNT];
unsigned char xdata 	TS_AreaConfirmTimer[OPENED_TS_COUNT];
unsigned int 	xdata 	TS_PostData[OPENED_TS_COUNT];

#if SUPPORT_KEY
unsigned int 	xdata 	TSKey_FingerThd[KEY_CH_COUNT];
unsigned char xdata 	TSKey_LongTouchLimitTimer[KEY_CH_COUNT];
#else
unsigned int 	xdata 	TSKey_FingerThd[1];
#endif
/***************************************************************************************************************/
/***************************************************************************************************************/
unsigned int xdata TS_FilterBuf[OPENED_TS_COUNT];	
unsigned int xdata TS_RefFilterBuf;												
unsigned char xdata TS_Init_Step;
unsigned char idata TS_RefCHBaseLineAdjuTimer;
unsigned char TS_Index;

unsigned char xdata TS_CH[OPENED_TS_COUNT];	
unsigned char  TS_AcqCnt;
unsigned char xdata EnterStopScanTimer;
unsigned char TS_AcqTimes;

unsigned char FilterCount;

bit TS_StableFlag;
unsigned char xdata TS_ForbidTimer;
#if SUPPORT_TOUCH_SLEEP_MODE
bit TS_SleepEn;
#endif
#if SUPPORT_WHEEL_SLIDER
unsigned char xdata TSWheelSlider_TouchConfirmTimer[WHEEL_SLIDER_COUNT];
unsigned char xdata TSWheelSlider_LongTouchLimitTimer[WHEEL_SLIDER_COUNT];
unsigned char xdata WheelSliderState[WHEEL_SLIDER_COUNT];
unsigned char xdata WheelSliderTouchFlag[WHEEL_SLIDER_COUNT];
int xdata WheelSliderPosition[WHEEL_SLIDER_COUNT];
unsigned char xdata WheelSliderRefCh[WHEEL_SLIDER_COUNT];
unsigned int xdata WheelSliderCapRateFilter[WHEEL_SLIDER_COUNT];
unsigned char xdata WheelSliderMaxIdx[WHEEL_SLIDER_COUNT];
bit W_S_RefChSet;
unsigned char ActiveWheelSliderNum;
#else
unsigned char xdata WheelSliderRefCh[1];
unsigned int xdata WheelSliderCapRateFilter[1];
unsigned char xdata WheelSliderMaxIdx[1];
#endif
unsigned char TS_BaseCh;
unsigned char ActiveTouchType;
#else
/***************************************************************************************************************/
/***************************************************************************************************************/											
extern TSState_T 	  xdata TS_State;
extern unsigned  long int xdata KeysFlagSN;	
extern unsigned int  TS_Key;	
extern unsigned int 	TS_LongKeyTimer;
extern unsigned char TK_State;	

extern bit TS_CycleScanDoneFlag;
extern unsigned char 	xdata 	TS_Cnt;			
extern unsigned char 	xdata 	Key_Cnt;	
extern unsigned int  	xdata 	TS_RefChBaseLineData;
extern unsigned int  	xdata 	TS_RefChRawData;					  
extern unsigned int 	xdata 	TS_RawData[];
extern unsigned int 	xdata 	TS_RefPostData;
extern unsigned int 	xdata 	TS_BaseLineData[];
extern unsigned int 	xdata 	TS_FirstAreaData[];
extern unsigned char 	xdata 	TS_AreaConfirmTimer[];
extern unsigned int 	xdata 	TS_PostData[];

extern unsigned int 	xdata 	TSKey_FingerThd[];
extern unsigned char 	xdata 	TSKey_LongTouchLimitTimer[];

/***************************************************************************************************************/
/***************************************************************************************************************/
extern unsigned int xdata TS_FilterBuf[];	
extern unsigned int xdata TS_RefFilterBuf;												
extern unsigned char xdata TS_Init_Step;
extern unsigned char idata TS_RefCHBaseLineAdjuTimer;
extern unsigned char TS_Index;

extern unsigned char xdata TS_CH[];	
extern unsigned char  TS_AcqCnt;
extern unsigned char xdata EnterStopScanTimer;
extern unsigned char TS_AcqTimes;
extern unsigned char FilterCount;

extern code unsigned int TS_CH_INFO_SEQ[][2];
extern bit TS_StableFlag;
extern unsigned char xdata TS_ForbidTimer;
extern bit TS_SleepEn;

extern unsigned char xdata TSWheelSlider_TouchConfirmTimer[];
extern unsigned char xdata TSWheelSlider_LongTouchLimitTimer[];

extern unsigned char xdata WheelSliderState[];
extern unsigned char xdata WheelSliderTouchFlag[];
extern int xdata WheelSliderPosition[];
extern unsigned int xdata WheelSliderCapRateFilter[];
extern unsigned char TS_BaseCh;
extern unsigned char ActiveTouchType;
extern unsigned char ActiveWheelSliderNum;
extern unsigned char xdata WheelSliderRefCh[];
extern unsigned char xdata WheelSliderMaxIdx[];
extern bit W_S_RefChSet;
extern code unsigned char SLIDER_CH_COUNT[];
extern code unsigned int 	TS_KEY_CH_INFO_SEQ[][2];
extern code unsigned char *WHEEL_SLIDER_MIN_RATE[];
extern code unsigned char WHEEL_SLIDER_TOUCH_THD[];
extern code unsigned char SLIDER_CH_COUNT[];
extern code unsigned char WHEEL_OR_SLIDER_DEF[];
extern code unsigned char WHEEL_SLIDER_NOISE_THD[];
extern code unsigned char AREA_CONFIRM_TIME_TAB[];
extern code unsigned long int MASK_TAB[];
#endif

void TS_init(void);
void TS_Action(void);
void TS_GetKey(void);
void TS_EnterSleepMode(void);		
void TS_ISR(void);
#endif