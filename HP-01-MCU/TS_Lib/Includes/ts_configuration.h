#ifndef _TS_CFG_H
#define _TS_CFG_H

//-------------------------------------------------------------------------------------------------------------------
#define DEBUG 					0 			//1:打开在线调试功能;	0:关闭在线调试功能
//注意：只有触摸键应用才支持在线调试，滑条应用不支持在线调试。
/********************************************************************************************************
说明：
触摸在线调试功能可在PC端显示当前触摸值、基准值、门限值，可在PC端设置触摸灵敏度，并导出配置文件，
此功能需配合仿真下载器及上位机工具CACHIPTOOL.exe才能使用。详细使用方法请参考相关文档说明。
********************************************************************************************************/

//-------------------------------------------------------------------------------------------------------------------
#define SUPPORT_KEY					1				//1:支持触摸按键;	0:不支持触摸按键
#define SUPPORT_WHEEL_SLIDER		0				//1:支持触摸触摸滑条或圆环；0:不支持触摸滑条或圆环
//-------------------------------------------------------------------------------------------------------------------


/***********触摸省电模式设置********************************************************************************************************/
#define SUPPORT_TOUCH_SLEEP_MODE				0		//1：支持  0：不支持  

#if SUPPORT_TOUCH_SLEEP_MODE
	#define ENTER_STOP_MODE_TIME				10		//进入触摸省电模式倒数时间，单位为0.5S，如定义为5，5*0.5=2.5秒，即2.5秒无触摸即进入省电模式。
	#define SLEEP_MODE_SCAN_INTERVAL_TIME		100		//扫描触摸的间隔时间，单位约为1ms，注意：此时间越长，芯片待机功耗越低，但触摸响应速度越慢。
	#define SLEEP_TOUTH_THD						5		//触摸省电模式下门限值设置，当触摸数据变化量大于此数值将退出省电模式。

	#define ENTER_SLEEP_PRINT_EN				0			//省电模式打印开关,主要是为了验证触摸是否正常进入省电模式。进入触摸省电模式时打印"sleep"，退出省电模式时打印"exit"

//注意：使能触摸省电模式后，如在某些条件不需要进入省电模式，只需要把TS_SleepEn设为0，如需要进省电模式，把TS_SleepEn设为1。
#endif
//-------------------------------------------------------------------------------------------------------------------

#define TS_ACQ_TIMES			                1		//该定义表示多少次采集数据相加进行运算

//-------------------------------------------------------------------------------------------------------------------
/********************触摸数据滤波设置*********************************************************/
#define FILTER_COUNT							5		
//说明：此数值越大，数据越平滑，但是按键响应速度越慢
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
/*******************触摸充电和比较器基准选择***********************************************************************/
#define SOURCE_VDD			0
#define SOURCE_INNER		1

#define TK_CHARGE_REF_SELECT		SOURCE_INNER		//SOURCE_VDD: 触摸充电电源选择为VDD,比较器基准为VDD分压 SOURCE_INNER：触摸充电电源为内部运放，比较器基准为内部基准			

#if (TK_CHARGE_REF_SELECT == SOURCE_VDD)
	#define VRS_VAL			2		//比较器阈值，取值范围为：0~7，数值越大，比较器阈值电压越低。
#elif (TK_CHARGE_REF_SELECT == SOURCE_INNER)
	#define VDS_VAL			1		//触摸内部运放输出电压选择，可选范围：0~3，0：2V   1：2.5V  2：3V  3：4V
	#define VIRS_VAL		1		//触摸比较器阈值电压选择，可选范围：0~3，0：1V   1：1.5V  2：2V  3：2.5V
#endif
#define TKDIV_VAL			0		//触摸充放电时钟分频系数，取值范围为：0~7，对应的时钟频率为：4M~500K，此数值越大，频率越低。
#define TKTMS_VAL			10		//放电时间定义，取值范围为：1~31，数值越大，放电时间越长。

/*
	说明：
	1.	当设置为内部运放及内部基准时（即TK_CHARGE_REF_SELECT==SOURCE_INNER），内部运放电压要大于比较器阈值电压，即VDS_VAL定义的电压要大于VIRS_VAL定义的电压。
	2. 	当设置为内部运放及内部基准时（即TK_CHARGE_REF_SELECT==SOURCE_INNER），内部运放电压要比芯片供电电压低0.5V以上，否则运放电压可能不稳定。
	3.	当设置为内部运放及内部基准时（即TK_CHARGE_REF_SELECT==SOURCE_INNER），芯片供电至少要接10uF以上电容。
*/
//-------------------------------------------------------------------------------------------------------------------

#define SUPPORT_ANTI_WATER_FUNCTION		0	//防水补偿模式开关

#if SUPPORT_ANTI_WATER_FUNCTION
	#define TK_PC_VAL					2
#else
	#define TK_PC_VAL					1
#endif
/*
说明：
	1. 此功能只能在触摸按键时打开，触摸滑条或圆环不支持。
	2. 打开防水补偿模式时，触摸充电电源最好选择为VDD(即 TK_CHARGE_REF_SELECT == SOURCE_VDD)。
	3. 在此模式下，触摸走线对地间的寄生电容必须大于触摸通道间的寄生电容，否则触摸充电无法达到比较器阈值电压，建议PCB多铺地，触摸走线的间距尽可能宽
*/
//-----------------触摸键应用设置--------------------------------------------------------------------------------------------------
#if SUPPORT_KEY
#define GENERATE_TS_KEY_EN					1			//根据KeysFlagSN状态产生触摸键消息TS_Key使能，如果不需要产生TS_Key，用户可直接根据KeysFlagSN来判断按键状态。
#if GENERATE_TS_KEY_EN
	#define GENERATE_DOUBLE_KEY_EN			0			//产生复合键
	#define PRINT_TS_KEY_EN					0			//打印触摸按键值开关
#endif

/***********上电再盖上触摸面板功能操作开关定义*******************************************************************************************************/
#define SUPPORT_COVER_PANAL_AFTER_POWERON			0		//1:支持上电再盖上触摸面板    0：不支持
#if SUPPORT_COVER_PANAL_AFTER_POWERON
	#define PANAL_COVER_JUDGE_TIME					2		//单位为15.625ms
	#define JUDGE_TK_NUM							(KEY_CH_COUNT-2)		
#endif
//说明：上电后再盖上触摸面板，一般情况下会有多个按键触摸数值变化量超过或接近触摸门限值，为了防止此类操作产生误动作，在检测到多个按键超过或接近触发门限值时，设置按键无效并重置触摸功能。
/*******************************************************************************************************************************/

//-------------------------------------------------------------------------------------------------------------------
/********触摸按键通道及触发门限值定义***********************************************************/
 	#define KEY_CH_COUNT			8			//触摸按键数量，必须正确填写
//switch-60-10-light
  #define KEY_SEQ       \
  {TS_CH0 ,  50 },      \
  {TS_CH1 ,  30 },      \
  {TS_CH2 ,  40 },      \
  {TS_CH3 ,  40 },      \
  {TS_CH4 ,  40 },      \
  {TS_CH5 ,  40 },      \
  {TS_CH6 ,  50 },      \
  {TS_CH10,  70 },      \

/*********************************************************************
说明：
1：	{TS_CHx, XX}
	   |			 |
		 |			 |	
		 |			 ------------->对应触摸通道的门限值，当触摸数据变化量大于此数值时，按键触发。
		 --------------------->触摸通道序号。
	
2：	以上触摸门限值可在触摸在线调试模式下由上位机软件(CACHIPTOOL.exe)导出。
*********************************************************************/
	
/***********NOISE门限值定义************************************************************************************/
#define NOISE_THRESHOLD  					20		//此门限值可设置为触摸按键门限值的1/4 ~ 1/2
/*************************************************************************************************************/	
	
	
//-------------------------------------------------------------------------------------------------------------------
#define TK_SHARE_LED_EN						0			//触摸引脚复用LED驱动引脚功能开关
	
#if TK_SHARE_LED_EN
/**************************************************************************************/
//------选择LED COM----------------------------------------------------------------------
	#define LED_COM_SEL_P00
// 	#define LED_COM_SEL_P01		
// 	#define LED_COM_SEL_P02		
// 	#define LED_COM_SEL_P03		
// 	#define LED_COM_SEL_P04		
//---------------------------------------------------------------------------------------
	#define LED_DRV_CNT			2000					//此项参数可设置LED扫描占空比，数值越大，LED亮度越高，但触摸采集的速度越慢
//---------------------------------------------------------------------------------------

	#define TK_SENSITIVE_AUTO_TRIM_EN			1	 //见以下说明

/*
	此功能选项用于解决生产过程中应用不同的LED灯造成灵敏度差异问题，
	在应用时必须填写以下列表数值，数值的涵义是无按键时每个触摸通道的计数数值，
	其顺序对应上面定义的KEY_SEQ列表，计数数值也对应KEY_SEQ中定义的门限值，
	在应用时如果换上不同批次或不同颜色的LED灯，由于不同颜色的LED灯的结电容可能不同，
	从而造成触摸计数数值也不同，程序会根据以下定义的参考计数值相应调整其门限值，从而使
	应用不同的LED灯灵敏度基本一致，而不需要用户更改软件。
*/

	#if TK_SENSITIVE_AUTO_TRIM_EN

		#define TK_BASELINE_VALUE_SEQ       \
		2034,      \
		2249,      \
		2083,      \
		1913,      \
		1930,      \
		2016,      \
		2175,      \
		2300,      \
		2202,      \
		2067,      \
		1927,      \
		1844,      \
		1724,      \
		1843,      \
		1993,      \
		2136,      
	#endif	
#else 
	#define TK_SENSITIVE_AUTO_TRIM_EN			0
#endif

//-------------------------------------------------------------------------------------------------------------------
/***********触摸按键消抖及按键输出时间定义************************************************************************************/	
#define FINGER_TOUCH_CONFIRM_TIME				2 				//触摸按键按下确认时间，单位为15.625ms
#define FINGER_TOUCH_RELEASE_CONFIRM_TIME		2 				//触摸按键释放确认时间，单位为15.625ms
#define FINGER_LONG_TOUCH_TIME_LIMIT			60    		    //限制按键输出时间，单位为0.5s，若定义为0，则关闭此功能	
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
/***********环境值更新速度设置********************************************************/
#define AREA_PNOISE_PLUS_CONFIRM_TIME			100 	//单位为15.625ms
#define AREA_PNOISE_CONFIRM_TIME				80 		//单位为15.625ms
#define AREA_NNOISE_CONFIRM_TIME				30 		//单位为15.625ms
#define AREA_OVERLOW_CONFIRM_TIME				30 		//单位为15.625ms

//说明：一般情况下，环境值更新速度设置用户不需要设置，保持默认值即可。
//-------------------------------------------------------------------------------------------------------------------
#else
#define KEY_CH_COUNT    0
#endif




//-----------------触摸滑条或圆环应用设置-------------------------------------------------------------------------------------------------
#if SUPPORT_WHEEL_SLIDER
//-----------------------------------------------------------------------------
	#define PRINT_WHEEL_SLIDER_POSITION_EN			1			//打印触摸圆环或滑条位置开关
	#define PRINT_WHEEL_SLIDER_DATA_EN				0			//打印触摸圆环或滑条触摸数据开关
	#define PRINT_WHEEL_SLIDER_RATE_EN				0			//打印比率值

	
	#define WHEEL_SLIDER_BASELINE_UPDATE_TIME		50 		//单位为15.625ms
	
//-----------------------------------------------------------------------------
	
	#define WHEEL_SLIDER_TOUCH_CONFIRM_TIME				2 			//圆环或滑条按下确认时间，单位为15.625ms
	#define WHEEL_SLIDER_TOUCH_RELEASE_CONFIRM_TIME		2 			//圆环或滑条释放确认时间，单位为15.625ms	
	#define WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT			60    	    //限制圆环和滑条触发时间，单位为0.5s，若定义为0，则关闭此功能			
//------------------------------------------------------------------------------------	

	#define WHEEL_OR_SLIDER_DEF0					WHEEL			//是滑条还是转盘
	#define WHEEL_SLIDER0_CH_COUNT					4						//第一个转盘或滑条通道数目，必须正确填写	
	#define WHEEL_SLIDER0_SEQ						TS_CH12,TS_CH13,TS_CH0,TS_CH11
	#define WHEEL_SLIDER0_CH_MIN_RATE				32,		 22,	 26,    22			//手指触摸时当前通道数据变化量占变化量最大两通道变化量之和的最大比率，顺序与上述通道定义一一对应。


	#define WHEEL_SLIDER0_TOUCH_THD					0x20			
	#define WHEEL_SLIDER0_NOISE_THD					0x05
//------------------------------------------------------------------------------------
#else
		#define WHEEL_SLIDER0_CH_COUNT	0
#endif

//-------------------------------------------------------------------------------------------------------------------		
#define OPENED_TS_COUNT				(KEY_CH_COUNT+WHEEL_SLIDER0_CH_COUNT)
		
#if (!SUPPORT_KEY)		
	#undef DEBUG		
	#define DEBUG 0
#endif
#if DEBUG
 	#define I2C_SELECT_P30_P31
//	#define I2C_SELECT_P11_P12

	#ifdef I2C_SELECT_P30_P31
		#ifdef UART0_EN
		 #error	"请在ca51f5_config.h中关闭宏定义UART0_EN!"
		#endif
	#elif defined I2C_SELECT_P11_P12
		#ifdef UART1_EN
		 #error	"请在ca51f5_config.h中关闭宏定义UART1_EN!"
		#endif
	#endif

	#undef SUPPORT_TOUCH_SLEEP_MODE				//省电模式不支持触摸在线调试，所以要关闭省电模式
	#define SUPPORT_TOUCH_SLEEP_MODE			0
#endif

#define TOUCH_PRINT_USE_UART0
// #define TOUCH_PRINT_USE_UART1

/*注意：所选择的UART端口需在ca51f_config.h中使能。*/

#ifdef TOUCH_PRINT_USE_UART0
	#define TK_Debug_UartPutChar			Uart0_PutChar
#elif defined TOUCH_PRINT_USE_UART1
	#define TK_Debug_UartPutChar			Uart1_PutChar
#endif
#endif
//-------------------------------------------------------------------------------------------------------------------
