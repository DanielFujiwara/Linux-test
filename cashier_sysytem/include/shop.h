#ifndef __SHOP_H__
#define __SHOP_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "kernel.h"
// #include "kernellist.h"

#define    COLOR_NONE                   "\033[0m"
#define    FONT_COLOR_RED             "\033[1;31m"
#define    FONT_COLOR_GREEN            "\033[1;32m"
#define    FONT_COLOR_YELLOW            "\033[1;33m"
#define    FONT_COLOR_BLUE            "\033[1;34m"
#define    FONT_COLOR_ZISE            "\033[1;35m"
#define    FONT_COLOR_QINGSE            "\033[1;36m"


#define    FONT_COLOR_RED_N             "\033[0;31m"
#define    FONT_COLOR_GREEN_N            "\033[0;32m"
#define    FONT_COLOR_YELLOW_N            "\033[0;33m"
#define    FONT_COLOR_BLUE_N            "\033[0;34m"
#define    FONT_COLOR_ZISE_N            "\033[0;35m"
#define    FONT_COLOR_QINGSE_N            "\033[0;36m"

#define    BACKGROUND_COLOR_RED        "\033[41m"    

#define    BG_RED_FONT_YELLOW        "\033[41;33m"









struct shop_list
		{
			char name[30];
			double price;
			double discounts;
			int id;

		};	

struct acontlist
{
	char name[50];
	char password[50];
	char question[50];
	char key[50];
	int id;

};

struct shopcar
{
	char name[30];
	double price;
	double discounts;
	int m;
	int id;
	double mp;
};

// struct load_shoplist
// {
// 	char name[30];
// 	double price;
// 	double discounts;
// 	int id;
// 	struct list_head my_list; 
// };

// /*初始化链表*/
// struct load_shoplist *init_list(void)
// {
// 	struct load_shoplist *head 
// 	= (struct load_shoplist *)malloc(sizeof(struct load_shoplist));
	
// 	if( head != NULL)
// 	{
// 		INIT_LIST_HEAD( & (head->my_list));
// 		return head;
// 	}
	
// 	return NULL;
// }

// /*创建节点*/
// struct load_shoplist *init_node(char *name,double price,double discounts,int id)
// {
// 	struct load_shoplist *new 
// 	= (struct load_shoplist *)malloc(sizeof(struct load_shoplist));
	
// 	if(new != NULL)
// 	{
		
// 		strcpy(new->name, name);
// 		new->price = price;
// 		new->discounts = discounts;
// 		new->id = id;
// 		new->my_list.next = NULL;
// 		new->my_list.prev = NULL;
		
// 		return new;
// 	}
	
// 	return NULL;
// }

// /* 遍历链表 */
// void show(struct load_shoplist *head)
// {
// 	struct load_shoplist *tmp;
// 	struct list_head *pos;

// 	list_for_each(pos, &(head->my_list))
// 	//for (pos = (head)->next; pos != (head);pos = pos->next)
// 	{
// 		tmp = list_entry(pos, struct load_shoplist, my_list);
// 		printf("name:%-22s price:%-6.2lf discount:%-6.2lf id:%2d\n"
// 			, tmp->name,tmp->price ,tmp->discounts,tmp->id);

		
// 	}
// }
//////////kernel//////////////////////
/*初始化链表*/
struct load_shoplist *init_list(void);
/*创建节点*/
struct load_shoplist *init_node(char *name,double price,double discounts,int id);
/* 遍历链表 */
void show(struct load_shoplist *head);
/* 删除节点 */
int del_node(struct load_shoplist *head, int id);
/* 定位节点 */
struct load_shoplist * locate_node(struct load_shoplist *head, int id);
/* 查找节点 */
struct load_shoplist * locate_node_name_shop(struct load_shoplist *head, char *name);



///////////////操作///////////////////////

int input_shoplist(void);//录入
struct load_shoplist * lodinglist(void);///载入
struct load_shoplist * del_shoplist(void);   ////删除
int show_shoplist(void); //展现商品
struct load_shoplist * modify_data(void);//修改价格或折购
struct load_shoplist * locate_node_name_shop(struct load_shoplist *head, char *name);//查找商品
int findshoplist(void);//查找商品
int createacount(void);//用户创建
struct load_acountlist *lodingacount(void);//用户信息载入
int show_acountlist(void);//展示用户信息
struct load_acountlist * del_acountlist(void);//删除商户信息
int acounthelp(void);//用户帮助
int password_mod(void);//修改密码
int write_acount_txt(struct load_acountlist *head);//录入账户进文件
int findyourpassword(void);///找回密码
int loginacount (void);//登录模块
int acount(void);//登录处理模块
int name_mod(void);//修改用户名


int admindesk(void);//管理员登录界面
///////////////////////////////////////////////////
int creatshoptxt(void);//用户文件创建
// char *runningname(void);//获取当前操作用户名称
int shopcar(void);//用户购物车

int useracount(void);//用户空间
struct load_shoplist *showshoptou(void);//用户商品展示
int prit(char *name);//
int maxshoplist(struct load_shoplist *head); //获取商品总数
int usershow(struct load_shoplist *head);//用户查看商品
int shopcar_in(int max,char *name,struct load_shoplist *head);//用户购物车添加
struct load_shopcar * loadshopcar(char *name);//载入用户购物车
int carjob(char *name);//购物车操作
int show_my_car(struct load_shopcar *head);//展示购物车内容
int del_car_shop(struct load_shopcar *head,char *name);//删除购物车
int mo_car_shop(struct load_shopcar *head,char *name);//修改数量
int byebye(struct load_shopcar *head,char *name);//结账
int cleancar(char* name);//清空购物车
int emptycar(struct load_shopcar *head);//判断购物车是否空
#endif