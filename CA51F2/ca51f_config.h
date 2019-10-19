#include "ca51f2sfr.h"


#define IRCH		0
#define IRCL		1
#define PLL			2
#define XOSCH		3
#define XOSCL		4

/**************************************************************************************************************/
#define SYSCLK_SRC	PLL									//оƬϵͳʱ��ѡ��,һ���������ΪIRCH��PLL
/**************************************************************************************************************/

/************ϵͳʱ��Ƶ�ʶ��壬��Ҫ��������UART������**********************************************************/
#if (SYSCLK_SRC == IRCH)
	#define FOSC		(3686400)
#elif (SYSCLK_SRC == PLL)
	#define PLL_Multiple			6			//����PLL��Ƶ����,��IRCH��Ƶ��Ϊ3.6864Mʱ����߱�Ƶ����Ҫ����6��
	#define FOSC		(3686400*PLL_Multiple)
#else
	#define FOSC		(3686400)
#endif
/***************************************************************************************************************/

#define RTC_CLK_SELECT		XOSCL			//����RTCʱ��Դ�� �����32768����ʱ����ΪXOSCL��������ΪIRCL
/***************************************************************************************************************/

#define LVD_RST_ENABLE		//оƬ���絽1.2V���������ϵ��п��Ե�����������LVD��λ���ܿɽ��������
//LVDCON    LVDE-LVDS-LVDF- -LVDTH(3:0)
//             1    0    1      0111            ʹ��LVD �жϷ�ʽ ���־  3.2V       A7
/*************************UART���ܿ��غ궨��********************************************************************/

/***********************LCD���ܶ���*******************************************************************/
#define LCD_CLK_SOURCE		IRCH//XOSCL//IRCL

#define LCD_RAM_SIZE	6







//#define UART0_EN			//���ʹ��UART0���򿪴˺궨��
// #define UART1_EN			//���ʹ��UART1���򿪴˺궨��
// #define UART2_EN 		//ֻ��F2ϵ�в���UART2�����ʹ��UART2���򿪴˺궨��



//#define PRINT_EN				//ʹ��uart_printf������ӡʹ��

#ifdef PRINT_EN
	#define UART0_PRINT		//���ʹ��UART0��ӡ���򿪴˺궨��
//	#define UART1_PRINT		//���ʹ��UART1��ӡ���򿪴˺궨��
//	#define UART2_PRINT		//���ʹ��UART2��ӡ���򿪴˺궨��
			
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









