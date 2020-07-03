#include <stdio.h>
#include "myprogam.h"

int main(void)
{

	// int ai;
	// int zi;
	// char a[20] = {"abssd123"};
	// char z[20] = {"abssd"};
	// char u[20] = {"1234567"};
	// char c[20] = {0};
	// char m[20] = {0};
	// ai = mystrlen(a);
	// zi = mystrlen(z);
	// printf("A的长度：%d,Z的长度：%d\n", ai, zi);

	// mystrcpy(a,c);
	// printf("把A:%s复制进C：%s\n", a, c);
	
	// mystrncpy(a,m,4);
	// printf("把A:%s的四个字符复制进m：%s\n", a, m);
	
	// mystrcat(a,z);
	// printf("把Z:%s的字符接到A后面：%s\n", z , a);
	// mystrncat(z,u,4);
	// printf("把u:%s的4个字符接到z后面：%s\n",u, z);
	char a[20] = {"abcder"};
	
	char b[20] = {"abcdr"};
    int ret;
	ret = mystrcmp(a,b);
	if(ret == 0)
	{
		printf("字符串A:%s,与字符串B：%s不相同\n", a, b);
	}
	else
		printf("字符串A:%s,与字符串B：%s相同\n", a, b);
	
	ret = mystrcnmp(a,b,4);
	if(ret == 0)
		{
		printf("字符串A:%s,与字符串B：%s的前4位不相同\n", a, b);
		}
	else
		printf("字符串A:%s,与字符串B：%s前4位相同\n", a, b);
	
	return 0;
}