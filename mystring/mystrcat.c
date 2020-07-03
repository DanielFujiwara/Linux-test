#include <stdio.h>
#include "myprogam.h"
// char mystrcat(char a[],char b[]);
// int main (void)
// {
	
	// char a[20] = {"abcder"};
	
	// char b[20] = {"123"};
    // int i;
	// mystrcat(a,b);
	
	// printf("%s\n", a);
	// return 0;
// }
/*把B接到A后面*/
char mystrcat(char a[],char b[])
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
	while(1)
	{
		if(b[x] == '\0')
			
		break;
		
		
			a[i+x] = b[x];
			x++;
	}
	a[i+x] = '\0';
	return *a;
	
	
}