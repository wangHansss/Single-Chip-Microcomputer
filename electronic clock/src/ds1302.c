#include "ds1302.h"

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;   // DS1302¸´Î»												

u8 BCD_DEC(bit flag, u8 dat){
	u8 a,b,i;
	if(flag){
		a = dat/10;
		b = dat%10;
		i = (a<<4)|b;
	}else{
		a = dat/16;
		b = dat%16;
		i = a*10+b;
	}	
	return i;
}

void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

void ds1302_init(){
 	Write_Ds1302_Byte(0x8e,0x00);
 	Write_Ds1302_Byte(0x84,0x23);
 	Write_Ds1302_Byte(0x82,0x59);
 	Write_Ds1302_Byte(0x80,0x55);
 	Write_Ds1302_Byte(0x8e,0x80);
}
