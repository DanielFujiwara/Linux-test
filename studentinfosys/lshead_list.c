#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct one_kernel_list
{
	char name[10]; 		//姓名
	int id; 			//学号
	int age;			//年龄
	struct list_head my_list; 
};

/*初始化链表*/
struct one_kernel_list *init_list(void)
{
	struct one_kernel_list *head 
	= (struct one_kernel_list *)malloc(sizeof(struct one_kernel_list));
	
	if( head != NULL)
	{
		INIT_LIST_HEAD( & (head->my_list));
		return head;
	}
	
	return NULL;
}

/*创建节点*/
struct one_kernel_list *init_node(char *name,int id,int age)
{
	struct one_kernel_list *new 
	= (struct one_kernel_list *)malloc(sizeof(struct one_kernel_list));
	
	if(new != NULL)
	{
		
		strcpy(new->name, name);
		new->id = id;
		new->age = age;
		new->my_list.next = NULL;
		new->my_list.prev = NULL;
		
		return new;
	}
	
	return NULL;
}

/* 插入节点 */

/* 遍历链表 */
void show(struct one_kernel_list *head)
{
	struct one_kernel_list *tmp;
	struct list_head *pos;

	list_for_each(pos, &(head->my_list))
	//for (pos = (head)->next; pos != (head);pos = pos->next)
	{
		tmp = list_entry(pos, struct one_kernel_list, my_list);
		printf("name:%s id:%d age:%d \n", tmp->name,tmp->id ,tmp->age);
		
	}
}
/* 逆向遍历链表 */
void reshow(struct one_kernel_list *head)
{
	struct one_kernel_list *tmp;
	struct list_head *pos;

	list_for_each_prev(pos, &(head->my_list))
	//for (pos = (head)->next; pos != (head);pos = pos->next)
	{
		tmp = list_entry(pos, struct one_kernel_list, my_list);
		printf("name:%s id:%d age:%d \n", tmp->name,tmp->id ,tmp->age);
		
	}
}
/* 删除节点 */
void del_node(struct one_kernel_list *head, int id)
{
	struct one_kernel_list *tmp;
	struct list_head *pos, *n;

	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct one_kernel_list, my_list);
		// printf("id:%d, name:%s\n", tmp->id, tmp->name);
		
		if(tmp->id == id )
		{
			list_del_init(pos);	
		}
	}
	
}

int main(void)
{
	struct one_kernel_list *head = init_list();;
	if(head == NULL)
	{
		printf("list init err!\n");
		return -1;
	}
	
	int num;
	char name[10]={0};
	int id;
	int age;
	while(1)
	{
		printf("输入1-5\n");
		printf("1按学号插入（学号按照升序排列）\n");
		printf("2按学号删除\n");
		printf("3顺序打印链表\n");
		printf("4逆序\n");
		printf("5退出\n");
		scanf("%d",&num);
		if(num == 1)
		{
			
			printf("输入姓名 学号 年龄\n");
			scanf("%s%d%d",name,&id,&age);
			
			struct one_kernel_list *new  = init_node(name,id,age);
			if(new == NULL)
			{
				printf("new node err!\n");
				return -2;
			}
			//tail_insert(head,new);
			list_add(&(new->my_list), &(head->my_list));
		}
		else if(num == 2)
		{
			show(head);
			printf("输入要删除的学号\n");
			scanf("%d",&id);
			del_node(head,id);
		}
		else if(num==3)
		{
			// sort_id_data(head);
			show(head);
		}		
		else if(num==4)
			// invert(head, head->next);
			reshow(head);
		else if(num == 5)
			break;
	}
	// struct one_kernel_list *head = init_list();
	
	// struct one_kernel_list *new  = init_node(50, "abc");
	
	// list_add(&(new->my_list), &(head->my_list));
	
	// new  = init_node(40, "123");
	
	// list_add(&(new->my_list), &(head->my_list));
	
	// new  = init_node(30, "ABC");
	
	// list_add_tail(&(new->my_list), &(head->my_list));
	
	// show(head);

	// del_node(head, 50, "abc");
	
	// show(head);
	
	
	return 0;
}


