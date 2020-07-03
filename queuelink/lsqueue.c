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
	// if(queue_full(p))
		// return -1;
	
	p->rear = (p->rear+1)%p->size;
	p->queue[p->rear] = data;
	printf("%d\n",p->rear);
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
		return -1;
	
	p->front = (p->front+1)%p->size;
	*data = p->queue[p->front];
	return 0;
}

int main(void)
{
	struct queue *queue = init_queue(10);
	
	int num = 0;
	
	while(1)
	{
		printf("input a num:");
		scanf("%d", &num);
		
		if(num == 0)
			break;
		
		else if(num>0)
			in_queue(queue, num);
		else
		{
			num = -num;
			while(num--)
			{
				int data;
				if(!out_queue(queue, &data))
					printf("data:%d\n", data);
				else
					printf("queue is empty\n");
			}
			
		}
	}
	
	return 0;
}