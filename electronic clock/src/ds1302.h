#ifndef __DS1302_H
#define __DS1302_H

#include "common.h"

void Write_Ds1302(unsigned char temp);
void Write_Ds1302_Byte( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302_Byte( unsigned char address );
u8 BCD_DEC(bit, u8);
void ds1302_init();


#endif
