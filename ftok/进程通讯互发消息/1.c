#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#define SPACE 0
#define DATA  1
union semun
{
	int val;
};

void initsem(int sem_id,int sems,int val)
{
	union semun arg;
	arg.val = val;			//代表有空间
	semctl(sem_id, sems, SETVAL, arg);
}

void sempnv(int sem_id, int sems,short opt,short flag)
{
	struct sembuf op[1];
		op[0].sem_num = sems;			//代表操作信号量中的第2个元素
		op[0].sem_op = opt;			//代表进行Pv操作
		op[0].sem_flg = flag;			//默认
		semop(sem_id, op, 1);
}


int main(int argc, char const *argv[])
{
	/* 获取键值 */
	key_t key = ftok(".", 2);
	printf("key:%d\n", key);
	
	/* 创建一个共享内存 */
	int shm_id = shmget(key, 1024, IPC_CREAT|0666);
	if(shm_id == -1)
	{
		perror("msgget");
		return -1;
	}
	
	/* 将共享内存映射到进程的虚拟空间中 */
	char *addr = shmat(shm_id, NULL, 0);
	bzero(addr, 1024);
	char arr[5] = {"12345"};

	/* 创建一个信号量 */
	int sem_id = semget(key, 2, IPC_CREAT|0666);
	if(sem_id == -1)
	{
		perror("semget");
		return -1;
	}

	/*初始化信号量*/
	initsem(sem_id,SPACE,1);
	initsem(sem_id,DATA,0);
	char mass[100];
	char i = 0;
	while(1)
	{
		sempnv(sem_id,SPACE,-1,0); //p

		printf("输入发送消息\n");
		scanf("%s",mass);
		strcpy(addr,mass);

		sempnv(sem_id,DATA,1,0);//v

		sempnv(sem_id,DATA,-1,0);//p	
		printf("new msg from 2:%s\n", addr);	
		sempnv(sem_id,SPACE,1,0);//v



	}


	shmdt(addr);
	sleep(5);





	return 0;
}