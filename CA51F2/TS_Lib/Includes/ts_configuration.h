#ifndef _TS_CFG_H
#define _TS_CFG_H

//-------------------------------------------------------------------------------------------------------------------
#define DEBUG 					1 			//1:打开在线调试功能;	0:关闭在线调试功能
//注意：只有触摸键应用才支持在线调试，滑条应用不支持在线调试。
/********************************************************************************************************
说明：
触摸在线调试功能可在PC端显示当前触摸值、基准值、门限值，可在PC端设置触摸灵敏度，并导出配置文件，
此功能需配合仿真下载器及上位机工具CACHIPTOOL.exe才能使用。详细使用方法请参考相关文档说明。
********************************************************************************************************/

//-------------------------------------------------------------------------------------------------------------------
#define SUPPORT_KEY							1				//1:支持触摸按键;	0:不支持触摸按键
#define SUPPORT_WHEEL_SLIDER		0				//1:支持触摸触摸滑条或圆环；0:不支持触摸滑条或圆环
//-------------------------------------------------------------------------------------------------------------------


/***********触摸省电模式设置********************************************************************************************************/
#define SUPPORT_TOUCH_SLEEP_MODE				0		//1：支持  0：不支持  

#if SUPPORT_TOUCH_SLEEP_MODE
	#define ENTER_STOP_MODE_TIME						5								//进入触摸省电模式倒数时间，单位为0.5S，如定义为5，5*0.5=2.5秒，即2.5秒无触摸即进入省电模式。
	#define SLEEP_MODE_SCAN_INTERVAL_TIME		100							//扫描触摸的间隔时间，单位约为1ms，注意：此时间越长，芯片待机功耗越低，但触摸响应速度越慢。
	#define SLEEP_TOUTH_THD									5								//触摸省电模式下门限值设置，当触摸数据变化量大于此数值将退出省电模式。

	#define ENTER_SLEEP_PRINT_EN						0			//省电模式打印开关,主要是为了验证触摸是否正常进入省电模式。进入触摸省电模式时打印"sleep"，退出省电模式时打印"exit"

//注意：使能触摸省电模式后，如在某些条件不需要进入省电模式，只需要把TS_SleepEn设为0，如需要进省电模式，把TS_SleepEn设为1。
#endif
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
/********************触摸数据滤波设置*********************************************************/
#define FILTER_COUNT											3		
//说明：滤波算法采用滑动滤波算法，FILTER_COUNT定义的是取多少个数据的平均值，此数值越大，数据越平滑，但是按键响应速度越慢
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
#define TS_ACQ_TIMES			4			//该定义表示多少次采集数据相加进行运算， 最大不能超过6次
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
/*******************触摸寄存器参数配置***********************************************************************/
#define TKDIV_VAL					0			//触摸充放电时钟分频系数，取值范围为：0~7，对应的时钟频率为：4M~500K，此数值越大，频率越低。
#define TKTMS_VAL					8			//放电时间定义，取值范围为：1~31，数值越大，放电时间越长。
#define VRS_VAL						7			//比较器阈值，取值范围为：0~7，数值越大，比较器阈值电压越低。
//说明：一般情况下，寄存器参数不建议修改
//-------------------------------------------------------------------------------------------------------------------







//-----------------触摸键应用设置--------------------------------------------------------------------------------------------------
#if SUPPORT_KEY
#define GENERATE_TS_KEY_EN					1			//根据KeysFlagSN状态产生触摸键消息TS_Key使能，如果不需要产生TS_Key，用户可直接根据KeysFlagSN来判断按键状态。
#if GENERATE_TS_KEY_EN
	#define PRINT_TS_KEY_EN							0			//打印触摸按键值开关
#endif
//-------------------------------------------------------------------------------------------------------------------
/********触摸按键通道及触发门限值定义***********************************************************/
	#define KEY_CH_COUNT			1			//触摸按键数量，必须正确填写
	
  #define KEY_SEQ       \
		{TS_CH13,50},			\			
		
	
/*********************************************************************
说明：
1：	{TS_CHx, XX}
	   |			 |
		 |			 |	
		 |			 ------------->对应触摸通道的门限值，当触摸数据变化量大于此数值时，按键触发。
		 --------------------->触摸通道序号。
	
2：	以上触摸门限值可在触摸在线调试模式下由上位机软件(CACHIPTOOL.exe)导出。
*********************************************************************/
//-------------------------------------------------------------------------------------------------------------------

	
//-------------------------------------------------------------------------------------------------------------------
/***********触摸按键消抖及按键输出时间定义************************************************************************************/	
#define FINGER_TOUCH_CONFIRM_TIME						3 				//触摸按键按下确认时间，单位为15.625ms
#define FINGER_TOUCH_RELEASE_CONFIRM_TIME		3 				//触摸按键释放确认时间，单位为15.625ms
#define FINGER_LONG_TOUCH_TIME_LIMIT				60    		//限制按键输出时间，单位为0.5s，若定义为0，则关闭此功能	
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
/***********环境值更新速度设置********************************************************/
#define AREA_PNOISE_PLUS_CONFIRM_TIME			50 		//单位为15.625ms
#define AREA_PNOISE_CONFIRM_TIME					50 		//单位为15.625ms
#define AREA_NNOISE_CONFIRM_TIME					50 		//单位为15.625ms
#define AREA_OVERLOW_CONFIRM_TIME					30 		//单位为15.625ms
//说明：一般情况下，环境值更新速度设置用户不需要设置，保持默认值即可。
//-------------------------------------------------------------------------------------------------------------------
#else
#define KEY_CH_COUNT    0
#endif




//-----------------触摸滑条或圆环应用设置-------------------------------------------------------------------------------------------------
#if SUPPORT_WHEEL_SLIDER
//-----------------------------------------------------------------------------
	#define PRINT_WHEEL_SLIDER_POSITION_EN			0			//打印触摸圆环或滑条位置开关
	#define PRINT_WHEEL_SLIDER_DATA_EN					0			//打印触摸圆环或滑条触摸数据开关
	#define PRINT_WHEEL_SLIDER_RATE_EN					0			//打印比率值
	#if (PRINT_WHEEL_SLIDER_DATA_EN || PRINT_WHEEL_SLIDER_RATE_EN)
		#define PRINT_WHEEL_SLIDER_NUM						0			//打印哪个圆环或滑条
	#endif
	#define WHEEL_SLIDER_BASELINE_UPDATE_TIME					50 		//滑条或圆环更新环境值时间，单位为15.625ms
	
//-----------------------------------------------------------------------------
	#define WHEEL_SLIDER_COUNT					2											//圆环或滑条数量，必须正确填写
	
	#define WHEEL_SLIDER_TOUCH_CONFIRM_TIME						2 			//圆环或滑条按下确认时间，单位为15.625ms
	#define WHEEL_SLIDER_TOUCH_RELEASE_CONFIRM_TIME		2 			//圆环或滑条释放确认时间，单位为15.625ms	
	#define WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT				60    	//限制圆环和滑条触发时间，单位为0.5s，若定义为0，则关闭此功能			
//------------------------------------------------------------------------------------	
	#if (WHEEL_SLIDER_COUNT > 0)

		#define WHEEL_OR_SLIDER_DEF0						SLIDER										//是滑条还是圆环，如果是滑条，定义为SLIDER,如果是圆环，定义为WHEEL

		#define WHEEL_SLIDER0_CH_COUNT					4																//第一个圆环或滑条通道数目，必须正确填写	
		#define WHEEL_SLIDER0_SEQ								TS_CH7,TS_CH6,TS_CH5,TS_CH4			//通道列表，以顺时钟或从左到右的顺序填写
		#define WHEEL_SLIDER0_CH_MIN_RATE				70,			40,			40,		70				//手指触摸某通道中间位置时，邻近通道与该通道变化量的比率，该数值与上述通道定义一一对应。该数值可通过打开宏定义PRINT_WHEEL_SLIDER_RATE_EN通过UART打印。


		#define WHEEL_SLIDER0_TOUCH_THD					0x18								//触发门限值定义，此参数决定滑条或圆环灵敏度，数值越小，灵敏度越高。
		#define WHEEL_SLIDER0_NOISE_THD					0x05								//噪声门限值定义
	#endif

		
//以下第二、第三、第四个圆环或滑条的说明参考第一个圆环或滑条的描述，不再赘述
		
//------------------------------------------------------------------------------------		
	#if (WHEEL_SLIDER_COUNT > 1)
		#define WHEEL_OR_SLIDER_DEF1						WHEEL						//是滑条还是圆环，如果是滑条，定义为SLIDER,如果是圆环，定义为WHEEL
	
		#define WHEEL_SLIDER1_CH_COUNT					4								//第二个圆环或滑条通道数目，必须正确填写
		#define WHEEL_SLIDER1_SEQ								TS_CH3,TS_CH0,TS_CH1,TS_CH2				
		#define WHEEL_SLIDER1_CH_MIN_RATE				44,			44,			44,			44
		
		
		#define WHEEL_SLIDER1_TOUCH_THD					0x12	
		#define WHEEL_SLIDER1_NOISE_THD					0x05
	#else
		#define WHEEL_SLIDER1_CH_COUNT					0
	#endif
//------------------------------------------------------------------------------------		
	#if (WHEEL_SLIDER_COUNT > 2)
		#define WHEEL_OR_SLIDER_DEF2						SLIDER					//是滑条还是转盘	
	
		#define WHEEL_SLIDER2_CH_COUNT					3								//第三个转盘或滑条通道数目，必须正确填写	
		#define WHEEL_SLIDER2_SEQ								TS_CH10,TS_CH11,TS_CH12		
		#define WHEEL_SLIDER2_CH_MIN_RATE				44,				44,			44
		
		#define WHEEL_SLIDER2_TOUCH_THD					0x18
		#define WHEEL_SLIDER2_NOISE_THD					0x05
	#else
		#define WHEEL_SLIDER2_CH_COUNT			0
	#endif
//------------------------------------------------------------------------------------	
	#if (WHEEL_SLIDER_COUNT > 3)
		#define WHEEL_OR_SLIDER_DEF3						SLIDER			
	
		#define WHEEL_SLIDER3_CH_COUNT					3								
		#define WHEEL_SLIDER3_SEQ	 							TS_CH15,TS_CH14,TS_CH13	
		#define WHEEL_SLIDER3_CH_MIN_RATE				44,				44,			44
		
		#define WHEEL_SLIDER3_TOUCH_THD					0x18
		#define WHEEL_SLIDER3_NOISE_THD					0x05
	#else
		#define WHEEL_SLIDER3_CH_COUNT			0
	#endif
//------------------------------------------------------------------------------------
#else
		#define WHEEL_SLIDER0_CH_COUNT	0
		#define WHEEL_SLIDER1_CH_COUNT	0
		#define WHEEL_SLIDER2_CH_COUNT	0
		#define WHEEL_SLIDER3_CH_COUNT	0
#endif

//-------------------------------------------------------------------------------------------------------------------		
#define OPENED_TS_COUNT				(KEY_CH_COUNT+WHEEL_SLIDER0_CH_COUNT+WHEEL_SLIDER1_CH_COUNT+WHEEL_SLIDER2_CH_COUNT+WHEEL_SLIDER3_CH_COUNT)
		
#if (!SUPPORT_KEY)		
	#undef DEBUG		
	#define DEBUG 0
#endif
#if DEBUG
// 	#define I2C_SELECT_P36_P37
	#define I2C_SELECT_P30_P31
// 	#define I2C_SELECT_P66_P67
// 	#define I2C_SELECT_P61_P60

	#ifdef I2C_SELECT_P30_P31
		#ifdef UART0_EN
		 #error	"请在ca51f5_config.h中关闭宏定义UART0_EN!"
		#endif
	#elif defined I2C_SELECT_P66_P67
		#ifdef UART1_EN
		 #error	"请在ca51f5_config.h中关闭宏定义UART1_EN!"
		#endif
	#elif defined I2C_SELECT_P61_P60
		#ifdef UART2_EN
		 #error	"请在ca51f5_config.h中关闭宏定义UART2_EN!"
		#endif
	#endif

	#undef SUPPORT_TOUCH_SLEEP_MODE				//省电模式不支持触摸在线调试，所以要关闭省电模式
	#define SUPPORT_TOUCH_SLEEP_MODE			0
#endif

#define TOUCH_PRINT_USE_UART0
// #define TOUCH_PRINT_USE_UART1
// #define TOUCH_PRINT_USE_UART2

/*注意：所选择的UART端口需在ca51f_config.h中使能。*/

#ifdef TOUCH_PRINT_USE_UART0
	#define TK_Debug_UartPutChar			Uart0_PutChar
#elif defined TOUCH_PRINT_USE_UART1
	#define TK_Debug_UartPutChar			Uart1_PutChar
#elif defined TOUCH_PRINT_USE_UART2
	#define TK_Debug_UartPutChar			Uart2_PutChar
#endif
#endif
//-------------------------------------------------------------------------------------------------------------------
