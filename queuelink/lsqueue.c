#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ��������ṹ�� */
struct queue
{
	int size;
	int *queue;
	int front;  //��ͷƫ����
	int rear;   //��βƫ����
};

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

/* �ж϶����Ƿ�Ϊ�� */
bool queue_full(struct queue *p)
{
	return p->front == (p->rear+1)%p->size;
}

/* ������� */
int in_queue(struct queue *p, int data)
{
	// if(queue_full(p))
		// return -1;
	
	p->rear = (p->rear+1)%p->size;
	p->queue[p->rear] = data;
	printf("%d\n",p->rear);
	return 0;
}

/* �ж϶����Ƿ�Ϊ�� */
bool queue_empty(struct queue *p)
{
	return p->front == p->rear;
}

/* ���ݳ��� */
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