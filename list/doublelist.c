/*排序 game*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*链表*/
struct data_list
{
	int data;
	struct data_list *next;
	struct data_list *prve;
	
};

/*初始化链表*/
struct data_list *init_datalist(void)
{
	struct data_list *head = malloc(sizeof(struct data_list));
	if(head == NULL)
	{
		printf("初始化申请内存失败\n");
		return NULL;
	}
	
	head->next = head;
	head->prve = head;
}

/*数据写入*/
struct data_list *write_in(int data)
{
	struct data_list *new = malloc(sizeof(struct data_list));
	if (new == NULL)
	{
		printf("数据写入申请内存失败\n");
		return NULL;
	}
	new->data = data;
	new->next = NULL;
	new->prve = NULL;
}

/*把节点插入到任意后面*/
int data_in_tail(struct data_list *p,struct data_list *desk)
{
	desk->prve = p;
	desk->next = p->next;
	desk->next->prve = desk;
	p->next = desk;
	
	return 0;
}
/*把节点插入到任意前面*/
int data_in_head(struct data_list *p,struct data_list *desk)
{
	desk->next = p;
	desk->prve = p->prve;
	p->prve = desk;
	desk->prve->next = desk;
	return 0;
}
// /*查找节点*/
// struct data_list *locate(struct data_list *head, int data)
// {
	
	// return NULL;
// }
/*指针删除节点*/
struct data_list *del_list(struct data_list *p)
{
	struct data_list *del = p;
	
	p->prve->next = p->next;
	p->next->prve = p->prve;
	
	p->next = NULL;
	p->prve = NULL;
	
	
	return p;
	
}
/*打印全部*/
int showlist(struct data_list *head)
{
	struct data_list *p = head->next;
	while(p != head)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	
	printf("\n");
	return 0;
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
		
		data_in_tail(head,new);
		
		
	}
	showlist(head);
	

	// if(a%2 != 0)
	// {
		// printf("请输入偶数\n");
		// return 0;
	// }
	// a = a/2;
	// int doui;
	// struct data_list *dou[a];
	// struct data_list *x = head;
	// struct data_list *y;
	// int numx = 0;
	// for(i=1;i<=a;i++)
	// {
		// if(i%2 == 0)
		// {
			// for(doui = 0;doui<i;doui++)
			// {	
				// x = x->next;
			// }

				// dou[numx] = x;
				// numx++;

				// x = head;
			
			
		// }
		
	// }

	// a = a/2;
	
	// for(i = (a-1);i>=0;i--)
	// {
		// y = del_list( dou[i] );
		// printf("%d\n", y->data);
		// data_in_head(head,y);
	// }
	struct data_list *dou[a];
	struct data_list *p = head->next;
	struct data_list *y;
	int doux = 0;
	
	for(i=0;i<a;i++)
	{
		if((p->data)%2 == 0)
		{
			dou[doux] = p;
			doux++;
		}
		p = p->next;		
	}
	

	for(i = (doux-1);i>=0;i--)
	{
		y = del_list( dou[i] );
		data_in_head(head,y);
	}
	showlist(head);	
	return 0;
}






