#include "main.h"

bit blink_flag = 0;
bit ds1302_flag = 0;
int h=23,m=59,s=55;
int ch=0,cm=0,cs=0;
u8 station_adj = 0;
u8 dsp_flag	= 1;
bit ds1302_enable = 1;
bit clock_flag = 0;
bit led_flag = 0;
u8 led_end_temp=0;
bit ds18b20_flag = 0;
void system_init(){
	 P2 = (P2&0X1F)|0XA0;
	 P0 = 0X00;
	 P2 &= 0X1F;

	 P2 = (P2&0X1F)|0X80;
	 P0 = 0XFF;
	 P2 &= 0X1F;
}	

void Timer0Init(void)		//2毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x9A;		//设置定时初值
	TH0 = 0xA9;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA = 1;
}

void main(){
	u8 tem;
 	system_init();
	Timer0Init();
	ds1302_init();
	while(1){
		key_scan();
	 	if(ds1302_flag){
		 	ds1302_flag = 0;
			h = BCD_DEC(0,Read_Ds1302_Byte(0x85));
			m = BCD_DEC(0,Read_Ds1302_Byte(0x83));
			s = BCD_DEC(0,Read_Ds1302_Byte(0x81));
		}
		if(ds18b20_flag){
	//		tem = read_tem();		
		}
		judge_clock();
	}
}

void servic0() interrupt 1{
	static u8 ds1302_flag_temp = 0;
	static u16 blink_flag_temp = 0;
	static u8 led_blink_temp = 0;
	static u8 ds18b20_flag_temp = 0;
	TL0 = 0x9A;		//设置定时初值
	TH0 = 0xA9;		//设置定时初值

	if(++led_blink_temp==100&&clock_flag==1){
	 	led_flag=!led_flag;
		led_blink_temp = 0;
 		//0.2s 1次		 
		
 	   if(led_flag){
			P2 = (P2&0X1F)|0X80;
			P0 = 0Xfe;
			P2 &= 0X1F;
	   }
	   if(!led_flag){
			P2 = (P2&0X1F)|0X80;
			P0 = 0Xff;
			P2 &= 0X1F;	   
	   }
		if(++led_end_temp >= 25){
		 	 clock_flag = 0;
			 led_end_temp = 0;
 			P2 = (P2&0X1F)|0X80;
			P0 = 0Xff;
			P2 &= 0X1F;	
		}	
	}

	if(++ds1302_flag_temp>=100&&ds1302_enable){
	 	ds1302_flag = 1;
		ds1302_flag_temp = 0;
	}
	if(++blink_flag_temp>=500){	 	//1秒
	 	blink_flag=!blink_flag;
		blink_flag_temp = 0;
	}
	if(++ds18b20_flag_temp>=200){	 	//1秒
	 	ds18b20_flag=1;
		ds18b20_flag_temp = 0;
	}

	if(dsp_flag==1)	
		time_dsp();
	else if(dsp_flag==2)
		time_dsp1();
	else if(dsp_flag==3)
		dsp_smg3();	 	
}

void judge_clock(){
	if(h==ch&&s==cs&&m==cm){
	   clock_flag = 1;
	}
}