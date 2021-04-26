#include "base64.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rtthread.h>
#include <rtdevice.h>
// #include <finsh.h>

#include <drivers/audio.h>

#include <rtthread.h>
#include <sys/socket.h> /* 使用BSD socket，需要包含sockets.h头文件 */



/*******************************************************************
 * 函数名称：Base64Enc
 * 
 * 形式参数：
 * 			s-------------------------------------编码buf
 * 			slen----------------------------------buf长度
 * 			out-----------------------------------输出buf
 * 			outlen--------------------------------输出长度
 * 
 * 返回参数：
 * 
 * 函数说明：base64 编码
 *******************************************************************/



int Base64Enc(const unsigned char *s,int slen,unsigned char *out,int outlen)
{
	

	static unsigned char codesym[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	unsigned int c,count=slen/3;int len=(slen+2)/3*4;
	if(slen<=0 || outlen<=0 || outlen<len)return-1;	
	// if(slen<=0 || outlen<=0 )return-1;	
	while(count--)
	{
		c=*s++;c<<=8;c|=*s++;c<<=8;c|=*s++;					
		*out++=codesym[(c>>18)&0x3F];
		*out++=codesym[(c>>12)&0x3F];
		*out++=codesym[(c>>6)&0x3F];
		*out++=codesym[(c)&0x3F];
	}
	if(slen%3 == 2)
	{
		c=*s++;c<<=8;c|=*s++;c<<=8;
		*out++=codesym[(c>>18)&0x3F];
		*out++=codesym[(c>>12)&0x3F];
		*out++=codesym[(c>>6)&0x3F];
		*out='=';
	}
	else if(slen%3 == 1)
	{
		c=*s;c<<=16;
		*out++=codesym[(c>>18)&0x3F];
		*out++=codesym[(c>>12)&0x3F];
		*out++='=';
		*out='=';
	}
	return len;
}


