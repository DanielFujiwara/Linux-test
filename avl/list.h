#ifndef __LIST_H__
#define __LIST_H__
#include "list.h"

#include <stdio.h>
#include <stdlib.h>

//设计节点
struct node
{
	int data;
	struct node* next;
};

//新建链表并初始化
struct node *init_list(void)
{
	struct node* head = malloc(sizeof(struct node));
	if(head == NULL)
	{
		printf("malloc list err!\n");
		return NULL;
	}
	
	head->next = NULL;
	
	return head;
}

//创建新节点
struct node *new_node(int data)
{
	struct node* new = malloc(sizeof(struct node));
	if(new == NULL)
	{
		printf("malloc node err!\n");
		return NULL;
	}
	
	new->data = data;
	new->next = NULL;
	
	return new;
}

//将新节点插入到链表末尾
int tail_ins(struct node *head, struct node *new)
{
	struct node *p = head;
	
	/* 让指针p指向链表中最后一个节点 */
	while(p->next)
		p = p->next;
	
	//将新节点插入到链表末尾
	p->next = new;
	
	return 0;
}

//将新节点插入到头节点之后
int head_ins(struct node *head, struct node *new)
{
	new->next = head->next;
	head->next = new;
	
	return 0;
}

//查找节点,通过节点中数据查找
struct node *find_node(struct node *head, int data)
{
	head = head->next;
	while(head)
	{
		if(head->data == data)
			break;
		head = head->next;
	}
	
	return head;
}

//指定位置插入
int ins_node(struct node *head, int data, struct node *new)
{
	struct node *p = find_node(head, data);
	if(p == NULL)
		return -1;
	
	new->next = p->next;
	p->next = new;
	
	return 0;
}

//指定节点删除
struct node *del_node(struct node *head, int data)
{
	struct node *p = find_node(head, data);
	if(p == NULL)
		return NULL;
	
	/* 让head指针指向p前面一个节点 */
	while(head->next != p)
		head = head->next;
	
	head->next = p->next;
	p->next = NULL;
	
	return p;
}


//链表遍历
void show(struct node *head)
{
	struct node *p = head->next;
	while(p)
	{
		printf("data:%d\n", p->data);
		p = p->next;
	}
}
#endif