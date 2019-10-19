#ifndef __CA51F2_SFR_H__
#define __CA51F2_SFR_H__

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
sfr S2CON           = 0xa1;
sfr S2BUF           = 0xa2;
sfr S2RELL          = 0xa3;
sfr S2RELH          = 0xa4;
sfr SPCON           = 0xa5;
sfr SPDAT           = 0xa6;
sfr SPSTA           = 0xa7;
sfr IE              = 0xa8;
sfr P6              = 0xa9;
sfr WDCON           = 0xaa;
sfr WDFLG           = 0xab;
sfr WDVTHL          = 0xac;
sfr WDVTHH          = 0xad;
sfr PLLCON          = 0xae;
sfr HVTH            = 0xaf;

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

sfr P4              = 0xc0;
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
sfr PWMDIVH         = 0xd1;
sfr PWMDUTL         = 0xd2;
sfr PWMDUTH         = 0xd3;
sfr PWMAIF          = 0xd4;
sfr PWMBIF          = 0xd5;
sfr PWMCIF          = 0xd6;
sfr PWMDIF          = 0xd7;
sfr P5              = 0xd8;
sfr P7              = 0xd9;
sfr PWMEN           = 0xda;
sfr PWMUPD          = 0xdb;
sfr PWMCMAX         = 0xdc;
sfr PWMCON          = 0xdd;
sfr PWMCFG          = 0xde;
sfr PWMDIVL         = 0xdf;

sfr ACC             = 0xe0;
sfr LXCON           = 0xe1;
sfr LXCFG           = 0xe2;
sfr LXDAT           = 0xe3;
sfr LXDIVL          = 0xe4;
sfr LXDIVH          = 0xe5;
sfr MDUCON          = 0xe6;
sfr MDUDAT          = 0xe7;
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
sfr INDEX           = 0xf7;
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
sbit INT9EN   		= 0xEF;
sbit INT8EN  		= 0xEE;
sbit INT7EN  		= 0xED;
sbit INT6EN	   		= 0xEC;
sbit INT5EN  		= 0xEB;
sbit INT4EN  		= 0xEA;
sbit INT3EN  		= 0xE9;
sbit INT2EN  		= 0xE8;

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

/*	P4	*/
sbit P40		= P4^0;
sbit P41		= P4^1;
sbit P42		= P4^2;
sbit P43		= P4^3;
sbit P44		= P4^4;
sbit P45		= P4^5;
sbit P46		= P4^6;
sbit P47		= P4^7;	

/*	P5	*/
sbit P50		= P5^0;
sbit P51		= P5^1;
sbit P52		= P5^2;
sbit P53		= P5^3;
sbit P54		= P5^4;
sbit P55		= P5^5;
sbit P56		= P5^6;
sbit P57		= P5^7;	

//注意：P6,P7不支持位操作
/*	P6	*/
#define P60(n)		{if(n) P6|=0x01;else P6&=~0x01;}
#define P61(n)		{if(n) P6|=0x02;else P6&=~0x02;}
#define P62(n)		{if(n) P6|=0x04;else P6&=~0x04;}
#define P63(n)		{if(n) P6|=0x08;else P6&=~0x08;}
#define P64(n)		{if(n) P6|=0x10;else P6&=~0x10;}
#define P65(n)		{if(n) P6|=0x20;else P6&=~0x20;}
#define P66(n)		{if(n) P6|=0x40;else P6&=~0x40;}
#define P67(n)		{if(n) P6|=0x80;else P6&=~0x80;}

/*	P7	*/
#define P70(n)		{if(n) P7|=0x01;else P7&=~0x01;}
#define P71(n)		{if(n) P7|=0x02;else P7&=~0x02;}
#define P72(n)		{if(n) P7|=0x04;else P7&=~0x04;}
#define P73(n)		{if(n) P7|=0x08;else P7&=~0x08;}
#define P74(n)		{if(n) P7|=0x10;else P7&=~0x10;}
#define P75(n)		{if(n) P7|=0x20;else P7&=~0x20;}




#ifdef _MAIN_C_
#define XRAM_U8										volatile unsigned char xdata
#define XRAM_U16									volatile unsigned int xdata
#define XRAM_AT_(x)									_at_ x		
#else
#define XRAM_U8										extern volatile unsigned char xdata
#define XRAM_U16									extern volatile unsigned int xdata
#define XRAM_AT_(x)
#endif

XRAM_U8 P00F     		XRAM_AT_(0x8000);
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
XRAM_U8 P22F        XRAM_AT_(0x8012);
XRAM_U8 P23F        XRAM_AT_(0x8013);
XRAM_U8 P24F        XRAM_AT_(0x8014);
XRAM_U8 P25F        XRAM_AT_(0x8015);
XRAM_U8 P26F        XRAM_AT_(0x8016);
XRAM_U8 P27F        XRAM_AT_(0x8017);
                           
XRAM_U8 P30F        XRAM_AT_(0x8018);
XRAM_U8 P31F        XRAM_AT_(0x8019);
XRAM_U8 P32F        XRAM_AT_(0x801a);
XRAM_U8 P33F        XRAM_AT_(0x801b);
XRAM_U8 P34F        XRAM_AT_(0x801c);
XRAM_U8 P35F        XRAM_AT_(0x801d);
XRAM_U8 P36F        XRAM_AT_(0x801e);
XRAM_U8 P37F        XRAM_AT_(0x801f);
                          
XRAM_U8 P40F        XRAM_AT_(0x8020);
XRAM_U8 P41F        XRAM_AT_(0x8021);
XRAM_U8 P42F        XRAM_AT_(0x8022);
XRAM_U8 P43F        XRAM_AT_(0x8023);
XRAM_U8 P44F        XRAM_AT_(0x8024);
XRAM_U8 P45F        XRAM_AT_(0x8025);
XRAM_U8 P46F        XRAM_AT_(0x8026);
XRAM_U8 P47F        XRAM_AT_(0x8027);
                           
XRAM_U8 P50F        XRAM_AT_(0x8028);
XRAM_U8 P51F        XRAM_AT_(0x8029);
XRAM_U8 P52F        XRAM_AT_(0x802a);
XRAM_U8 P53F        XRAM_AT_(0x802b);
XRAM_U8 P54F        XRAM_AT_(0x802c);
XRAM_U8 P55F        XRAM_AT_(0x802d);
XRAM_U8 P56F        XRAM_AT_(0x802e);
XRAM_U8 P57F        XRAM_AT_(0x802f);
                           
XRAM_U8 P60F        XRAM_AT_(0x8030);
XRAM_U8 P61F        XRAM_AT_(0x8031);
XRAM_U8 P62F        XRAM_AT_(0x8032);
XRAM_U8 P63F        XRAM_AT_(0x8033);
XRAM_U8 P64F        XRAM_AT_(0x8034);
XRAM_U8 P65F        XRAM_AT_(0x8035);
XRAM_U8 P66F        XRAM_AT_(0x8036);
XRAM_U8 P67F        XRAM_AT_(0x8037);
                           
XRAM_U8 P70F        XRAM_AT_(0x8038);
XRAM_U8 P71F        XRAM_AT_(0x8039);
XRAM_U8 P72F        XRAM_AT_(0x803a);
XRAM_U8 P73F        XRAM_AT_(0x803b);
XRAM_U8 P74F        XRAM_AT_(0x803c);
XRAM_U8 P75F        XRAM_AT_(0x803d);

                           
XRAM_U8 OPACON      XRAM_AT_(0x8040);
XRAM_U8 OPBCON      XRAM_AT_(0x8041);
                           
XRAM_U8 CP0CON      XRAM_AT_(0x8048);
XRAM_U8 CP1CON      XRAM_AT_(0x8049);
XRAM_U8 CP2CON      XRAM_AT_(0x804a);
XRAM_U8 CP3CON      XRAM_AT_(0x804b);
XRAM_U8 CPCKS       XRAM_AT_(0x804c);
XRAM_U8 CPSTA       XRAM_AT_(0x804d);
XRAM_U8 CPVTC       XRAM_AT_(0x804e);
                        
XRAM_U8 FT0SL       XRAM_AT_(0x8050);
XRAM_U8 FT0SH       XRAM_AT_(0x8051);
XRAM_U8 FT1SL       XRAM_AT_(0x8052);
XRAM_U8 FT1SH       XRAM_AT_(0x8053);
XRAM_U8 FT2SL       XRAM_AT_(0x8054);
XRAM_U8 FT2SH       XRAM_AT_(0x8055);
XRAM_U8 FT3SL       XRAM_AT_(0x8056);
XRAM_U8 FT3SH       XRAM_AT_(0x8057);
                          
XRAM_U8 CTMCON      XRAM_AT_(0x8058);
XRAM_U8 CTMVTHL     XRAM_AT_(0x8059);
XRAM_U8 CTMVTHH     XRAM_AT_(0x805a);

XRAM_U8 CTMCAPL     XRAM_AT_(0x805b);
XRAM_U8 CTMCAPH     XRAM_AT_(0x805c);
                           
XRAM_U8 MOTCON      XRAM_AT_(0x8060);
XRAM_U8 MOTCFG      XRAM_AT_(0x8061);
XRAM_U8 MTGCON      XRAM_AT_(0x8062);
XRAM_U8 MHLCON      XRAM_AT_(0x8063);
XRAM_U8 MFPCON      XRAM_AT_(0x8064);
XRAM_U8 MOTCMD      XRAM_AT_(0x8065);
XRAM_U8 MTGDL       XRAM_AT_(0x8066);
XRAM_U8 MOTIF       XRAM_AT_(0x8067);
                         
XRAM_U8 HDCT0       XRAM_AT_(0x8068);
XRAM_U8 HDCT1       XRAM_AT_(0x8069);
XRAM_U8 HDCT2       XRAM_AT_(0x806a);
XRAM_U8 HDCT3       XRAM_AT_(0x806b);
XRAM_U8 HDCT4       XRAM_AT_(0x806c);
XRAM_U8 HDCT5       XRAM_AT_(0x806d);
XRAM_U8 HDCT6       XRAM_AT_(0x806e);
XRAM_U8 HDCT7       XRAM_AT_(0x806f);
                           
XRAM_U8 HDCT8       XRAM_AT_(0x8070);
XRAM_U8 HDCT9       XRAM_AT_(0x8071);
XRAM_U8 HDCT10      XRAM_AT_(0x8072);
XRAM_U8 HDCT11      XRAM_AT_(0x8073);
XRAM_U8 MOTPLC      XRAM_AT_(0x8074);
                          
XRAM_U8 SMCON       XRAM_AT_(0x8078);
XRAM_U8 SMSTA       XRAM_AT_(0x8079);
XRAM_U8 SMDIV       XRAM_AT_(0x807a);
XRAM_U8 SMDATL      XRAM_AT_(0x807b);
XRAM_U8 SMDATH      XRAM_AT_(0x807c);
XRAM_U8 SMVTHL      XRAM_AT_(0x807d);
XRAM_U8 SMVTHH      XRAM_AT_(0x807e);
                        
XRAM_U8 CKCON       XRAM_AT_(0x8080);
XRAM_U8 CKSEL       XRAM_AT_(0x8081);
XRAM_U8 CKDIV       XRAM_AT_(0x8082);
XRAM_U8 IHCFGL      XRAM_AT_(0x8083);
XRAM_U8 IHCFGH      XRAM_AT_(0x8084);
XRAM_U8 ILCFGL      XRAM_AT_(0x8085);
XRAM_U8 ILCFGH      XRAM_AT_(0x8086);
XRAM_U8 TFCFG       XRAM_AT_(0x8087);
                           
XRAM_U8 ADCALL      XRAM_AT_(0x8088);
XRAM_U8 ADCALH      XRAM_AT_(0x8089);
XRAM_U8 ACPDLL      XRAM_AT_(0x808a);
XRAM_U8 ACPDLH      XRAM_AT_(0x808b);
XRAM_U8 ACPDHL      XRAM_AT_(0x808c);
XRAM_U8 ACPDHH      XRAM_AT_(0x808d);
XRAM_U8 TKMAXF      XRAM_AT_(0x8090);
XRAM_U8 TKMINF      XRAM_AT_(0x8091);
XRAM_U8 ATKNL       XRAM_AT_(0x8092);
XRAM_U8 ATKNH       XRAM_AT_(0x8093);

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
	HIGH_Z		            = 0,					
	INPUT		            = 1,          
	OUTPUT		            = 2,          
                            
	P00_COM0_SETTING		= 3,  
	P01_COM1_SETTING		= 3,  
	P02_COM2_SETTING		= 3,  
	P03_COM3_SETTING		= 3,  
	P04_COM4_SETTING		= 3,  
	P05_COM5_SETTING		= 3,  
	P06_COM6_SETTING		= 3,  
	P07_COM7_SETTING		= 3,  
	
	P57_SEG0_SETTING		= 3,  
	P34_SEG1_SETTING		= 3,  
	P35_SEG2_SETTING		= 3,  
	P56_SEG3_SETTING		= 3,  
	P50_SEG4_SETTING		= 3,  
	P51_SEG5_SETTING		= 3,  
	P52_SEG6_SETTING		= 3,  
	P53_SEG7_SETTING		= 3,  
	P54_SEG8_SETTING		= 3,  
	P55_SEG9_SETTING		= 3,  
	P60_SEG10_SETTING		= 3,  
	P61_SEG11_SETTING		= 3,  
	P62_SEG12_SETTING		= 3,  
	P63_SEG13_SETTING		= 3,  
	P64_SEG14_SETTING		= 3,  
	P65_SEG15_SETTING		= 3,  
	P10_SEG16_SETTING		= 3,  
	P11_SEG17_SETTING		= 3,  
	P12_SEG18_SETTING		= 3,  
	P13_SEG19_SETTING		= 3,  
	P14_SEG20_SETTING		= 3,  
	P15_SEG21_SETTING		= 3,  
	P16_SEG22_SETTING		= 3,  
	P17_SEG23_SETTING		= 3,  
	P27_SEG24_SETTING		= 3,  
	P26_SEG25_SETTING		= 3,  
	P25_SEG26_SETTING		= 3,  
	P24_SEG27_SETTING		= 3,  
	P23_SEG28_SETTING		= 3,  
	P22_SEG29_SETTING		= 3,  
	P21_SEG30_SETTING		= 3,  
	P20_SEG31_SETTING		= 3,  
	P07_LCD_SEG32_SETTING		= 4,  
	P06_LCD_SEG33_SETTING		= 4,  
	P05_LCD_SEG34_SETTING		= 4,  
	P04_LCD_SEG35_SETTING		= 4,  
                        
	P70_TK0_SETTING				= 4,
	P67_TK1_SETTING				= 4,
	P66_TK2_SETTING				= 4,
	P37_TK3_SETTING				= 4,
	P36_TK4_SETTING				= 4,
	P33_TK5_SETTING				= 4,
	P32_TK6_SETTING				= 4,
	P47_TK7_SETTING				= 4,
	P46_TK8_SETTING				= 4,
	P45_TK9_SETTING				= 4,
	P44_TK10_SETTING			= 4,
	P43_TK11_SETTING			= 4,
	P42_TK12_SETTING			= 4,
	P41_TK13_SETTING			= 4,
	P40_TK14_SETTING			= 4,
	P34_TK15_SETTING			= 4,
	P35_TK16_SETTING			= 4,
	P56_TK17_SETTING			= 4,
	P50_TK18_SETTING			= 4,
	P51_TK19_SETTING			= 4,
	P52_TK20_SETTING			= 4,
	P53_TK21_SETTING			= 4,
	P54_TK22_SETTING			= 4,
	P55_TK23_SETTING			= 4,
                      
	P50_PWM0_SETTING			= 5,
	P51_PWM1_SETTING			= 5,
	P52_PWM2_SETTING			= 5,
	P53_PWM3_SETTING			= 5,
	P54_PWM4_SETTING			= 5,
	P55_PWM5_SETTING			= 5,
	P33_PWM6_SETTING			= 5,
	P32_PWM7_SETTING			= 5,
                        
	P40_ADC0_SETTING			= 3,
	P41_ADC1_SETTING			= 3,
	P42_ADC2_SETTING			= 3,
	P43_ADC3_SETTING			= 3,
	P44_ADC4_SETTING			= 3,
	P45_ADC5_SETTING			= 3,
	P46_ADC6_SETTING			= 3,
	P47_ADC7_SETTING			= 3,
	P32_ADC_VREF_SETTING		= 0,
                       
	P30_UART0_TX_SETTING		= 3,      
	P31_UART0_RX_SETTING		= 3,      
	P66_UART1_TX_SETTING		= 3,      
	P67_UART1_RX_SETTING		= 3,      
	P61_UART2_TX_SETTING		= 4,      
	P60_UART2_RX_SETTING		= 4,      
                       
	P36_I2C_SDA_SETTING		    = 3,      
	P37_I2C_SCL_SETTING		    = 3,      
                      
	P30_I2C_SDA_SETTING		    = 4,      
	P31_I2C_SCL_SETTING		    = 4,      
	P66_I2C_SDA_SETTING		    = 5,      
	P67_I2C_SCL_SETTING		    = 5,      
	P61_I2C_SDA_SETTING		    = 5,      
	P60_I2C_SCL_SETTING		    = 5,      
	
	P64_SPI_SCK_SETTING			= 4,      
	P62_SPI_MISO_SETTING		= 4,      
	P63_SPI_MOSI_SETTING		= 4,      
	P65_SPI_SSB_SETTING			= 4,      
	
	P34_OPAPS_SETTING		    = 5,
	P35_OPBPS_SETTING		    = 5,
	
	P17_OPAPS_SETTING		    = 4,
	P16_OPBPS_SETTING		    = 4,
	
	P20_CMP0P_SETTING		    = 4,
	P21_CMP0N_SETTING		    = 4,
	
	P22_CMP1P_SETTING		    = 4,
	P23_CMP1N_SETTING		    = 4,
	
	P24_CMP2P_SETTING		    = 4,
	P25_CMP2N_SETTING		    = 4,
	
	P26_CMP3P_SETTING		    = 4,
	P27_CMP3N_SETTING		    = 4,
	
                        
	P34_T0_SETTING			    = 1,        
	P35_T1_SETTING			    = 1,        
	P10_T2_SETTING			    = 1,        
                        
	P75_RESET_SETTING		    = 3,			  
	P57_CAP_SETTING			    = 4,        
	P72_XOSCL_IN_SETTING	    = 3,
	P71_XOSCL_OUT_SETTING	    = 3,  
	P74_XOSCH_IN_SETTING	    = 3,
	P73_XOSCH_OUT_SETTING	    = 3,  
	
	P73_ERC_SETTING		        = 3,      
	P12_T2CP_SETTING	        = 4,  
	P11_T2EX_SETTING		    = 1,  

	P70_SAMPLE_SETTING		    = 3,
	P56_FAULT_SETTING		    = 1,

	PU_EN			            = 0x80,
	PD_EN			            = 0x40,
	OP_EN				        = 0x20,
};	
#define  GPIO_Init(reg,val)	reg = val





#define BIT0         						0x01
#define BIT1         						0x02
#define BIT2         						0x04
#define BIT3         						0x08
#define BIT4         						0x10
#define BIT5         						0x20
#define BIT6         						0x40
#define BIT7         						0x80
#define BIT8         						0x100
#define BIT9         						0x200
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


#define DelayNop(a)             						\
    if ((a)&(0x01))    {__NOP1__;}                    \
    if ((a)&(0x02))    {__NOP2__;}                    \
    if ((a)&(0x04))    {__NOP4__;}                    \
    if ((a)&(0x08))    {__NOP8__;}                    \
    if ((a)&(0x10))    {__NOP16__;}                    \
    if ((a)&(0x20))    {__NOP32__;}                    \
    if ((a)&(0x40))    {__NOP64__;}                    \
    if ((a)&(0x80))    {__NOP128__;}          


//====================用户自定义区=============================//
typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;

typedef unsigned char uchar;
typedef unsigned int  uint;

#define     TRUE	   1
#define	    FALSE	   0
    
#define		ENABLE		1
#define		DISABLE		0

#define		High		1
#define		Low		    0    

#endif  
