#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BST.h"

/* 声明管理结构体 */
struct queue
{
	int size;
	struct node **queue;
	int front;  //队头偏移量
	int rear;   //队尾偏移量
};

struct queue *init_queue(int size);
int in_queue(struct queue *p, struct node *data);
int out_queue(struct queue *p, struct node **data);



#endif