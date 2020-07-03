#include <stdio.h>
#include "myprogam.h"
// int mystrcnmp(char a[],char b[]);
// int main (void)
// {
	
	// char a[20] = {"abcder"};
	
	// char b[20] = {"abcder"};
    // int ret;
	// ret = mystrcnmp(a,b);
	// printf("%d\n", ret);
	
	// return 0;
// }
/*比较指定字符串是否相同(暂时不能比较不同空间大小的字符串*/
/*若相同则返回1，不同为0*/
int mystrcnmp(char a[],char b[],int e)
{
	int ret;
	int ai;
	int bi;
	char *p;
	char *q;
	p = a;
	q = b;
	int i = 0;
	
	// while(*(p+ai) != '\0')
		// ai++;
	
	// while(*(q+bi) != '\0')
		// bi++;
	// printf("%d,%d\n",ai,bi);
	// ai = mystrlen(a);
	// bi = mystrlen(b);
	// if(ai == bi)
	// {
		// ret = 1; 
		// printf("%d,%d\n",ai,bi);
		// ai = ai>bi ? ai:bi;
			
			for(e;e>0;e--)
			{
				if(*(p+i) - *(q+i) == 0)
				{
					i++;
					ret = 1;
					// printf("%d\n", ret);
				}
				else
				{
					ret = 0;
					break;
				}
				
			}
		
	// }
	// else
	// {
			// printf("%d,%d\n",ai,bi);
		// ret = 0;
	// }
	
	
	return ret;
}