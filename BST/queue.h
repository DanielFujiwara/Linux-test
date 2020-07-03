#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BST.h"

/* ��������ṹ�� */
struct queue
{
	int size;
	struct node **queue;
	int front;  //��ͷƫ����
	int rear;   //��βƫ����
};

struct queue *init_queue(int size);
int in_queue(struct queue *p, struct node *data);
int out_queue(struct queue *p, struct node **data);



#endif