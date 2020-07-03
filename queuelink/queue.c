#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/////////////////////˳�����
/*����ṹ��*/
struct queue
{
	int size;
	int *queue;
	int front;  //��ͷ�����������
	int rear;   //��β������д�룩
	
};
/*��ʼ���ṹ�����*/
struct queue *init_queue(int size)
{
	struct queue*p = malloc(sizeof(struct queue));
	if(p == NULL)
	{
		printf("����ṹ�崴��ʧ��\n");
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
/*����Ƿ���*/
bool check_full(struct queue*p)
{
	return p->front == (p->rear+1)%(p->size);
	
}
/*����Ƿ�Ϊ��*/
bool check_empty(struct queue*p)
{
	return p->front == p->rear;
	
}
/*����д�����*/
int write_in(struct queue *p,int data)
{

	if(check_full(p))
		return -1;

	p->rear = (p->rear+1)%(p->size);
	
	p->queue[p->rear] = data;
	
	printf("%d\n",p->rear);
	return 0;	
	
}
/*���ݳ���*/
int print_out(struct queue *p,int *data)
{
	if(check_empty(p))
		return -1;
	
	p->front = (p->front+1)%(p->size);
	*data = p->queue[p->front];
	// printf("%d\n",p->queue[p->front]);
	return 0;
	
}



int main(void)
{
	int a1 = 1;
	int a2 = 2;
	int a3 = 3;
	int a4 = 4;
	int a5 = 5;
	
	struct queue *p = init_queue(10);
	if(p == NULL)
		return -1;


	write_in(p,a1);

	write_in(p,a2);

	write_in(p,a3);

	write_in(p,a4);

	write_in(p,a5);

	int data;
	
	print_out(p,&data);
	print_out(p,&data);
	print_out(p,&data);
	print_out(p,&data);
	print_out(p,&data);
	printf("%d\n", data);

	
	
	
	
	
	
	
	return 0;
}

















