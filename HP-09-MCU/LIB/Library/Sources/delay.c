#include "delay.h"

void Delay_50us(unsigned int n)	   
{
	unsigned char i;
	while(n--)
	{
		for(i=0;i<68;i++);
	}
}

void Delay_ms(unsigned char n)
{
	while(n--)
	{
		Delay_50us(20);
	}
}
