#include "agc_nax.h"
#include <stdio.h>
#include "gain_control.h"


static void *NaxAgcInst;

static int agcinitflag = 0;

void nax_webrtc_agc_init()
{

    if(agcinitflag == 1)
        return 0;
    agcinitflag = 1;
    int ret = 0;

	ret = WebRtcAgc_Create(&NaxAgcInst);
	if(ret != 0)
	{
		ret = __LINE__;
		goto agcerr;
	}
    ret = WebRtcAgc_Init(NaxAgcInst,0,255,3,8000);
	if(ret != 0)
	{
		ret = __LINE__;
		goto agcerr;
	}

	WebRtcAgc_config_t agcConfig;
	agcConfig.compressionGaindB = 20;//在Fixed模式下，越大声音越大
    agcConfig.limiterEnable = 1;
    agcConfig.targetLevelDbfs = 3;   //dbfs表示相对于full scale的下降值，0表示full scale，越小声音越大
    ret = WebRtcAgc_set_config(NaxAgcInst, agcConfig);
	if(ret != 0)
	{
		ret = __LINE__;
		goto agcerr;
	}

    rt_kprintf("WebRtc agc init\n");

    return 0;


agcerr:
rt_kprintf("WebRtc agc err %d\n",ret);
	return -1;

}


int pcm_webrtc_agc(void *mic,void*out)
{
	char bufagch[640] = {0};
	uint8_t saturationWarning;
		rt_kprintf("agc %d\n",__LINE__);

	int ret = WebRtcAgc_Process(NaxAgcInst,mic,NULL,160,out,bufagch,0,0,0,&saturationWarning);
	if(ret != 0)
	{
		rt_kprintf("agc rtt %s\n",saturationWarning);
		
	}
	return ret;
}
