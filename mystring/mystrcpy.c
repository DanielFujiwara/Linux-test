#include <stdio.h>
#include "myprogam.h"
// char mystrcpy(char a[],char b[]);
// int main (void)
// {
	
	// char a[20] = {"abcd"};
	
	// char b[20] = {0};
    // int i;
	// b[20] = mystrcpy(a,b);
	// printf("%s\n", b);
	// return 0;
// }
/*把A复制到B里面*/
char mystrcpy(char a[],char b[])
{
	int i = 0;
	char *p;
	p = a;
	while(1)
	{
		if(*(p+i) == '\0')
		{
			b[i] = *(p+i);
			b[i+1] = '\0';
			break;
		}
		
		
		b[i] = *(p+i) ;
		i++;
		
	}
	// printf("%s\n", b);
	
	
	return *b;
	
	
}