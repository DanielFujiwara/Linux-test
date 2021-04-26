#include "wbtest.h"
#include "rtthread.h"

#include "debugtool.h"



/*AEC NAXCLOW*/
static void *NaxAecmInst;
AecmConfig Naxconfig = {0};
static int initflag = 0;
int AEC_INIT_NAX()
{
	if(initflag == 1)
		return 0;

	initflag = 1;
	int ret = 0;
	ret = WebRtcAecm_Create(&NaxAecmInst);
	if(ret != 0)
	{
		ret = __LINE__;
		goto aecerr;
	}
	ret = WebRtcAecm_Init(NaxAecmInst, 8000);
	if(ret != 0)
	{
		ret = __LINE__;
		goto aecerr;
	}
	Naxconfig.cngMode = AecmTrue;
	Naxconfig.echoMode = 4;
	ret = WebRtcAecm_set_config(NaxAecmInst,Naxconfig);
	if(ret != 0)
	{
		ret = __LINE__;
		goto aecerr;
	}
	
	LOG_DEBUG("AEC init\n");
	return 0;


aecerr:
	ERR_DEBUG("webrtc AEC init err %d\n",ret);
	return -1;

}

int pcm_webrtc_aecm(void *spk,void *mic,void *desk,int size)
{
	int ret = 0;

	ret = WebRtcAecm_BufferFarend(NaxAecmInst, spk, size/2);
	if(ret != 0)
	{
		ret = __LINE__;
		goto aecbuferr;
	}

	ret = WebRtcAecm_Process(NaxAecmInst, mic, mic, desk, size/2, 21);
	if(ret != 0)
	{
		ret = __LINE__;
		goto aecbuferr;
	}
	return 0;
aecbuferr:
ERR_DEBUG("aecm err %d last err %d\n",ret);
	return -1;

} 


