#include "ca51f2sfr.h"


#define IRCH		0
#define IRCL		1
#define PLL			2
#define XOSCH		3
#define XOSCL		4

/**************************************************************************************************************/
#define SYSCLK_SRC	PLL									//芯片系统时钟选择,一般情况设置为IRCH或PLL
/**************************************************************************************************************/

/************系统时钟频率定义，主要用于配置UART波特率**********************************************************/
#if (SYSCLK_SRC == IRCH)
	#define FOSC		(3686400)
#elif (SYSCLK_SRC == PLL)
	#define PLL_Multiple			6			//定义PLL倍频倍数,当IRCH的频率为3.6864M时，最高倍频数不要超过6倍
	#define FOSC		(3686400*PLL_Multiple)
#else
	#define FOSC		(3686400)
#endif
/***************************************************************************************************************/

#define RTC_CLK_SELECT		XOSCL			//定义RTC时钟源， 在外接32768晶振时定义为XOSCL，否则定义为IRCL
/***************************************************************************************************************/

#define LVD_RST_ENABLE		//芯片掉电到1.2V左右再重上电有可以导致死机，打开LVD复位功能可解决此问题
//LVDCON    LVDE-LVDS-LVDF- -LVDTH(3:0)
//             1    0    1      0111            使能LVD 中断方式 清标志  3.2V       A7
/*************************UART功能开关宏定义********************************************************************/

/***********************LCD功能定义*******************************************************************/
#define LCD_CLK_SOURCE		IRCH//XOSCL//IRCL

#define LCD_RAM_SIZE	6







//#define UART0_EN			//如果使用UART0，打开此宏定义
// #define UART1_EN			//如果使用UART1，打开此宏定义
// #define UART2_EN 		//只有F2系列才有UART2，如果使用UART2，打开此宏定义



//#define PRINT_EN				//使用uart_printf函数打印使能

#ifdef PRINT_EN
	#define UART0_PRINT		//如果使用UART0打印，打开此宏定义
//	#define UART1_PRINT		//如果使用UART1打印，打开此宏定义
//	#define UART2_PRINT		//如果使用UART2打印，打开此宏定义
			
	#ifdef UART0_PRINT
		#define UART0_EN
	#elif defined  UART1_PRINT
		#define UART1_EN
	#elif defined  UART2_PRINT
		#define UART2_EN
	#endif
#endif



#ifdef UART0_EN
	#define UART0_BAUTRATE		115200
#endif
#ifdef UART1_EN
	#define UART1_BAUTRATE		115200
#endif
#ifdef UART2_EN
	#define UART2_BAUTRATE		115200
#endif
/*********************************************************************************************************************/

/*********************************************/









