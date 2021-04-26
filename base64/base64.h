#ifndef __BASE64_H__
#define __BASE64_H__


#include <stdio.h>
/*******************************************************************
 * 组件名称：base64
 * 组件说明：base64 编码
 *******************************************************************/


//encoding blob to base64 character array
//s    - input blob (byte array),
//slen - length of s,
//out  - output character array (without terminating character '\0'),
//       output length = int((slen+2)/3)*4,
//outlen - output array length,
//returns
//      the number of characters actually written to the output array
//      or -1 on error.
// int Base64Enc(const unsigned char *s,int slen,unsigned char *out,int outlen);
int Base64Enc(const unsigned char *src, int slen,unsigned char *dst, int dlen);


#endif