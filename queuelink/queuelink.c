#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
////////////////////��ʽ����β��
/*��������*/
struct list
{
	int data;
	struct list *next;
	
};
/*����ṹ��*/
struct queue
{
	int size;
	struct list *queue;
	// int front;  //��ͷ�����������
	// int rear;   //��β������д�룩
	
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
	p->queue = NULL;
	p->size = 0;
	
	return p;
	
	
}
/*����Ƿ���*/
// bool check_full(struct queue*p)
// {
	// return p->front == (p->rear+1)%(p->size);
	
// }
/*����Ƿ�Ϊ��*/
bool check_empty(struct queue*p)
{
	return p->size == 0;
	
}
/*����д��*/
struct list *write_in_list(int data)
{
	struct list *new_list = malloc(sizeof(struct list));
	if(new_list == NULL)
		return NULL;
	
	new_list->data = data;
	new_list->next = NULL;
	return new_list;

}
/*����д�����*/
int write_in(struct queue *p,int data)
{
		struct list *new_list = write_in_list(data);
		struct list *last = p->queue;
		if(new_list == NULL)
			return -1;
		
			if(p->size == 0)
			{
				p->queue = new_list;
			}
			else
			{
				while(last->next != NULL)
				{
					last = last->next;
				}
				
				new_list->next = last->next;
				last->next = new_list;
			}
		// printf("%d\n",p->queue->data);
		// printf("p:%d\n",p->size);
		p->size++;
	return 0;	
	
}
/*���ݳ���*/
int print_out(struct queue *p,int *data)
{
	
	// printf("%d\n",__LINE__);
	struct list *del = p->queue;
	struct list *dell;
	if(check_empty(p))
		return -1;
	// printf("%d\n",__LINE__);
	
	if(p->size == 1)
	{
		*data = del->data;
		
		p->queue = NULL;		
		p->size--;
		free(del);
		del = NULL;
		return 0;
	}
	// printf("%d\n",__LINE__);
		while(1)
		{
			if(del->next->next == NULL)
				break;	
			// printf("%d\n",__LINE__);			
			del = del->next;
		}
		// printf("%d\n",__LINE__);
		*data = del->next->data;
		dell = del->next;
		free(dell);
		del->next = NULL;
		dell = NULL;
		p->size--;
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
		printf("%d\n", data);
	print_out(p,&data);
		printf("%d\n", data);
	print_out(p,&data);
		printf("%d\n", data);
	print_out(p,&data);
		printf("%d\n", data);
	print_out(p,&data);
	printf("%d\n", data);

	
	
	
	
	
	
	
	return 0;
}

















