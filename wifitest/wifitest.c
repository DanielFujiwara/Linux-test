#include "wifitest.h"

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <stdio.h>
#include "player.h"
#include "ringtips.h"
#include "board.h"
#include "audio_device.h"
#include <webclient.h>  /* 使用 HTTP 协议与服务器通信需要包含此头文件 */
#include <sys/socket.h> 
#include <netdb.h>
// #include "lwip/sockets.h"
#include <drivers/audio.h>
// #include "pcmdata.h"
#include "timertools.h"
#include "ring_buffer.h"
#include <drivers/audio.h>
#include "httppost.h"
#include "camera_shot.h"
#include "adcprj.h"
#include "btnisr.h"
// #include "tcptalk.h"
#include "cjsonapi.h"
#include "debugtool.h"

void start_wifi_test()
{
    int waitingwifitimeout = 0;
    while (1)
    {
        if(wifi_connect_detect() != 0)
            {
                waitingwifitimeout = 0;
                break;
            }
        rt_thread_mdelay(500);
        LOG_DEBUG("waiting wifi connect\n");
        if(waitingwifitimeout++ >30)
            return;

    }
    int ret = 0;
    int qc_sock;
    /*创建sock*/
    qc_sock = socket(AF_INET,SOCK_DGRAM,0);
    if(qc_sock < 0)
        goto errsock;
    int set  = 1;
    /*sock 配置*/
    setsockopt(qc_sock,SOL_SOCKET,SO_BROADCAST,&set,sizeof(int));
    /*add 配置*/
	struct sockaddr_in recvAddr;
	memset(&recvAddr, 0, sizeof(struct sockaddr_in));
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_port = htons(4001);
    recvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// recvAddr.sin_addr.s_addr = "192.168.8.168";
        // recvAddr.sin_addr.s_addr = inet_addr("255.255.255.255");

    /*绑定*/
    ret = bind(qc_sock,(struct sockaddr *)&recvAddr, sizeof(struct sockaddr));
    if(ret < 0)
        goto errsock;
    int rcvlenth = 0;
    char rcvbuf[128] = {0};
    int addrlen = sizeof(struct  sockaddr_in);
    NEEDDED_DEBUG("rcving\n");
    int comget = 0;
    int valb = 0;
    char ipbuf[20] = {0};
    char batterybuf[10]  = {0};
    // adcprj_get_battery
    while (1)
    {
        /* code */
        rcvlenth = recvfrom(qc_sock,rcvbuf,sizeof(rcvbuf)-1,0,(struct sockaddr *)&recvAddr, &addrlen);
        if(rcvlenth > 0 )
        {
                 int ret = cjson_api_for_qc(rcvbuf,ipbuf,&comget,&valb);
                if(ret == 1)
                {
                NEEDDED_DEBUG("rcving %s",rcvbuf);
                NEEDDED_DEBUG("ip %s",ipbuf);
                NEEDDED_DEBUG("com %d",comget);
                UDP_Send(ipbuf,comget);
                close(qc_sock);

                return;

                }
                else{

                memset(ipbuf,0,20);
                comget = 0;
                valb = 0;
                // NEEDDED_DEBUG("rcving %s",rcvbuf);
                memset(rcvbuf,0,128);
                continue;    
                }

        }
        else
        {
            close(qc_sock);
            ERR_DEBUG("sock err \n");
            return;
        }
        

    }
    

errsock:
    ERR_DEBUG("sock err \n");

    return;



}
char bufsend[2048] = "wqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgowehwqoewhgoabngasdhgopaewhgoweh";
void UDP_Send(char *ip,int com)
{

    int fd = socket(AF_INET , SOCK_DGRAM , 0);
    if(fd == -1)
    {
        ERR_DEBUG("CREATE SOCKET  DEVICE FAILED \r\n");
        return;
    }
    int ret = 0;
    struct sockaddr_in inaddr;
    inaddr.sin_addr.s_addr = inet_addr(ip);
    inaddr.sin_port = htons(com);
    inaddr.sin_family = AF_INET;
    while (1)
    {
        /* code */
        ret = sendto(fd , bufsend ,1024 , 0 , (struct sockaddr*)&inaddr , sizeof(inaddr));
        rt_thread_mdelay(2);
        // ret = rt_tick_get();
 
        


        
        

        
        
    }
    

}
MSH_CMD_EXPORT(start_wifi_test,start_wifi_test);
