#ifndef _TS_SERVICE_H_
#define _TS_SERVICE_H_

void TS_IO_init(void);
void TS_ScanStart(void);
void TS_ScanContinue(void);
void TSKey_DataDeal(void);
void TS_RunInit(void);
void TS_CheckRefCh(void);
void TS_AreaConfirmTimerSet(unsigned char ts_ch, unsigned char area);
void TS_DataFiltering(void);
void TS_MS_ISR(void);
void TS_HS_ISR(void);
void TS_CfgPinFunc(unsigned char idx,unsigned char Func);
unsigned char TS_GetDataArea(unsigned char ts_ch,unsigned int ts_data);
unsigned char TS_AreaDeviateDetection(	unsigned char ts_ch,unsigned int cmp_data,unsigned int real_data);
void SetWheelSliderRefCh(unsigned char SliderNum);
int WheelSliderTouchJudge(unsigned char num);
#endif
