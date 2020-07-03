#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/////////////////////顺序队列
/*管理结构体*/
struct queue
{
	int size;
	int *queue;
	int front;  //队头（用于输出）
	int rear;   //对尾（用于写入）
	
};
/*初始化结构体队列*/
struct queue *init_queue(int size)
{
	struct queue*p = malloc(sizeof(struct queue));
	if(p == NULL)
	{
		printf("管理结构体创建失败\n");
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
/*检查是否满*/
bool check_full(struct queue*p)
{
	return p->front == (p->rear+1)%(p->size);
	
}
/*检查是否为空*/
bool check_empty(struct queue*p)
{
	return p->front == p->rear;
	
}
/*数据写入队列*/
int write_in(struct queue *p,int data)
{

	if(check_full(p))
		return -1;

	p->rear = (p->rear+1)%(p->size);
	
	p->queue[p->rear] = data;
	
	printf("%d\n",p->rear);
	return 0;	
	
}
/*数据出列*/
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

















