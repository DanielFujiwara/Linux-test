#ifndef __KERNEL_H__
#define __KERNEL_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernellist.h"
///////////////////////////////常规操作//////////////////////////////////////

struct load_shoplist
{
	char name[30];
	double price;
	double discounts;
	int id;
	struct list_head my_list; 
};

struct load_shopcar
{
	char name[30];
	double price;
	double discounts;
	int m;
	int id;
	double mp;
	struct list_head my_list; 
};
struct load_acountlist
{
	char name[50];
	char password[50];
	char question[50];
	char key[50];
	int id;
	struct list_head my_list; 
};
///////////////////////////商品链表///////////////////////
///////////////////////////商品链表///////////////////////
///////////////////////////商品链表///////////////////////
///////////////////////////商品链表///////////////////////
///////////////////////////商品链表///////////////////////
/*初始化链表*/
struct load_shoplist *init_list(void)
{
	struct load_shoplist *head 
	= (struct load_shoplist *)malloc(sizeof(struct load_shoplist));
	
	if( head != NULL)
	{
		INIT_LIST_HEAD( & (head->my_list));
		return head;
	}
	
	return NULL;
}

/*创建节点*/
struct load_shoplist *init_node(char *name,double price,double discounts,int id)
{
	struct load_shoplist *new 
	= (struct load_shoplist *)malloc(sizeof(struct load_shoplist));
	
	if(new != NULL)
	{
		
		strcpy(new->name, name);
		new->price = price;
		new->discounts = discounts;
		new->id = id;
		new->my_list.next = NULL;
		new->my_list.prev = NULL;
		
		return new;
	}
	
	return NULL;
}

/* 遍历链表 */
void show(struct load_shoplist *head)
{
	struct load_shoplist *tmp;
	struct list_head *pos;

	list_for_each(pos, &(head->my_list))
	//for (pos = (head)->next; pos != (head);pos = pos->next)
	{
		tmp = list_entry(pos, struct load_shoplist, my_list);
		printf("id:%-2d 商品:%-21s\n"
			, tmp->id, tmp->name);
		printf(FONT_COLOR_GREEN_N"      价格:%-6.2lf元 折购:%-6.2lf%% \n"COLOR_NONE
			, tmp->price ,tmp->discounts);
		printf("\n");

		
	}
}

/* 删除节点 */
int del_node(struct load_shoplist *head, int id)
{
	struct load_shoplist *tmp;
	struct list_head *pos, *n;
	char a[3]= {0};
	int rety;
	int retn;
	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct load_shoplist, my_list);
		// printf("id:%d, name:%s\n", tmp->id, tmp->name);
		
		if(tmp->id == id )
		{
			printf("你已选中以下商品:\n");
			printf(FONT_COLOR_BLUE"id:%-2d 商品:%-21s 价格:%-6.2lf元 折购:%-6.2lf%% \n"COLOR_NONE
			,tmp->id, tmp->name,tmp->price ,tmp->discounts);
			printf(FONT_COLOR_RED"是否确认删除yes/no\n"COLOR_NONE);
			while(1)
			{
				scanf("%s",a);
				
				rety = strcmp(a,"yes");
				retn = strcmp(a,"no");

				if(rety == 0)
					break;
				else if(retn == 0)
				{
					printf(FONT_COLOR_RED"取消操作！\n"COLOR_NONE);
					return 0;
				}
				else
				{
					printf(FONT_COLOR_RED"输入错误请重新输入\n"COLOR_NONE);
					while(getchar() != '\n');
				}
			}

			printf(FONT_COLOR_GREEN"删除成功！\n"COLOR_NONE);
			list_del_init(pos);	
			return 0;
		}

	}
	printf(FONT_COLOR_RED"没有此商品！\n"COLOR_NONE);
	return -1;
}

/* 定位节点 */
struct load_shoplist * locate_node(struct load_shoplist *head, int id)
{
	struct load_shoplist *tmp;
	struct list_head *pos, *n;

	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct load_shoplist, my_list);
		if(tmp->id == id )
		{
			printf("你已选中以下商品:\n");
			printf(FONT_COLOR_RED"id:%-2d 商品:%-21s 价格:%-6.2lf元 折购:%-6.2lf%% \n"COLOR_NONE
			,tmp->id, tmp->name,tmp->price ,tmp->discounts);	
			return tmp;
		}		
	}
	printf("没有此商品！\n");
	return NULL;
	
}
/* 查找节点 */
struct load_shoplist * locate_node_name_shop(struct load_shoplist *head, char *name)
{
	struct load_shoplist *tmp;
	struct list_head *pos, *n;
	int ret;
	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct load_shoplist, my_list);
		ret = strcmp(tmp->name, name);
		if(ret == 0  )
		{	
			return tmp;
		}		
	}
	// printf(FONT_COLOR_RED"没有此商品！\n"COLOR_NONE);
	return NULL;
	
}

///////////////////////..账号链表../////////////////////////////
///////////////////////..账号链表../////////////////////////////
///////////////////////..账号链表../////////////////////////////
///////////////////////..账号链表../////////////////////////////
///////////////////////..账号链表../////////////////////////////
///////////////////////..账号链表../////////////////////////////
///////////////////////..账号链表../////////////////////////////
///////////////////////..账号链表../////////////////////////////
struct load_acountlist *init_list_acount(void)
{
	struct load_acountlist *head 
	= (struct load_acountlist *)malloc(sizeof(struct load_acountlist));
	
	if( head != NULL)
	{
		INIT_LIST_HEAD( & (head->my_list));
		return head;
	}
	
	return NULL;
}

/*创建节点*/
struct load_acountlist *init_node_acount(char *name,
	char *password, char *question, char *key, int id)
{
	struct load_acountlist *new 
	= (struct load_acountlist *)malloc(sizeof(struct load_acountlist));
	
	if(new != NULL)
	{
		
		strcpy(new->name,name);
		strcpy(new->password,password);
		strcpy(new->question,question);
		strcpy(new->key,key);
		new->id = id;
		new->my_list.next = NULL;
		new->my_list.prev = NULL;
		
		return new;
	}
	
	return NULL;
}

/* 遍历链表 */
void show_acount(struct load_acountlist *head)
{
	struct load_acountlist *tmp;
	struct list_head *pos;

	list_for_each(pos, &(head->my_list))
	//for (pos = (head)->next; pos != (head);pos = pos->next)
	{
		tmp = list_entry(pos, struct load_acountlist, my_list);
		printf("id:%-2d 用户:%-21s  \n"
			, tmp->id, tmp->name);
		printf(FONT_COLOR_GREEN_N"      密码%s,问题%s,答案%s\n"COLOR_NONE,tmp->password,tmp->question,tmp->key );

		
	}
}

/* 删除节点 */
int del_node_acount(struct load_acountlist *head, int id)
{
	struct load_acountlist *tmp;
	struct list_head *pos, *n;
	char a[3]= {0};
	int rety;
	int retn;
	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct load_acountlist, my_list);
		// printf("id:%d, name:%s\n", tmp->id, tmp->name);
		
		if(tmp->id == id )
		{
			printf("你已选中以下用户:\n");
			printf(FONT_COLOR_RED"id:%2d 用户:%s  \n"COLOR_NONE
			,tmp->id, tmp->name);
			printf("是否确认删除yes/no\n");
			while(1)
			{
				scanf("%s",a);
				
				rety = strcmp(a,"yes");
				retn = strcmp(a,"no");

				if(rety == 0)
					break;
				else if(retn == 0)
				{
					printf(FONT_COLOR_RED"取消操作！\n"COLOR_NONE);
					return 0;
				}
				else
				{
					printf(FONT_COLOR_RED"输入错误请重新输入\n"COLOR_NONE);
					while(getchar() != '\n');
				}
			}

			printf(FONT_COLOR_GREEN"删除成功！\n"COLOR_NONE);
			list_del_init(pos);	
			return 0;
		}

	}
	printf(FONT_COLOR_RED"没有此用户！\n"COLOR_NONE);
	return -1;
}

/* 定位节点 */
struct load_acountlist * locate_node_acount(struct load_acountlist *head, int id)
{
	struct load_acountlist *tmp;
	struct list_head *pos, *n;

	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct load_acountlist, my_list);
		if(tmp->id == id )
		{
			// printf("你已选中以下用户:\n");
			// printf("id:%-2d 用户:%s  \n"
			// ,tmp->id, tmp->name);	
			return tmp;
		}		
	}
	printf(FONT_COLOR_RED"没有此用户！\n"COLOR_NONE);
	return NULL;
	
}

/* 重名确认 */
int locate_node_name(struct load_acountlist *head, char *name)
{
	struct load_acountlist *tmp;
	struct list_head *pos, *n;
	int ret;

	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct load_acountlist, my_list);
		ret = strcmp(tmp->name, name);
		if(ret == 0 )
		{
			return 0;
		}		
	}
	return 1;
	
}

/* 用户名定位 */
struct load_acountlist * locate_resign_name(struct load_acountlist *head, char *name)
{
	struct load_acountlist *tmp;
	struct list_head *pos, *n;
	int ret;

	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct load_acountlist, my_list);
		ret = strcmp(tmp->name, name);
		if(ret == 0 )
		{
			return tmp;
		}		
	}
	return NULL;
	
}

///////////////////////////////购物车链表///////////////////////
///////////////////////////////购物车链表///////////////////////
///////////////////////////////购物车链表////////////////////////
///////////////////////////////购物车链表////////////////////////
///////////////////////////////购物车链表////////////////////////
///////////////////////////////购物车链表////////////////////////
/*初始化链表*/
struct load_shopcar *init_list_car(void)
{
	struct load_shopcar *head 
	= (struct load_shopcar *)malloc(sizeof(struct load_shopcar));
	
	if( head != NULL)
	{
		INIT_LIST_HEAD( & (head->my_list));
		return head;
	}
	
	return NULL;
}

/*创建节点*/
struct load_shopcar *init_node_car(char *name,double price,double discounts,int id,int m,double mp)
{
	struct load_shopcar *new 
	= (struct load_shopcar *)malloc(sizeof(struct load_shopcar));
	
	if(new != NULL)
	{
		
		strcpy(new->name, name);
		new->price = price;
		new->discounts = discounts;
		new->id = id;
		new->m = m;
		new->mp = mp;
		new->my_list.next = NULL;
		new->my_list.prev = NULL;
		
		return new;
	}
	
	return NULL;
}

/* 遍历链表 */
void show_car(struct load_shopcar *head)
{
	struct load_shopcar *tmp;
	struct list_head *pos;

	list_for_each(pos, &(head->my_list))
	//for (pos = (head)->next; pos != (head);pos = pos->next)
	{
		tmp = list_entry(pos, struct load_shopcar, my_list);
		printf("id:%-2d 商品:%-21s  \n"
			, tmp->id, tmp->name);
		printf(FONT_COLOR_BLUE_N"单价:%-6.2lf元 数量： %6d 折购:%-6.2lf%% 单计：%-6.2lf元 \n"COLOR_NONE
			, tmp->price,tmp->m ,tmp->discounts,tmp->mp);

		
	}
}

/* 删除节点 */
int del_node_car(struct load_shopcar *head, int id)
{
	struct load_shopcar *tmp;
	struct list_head *pos, *n;
	char a[3]= {0};
	int rety;
	int retn;
	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct load_shopcar, my_list);
		// printf("id:%d, name:%s\n", tmp->id, tmp->name);
		
		if(tmp->id == id )
		{
			printf("你已选中以下商品:\n");
			printf(FONT_COLOR_RED"id:%-2d 商品:%-21s 单价:%-6.2lf元 数量： %6d 折购:%-6.2lf%% 单计：%-6.2lf元 \n"COLOR_NONE
			, tmp->id, tmp->name,tmp->price,tmp->m ,tmp->discounts,tmp->mp);
			printf("是否确认删除yes/no\n");
			while(1)
			{
				scanf("%s",a);
				
				rety = strcmp(a,"yes");
				retn = strcmp(a,"no");

				if(rety == 0)
					break;
				else if(retn == 0)
				{
					printf(FONT_COLOR_RED"取消操作！\n"COLOR_NONE);
					return 0;
				}
				else
				{
					printf(FONT_COLOR_RED"输入错误请重新输入\n"COLOR_NONE);
					while(getchar() != '\n');
				}
			}

			printf(FONT_COLOR_GREEN"删除成功！\n"COLOR_NONE);
			list_del_init(pos);	
			return 0;
		}

	}
	printf(FONT_COLOR_RED"没有此商品！\n"COLOR_NONE);
	return -1;
}

/* 定位节点 */
struct load_shopcar * locate_node_car(struct load_shopcar *head, int id)
{
	struct load_shopcar *tmp;
	struct list_head *pos, *n;

	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct load_shopcar, my_list);
		if(tmp->id == id )
		{
			printf("你已选中以下商品:\n");
			printf(FONT_COLOR_GREEN"id:%-2d 商品:%-21s 单价:%-6.2lf元 数量： %6d 折购:%-6.2lf%% 单计：%-6.2lf元 \n"COLOR_NONE
			, tmp->id, tmp->name,tmp->price,tmp->m ,tmp->discounts,tmp->mp);	
			return tmp;
		}		
	}
	printf(FONT_COLOR_RED"没有此商品！\n"COLOR_NONE);
	return NULL;
	
}
/* 查找节点 */
struct load_shopcar * locate_node_name_shop_car(struct load_shopcar *head, char *name)
{
	struct load_shopcar *tmp;
	struct list_head *pos, *n;
	int ret;
	list_for_each_safe(pos, n, &(head->my_list))
	{
		
		tmp = list_entry(pos, struct load_shopcar, my_list);
		ret = strcmp(tmp->name, name);
		if(ret == 0  )
		{	
			return tmp;
		}		
	}
	printf("没有此商品！\n");
	return NULL;
	
}
#endif