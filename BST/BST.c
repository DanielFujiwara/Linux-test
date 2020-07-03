#include "BST.h"




/* 2、	创建一个空树 */
struct node *init_bst(void)
{
	return NULL;	
}

/* 3、	新建节点 */
struct node *new_node(int data)
{
	struct node *new = malloc(sizeof(struct node));
	if(new != NULL)
	{
		new->data = data;
		new->left = NULL;
		new->right = NULL;
	}
	
	return new;
}

/* 4、	插入节点  插入之后满足“小-中-大” */
struct node *ins_node(struct node *root, struct node *new)
{
	/* 如果是第一个节点，直接返回new */
	if(root == NULL)
		return new;
	
	if(root->data > new->data)
		root->left = ins_node(root->left, new);
	else if(root->data < new->data)
		root->right = ins_node(root->right, new);
	else
		printf(" ins err!\n");
	
	return root;
}

/* 5、	查找节点 */
struct node *find_node(struct node *root, int data)
{
	if(root == NULL)
		return NULL;
	
	if(root->data > data)
		return find_node(root->left,data);
	else if(root->data < data)
		return find_node(root->right,data);
	else
		return root;
}

/* 6、	遍历BST 前中后序*/
void show(struct node *root)
{
	if(root == NULL)
		return ;
	
	show(root->left);
	show(root->right);
	printf("-->  %d  <--", root->data);
}

void print(struct node *tmp)
{
	printf("--> %d <--\n", tmp->data);
}

/* 6、	遍历BST 按层 */
void show_c(struct node *root, void (*handler)(struct node *))
{
	/* 1 入队节点的指针 
		a 新建队列
		b 将第一个节点的指针入队
		
		c 循环出队，将出队元素的左右孩子入队 
			出队时为NULL，遍历结束
	*/
	if(root == NULL)
		return ;
	struct queue *queue = init_queue(30);
	in_queue(queue, root);
	struct node *tmp;
	
	while(1)
	{
		int ret = out_queue(queue, &tmp);
		if(ret == -1)
			break;
		
		print(tmp);
		
		
		if(tmp->left != NULL)
			in_queue(queue, tmp->left);
		if(tmp->right != NULL)
			in_queue(queue, tmp->right);	
	}

	
	
	/* 2  入队节点的数据
		a 新建队列
		b 将第一个节点的数据入队
		
		c 循环出队，获得出队元素在BST中的节点地址
			将该节点的左右孩子入队
			出队时为NULL，遍历结束
	*/
	
}

/* 7、  节点删除 */
struct node *del_node(struct node *root, int data)
{
	/* 判断树为空 、 防止递归时root指向NULL（树中没有找到要删除的数据）*/
	if(root == NULL)
		return NULL;
	
	/* 先找到要删除的节点 */
	if(data > root->data)
		root->right = del_node(root->right,data);
	else if(data < root->data)
		root->left = del_node(root->left,data);
	else
	{
		// 左子树不为NULL
		if(root->left != NULL)
		{
			//找到左子树中的最大值
			struct node *tmp = root->left;
			for(; tmp->right!=NULL; tmp=tmp->right);
			
			//覆盖要删除的节点的值
			root->data = tmp->data;
			
			//删除左子树中的最大值
			root->left = del_node(root->left, tmp->data);
		}
		// 左子树为NULL，右子树不为NULL
		else if(root->right != NULL)
		{
			//找到右子树中的最小值
			struct node *tmp = root->right;
			for(; tmp->left!=NULL; tmp=tmp->left);
			
			//覆盖要删除的节点的值
			root->data = tmp->data;
			
			//删除右子树中的最小值
			root->right = del_node(root->right, tmp->data);
		}
		//叶子节点
		else
		{
			free(root);
			root = NULL;
			return NULL;
		}
		
	}	
	
	return root;
}


int main(void)
{
	struct node *root = init_bst();
	
	struct node *new = new_node(10);
	root = ins_node(root, new);
	
	new = new_node(12);
	root = ins_node(root, new);
	
	new = new_node(8);
	root = ins_node(root, new);
	
	new = new_node(9);
	root = ins_node(root, new);
	
	int data = 0;
	scanf("%d", &data);
	
	struct node *p = find_node(root, data);
	if(p == NULL)
		printf("not find\n");
	else
		printf("p->data:%d\n", p->data);
	
	show(root);
	
	del_node(root, data);
	
	show_c(root, print);
	
	return 0;
}