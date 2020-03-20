#include "key.h"

sbit S7 = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;

void key_scan(){
	if(S7 == 0){
	 	if(S7 == 0){
			if(clock_flag==1)
				clock_flag=0;		
			station_adj++;
			if(dsp_flag!=1){
				dsp_flag = 1;
				station_adj=0;
			}
			if(station_adj==4){
			 	station_adj = 0;	
			}
			while(!S7);
			if(station_adj!=0){
			 	ds1302_enable = 0;
			}else{
		 	 	Write_Ds1302_Byte(0x8e,0x00);
			 	Write_Ds1302_Byte(0x84,BCD_DEC(1,h));
			 	Write_Ds1302_Byte(0x82,BCD_DEC(1,m));
			 	Write_Ds1302_Byte(0x80,BCD_DEC(1,s));
			 	Write_Ds1302_Byte(0x8e,0x80);
				ds1302_enable = 1;
			}
		}
	}

 	if(S6==0){
	 	if(S6==0){
			if(clock_flag==1)
				clock_flag=0;	
			station_adj++;
			if(dsp_flag!=2){
				dsp_flag = 2;
				station_adj=0;
			}
			if(station_adj==4){
			 	station_adj = 0;	
			}
			while(!S6);
		}
	}

	if(S5==0){
	 	if(S5==0){
			if(clock_flag==1)
				clock_flag=0;
			if(dsp_flag==1){
			 	if(station_adj==1){
				 	h++;
					if(h==24){
					 	h = 0;
					}
				}else if(station_adj==2){
				 	m++;
					if(m==60){
					 	m = 0;
					}
				}else if(station_adj==3){
				 	s++;
					if(s==60)
						s = 0;
				}
				while(!S5);
			}else if(dsp_flag==2){
			 	if(station_adj==1){
				 	ch++;
					if(ch==24){
					 	ch = 0;
					}
				}else if(station_adj==2){
				 	cm++;
					if(cm==60){
					 	cm = 0;
					}
				}else if(station_adj==3){
				 	cs++;
					if(cs==60)
						cs = 0;
				}
				while(!S5);
			}
		}
	}

	if(S4==0){
	 	if(S4==0){
			if(dsp_flag==1&&station_adj==0){
			 	dsp_flag = 3;

			}


			if(clock_flag==1)
				clock_flag=0;
			if(dsp_flag==1){
			 	if(station_adj==1){
				 	h--;
					if(h<0)
						h = 23;
				}else if(station_adj==2){
				 	m--;
					if(m<0)
						m = 59;
				}else if(station_adj==3){
				 	s--;
					if(s<0)
						s = 59;
				}
			
				
			}else if(dsp_flag==2){
				 if(station_adj==1){
				 	ch--;
					if(ch<0)
						ch = 23;
				}else if(station_adj==2){
				 	cm--;
					if(cm<0)
						cm = 59;
				}else if(station_adj==3){
				 	cs--;
					if(cs<0)
						cs = 59;
				}
			
	
			}	
			while(!S4);
			if(dsp_flag == 3){
			   dsp_flag = 1;
			}			
		}	
	}
}