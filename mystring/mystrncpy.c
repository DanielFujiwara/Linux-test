#include <stdio.h>
#include "myprogam.h"
// char mystrncpy(char a[],char b[],int i);
// int main (void)
// {
	
	// char a[20] = {"abcder"};
	
	// char b[20] = {0};
    // int i;
	// b[20] = mystrncpy(a,b,4);
	// printf("%s\n", b);
	// return 0;
// }
/*复制指定长度的a到b*/
char mystrncpy(char a[],char b[],int i)
{
	int q = 0;
	char *p;
	p = a;
	int x = i;
	for(i;i>0;i--)
	{
		if(*(p+q) == '\0')
		{
			b[q] = *(p+q)	;
			break;
		}
		
		
		b[q] = *(p+q) ;
		q++;
		
	}
	b[x+1] = '\0';
	// printf("%s\n", b);
	
	
	return *b;
	
	
}