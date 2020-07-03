#include <stdio.h>
#include "myprogam.h"
// char mystrncat(char a[],char b[]);
// int main (void)
// {
	
	// char a[20] = {"abcder"};
	
	// char b[20] = {"123"};
    // int i;
	// mystrncat(a,b);
	
	// printf("%s\n", a);
	// return 0;
// }
/*把指定长度B接到A后面*/
char mystrncat(char a[],char b[],int y)
{
	int i = 0;
	while(1)
	{
		if(a[i] == '\0')
			break;
		
		i++;
	}
	char *p;
	char *q;
	p = a;
	q = b;
	int x = 0;
	for(y;y>0;y--)
	{
		if(b[x] == '\0')
			
		break;
		
		
			a[i+x] = b[x];
			x++;
	}
	a[i+x] = '\0';
	return *a;
	
	
}