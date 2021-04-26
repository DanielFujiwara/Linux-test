#ifndef __WBRTC_H__
#define __WBRTC_H__


#include <stdio.h>
#include "echo_control_mobile.h"
int wbtest_entry();
int AEC_INIT_NAX();
int pcm_webrtc_aecm(void *spk,void *mic,void *desk,int size);


#endif