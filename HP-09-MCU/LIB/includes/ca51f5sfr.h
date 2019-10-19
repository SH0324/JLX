#ifndef __CA51F2_SFR_H__
#define __CA51F2_SFR_H__

#include <intrins.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <absacc.h>

sfr P0              = 0x80;
sfr SP              = 0x81;
sfr DP0L            = 0x82;
sfr DP0H            = 0x83;
sfr DP1L            = 0x84;
sfr DP1H            = 0x85;
sfr PWCON           = 0x86;
sfr PCON            = 0x87;
sfr TCON            = 0x88;
sfr TMOD            = 0x89;
sfr TL0             = 0x8a;
sfr TL1             = 0x8b;
sfr TH0             = 0x8c;
sfr TH1             = 0x8d;
sfr IDLST           = 0x8e;
sfr STPST           = 0x8f;

sfr PWMEN           = 0x90;
sfr PWM2DUTH        = 0x91;
sfr PWM3DUTL        = 0x92;
sfr PWM3DUTH        = 0x93;
sfr PWM4DUTL        = 0x94;
sfr PWM4DUTH        = 0x95;
sfr PWM5DUTL        = 0x96;
sfr PWM5DUTH        = 0x97;
sfr S0CON           = 0x98;
sfr S0BUF           = 0x99;
sfr PWM5DIVH        = 0x9a;
sfr PWM0DUTL        = 0x9b;
sfr PWM0DUTH        = 0x9c;
sfr PWM1DUTL        = 0x9d;
sfr PWM1DUTH        = 0x9e;
sfr PWM2DUTL        = 0x9f;

sfr WDCON           = 0xa0;
sfr WDFLG           = 0xa1;
sfr WDVTHL          = 0xa2;
sfr WDVTHH          = 0xa3;
sfr PWM3DIVH        = 0xa4;
sfr PWM4DIVL        = 0xa5;
sfr PWM4DIVH        = 0xa6;
sfr PWM5DIVL        = 0xa7;
sfr IE              = 0xa8;
sfr PWM0DIVL        = 0xa9;
sfr PWM0DIVH        = 0xaa;
sfr PWM1DIVL        = 0xab;
sfr PWM1DIVH        = 0xac;
sfr PWM2DIVL        = 0xad;
sfr PWM2DIVH        = 0xae;
sfr PWM3DIVL        = 0xaf;

sfr P3              = 0xb0;
sfr PWM0CKD         = 0xb1;
sfr PWM1CKD         = 0xb2;
sfr PWM2CKD         = 0xb3;
sfr PWM3CKD         = 0xb4;
sfr PWM4CKD         = 0xb5;
sfr PWM5CKD         = 0xb6;
sfr PWMIF           = 0xb7;
sfr IP              = 0xb8;
sfr PWM0CON         = 0xb9;
sfr PWM1CON         = 0xba;
sfr PWM2CON         = 0xbb;
sfr PWM3CON         = 0xbc;
sfr PWM4CON         = 0xbd;
sfr PWM5CON         = 0xbe;
sfr LEFLG           = 0xbf;

sfr I2CCON          = 0xc0;
sfr I2CADR          = 0xc1;
sfr I2CADM          = 0xc2;
sfr I2CCR           = 0xc3;
sfr I2CDAT          = 0xc4;
sfr I2CSTA          = 0xc5;
sfr I2CFLG          = 0xc6;
sfr LEDAT1          = 0xc7;
sfr T2CON           = 0xc8;
sfr T2MOD           = 0xc9;
sfr T2CL            = 0xca;
sfr T2CH            = 0xcb;
sfr TL2             = 0xcc;
sfr TH2             = 0xcd;
sfr LEDWTML         = 0xce;
sfr LEDWTMH         = 0xcf;

sfr PSW             = 0xd0;
sfr EP0CON          = 0xd1;
sfr EP1CON          = 0xd2;
sfr EP2CON          = 0xd3;
sfr EPIF            = 0xd4;
sfr TMCON           = 0xd5;			   
sfr TMSNU           = 0xd6;
sfr LEDAT0          = 0xd7;
sfr UDCKS          	= 0xd8;
sfr TK3MSH          = 0xd9;
sfr TK4MSL          = 0xda;
sfr TK4MSH          = 0xdb;
sfr TK5MSL          = 0xdc;
sfr TK5MSH          = 0xdd;
sfr AK0CON          = 0xde;
sfr AK1CON          = 0xdf;

sfr ACC             = 0xe0;
sfr TK0MSL          = 0xe1;
sfr TK0MSH          = 0xe2;
sfr TK1MSL          = 0xe3;
sfr TK1MSH          = 0xe4;
sfr TK2MSL          = 0xe5;
sfr TK2MSH          = 0xe6;
sfr TK3MSL          = 0xe7;
sfr LVDCON          = 0xe8;
sfr ATK2CH          = 0xe9;
sfr ATK3CL          = 0xea;
sfr ATK3CH          = 0xeb;
sfr ATK4CL          = 0xec;
sfr ATK4CH          = 0xed;
sfr ATK5CL          = 0xee;
sfr ATK5CH          = 0xef;
sfr ATK2MH          = 0xe9;
sfr ATK3ML          = 0xea;
sfr ATK3MH          = 0xeb;
sfr ATK4ML          = 0xec;
sfr ATK4MH          = 0xed;
sfr ATK5ML          = 0xee;
sfr ATK5MH          = 0xef;

sfr B               = 0xf0;
sfr TK4CHS          = 0xf1;
sfr TK5CHS          = 0xf2;
sfr ATK0CL          = 0xf3;
sfr ATK0CH          = 0xf4;
sfr ATK1CL          = 0xf5;
sfr ATK1CH          = 0xf6;
sfr ATK2CL          = 0xf7;
sfr ATK0ML          = 0xf3;
sfr ATK0MH          = 0xf4;
sfr ATK1ML          = 0xf5;
sfr ATK1MH          = 0xf6;
sfr ATK2ML          = 0xf7;
sfr TKCON           = 0xf8;
sfr TKCFG           = 0xf9;
sfr TKMTS           = 0xfa;
sfr TKIF            = 0xfb;
sfr TK0CHS          = 0xfc;
sfr TK1CHS          = 0xfd;
sfr TK2CHS          = 0xfe;
sfr TK3CHS          = 0xff;

/*  BIT Register  */
/*	PSW	*/
sbit CY   		= 0xD7;
sbit AC   		= 0xD6;
sbit F0   		= 0xD5;
sbit RS1  		= 0xD4;
sbit RS0  		= 0xD3;
sbit OV   		= 0xD2;
sbit DPS   		= 0xD1;
sbit P    		= 0xD0;
		  		
/*	TCON	*/
sbit TF1  		= 0x8F;
sbit TR1  		= 0x8E;
sbit TF0  		= 0x8D;
sbit TR0  		= 0x8C;
sbit IE1  		= 0x8B;
sbit IT1  		= 0x8A;
sbit IE0  		= 0x89;
sbit IT0  		= 0x88;

/*	S0CON   */
sbit SM0  		= 0x9F;
sbit SM1  		= 0x9E;
sbit SM2  		= 0x9D;
sbit REN  		= 0x9C;
sbit TB8  		= 0x9B;
sbit RB8  		= 0x9A;
sbit TI0  		= 0x99;
sbit RI0  		= 0x98;

/*	IE	*/
sbit EA   		= 0xAF;
sbit INT4EN  	= 0xAE;
sbit INT3EN  	= 0xAD;
sbit INT2EN	   	= 0xAC;
sbit ES0	   	= 0xAC;
sbit ET1  		= 0xAB;
sbit EX1  		= 0xAA;
sbit ET0  		= 0xA9;
sbit EX0  		= 0xA8;

/*	IP	*/ 
sbit PS1  		= 0xBE;
sbit PT2  		= 0xBD;
sbit PS0   		= 0xBC;
sbit PT1  		= 0xBB;
sbit PX1  		= 0xBA;
sbit PT0  		= 0xB9;
sbit PX0  		= 0xB8;

/*	T2CON	*/
sbit TF2   		= 0xCF;
sbit TR2  		= 0xCE;
sbit T2R1  		= 0xCD;
sbit T2R0  		= 0xCC;
sbit T2IE       = 0xCB;
sbit UCKS  		= 0xCA;
sbit T2P1  		= 0xC9;
sbit T2P0  		= 0xC8;


/*	P0	*/
sbit P00		= P0^0;
sbit P01		= P0^1;
sbit P02		= P0^2;
sbit P03		= P0^3;
sbit P04		= P0^4;
sbit P05		= P0^5;
sbit P06		= P0^6;
sbit P07		= P0^7;

/*	P3	*/
sbit P30		= P3^0;
sbit P31		= P3^1;
sbit P32		= P3^2;
sbit P33		= P3^3;
sbit P34		= P3^4;
sbit P35		= P3^5;


#ifdef _MAIN_C_
#define XRAM_U8				volatile unsigned char xdata
#define XRAM_U16			volatile unsigned int xdata
#define XRAM_AT_(x)			_at_ x		
#else
#define XRAM_U8				extern volatile unsigned char xdata
#define XRAM_U16			extern volatile unsigned int xdata
#define XRAM_AT_(x)
#endif

XRAM_U8 P00F     	XRAM_AT_(0x8000);
XRAM_U8 P01F        XRAM_AT_(0x8001);
XRAM_U8 P02F        XRAM_AT_(0x8002);
XRAM_U8 P03F        XRAM_AT_(0x8003);
XRAM_U8 P04F        XRAM_AT_(0x8004);
XRAM_U8 P05F        XRAM_AT_(0x8005);
XRAM_U8 P06F        XRAM_AT_(0x8006);
XRAM_U8 P07F        XRAM_AT_(0x8007);
                      
                           
XRAM_U8 P30F        XRAM_AT_(0x8018);
XRAM_U8 P31F        XRAM_AT_(0x8019);
XRAM_U8 P32F        XRAM_AT_(0x801a);
XRAM_U8 P33F        XRAM_AT_(0x801b);
XRAM_U8 P34F        XRAM_AT_(0x801c);
XRAM_U8 P35F        XRAM_AT_(0x801d);

                        
XRAM_U8 CKCON       XRAM_AT_(0x8030);
XRAM_U8 CKDIV       XRAM_AT_(0x8031);
XRAM_U8 IHCFG      	XRAM_AT_(0x8032);
XRAM_U8 ILCFGL      XRAM_AT_(0x8033);
XRAM_U8 ILCFGH     	XRAM_AT_(0x8034);


XRAM_U8 ATK0NL     	XRAM_AT_(0x8050);
XRAM_U8 ATK0NH     	XRAM_AT_(0x8051);
XRAM_U8 ATK1NL     	XRAM_AT_(0x8052);
XRAM_U8 ATK1NH     	XRAM_AT_(0x8053);
XRAM_U8 ATK2NL     	XRAM_AT_(0x8054);
XRAM_U8 ATK2NH     	XRAM_AT_(0x8055);
XRAM_U8 ATK3NL     	XRAM_AT_(0x8056);
XRAM_U8 ATK3NH     	XRAM_AT_(0x8057);
XRAM_U8 ATK4NL     	XRAM_AT_(0x8058);
XRAM_U8 ATK4NH     	XRAM_AT_(0x8059);
XRAM_U8 ATK5NL     	XRAM_AT_(0x805a);
XRAM_U8 ATK5NH     	XRAM_AT_(0x805b);
XRAM_U8 TKMAXF     	XRAM_AT_(0x805c);
XRAM_U8 TKMINF     	XRAM_AT_(0x805d);

XRAM_U8 LEDUTL      XRAM_AT_(0x8060);
XRAM_U8 LEDUTH     	XRAM_AT_(0x8061);

XRAM_U8 SPMAX      	XRAM_AT_(0x8100);
XRAM_U8 I2CIOS      XRAM_AT_(0x8101);
                            
XRAM_U8 MECON       XRAM_AT_(0xfc00);
XRAM_U8 FSCMD       XRAM_AT_(0xfc01);
XRAM_U8 FSDAT       XRAM_AT_(0xfc02);
XRAM_U8 LOCK        XRAM_AT_(0xfc03);
XRAM_U8 PADRD       XRAM_AT_(0xfc04);
XRAM_U8 PTSL        XRAM_AT_(0xfc05);
XRAM_U8 PTSH        XRAM_AT_(0xfc06);
XRAM_U8 REPSET      XRAM_AT_(0xfc07);



enum
{
	HIGH_Z		= 0,					
	INPUT		= 1,          
	OUTPUT		= 2,          
                        
	P31_TK0_SETTING			= 4,
	P30_TK1_SETTING			= 4,
	P07_TK2_SETTING			= 4,
	P06_TK3_SETTING			= 4,
	P05_TK4_SETTING			= 4,
	P04_TK5_SETTING			= 4,
	P03_TK6_SETTING			= 4,
	P02_TK7_SETTING			= 4,
	P01_TK8_SETTING			= 4,
	P00_TK9_SETTING			= 4,
	P34_TK10_SETTING		= 4,
	P33_TK11_SETTING		= 4,
	P32_TK12_SETTING		= 4,
	P35_CAP_SETTING			= 4,
                     
	P32_PWM0_SETTING		= 5,
	P33_PWM1_SETTING		= 5,
	P34_PWM2_SETTING		= 5,
	P01_PWM3_SETTING		= 5,
	P04_PWM4_SETTING		= 5,
	P05_PWM5_SETTING		= 5,

	P00_DAK0_SETTING		= 3,
	P01_DAK1_SETTING		= 3,                        
                       
	P30_UART0_TX_SETTING	= 5,      
	P31_UART0_RX_SETTING	= 5,       
                                           
	P30_I2C_SDA_SETTING		= 3,      
	P31_I2C_SCL_SETTING		= 3,      
	P03_I2C_SDA_SETTING		= 3,      
	P02_I2C_SCL_SETTING		= 3,  	
                        
	P32_T0_SETTING			= 3,        
	P35_T1_SETTING			= 3,        
	P06_T2_SETTING			= 3,        
                        
	P07_RESET_SETTING		= 3,			  
	        
	
	P04_T2CP_SETTING		= 3,  
	P05_T2EX_SETTING		= 3,  

	PU_EN				= 0x80,
	PD_EN				= 0x40,
	OP_EN				= 0x20,
};	
#define  GPIO_Init(reg,val)	reg = val




#define BIT0         					0x01
#define BIT1         					0x02
#define BIT2         					0x04
#define BIT3         					0x08
#define BIT4         					0x10
#define BIT5         					0x20
#define BIT6         					0x40
#define BIT7         					0x80
#define BIT8         					0x100
#define BIT9         					0x200
#define BIT10         					0x400
#define BIT11         					0x800
#define BIT12         					0x1000
#define BIT13         					0x2000
#define BIT14         					0x4000
#define BIT15         					0x8000


#define __NOP1__  	_nop_()
#define __NOP2__ 	__NOP1__; __NOP1__
#define __NOP4__ 	__NOP2__; __NOP2__
#define __NOP8__ 	__NOP4__; __NOP4__
#define __NOP16__ 	__NOP8__; __NOP8__
#define __NOP32__ 	__NOP16__; __NOP16__
#define __NOP64__ 	__NOP32__; __NOP32__
#define __NOP128__ 	__NOP64__; __NOP64__


#define DelayNop(a)             				\
    if ((a)&(0x01))    {__NOP1__;}              \
    if ((a)&(0x02))    {__NOP2__;}              \
    if ((a)&(0x04))    {__NOP4__;}              \
    if ((a)&(0x08))    {__NOP8__;}              \
    if ((a)&(0x10))    {__NOP16__;}             \
    if ((a)&(0x20))    {__NOP32__;}             \
    if ((a)&(0x40))    {__NOP64__;}             \
    if ((a)&(0x80))    {__NOP128__;}          


#endif  
