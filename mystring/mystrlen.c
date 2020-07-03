#include <stdio.h>
#include "myprogam.h"
// int mystrlen(char a[]);
// int main (void)
// {
	
	// char a[20] = {"1"};
    // int i;
	// i = mystrlen(a);
	// printf("%d\n", i);
	// return 0;
// }

int mystrlen(char a[])
{
	int i = 0;
	char *p;
	p = a;
	
	// for(i=0;;i++)
	// {
		// if(*(p+i) == '\0')
			// break;
	// }
	while(*(p+i) != '\0')
		i++;
		
	return i;
	
	
}