#include "smg.h"

u8 code seg_code[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff,0xc6};
	
void dsp_single(u8 we, u8 du){
	P2 = (P2&0x1f)|0xe0;
	P0 = 0Xff;
	P2 = P2&0X1F;

 	P2 = (0X1F&P2)|0Xc0;
	P0 = 0x01<<we;
	P2 &= 0X1F;

	P2 = (0X1F&P2)|0Xe0;
	P0 = seg_code[du];
	P2 &= 0X1F;
}

void time_dsp(){
	static u8 i;
	u8 temp[8] = 0;
	if(station_adj == 0){
		temp[0] = h/10;
		temp[1] = h%10;
		temp[2] = 10;
		temp[3] = m/10;
		temp[4] = m%10;
		temp[5] = 10;
		temp[6] = s/10;
		temp[7] = s%10;
	}
	else if(station_adj==1){
		if(blink_flag){
			temp[0] = h/10;
			temp[1] = h%10;
		}else{
			temp[0] = 11;
			temp[1] = 11;		 	
		}
		temp[2] = 10;
		temp[3] = m/10;
		temp[4] = m%10;
		temp[5] = 10;
		temp[6] = s/10;
		temp[7] = s%10;			 	
	}
	else if(station_adj==2){
		temp[0] = h/10;
		temp[1] = h%10;
		temp[2] = 10;
		if(blink_flag){
			temp[3] = m/10;
			temp[4] = m%10;
		}else{
			temp[3] = 11;
			temp[4] = 11;
		}
		temp[5] = 10;
		temp[6] = s/10;
		temp[7] = s%10;			 	
	}
	else if(station_adj==3){
		temp[0] = h/10;
		temp[1] = h%10;
		temp[2] = 10;
		temp[3] = m/10;
		temp[4] = m%10;
		temp[5] = 10;
		if(blink_flag){
			temp[6] = s/10;
			temp[7] = s%10;
		}else{
			temp[6] = 11;
			temp[7] = 11;		
		}			 	
	}
	dsp_single(i, temp[i]);
	i>=7?i=0:i++;
}


void time_dsp1(){
	static u8 i;
	u8 temp[8] = 0;
	if(station_adj == 0){
		temp[0] = ch/10;
		temp[1] = ch%10;
		temp[2] = 10;
		temp[3] = cm/10;
		temp[4] = cm%10;
		temp[5] = 10;
		temp[6] = cs/10;
		temp[7] = cs%10;
	}
	else if(station_adj==1){
		if(blink_flag){
			temp[0] = ch/10;
			temp[1] = ch%10;
		}else{
			temp[0] = 11;
			temp[1] = 11;		 	
		}
		temp[2] = 10;
		temp[3] = cm/10;
		temp[4] = cm%10;
		temp[5] = 10;
		temp[6] = cs/10;
		temp[7] = cs%10;			 	
	}
	else if(station_adj==2){
		temp[0] = ch/10;
		temp[1] = ch%10;
		temp[2] = 10;
		if(blink_flag){
			temp[3] = cm/10;
			temp[4] = cm%10;
		}else{
			temp[3] = 11;
			temp[4] = 11;
		}
		temp[5] = 10;
		temp[6] = cs/10;
		temp[7] = cs%10;			 	
	}
	else if(station_adj==3){
		temp[0] = ch/10;
		temp[1] = ch%10;
		temp[2] = 10;
		temp[3] = cm/10;
		temp[4] = cm%10;
		temp[5] = 10;
		if(blink_flag){
			temp[6] = cs/10;
			temp[7] = cs%10;
		}else{
			temp[6] = 11;
			temp[7] = 11;		
		}			 	
	}
	dsp_single(i, temp[i]);
	i>=7?i=0:i++;
}

void dsp_smg3(){
	static u8 i;
	u8 temp[8] = 0;

	temp[0] = 11;
	temp[1] = 11;
	temp[2] = 11;
	temp[3] = 11;
	temp[4] = 11;
	temp[5] = 2;
	temp[6] = 1;
	temp[7] = 12;		//c


	dsp_single(i, temp[i]);
	i>=7?i=0:i++;
}
