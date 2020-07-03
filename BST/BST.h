#ifndef _BST_H_
#define _BST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"


/* 1、	结构体模板声明 */
struct node
{
	int data;
	struct node *left;
	struct node *right;
};


struct node *init_bst(void);
struct node *new_node(int data);
struct node *ins_node(struct node *root, struct node *new);
struct node *find_node(struct node *root, int data);
void show(struct node *root);
void show_c(struct node *root, void (*handler)(struct node *));
void show_c(struct node *root, void (*handler)(struct node *));

#endif