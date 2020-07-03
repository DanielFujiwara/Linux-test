#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 声明管理结构体 */
struct queue
{
	int size;
	int *queue;
	int front;  //队头偏移量
	int rear;   //队尾偏移量
};

/* 顺序队列初始化 */
struct queue *init_queue(int size)
{
	struct queue *p = malloc(sizeof(struct queue));
	if(p == NULL)
	{
		printf("malloc err!\n");
		return NULL;
	}
	
	p->size = size;
	p->queue = malloc(size*sizeof(int));
	if(p->queue == NULL)
	{
		printf("malloc err!\n");
		return NULL;
	}
	p->front = 0;
	p->rear = 0;
	return p;
}

/* 判断队列是否为满 */
bool queue_full(struct queue *p)
{
	return p->front == (p->rear+1)%p->size;
}

/* 数据入队 */
int in_queue(struct queue *p, int data)
{
	if(queue_full(p))
		return -1;
	
	p->rear = (p->rear+1)%p->size;
	p->queue[p->rear] = data;
	return 0;
}

/* 判断队列是否为空 */
bool queue_empty(struct queue *p)
{
	return p->front == p->rear;
}

/* 数据出队 */
int out_queue(struct queue *p, int *data)
{
	if(queue_empty(p))
	{
		printf("当前队列没人\n" );
		return -1;
	}
	
	p->front = (p->front+1)%p->size;
	*data = p->queue[p->front];
	return 0;
}


void* pret;

void cancelpo(void *arg)
{
	exit(1);
}

void *fun1(void *arg)//线程例程
{
	while(1)
	{	
		printf("输入当前入队的人员编号\n");
		int a;
		scanf("%d",&a);
		in_queue(arg,a);
		printf("编号%d已成功入队\n",a );
	}

	
}

int main(int argc, char const *argv[])
{
	

	

	struct queue *queue = init_queue(10);

	pthread_t tid;//线程id
	pthread_create(&tid,NULL,fun1,queue);//创建线程


	in_queue(queue, 1);
	in_queue(queue, 2);
	in_queue(queue, 3);

	int retque;
	int data;
	while(1)
	{
		sleep(3);
		retque = out_queue(queue, &data);
		if(retque == 0)
			printf("当前出队人员编号:%d\n", data);
		else
			printf("最后出队人员编号:%d\n", data);
	}








	return 0;
}