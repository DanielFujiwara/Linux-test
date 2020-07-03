// #include <stdio.h>
// #include "myprogam.h"
// char *mystrstr(char a[],char b[]);
// int main (void)
// {
	// char *ret;
	// char a[20] = {"abcder"};
	
	// char b[4] = {"cde"};
    // ret = mystrstr(a,b);
	// printf("%s\n", ret);
	
	// return 0;
// }
// /*查找字符串中的子串，返回子串首元素指针*/
// char *mystrstr(char a[],char b[])
// {
	// char *ret;
	// char *p;
	// char *q;
	// int ai;
	// int bi;
	// p = a;
	// q = b;
	
	// while(*(p+ai) != '\0')
		// ai++;
	
	// while(*(q+bi) != '\0')
		// bi++;
	
	// int i;
	// int x=0;
	// int y=0;
	// for(i=ai;i>0;i--)
	// {
		// if(*(q) == *(p+x))
		// {
			// for(y=bi;y>0;y--)
			// {
				// if(*(q+x+y) == *(p+x+y))
					// {	
						// y++;
						// ret = p+x+y;
					// }
						// else
					// {
						// break;
						// ret = NULL;
					// }
			// }
			
			
			
			
			
		// }
		
	// }
	
	
	
	// return ret;
// }