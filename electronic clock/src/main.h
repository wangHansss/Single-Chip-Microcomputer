#ifndef _MAIN_H_
#define _MAIN_H_

#include "common.h"
#include "key.h"
#include "smg.h"
#include "ds1302.h"
#include "onewire.h"

extern int h,m,s;
extern bit blink_flag;
extern u8 station_adj;
extern u8 dsp_flag;
extern bit ds1302_enable;
extern bit clock_flag;
extern int ch,cm,cs;
void judge_clock();
#endif
