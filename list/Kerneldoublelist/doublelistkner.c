/*排序 game*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

/*链表*/
struct data_list
{
	int data;
	struct list_head my_list;
	
};

/*初始化链表*/
struct data_list *init_datalist(void)
{
	struct data_list *head 
	= (struct data_list *)malloc(sizeof(struct data_list));
	
	if( head != NULL)
	{
		INIT_LIST_HEAD( & (head->my_list));
		return head;
	}
	
	return NULL;
}

/*数据写入*/
struct data_list *write_in(int data)
{
	struct data_list *new 
	= (struct data_list *)malloc(sizeof(struct data_list));
	
	if(new != NULL)
	{
		
		new->data = data;
		new->my_list.next = NULL;
		new->my_list.prev = NULL;
		
		return new;
	}
	return NULL;
}

// /*把节点插入到任意后面*/
// int data_in_tail(struct data_list *p,struct data_list *desk)
// {
	// desk->prve = p;
	// desk->next = p->next;
	// desk->next->prve = desk;
	// p->next = desk;
	
	// return 0;
// }
// /*把节点插入到任意前面*/
// int data_in_head(struct data_list *p,struct data_list *desk)
// {
	// desk->next = p;
	// desk->prve = p->prve;
	// p->prve = desk;
	// desk->prve->next = desk;
	// return 0;
// }
// /*查找节点*/
// struct data_list *locate(struct data_list *head, int data)
// {
	
	// return NULL;
// }
// /*指针删除节点*/
// struct data_list *del_list(struct data_list *p)
// {
	// struct data_list *del = p;
	
	// p->prve->next = p->next;
	// p->next->prve = p->prve;
	
	// p->next = NULL;
	// p->prve = NULL;
	
	
	// return p;
	
// }
/*打印全部*/
void showlist(struct data_list *head)
{
	struct data_list *tmp;
	struct list_head *pos;

	list_for_each(pos, &(head->my_list))
	{
		tmp = list_entry(pos, struct data_list, my_list);
		printf("%d ", tmp->data);
		

	}
	printf("\n");
}


int main(void)
{
	printf("please input a num\n");
	int a;
	scanf("%d", &a);
	
	struct data_list *new;
	struct data_list *head;
	
	head = init_datalist();
	if(head == NULL)
	{
		printf("初始化失败\n");
		return -1;
	}
	
	int i = 0;
	for(i=a;i>0;i--)
	{
		new = write_in(i);
		if(new == NULL)
		{
			printf("数据写入失败\n");
			return -1;
		}
		list_add(&(new->my_list), &(head->my_list));
		// data_in_tail(head,new);
		
	}
	
	showlist(head);
	
	int doux = 0;
	struct data_list *dou[a];
	struct data_list *tmp;
	struct list_head *pos;
	

		list_for_each(pos, &(head->my_list))
		{
			tmp = list_entry(pos, struct data_list, my_list);
			if((tmp->data)%2 == 0)
			{
				dou[doux] = tmp;
				
				// printf("data:%d\n", dou[doux]->data);
				doux++;
			}			
		}

	struct data_list *y[a];
	
	for(i = (doux-1);i>=0;i--)
	{
		y[i] = dou[i];
		list_del_init( &(dou[i]->my_list) );
		// data_in_head(head,y);
		dou[i] = y[i];
		list_add_tail(&(dou[i]->my_list), &(head->my_list));
	}
	showlist(head);	
	
	return 0;
}






