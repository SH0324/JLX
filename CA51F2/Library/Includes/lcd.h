#ifndef LCD_H
#define LCD_H

#include "ca51f_config.h"

//LXCON����
#define LEN(N)		(N<<5) 	//N=0~6
#define LMOD(N)		(N<<4)	//N=0~1


//LXCFG����
#define DMOD(N)		(N<<6)
#define BIAS(N)		(N<<4)

#define LDRV(N)		(N) //N=0-7

#define COMHV(N)	(N<<5)	//N=0~1
#define SEGHV(N)	(N<<4)	//N=0~1
#define BLNK(N)		(N<<3)	//N=0~1

typedef enum {
    LEN_DISABLE	= 0,
    LEN_IRCL  	= 1,
    LEN_IRCH  	= 2,
    LEN_XOSCL  	= 3,
    LEN_ERC     = 4,
    LEN_PLL     = 5,
    LEN_TF      = 6,
} LEN_TypeDef;

typedef enum {
    LMOD_lcd	= 0,
    LMOD_led  = 1,
} LMOD_TypeDef;

typedef enum {
    DMOD_5ua		= 0,
    DMOD_40ua  	= 1,
	DMOD_80ua 	= 2,
	DMOD_130ua 	= 3,
} DMOD_TypeDef;

typedef enum {
  BIAS_1_4		= 0,
  BIAS_1_2  	= 1,
  BIAS_1_3 	    = 2,
} BIAS_TypeDef;

typedef enum {
	COM_L  		= 0,
  	COM_H		= 1,
} COMHV_TypeDef;

typedef enum {
	SEG_L  		= 0,
  	SEG_H		= 1,
} SEGHV_TypeDef;

typedef enum {
    LDRV_0		= 0,
    LDRV_1		= 1,
	LDRV_2		= 2,
	LDRV_3		= 3,
	LDRV_4		= 4,
	LDRV_5		= 5,
	LDRV_6		= 6,
	LDRV_7		= 7,
} LDRV_TypeDef;

void LCD_init(LEN_TypeDef len,DMOD_TypeDef dmod,BIAS_TypeDef bias,LDRV_TypeDef ldrv,unsigned int lxdiv);
void SEG_init(LEN_TypeDef len,COMHV_TypeDef comhv,SEGHV_TypeDef seghv,LDRV_TypeDef ldrv,unsigned int lxdiv);
void LCD_WriteLram(unsigned char laddr, unsigned char ldata);
unsigned char LCD_ReadLram(unsigned char laddr);

#endif