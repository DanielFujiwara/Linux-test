#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>


#include <sys/wait.h>
#include <sys/types.h>
#define MYFIFO1 "/tmp/myfifo1"
#define MYFIFO2 "/tmp/myfifo2"
void readmassage(int sig)
{
	// printf("收到信号 %d\n",sig );
	int ret;
	int fifo_fd2 = open(MYFIFO2, O_RDWR);
	if(fifo_fd2 < 0)
	{
		perror("open");
		return ;
	}	
	char massage[100];
	ret = read(fifo_fd2, massage, 10);
		if(ret == -1)
		{
			perror("read");
			return ;
		}
		close(fifo_fd2);
	printf("new massage:%s\n",massage );
	return;
}

void byebye(int sig)
{
	printf("对方已经下线，自动退出聊天。\n");
	exit(1);
}

int main(int argc, char const *argv[])
{
	
	int ret;
	/*判断文件是否存在*/
	if(access(MYFIFO1, F_OK))
	{

		/*创建有名管道*/
		ret = mkfifo(MYFIFO1,0777);
		if(ret == -1)
		{
			perror("mkfifo");
			
			return -1;
		}
	}

	/*判断文件是否存在*/
	if(access(MYFIFO2, F_OK))
	{

		/*创建有名管道*/
		ret = mkfifo(MYFIFO2,0777);
		if(ret == -1)
		{
			perror("mkfifo");
			
			return -1;
		}
	}
	/* 打开有名管道文件 */
	int fifo_fd1 = open(MYFIFO1, O_RDWR);
	if(fifo_fd1 < 0)
	{
		perror("open");
		return -1;
	}	

	int fifo_fd2 = open(MYFIFO2, O_RDWR);
	if(fifo_fd2 < 0)
	{
		perror("open");
		return -1;
	}	

	int pid1;
	pid1 = getpid();
	char mypid[10] = {0};
	sprintf(mypid,"%d",pid1);

	ret = write(fifo_fd1, mypid, 10);
		if(ret == -1)
		{
			perror("write");
			return -1;
		}
	printf("已经发送聊天请求，等待对方回应！\n");
	char tpid[10] = {10};
	ret = read(fifo_fd2, tpid, 10);
	if(ret == -1)
	{
		perror("read");
		return -1;
	}

	// printf("i am 1,2 pid: %s\n", tpid);	
	
	////对方id转换int/////
	int pidint;
	pidint = atoi(tpid);
	printf("对方ID已获取：%d\n", pidint);
	printf("连接成功！\n");


	//////通过管道获取对方pid建立连接//////
	signal(2,byebye);
	signal(10,readmassage);
	int k;
	char massage[100];
	
	while(1)
	{
		printf("1.send massage 2.bye\n");
		scanf("%d",&k);
		if(k == 2)
		{
			kill(pidint,2);
			printf("已断开连接\n");
			return 0;
		}
		else if(k == 1)
		{
			
			scanf("%s",massage);
			ret = write(fifo_fd1, massage, 10);
			if(ret == -1)
			{
				perror("write");
				return -1;
			}
			kill(pidint,10);
		}
		else
		{
			printf("input again\n");
		}
	}





	close(fifo_fd1);
	close(fifo_fd2);

	return 0;
}