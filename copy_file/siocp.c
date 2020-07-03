#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	int fd_a = open("apple",O_RDONLY,0777);//打开aplle
	if(fd_a == -1)
	{
		perror("open");
		printf("file apple erro\n");
		return -1;
	}

	char ctl;
	int fd_b = open("cherry",O_RDWR,0777); //新建一个 cp.txt被复制的文件
	if(fd_b != -1)
	{
		while(1)
		{
			printf("cherry文件已经存在，是否覆盖？ y/n\n");
			scanf("%c",&ctl);
			if(ctl == 'n')
				return 0;
			else if(ctl == 'y')
			{
				printf("开始复制文件\n");
				break;
			}
			else
			{
				printf("指令错误，请重新输入\n");
				while(getchar() != '\n');
			}
		}

	}


	fd_b = open("cherry",O_RDWR|O_CREAT,0777);
	if(fd_b == -1)
	{
		perror("open");
		printf("file cherry erro\n");
		return -1;
	}

	char buf[1024] = {0};
	int ret;
	int retw;
	while(1)
	{
		ret = read(fd_a,buf,sizeof(buf));
		if(ret == -1)
		{
			printf("读取失败！\n");
			return -1;
		}

		if(ret == 0)
			break;
		retw = write(fd_b,buf,ret);
		if(retw == -1)
		{
			printf("写入失败！\n");
			return -1;
		}

	}

	printf("写入完成！\n");


	close(fd_b);
	close(fd_a);





	return 0;
}