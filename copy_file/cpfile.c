#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define M 2048

int main(int argc, char const *argv[]) //argv获取要复制的文件名字
{

	char name[100] = {0};
	char namecp[100] = {0};

	strcat(name,argv[1]);
	strcat(namecp,argv[1]);
	strcat(namecp,"cp");
	strcat(namecp,argv[2]);

	strcat(name,argv[2]);

	FILE *p1 = fopen(name,"r+"); //打开要复制的文件
	if( p1 == NULL)
	{
		perror("fopen");
		return -1;
	}
	
	FILE *p2 = fopen(namecp,"a+"); //新建一个 cp.txt被复制的文件
	if(p2 == NULL)
	{
		perror("fopen");
		return -1;
	}

	struct stat info;
	int rets = stat(name,&info);
	if(rets != 0)
	{
		perror("stat");
		return -1;
	}
	long int size = info.st_size;
	printf("%ld\n", info.st_size);

	long double p;

	char buf[M] = {0};
	int ret;
	int retw;
	long int i = 0;
	int j;
	while(1)
	{
		j = ftell(p1);
		p = j/size;
		printf("%LF\n",p );	




		ret = fread(buf,1024,2,p1);
		if(ret < 2)  //最后写入
		{
			p = j/size;
			j = ftell(p1) - j;
			retw = fwrite(buf,1,j,p2);
			printf("%d\n",j );		
				
			perror("fwrite");
			return 0;
		}


		retw = fwrite(buf,1024,ret,p2);
		if(retw == -1)
		{
			perror("fwrite");
			return -1;
		}
		
		

	}



	fclose(p1);
	fclose(p2);


	



	return 0;
}

