#ifndef __CA51F3_SFR_H__
#define __CA51F3_SFR_H__

#include <intrins.h>


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
sfr IT1CON          = 0x8e;
sfr IT0CON          = 0x8f;

sfr P1              = 0x90;
sfr RCCON           = 0x91;
sfr VCKDL           = 0x92;
sfr VCKDH           = 0x93;
sfr RCTAGL          = 0x94;
sfr RCTAGH          = 0x95;
sfr RCMSLL          = 0x96;
sfr RCMSLH          = 0x97;
sfr S0CON           = 0x98;
sfr S0BUF           = 0x99;
sfr S1CON           = 0x9a;
sfr S1BUF           = 0x9b;
sfr S1RELL          = 0x9c;
sfr S1RELH          = 0x9d;
sfr RCMSHL          = 0x9e;
sfr RCMSHH          = 0x9f;

sfr P2              = 0xa0;
sfr CKCON           = 0xa1;
sfr CKSEL           = 0xa2;
sfr CKDIV           = 0xa3;
sfr IHCFGL          = 0xa4;
sfr IHCFGH          = 0xa5;
sfr ILCFGL          = 0xa6;
sfr ILCFGH          = 0xa7;
sfr IE              = 0xa8;
sfr WDCON           = 0xa9;
sfr WDFLG           = 0xaa;
sfr WDVTHL          = 0xab;
sfr WDVTHH          = 0xac;
sfr PLLCON          = 0xad;
//                    0xae;
sfr TFCFG           = 0xaf;

sfr P3              = 0xb0;
sfr I2CCON          = 0xb1;
sfr I2CADR          = 0xb2;
sfr I2CADM          = 0xb3;
sfr I2CCR           = 0xb4;
sfr I2CDAT          = 0xb5;
sfr I2CSTA          = 0xb6;
sfr I2CFLG          = 0xb7;
sfr IP              = 0xb8;
sfr ADCON           = 0xb9;
sfr ADCFGL          = 0xba;
sfr ADCFGH          = 0xbb;
sfr ADCDL           = 0xbc;
sfr ADCDH           = 0xbd;
sfr CKMON           = 0xbe;
sfr CKMIF           = 0xbf;

sfr INDEX           = 0xc0;
sfr TKCON           = 0xc1;
sfr TKCFG           = 0xc2;
sfr TKMTS           = 0xc3;
sfr TKCHS           = 0xc4;
sfr ATKCL           = 0xc5;
sfr ATKCH           = 0xc6;
sfr TKIF            = 0xc7;
sfr T2CON           = 0xc8;
sfr T2MOD           = 0xc9;
sfr T2CL            = 0xca;
sfr T2CH            = 0xcb;
sfr TL2             = 0xcc;
sfr TH2             = 0xcd;
sfr TKMSL           = 0xce;
sfr TKMSH           = 0xcf;

sfr PSW             = 0xd0;
sfr PWMDUTH         = 0xd1;
sfr PWMAIF          = 0xd2;
sfr PWMBIF          = 0xd3;
sfr PWMCIF          = 0xd4;
sfr TKMAXF          = 0xd5;
sfr TKMINF          = 0xd6;

sfr PWMEN           = 0xd8;
sfr PWMUPD          = 0xd9;
sfr PWMCMAX         = 0xda;
sfr PWMCON          = 0xdb;
sfr PWMCFG          = 0xdc;
sfr PWMDIVL         = 0xdd;
sfr PWMDIVH         = 0xde;
sfr PWMDUTL         = 0xdf;

sfr ACC             = 0xe0;
sfr LXCON           = 0xe1;
sfr LXCFG           = 0xe2;
sfr LXDAT           = 0xe3;
sfr LXDIVL          = 0xe4;
sfr LXDIVH          = 0xe5;
sfr ATKNL          	= 0xe6;
sfr ATKNH          	= 0xe7;

sfr EXIE            = 0xe8;
sfr RTCSS           = 0xe9;
sfr RTAS            = 0xea;
sfr RTAM            = 0xeb;
sfr RTAH            = 0xec;
sfr RTMSS           = 0xed;
sfr RTCIF           = 0xee;
sfr LVDCON          = 0xef;

sfr B               = 0xf0;
sfr RTCON           = 0xf1;
sfr RTCS            = 0xf2;
sfr RTCM            = 0xf3;
sfr RTCH            = 0xf4;
sfr RTCDL           = 0xf5;
sfr RTCDH           = 0xf6;
sfr RSTF            = 0xf7;
sfr EXIP            = 0xf8;
sfr EPIE            = 0xf9;
sfr EPIF            = 0xfa;
sfr EPCON           = 0xfb;
sfr IDLSTL          = 0xfc;
sfr IDLSTH          = 0xfd;
sfr STPSTL          = 0xfe;
sfr STPSTH          = 0xff;

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
sbit ES1  		= 0xAE;
sbit ET2  		= 0xAD;
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

/*	EXIE	*/
sbit INT9EN     = 0xEF;
sbit INT8EN     = 0xEE;
sbit INT7EN     = 0xED;
sbit INT6EN     = 0xEC;
sbit INT5EN     = 0xEB;
sbit INT4EN     = 0xEA;
sbit INT3EN     = 0xE9;
sbit INT2EN     = 0xE8;

/*	P0	*/
sbit P00		= P0^0;
sbit P01		= P0^1;
sbit P02		= P0^2;
sbit P03		= P0^3;
sbit P04		= P0^4;
sbit P05		= P0^5;
sbit P06		= P0^6;
sbit P07		= P0^7;
/*	P1	*/     	
sbit P10		= P1^0;
sbit P11		= P1^1;
sbit P12		= P1^2;
sbit P13		= P1^3;
sbit P14		= P1^4;
sbit P15		= P1^5;
sbit P16		= P1^6;
sbit P17		= P1^7;
/*	P2	*/        	
sbit P20		= P2^0;
sbit P21		= P2^1;
sbit P22		= P2^2;
sbit P23		= P2^3;
sbit P24		= P2^4;
sbit P25		= P2^5;
sbit P26		= P2^6;

/*	P3	*/
sbit P30		= P3^0;
sbit P31		= P3^1;
sbit P32		= P3^2;
sbit P33		= P3^3;
sbit P34		= P3^4;
sbit P35		= P3^5;
sbit P36		= P3^6;
sbit P37		= P3^7;		

#ifdef _MAIN_C_
#define XRAM_U8				volatile unsigned char xdata
#define XRAM_U16			volatile unsigned int xdata
#define XRAM_AT_(x)			_at_ x		
#else
#define XRAM_U8				extern volatile unsigned char xdata
#define XRAM_U16			extern volatile unsigned int xdata
#define XRAM_AT_(x)
#endif

XRAM_U8 P00F        XRAM_AT_(0x8000);
XRAM_U8 P01F        XRAM_AT_(0x8001);
XRAM_U8 P02F        XRAM_AT_(0x8002);
XRAM_U8 P03F        XRAM_AT_(0x8003);
XRAM_U8 P04F        XRAM_AT_(0x8004);
XRAM_U8 P05F        XRAM_AT_(0x8005);
XRAM_U8 P06F        XRAM_AT_(0x8006);
XRAM_U8 P07F        XRAM_AT_(0x8007);

XRAM_U8 P10F        XRAM_AT_(0x8008);
XRAM_U8 P11F        XRAM_AT_(0x8009);
XRAM_U8 P12F        XRAM_AT_(0x800a);
XRAM_U8 P13F        XRAM_AT_(0x800b);
XRAM_U8 P14F        XRAM_AT_(0x800c);
XRAM_U8 P15F        XRAM_AT_(0x800d);
XRAM_U8 P16F        XRAM_AT_(0x800e);
XRAM_U8 P17F        XRAM_AT_(0x800f);

XRAM_U8 P20F        XRAM_AT_(0x8010);
XRAM_U8 P21F        XRAM_AT_(0x8011);

XRAM_U8 P30F        XRAM_AT_(0x8018);
XRAM_U8 P31F        XRAM_AT_(0x8019);
XRAM_U8 P32F        XRAM_AT_(0x801a);
XRAM_U8 P33F        XRAM_AT_(0x801b);
XRAM_U8 P34F        XRAM_AT_(0x801c);
XRAM_U8 P35F        XRAM_AT_(0x801d);
XRAM_U8 P36F        XRAM_AT_(0x801e);
XRAM_U8 P37F        XRAM_AT_(0x801f);

XRAM_U8 ADCALL      XRAM_AT_(0x8020);
XRAM_U8 ADCALH      XRAM_AT_(0x8021);

XRAM_U8 SPMAX      	XRAM_AT_(0x8100);
XRAM_U8 I2CIOS      XRAM_AT_(0x8101);

XRAM_U8 TKPWC       XRAM_AT_(0x8103);
XRAM_U8 TLEN        XRAM_AT_(0x8106);
XRAM_U8 TLDAT       XRAM_AT_(0x8107);
XRAM_U8 TLCON       XRAM_AT_(0x8108);
XRAM_U8 TLFLG       XRAM_AT_(0x8109);
XRAM_U8 TLCKS       XRAM_AT_(0x810a);
XRAM_U8 TLCNTKL     XRAM_AT_(0x810b);
XRAM_U8 TLCNTKH     XRAM_AT_(0x810c);
XRAM_U8 TLCNTLL     XRAM_AT_(0x810d);
XRAM_U8 TLCNTLH     XRAM_AT_(0x810e);
XRAM_U8 TLCNTD      XRAM_AT_(0x810f);
XRAM_U8 TLCOMS      XRAM_AT_(0x8110);
XRAM_U8 LXCAD       XRAM_AT_(0x8117);
XRAM_U8 FTCTL       XRAM_AT_(0x811e);
XRAM_U8 TPCTL       XRAM_AT_(0x811f);
XRAM_U8 P00C        XRAM_AT_(0x8120);
XRAM_U8 P01C        XRAM_AT_(0x8121);
XRAM_U8 P02C        XRAM_AT_(0x8122);
XRAM_U8 P03C        XRAM_AT_(0x8123);
XRAM_U8 P04C        XRAM_AT_(0x8124);
XRAM_U8 P05C        XRAM_AT_(0x8125);
XRAM_U8 P06C        XRAM_AT_(0x8126);
XRAM_U8 P07C        XRAM_AT_(0x8127);
XRAM_U8 P10C        XRAM_AT_(0x8128);
XRAM_U8 P11C        XRAM_AT_(0x8129);
XRAM_U8 P12C        XRAM_AT_(0x812a);
XRAM_U8 P13C        XRAM_AT_(0x812b);
XRAM_U8 P14C        XRAM_AT_(0x812c);
XRAM_U8 P15C        XRAM_AT_(0x812d);
XRAM_U8 P16C        XRAM_AT_(0x812e);
XRAM_U8 P17C        XRAM_AT_(0x812f);
XRAM_U8 P20C        XRAM_AT_(0x8130);
XRAM_U8 P21C        XRAM_AT_(0x8131);
XRAM_U8 P30C        XRAM_AT_(0x8138);
XRAM_U8 P31C        XRAM_AT_(0x8139);
XRAM_U8 P32C        XRAM_AT_(0x813a);
XRAM_U8 P33C        XRAM_AT_(0x813b);
XRAM_U8 P34C        XRAM_AT_(0x813c);
XRAM_U8 P35C        XRAM_AT_(0x813d);
XRAM_U8 P36C        XRAM_AT_(0x813e);
XRAM_U8 P37C        XRAM_AT_(0x813f);


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

	P00_COM0_SETTING		= 3,
	P01_COM1_SETTING		= 3,
	P02_COM2_SETTING		= 3,
	P03_COM3_SETTING		= 3,
	P04_COM4_SETTING		= 3,
	P17_SEG0_SETTING		= 3,
	P37_SEG1_SETTING		= 3,
	P36_SEG2_SETTING		= 3,
	P35_SEG3_SETTING		= 3,
	P34_SEG4_SETTING		= 3,
	P07_SEG5_SETTING		= 3,
	P06_SEG6_SETTING		= 3,
	P05_SEG7_SETTING		= 3,
	P04_SEG8_SETTING		= 5,
	P03_SEG9_SETTING		= 5,

	P10_TK0_SETTING			= 4,
	P11_TK1_SETTING			= 4,
	P12_TK2_SETTING			= 4,
	P13_TK3_SETTING			= 4,
	P14_TK4_SETTING			= 4,
	P15_TK5_SETTING			= 4,
	P16_TK6_SETTING			= 4,
	P17_TK7_SETTING			= 4,
	P37_TK8_SETTING			= 4,
	P36_TK9_SETTING			= 4,
	P35_TK10_SETTING		= 4,
	P34_TK11_SETTING		= 4,
	P07_TK12_SETTING		= 4,
	P06_TK13_SETTING		= 4,
	P05_TK14_SETTING		= 4,
	P04_TK15_SETTING		= 4,
	P03_TK16_SETTING		= 4,
	P02_TK17_SETTING		= 4,
	P01_TK18_SETTING		= 4,
	P00_TK19_SETTING		= 4,

	P15_PWM0_SETTING		= 6,
	P16_PWM1_SETTING		= 6,
	P35_PWM2_SETTING		= 6,
	P34_PWM3_SETTING		= 6,
	P07_PWM4_SETTING		= 6,
	P06_PWM5_SETTING		= 6,
    
	P10_ADC0_SETTING		= 5,
	P11_ADC1_SETTING		= 5,
	P12_ADC2_SETTING		= 5,
	P13_ADC3_SETTING		= 5,
	P14_ADC4_SETTING		= 5,
	P15_ADC5_SETTING		= 5,
	P16_ADC6_SETTING		= 5,
	P17_ADC7_SETTING		= 5,
	P10_ADC_VREF_SETTING	= 0,

	P30_UART0_TX_SETTING	= 3,
	P31_UART0_RX_SETTING	= 3,
	P11_UART1_TX_SETTING	= 3,
	P12_UART1_RX_SETTING	= 3,
        
	P30_I2C_SDA_SETTING		= 4,
	P31_I2C_SCL_SETTING		= 4,
      
	P11_I2C_SDA_SETTING		= 6,
	P12_I2C_SCL_SETTING		= 6,
 
	P13_T0_SETTING			= 1,
	P14_T1_SETTING			= 1,
	P15_T2_SETTING			= 1,

	P20_RESET_SETTING		= 3,
	P21_CAP_SETTING			= 3,
	P32_XOSC_IN_SETTING		= 3,
	P33_XOSC_OUT_SETTING	= 3,
	P36_T2CP_SETTING		= 5,
	P37_T2EX_SETTING		= 1,

	P00_ERC_SETTING			= 5,

	PU_EN			    	= 0x80,
	PD_EN			    	= 0x40,
	OP_EN			    	= 0x20,
};	
#define  GPIO_Init(reg,val)	reg = val

#define BIT0         		0x01
#define BIT1         		0x02
#define BIT2         		0x04
#define BIT3         		0x08
#define BIT4         		0x10
#define BIT5         		0x20
#define BIT6         		0x40
#define BIT7         		0x80
#define BIT8         		0x100
#define BIT9         		0x200
#define BIT10         		0x400
#define BIT11         		0x800
#define BIT12         		0x1000
#define BIT13         		0x2000
#define BIT14         		0x4000
#define BIT15         		0x8000


#define __NOP1__  	_nop_()
#define __NOP2__ 	__NOP1__; __NOP1__
#define __NOP4__ 	__NOP2__; __NOP2__
#define __NOP8__ 	__NOP4__; __NOP4__
#define __NOP16__ 	__NOP8__; __NOP8__
#define __NOP32__ 	__NOP16__; __NOP16__
#define __NOP64__ 	__NOP32__; __NOP32__
#define __NOP128__ 	__NOP64__; __NOP64__


#define DelayNop(a)             		\
    if ((a)&(0x01))    {__NOP1__;}      \
    if ((a)&(0x02))    {__NOP2__;}      \
    if ((a)&(0x04))    {__NOP4__;}      \
    if ((a)&(0x08))    {__NOP8__;}      \
    if ((a)&(0x10))    {__NOP16__;}     \
    if ((a)&(0x20))    {__NOP32__;}     \
    if ((a)&(0x40))    {__NOP64__;}     \
    if ((a)&(0x80))    {__NOP128__;}    


#endif

