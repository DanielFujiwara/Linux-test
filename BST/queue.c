#include "queue.h"

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
	p->queue = malloc(size*sizeof(struct node *));
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
int in_queue(struct queue *p, struct node *data)
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
int out_queue(struct queue *p, struct node **data)
{
	if(queue_empty(p))
		return -1;
	
	p->front = (p->front+1)%p->size;
	*data = p->queue[p->front];
	return 0;
}

