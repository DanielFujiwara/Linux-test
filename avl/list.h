#ifndef __LIST_H__
#define __LIST_H__
#include "list.h"

#include <stdio.h>
#include <stdlib.h>

//��ƽڵ�
struct node
{
	int data;
	struct node* next;
};

//�½�������ʼ��
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

//�����½ڵ�
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

//���½ڵ���뵽����ĩβ
int tail_ins(struct node *head, struct node *new)
{
	struct node *p = head;
	
	/* ��ָ��pָ�����������һ���ڵ� */
	while(p->next)
		p = p->next;
	
	//���½ڵ���뵽����ĩβ
	p->next = new;
	
	return 0;
}

//���½ڵ���뵽ͷ�ڵ�֮��
int head_ins(struct node *head, struct node *new)
{
	new->next = head->next;
	head->next = new;
	
	return 0;
}

//���ҽڵ�,ͨ���ڵ������ݲ���
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

//ָ��λ�ò���
int ins_node(struct node *head, int data, struct node *new)
{
	struct node *p = find_node(head, data);
	if(p == NULL)
		return -1;
	
	new->next = p->next;
	p->next = new;
	
	return 0;
}

//ָ���ڵ�ɾ��
struct node *del_node(struct node *head, int data)
{
	struct node *p = find_node(head, data);
	if(p == NULL)
		return NULL;
	
	/* ��headָ��ָ��pǰ��һ���ڵ� */
	while(head->next != p)
		head = head->next;
	
	head->next = p->next;
	p->next = NULL;
	
	return p;
}


//�������
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