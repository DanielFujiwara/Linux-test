#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX(a,b)\
({\
	typeof(a) _a = a;\
	typeof(b) _b = b;\
	((_a)>(_b) ? (_a):(_b));\
})

int i = 0;
int a[100];
/*结构体模板声明*/
struct bst_tem
{
	int data;
	struct bst_tem *left;
	struct bst_tem *right;
	int h;
	struct bst_tem *link;
};
/*创建一个空树*/
struct bst_tem *bst_init()
{
	return NULL;
}
//获取树的高度
int get_h(struct bst_tem *root)
{
	if(root == NULL)
		return 0;
	
	return root->h;
}
/*新建节点*/
struct bst_tem *bst_new(int data)
{
	struct bst_tem *new = malloc(sizeof(struct bst_tem));
	if(new != NULL)
	{
		new->data = data;
		new->left = NULL;
		new->right = NULL;	
		new->link = NULL;
		new->h = 1;
	}
	else
	{
		printf("创建节点失败\n");
		return NULL;
		
	}
	return new;
}
/*左左右转*/
struct bst_tem *bst_right_turn(struct bst_tem *root)
{
		printf("%d\n",root->data);
	struct bst_tem *p = root->left;
	root->left = p->right;
	p->right = root;
	printf("%d\n",__LINE__);
	root->h = MAX(get_h(root->left),get_h(root->right)) +1;
	p->h = MAX(get_h(root),get_h(p->left)) +1;
	return p;
	
}
/*右右左转*/
struct bst_tem *bst_left_turn(struct bst_tem *root)
{
		// printf("%d\n",__LINE__);
	struct bst_tem *p = root->right;
	root->right = p->left;
	p->left = root;
	
	root->h = MAX(get_h(root->left),get_h(root->right)) +1;
	p->h = MAX(get_h(root),get_h(p->right)) +1;
	
	
	return p;
	
}
/*左右转*/
struct bst_tem *bst_leftright_turn(struct bst_tem *root)
{
		printf("%d\n",__LINE__);
	struct bst_tem *p = bst_left_turn(root->left);
	p = bst_right_turn(root);
	
	return p;
	
}
/*右左转*/
struct bst_tem *bst_rightleft_turn(struct bst_tem *root)
{
		printf("%d\n",__LINE__);
	struct bst_tem *p = bst_right_turn(root->right);
	p = bst_left_turn(root);
	
	return p;
	
}


/*插入节点*/
struct bst_tem *bst_inser(struct bst_tem *root,struct bst_tem *new)
{
		// printf("%d\n",__LINE__);
	if(root == NULL)
		return new;
	/*如果新数据比当前根小*/
	if(root->data > new->data)
		root->left = bst_inser(root->left,new);
	/*如果新数据比当前根大*/
	else if(root->data < new->data)
		root->right = bst_inser(root->right,new);
	/*如果新数据与当前根一样*/
	else
		printf("不能插入相同数据\n");
	//////////////////////////////检查////////////////////
		// printf("%d\n",__LINE__);
	
		if(get_h(root->left) - get_h(root->right) == 2) /////////左边平衡检查
		{
				printf("%d\n",__LINE__);
			if(root->left->data > new->data)
				root = bst_right_turn(root);
			else if(root->left->data < new->data)
				root = bst_leftright_turn(root);     ///////左右
		}
		else if(get_h(root->right) - get_h(root->left) == 2) /////////右边平衡检查
		{
				// printf("%d\n",__LINE__);
			if(root->right->data < new->data)
			{
				// printf("%d\n",__LINE__);
				root = bst_left_turn(root);
				// printf("%d\n",__LINE__);
			}//////右右
			else if(root->right->data > new->data)
				root = bst_rightleft_turn(root);///////右左
		}
	
	///////////////重置root高度///////////////////////
		// printf("%d\n",__LINE__);
	root->h = MAX(get_h(root->left),get_h(root->right)) +1;
	return root;
	
}

/*查找节点*/
struct bst_tem *bst_find(struct bst_tem *root,int data)
{
	if(root == NULL)
		return NULL;

	if(root->data > data)
		return bst_find(root->left,data);
	else if(root->data < data)
		return bst_find(root->right,data);
	else
		return root;	
}


/*遍历BST*/
int bst_show(struct bst_tem *root)
{
	if(root == NULL)
		return 0;
	
	printf("->%d<-",root->data);//先序
	
	bst_show(root->left);
	
	bst_show(root->right);
	
	
	return 0;
}
/*中遍历BST*/
int bst_show_mid(struct bst_tem *root)
{
	if(root == NULL)
		return 0;
	
	
	
	bst_show(root->left);
	printf("->%d<-",root->data);//中序
	bst_show(root->right);
	
	
	return 0;
}
/*后遍历BST*/
// int bst_show_last(struct bst_tem *root)
// {
	// if(root == NULL)
		// return 0;
	
	// root->link = printf("->%d<-",root->data);//后序
	
	// bst_show(root->left);
	
	// bst_show(root->right);
	
	
	// return 0;
// }
// /*缓存一个BST*/
int bst_to_group(struct bst_tem *root)
{
	if(root == NULL)
		return 0;
	
		a[i] = root->data;
		i++;                    //先序
	
	bst_to_group(root->left);
	
	bst_to_group(root->right);


	return 0;
}
/*缓存一个BST*/
// int bst_show_2(struct bst_tem *root)
// {
	// if(root == NULL)
		// return 0;
	
		// b[o] = root->data;
		// o++;                  
	
	// bst_show_2(root->left);

	// bst_show_2(root->right);
	

	// return 0;
// }

/*遍历BST按层*/

/*删除节点*/
struct bst_tem *bst_del(struct bst_tem *root,int data)
{
	if(root == NULL)
		return NULL;
	
	/*找到对应节点*/
	if(root->data > data)
		root->left = bst_del(root->left,data);
	else if(root->data < data)
		root->right = bst_del(root->right,data);
	/*找到data*/
	else
	{
		if(root->left != NULL)
		{
			struct bst_tem *leftMAX = root->left;
			
			for( ;leftMAX->right != NULL;leftMAX = leftMAX->right) ;//让leftMAX指向左树中最大值
				// printf("%d\n",leftMAX->data);
			root->data = leftMAX->data;//让最大值覆盖被删除的点
			// printf("%d\n",__LINE__);
			root->left = bst_del(root->left,leftMAX->data);
		}
		else if(root->right != NULL)
		{
			struct bst_tem *leftMIN = root->right;
			
			for( ;leftMIN->left != NULL;leftMIN = leftMIN->left); //让leftMIN指向右边树中最小值
			printf("%d\n",leftMIN->data);
			root->data = leftMIN->data;//让最小值覆盖被删除的点

			
			root->right = bst_del(root->right,leftMIN->data);
		}
		else
		{
			free(root);
			root = NULL;
			return NULL;
		}
		
	}
	
	return root;
	
}

/*直接对比*/
int compera(struct bst_tem *root1,struct bst_tem *root2)
{
	if(root1 == NULL && root2 == NULL)
		return 0;
	else if (root1 == NULL || root2 == NULL)
		return -1;
	else
	{
		if(root1->data == root2->data)
		{
			int ret = compera(root1->left,root2->left);
			int ret1 = compera(root1->right,root2->right);	
			if(ret == 0 && ret1 == 0)
				return 0;
		}
		else
			return -1;
		
		
	}
	

	
}
/*遍历对比*/
int compera_t(struct bst_tem *root1,struct bst_tem *root2)
{
	int ret;
	int ret1;
	if(root1 == NULL && root2 == NULL)
		return 0;
	else if(root1->data != root2->data)
		return -1;	
	else
	{
		ret = compera_t(root1->left,root2->left) ;				
		ret1 =  compera(root1->right,root2->right);		
	}
	printf("%d,%d\n",ret,ret1);
	if(ret == 0 && ret1 == 0)
	{
		ret = compera_t(root1->left,root2->left);
		if (ret == 0)
		{
			if(root1->data == root2->data)
			{
				ret = compera_t(root1->right,root2->right);
				// printf("1\n");
			}
			else
				return -1;
		}
		else
			return -1;
	}
	else
		return -1;

}

/*avl删除*/
struct bst_tem *avl_del(struct bst_tem *root,int data)
{
	if(root == NULL)
		return NULL;
	
	/*找到对应节点*/
	if(root->data > data)
		root->left = bst_del(root->left,data);
	else if(root->data < data)
		root->right = bst_del(root->right,data);
	/*找到data*/
	else
	{
		if(root->left != NULL)
		{
			struct bst_tem *leftMAX = root->left;
			
			for( ;leftMAX->right != NULL;leftMAX = leftMAX->right) ;//让leftMAX指向左树中最大值
				// printf("%d\n",leftMAX->data);
			root->data = leftMAX->data;//让最大值覆盖被删除的点
			// printf("%d\n",__LINE__);
			root->left = bst_del(root->left,leftMAX->data);
		}
		else if(root->right != NULL)
		{
			struct bst_tem *leftMIN = root->right;
			
			for( ;leftMIN->left != NULL;leftMIN = leftMIN->left); //让leftMIN指向右边树中最小值
			printf("%d\n",leftMIN->data);
			root->data = leftMIN->data;//让最小值覆盖被删除的点

			
			root->right = bst_del(root->right,leftMIN->data);
		}
		else
		{
			free(root);
			
			return NULL;
		}
		
	}
	/////////////判断平衡是否出现问题/////////////////
	if(get_h(root->left->right) - get_h(root->left->right) == 1)
	{
		if(get_h(root->left->right) - get_h(root->left->right) == 1)
			root = bst_leftright_turn(root); //////////左右
		else
			root = bst_right_turn(root);    ///////////左左
		
	}
	else if(get_h(root->right) - get_h(root->left) == 2)
	{
		if(get_h(root->right->left) - get_h(root->right->right) == 1)
			root = bst_rightleft_turn(root);//////////右右
		else
			root = bst_left_turn(root); ///////////////右左
	}
	
	root->h = MAX(get_h(root->right) , get_h(root->right)) +1;
	return root;
	
}

int main(void)
{
	struct bst_tem *root = bst_init();
	
	struct bst_tem *new = bst_new(1);
	
	root = bst_inser(root , new);
		// printf("%d\n",root->h);
	new = bst_new(2);
		// printf("%d\n",new->h);
	root = bst_inser(root , new);
		
	new = bst_new(3);
	root = bst_inser(root , new);

	new = bst_new(4);
	root = bst_inser(root , new);
	
	new = bst_new(5);
	root = bst_inser(root , new);
	
	new = bst_new(6);
	root = bst_inser(root , new);	
	
	new = bst_new(7);
	root = bst_inser(root , new);
	
	new = bst_new(8);
	root = bst_inser(root , new);
	new = bst_new(18);
	root = bst_inser(root , new);

	
	printf("树1：\n");
	bst_show(root);
	printf("\n");

	i = 0;
	memset(a,0,sizeof(a[100]));
	bst_to_group(root);
	
	
	
	struct node *head = init_list();
	struct node *newlist;
	
	for(i=0;i<9;i++)
	{
		newlist = new_node(a[i]);
		head_ins(head,newlist);
	}
	
	show(head);
	// struct bst_tem *root1 = bst_init();
	
	// struct bst_tem *new1 = bst_new('a');
	// root1 = bst_inser(root1 , new1);
	
	// new1 = bst_new('b');
	// root1 = bst_inser(root1 , new1);
	
	// new1 = bst_new('c');
	// root1 = bst_inser(root1 , new1);

	// new1 = bst_new('d');
	// root1 = bst_inser(root1 , new1);
	
	// new1 = bst_new('e');
	// root1 = bst_inser(root1 , new1);
	
	// new1 = bst_new('f');
	// root1 = bst_inser(root1 , new1);	
	
	// new1 = bst_new('g');
	// root1 = bst_inser(root1 , new1);
	
	// new1 = bst_new('h');
	// root1 = bst_inser(root1 , new1);

	
	// printf("树2：\n");
	// bst_show(root);
	// printf("\n");
	// bst_show_mid(root);
	// printf("\n");
	
	
	// bst_del(root,2);
	// bst_del(root,3);
	// bst_del(root,8);
	
	// printf("\n");
	// bst_show(root);
	// printf("\n");
	// bst_show_mid(root);
	// printf("\n");
	// bst_show_last(root);
	// printf("\n");
	// printf("\n");
	
	
	
	// int ret = compera_t(root,root1);
	// printf("遍历");
	// printf("%d\n",ret);
	
	// printf("直接");
	// ret = compera(root,root1);
	// printf("%d\n",ret);
	
	return 0;
}