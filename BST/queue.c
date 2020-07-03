#include "queue.h"

/* ˳����г�ʼ�� */
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

/* �ж϶����Ƿ�Ϊ�� */
bool queue_full(struct queue *p)
{
	return p->front == (p->rear+1)%p->size;
}

/* ������� */
int in_queue(struct queue *p, struct node *data)
{
	if(queue_full(p))
		return -1;
	
	p->rear = (p->rear+1)%p->size;
	p->queue[p->rear] = data;
	return 0;
}

/* �ж϶����Ƿ�Ϊ�� */
bool queue_empty(struct queue *p)
{
	return p->front == p->rear;
}

/* ���ݳ��� */
int out_queue(struct queue *p, struct node **data)
{
	if(queue_empty(p))
		return -1;
	
	p->front = (p->front+1)%p->size;
	*data = p->queue[p->front];
	return 0;
}

