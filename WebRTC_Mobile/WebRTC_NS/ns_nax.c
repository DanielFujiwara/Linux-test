#include "ns_nax.h"
#include <stdio.h>
// #include "noise_suppression.h"
#include "rtthread.h"

#include "noise_suppression_x.h"
#include "debugtool.h"
static void *NaxNsInst;
static int nsinitflag = 0;

void nax_webrtc_ns_init()
{

    if(nsinitflag == 1)
        return 0;
    nsinitflag = 1;
    int ret = 0;

	ret = WebRtcNsx_Create(&NaxNsInst);
	if(ret != 0)
	{
		ret = __LINE__;
		goto nserr;
	}
    ret = WebRtcNsx_Init(NaxNsInst, 16000);
	if(ret != 0)
	{
		ret = __LINE__;
		goto nserr;
	}
    ret = WebRtcNsx_set_policy(NaxNsInst, 3);
	if(ret != 0)
	{
		ret = __LINE__;
		goto nserr;
	}

    LOG_DEBUG("WebRtc Ns init\n");

    return 0;


nserr:
ERR_DEBUG("WebRtc Ns err %d\n",ret);
	return -1;

}

int pcm_webrtc_ns(void* inbuf,void* outbuf)
{
    char nsbuf[2028] = {0};

    int ret = WebRtcNsx_Process(NaxNsInst,inbuf,NULL,outbuf,nsbuf);
	if(ret != 0)
    {
        ERR_DEBUG("webrtc run err\n");
    }	
    return ret;
}

// void aec_config()
// {
// 	static int a = 0;
// 	int ret = WebRtcNsx_set_policy(NaxNsInst, a);
// 	LOG_DEBUG("ret %d,mode %d\n",ret,a);
// 	if(a == 4)
// 	{
// 		a = 0;
// 	}
// 	else
// 	{
// 		a++;
// 	}
// }
// MSH_CMD_EXPORT(aec_config , aec_config);