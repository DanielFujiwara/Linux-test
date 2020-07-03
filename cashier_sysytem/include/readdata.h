#ifndef __READDATA_H__
#define __READDATA_H__
#include "shop.h"
#include "kernel.h"

// struct shop_list
// 		{
// 			char name[30];
// 			double price;
// 			double discounts;
// 			int id;

// 		};	

// struct acontlist
// {
// 	char name[50];
// 	char password[50];
// 	char question[50];
// 	char key[50];
// 	int id;

// };


///////////// 写入商品信息到txt//////////////////////////////////////////////////////////////////////////////
///////////// 写入商品信息到txt//////////////////////////////////////////////////////////////////////////////
int input_shoplist(void)
{
	
	int i = 0;
	char namei[30];
	struct shop_list p[100];
	struct shop_list *new = malloc(sizeof(struct shop_list));
	char writein[3]= {0};
	int rety;
	int retn;

	while(1)
	{
		while(1)
		{
			printf("是否开始录入信息，yes/no?\n");
			scanf("%s",writein);
			rety = strcmp(writein,"yes");
			retn = strcmp(writein,"no");

			if(rety == 0)
				break;
			else if(retn == 0)
				{
					printf(FONT_COLOR_GREEN"停止录入数据！\n"COLOR_NONE);
					goto write_in_file;
				}
			else
				{
					printf(FONT_COLOR_RED"输入错误请重新输入\n"COLOR_NONE);
					while(getchar() != '\n');
				}
		}
		// while(1)
		// {
		// 	printf("大于零继续录入\n");
		// 	// p[i] = malloc(sizeof(struct shop_list));
		// 	scanf("%d",&(p[i].id));
		// 	if((p[i].id) < 0)
		// 		break;
		// 	else if(getchar() != '\n')
		// 	{
		// 		printf("erro,try again");
		// 		while(getchar() != '\n');
		// 	}
		// 	else
		// 		p[i].id = i;
		// }

		while(1)
		{
samename:		
			printf("请输入商品名称！\n");
			scanf("%s",namei);
			if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"输入格式有误（请重新输入）！\n"COLOR_NONE);
				while(getchar() != '\n');
			}
			else
			{
					//////名称重复判断//////
				struct load_shoplist *dataname = lodinglist();
				struct load_shoplist *samedata = locate_node_name_shop(dataname,namei);
				if(samedata != NULL)
				{
					printf(FONT_COLOR_RED"已有同名称商品，请重新录入。\n"COLOR_NONE);
					goto samename;
				}
				strcpy(p[i].name,namei);       
				break;
			}
		}

		while(1)
		{
			printf("请输入商品价格（元）\n");
			scanf("%lf",&(p[i].price));  
			if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"输入格式有误（请重新输入）！\n"COLOR_NONE);
				while(getchar() != '\n');
			}
			else
				break;
		}

		while(1)
		{
			printf("请输入商品折购 （%%）！\n");
			scanf("%lf",&(p[i].discounts));		
			if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"输入格式有误（请重新输入）！\n"COLOR_NONE);
				while(getchar() != '\n');
			}
			else
				break;
		}
		p[i].id = i;
		i++;
		
	}




write_in_file:	
	if(i == 0)
		return i;
	printf(FONT_COLOR_GREEN"你录入了%d件商品\n"COLOR_NONE,i);
	i--;
	int a = i;

    ///////////////录入数据/////////////////////////////		
	FILE *fp;
	fp = fopen("../image/data.txt","ab");
    if(fp == NULL)
	{
		printf("erro:file not find!");
		return 0;
	}
	
	// printf("i:%d\n",i);
	
	for(a;a>=0;a--)
	{
		new = &p[a];
		fwrite(new,sizeof(struct shop_list),1,fp);
		// printf("i:%d\n",i);
	}
	
	fclose(fp);

	return i;
}

/////////////////////载入商品信息///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////载入商品信息///////////////////////////////////////////////////////////////////////////////////////////////
struct load_shoplist * lodinglist(void)
{
	struct load_shoplist *head = init_list();//内核链表头
	struct load_shoplist *new;//内核链表新增

	if(head == NULL)
	{
		printf("list init err!\n");
		return NULL;
	}

	/////////////////////文件打开//////////////////////////
	FILE *fp;
	fp = fopen("../image/data.txt","rb");
	 if(!fp)
	{
		printf("erro:file not find!\n");
		return NULL;
	}
	//////////////////////读取文件到内核链表//////////////////////////
	struct shop_list p[100];
	struct shop_list *new_file = malloc(sizeof(struct shop_list));
	int countid = 1;
	char namecp[30]={0};
	while(1)            
	{
		
		fread(new_file,sizeof(struct shop_list),1,fp);
		new_file->id = countid++;   ///重置id
		if(!strcmp(namecp,new_file->name))
			break;
		else
			strcpy(namecp,new_file->name);/////载入重复中断

		// strncpy(namecp,new_file->name,2);
		new  = init_node(new_file->name,new_file->price,new_file->discounts,new_file->id);
		if(new == NULL)
			{
				printf("new node err!\n");
				return NULL;
			}
		list_add(&(new->my_list), &(head->my_list));
	}



	fclose(fp);

	// show(head);
	return head;
}



///////////////////////删除/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////删除/////////////////////////////////////////////////////////////////////////////////////////

struct load_shoplist * del_shoplist(void)
{
	 int ret;
	 struct load_shoplist *data_shoplist = lodinglist();
	 show(data_shoplist);
	 int del_id;
	 int r;
	 int rret;
	 while(1)
	 {
	 	printf("1.开始删除商品。2.退出。\n");
	 	rret = scanf("%d",&r);
	 	if(rret == 1 && getchar() == '\n')
	 	{
	 		if(r == 1)
	 			break;
	 		else if(r == 2)
	 			return NULL;
	 		else
	 		{
	 			printf(FONT_COLOR_RED"请输入正确指令！\n"COLOR_NONE);
	 			while(getchar() != '\n');
	 		}

	 	}
	 	else
	 	{
	 		printf(FONT_COLOR_RED"请输入正确指令！\n"COLOR_NONE);
	 		while(getchar() != '\n');
	 	}
	 }
	 while(1)
	 {
		 printf("请输入你想要删除商品的id\n");
		 
		 scanf("%d",&del_id);
		 if(getchar() != '\n')
				{
					printf(FONT_COLOR_RED"输入错误请重新输入\n"COLOR_NONE);
					while(getchar() != '\n');
				}
				else
					break;
	}
	 ret = del_node(data_shoplist,del_id);
	 if(ret != 0)
	 	return NULL;
	 // show(data_shoplist);
	 // printf("%d\n",__LINE__ );
	 //////////////////更新链表进文件//////////////////
	char namei[30];
	struct shop_list p[100];
	struct shop_list *new = malloc(sizeof(struct shop_list));
	
	struct load_shoplist *tmp;
	struct list_head *pos;
	int i = 0;

	list_for_each(pos, &(data_shoplist->my_list))
	{
		tmp = list_entry(pos, struct load_shoplist, my_list);
		strcpy(p[i].name,tmp->name);
		p[i].price = tmp->price;
		p[i].discounts = tmp->discounts;
		p[i].id = tmp->id;
		i++;
		
	}
	i--;		
    ////////////////////////写入文件/////////////////////
	FILE *fp;
	fp = fopen("../image/data.txt","wb");
    if(fp == NULL)
	{
		printf("erro:file not find!");
		return NULL;
	}
	
	// printf("i:%d\n",i);
	
	for(i;i>=0;i--)
	{
		new = &p[i];
		fwrite(new,sizeof(struct shop_list),1,fp);
		// printf("i:%d\n",i);
	}
	
	fclose(fp);

	 return NULL;
}

////////////////展现商品/////////////////////////
int show_shoplist(void)
{
	struct load_shoplist *data_shoplist = lodinglist();
	show(data_shoplist);
	 return 0;
	
}

//////////////////////修改折购或价格////////////////////////////////////////////////////////////////////////////////
//////////////////////修改折购或价格///////////////////////////////////////////////////////////////////////////////
struct load_shoplist * modify_data(void)
{
	 struct load_shoplist *data_shoplist = lodinglist();
	 struct load_shoplist *modify_node;
	 show(data_shoplist);
	 
	 int modify_id;
	 int order;
	 
	 int r;
	 int rret;
	 while(1)
	 {
	 	printf("1.开始修改商品信息。2.退出。\n");
	 	rret = scanf("%d",&r);
	 	if(rret == 1 && getchar() == '\n')
	 	{
	 		if(r == 1)
	 			break;
	 		else if(r == 2)
	 			return NULL;
	 		else
	 		{
	 			printf(FONT_COLOR_RED"请输入正确指令！\n"COLOR_NONE);
	 			while(getchar() != '\n');
	 		}

	 	}
	 	else
	 	{
	 		printf(FONT_COLOR_RED"请输入正确指令！\n"COLOR_NONE);
	 		while(getchar() != '\n');
	 	}
	 }
	// printf("请输入你想要修改的商品id\n");
	 while(1)
		{
			printf("请输入你想要修改的商品id\n");
			scanf("%d",&modify_id);		
			if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"输入有误，请重新输入！"COLOR_NONE);
				while(getchar() != '\n');
			}
			else
				break;
		}
		modify_node = locate_node(data_shoplist,modify_id);
		if(modify_node == NULL)
			return NULL;
modifyinser:	 
	 printf("请输入你想要修改的内容:修改价格请输入1，修改折购请输入2。\n");
	  while(1)
		{
			scanf("%d",&order);		
			if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"输入有误，请重新输入！"COLOR_NONE);
				while(getchar() != '\n');
			}
			else
				break;
		}
	double modp;
	if(order == 1)
	{
		printf("请输入修改后的价格：");
		
		  while(1)
		{
			scanf("%lf",&modp);		
			if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"输入有误，请重新输入！"COLOR_NONE);
				while(getchar() != '\n');
			}
			else
				break;
		}
		modify_node->price = modp;
	}
	else if(order == 2)
	{
		printf("请输入修改后的折购：");
		while(1)
		{
			scanf("%lf",&modp);		
			if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"输入有误，请重新输入！"COLOR_NONE);
				while(getchar() != '\n');
			}
			else
				break;
		}
		modify_node->discounts = modp;
	
	}
	else
	{
		printf(FONT_COLOR_RED"输入有误，请重新输入\n"COLOR_NONE);
		goto modifyinser;
	}
	 // show(data_shoplist);

	 //////////////////更新链表进文件//////////////////
	char namei[30];
	struct shop_list p[100];
	struct shop_list *new = malloc(sizeof(struct shop_list));
	
	struct load_shoplist *tmp;
	struct list_head *pos;
	int i = 0;

	list_for_each(pos, &(data_shoplist->my_list))
	{
		tmp = list_entry(pos, struct load_shoplist, my_list);
		strcpy(p[i].name,tmp->name);
		p[i].price = tmp->price;
		p[i].discounts = tmp->discounts;
		p[i].id = tmp->id;
		i++;
		
	}
	i--;		
////////////////////////////写入文件///////////////////
	FILE *fp;
	fp = fopen("../image/data.txt","wb");
    if(fp == NULL)
	{
		printf("erro:file not find!");
		return NULL;
	}
	
	// printf("i:%d\n",i);
	
	for(i;i>=0;i--)
	{
		new = &p[i];
		fwrite(new,sizeof(struct shop_list),1,fp);
		// printf("i:%d\n",i);
	}
	
	fclose(fp);
	printf(FONT_COLOR_GREEN"修改成功！\n"COLOR_NONE);
	 return NULL;
}
/////////////////////////////查找商品/////////////////////
/////////////////////////////查找商品/////////////////////
/////////////////////////////查找商品/////////////////////
/////////////////////////////查找商品/////////////////////
int findshoplist(void)
{
	 struct load_shoplist *head = lodinglist();
	 char namef[30];
	 int retname;
rery:
	 while(1)
	 {
	 	printf("请出入你想要查找的商品名称：\n");
	 	retname = scanf("%s",namef);
	 	if(retname == 1 && getchar() == '\n')
	 	{
	 		break;
	 	}
	 	else
	 	{
	 		printf(FONT_COLOR_RED"输入格式有误（请重新输入）！\n"COLOR_NONE);
	 		while(getchar() != '\n');

	 	}
	 }

	 struct load_shoplist * tmp = locate_node_name_shop(head,namef);
	 if(tmp == NULL)
	 {
	 	printf(FONT_COLOR_RED"没有此商品！\n"COLOR_NONE);
	 	int ip;
	int ipret;
erro:
	while(1)
	{
		printf("1.重新输入。2.退出。\n");

		printf("请输入操作指令：\n");
		ipret = scanf("%d",&ip);
		if(ipret == 1 && getchar() == '\n')
		{	
			switch (ip)
			{
				case 1:goto rery;
				case 2:return 0;
				default :printf(FONT_COLOR_RED"请输入正确指令！(回车继续)\n"COLOR_NONE);while(getchar() != '\n');goto erro;
			}
			break;


		}
		else
		{
			printf(FONT_COLOR_RED"输入指令错误，请重新输入！\n"COLOR_NONE);
			while(getchar() != '\n');
		}

	}
	 }

	 printf(FONT_COLOR_GREEN"你要查找的商品 ID：%4d 名称：%-15s 单价:%6.2lf元 折购:%6.2lf\n"COLOR_NONE,tmp->id,tmp->name,tmp->price,tmp->discounts);




	return 0;
}


/////////////////////////账户设置//////////////////
/////////////////////////账户设置//////////////////
/////////////////////////账户设置//////////////////
/////////////////////////账户设置//////////////////
/////////////////////////账户设置//////////////////
/////////////////////////账户设置//////////////////
/////////////////////////账户设置//////////////////
/////////////////////////账户设置//////////////////
//////////////////账户结构体////////////////////////////////

///////////////////创建账户写入TXT/////////////////////////////////////////////////
///////////////////创建账户写入TXT/////////////////////////////////////////////////
int createacount(void)
{
	char name[50];
	char password[50];
	char password1[50];
	char question[50];
	char key[50];
	struct acontlist *new = malloc(sizeof(struct acontlist));
	char i;
	
name:
	while(1)
	{
		printf("请输入你想要的账号名称：\n");
		scanf("%s", name);
		if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
				while(getchar() != '\n');
			}
		else
		{
			printf("你输入的用户名称为：%s\n", name);
			while(1)
			{
				printf(FONT_COLOR_YELLOW"是否采用这个名称？y or n\n"COLOR_NONE);
				scanf("%c", &i);
				if(getchar() != '\n')
				{
					printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
					while(getchar() != '\n');
				}
				else
				{	
					if(i == 'y')
					{
						// strcpy(new->name,name);
							struct load_acountlist *head = lodingacount();
							int nameret = locate_node_name(head,name);
							// printf("%d\n",__LINE__ );
							// show_acount(head);
							if(nameret == 0)
							{
								printf(FONT_COLOR_RED"输入的用户名重复，请重新设置！\n"COLOR_NONE);
								goto name;
							}
						goto password;
					}
					else if(i == 'n')
						break;
				}

				
			}

		}

	}



password:



	while(1)
	{
		printf("请输入你的密码：\n");
		scanf("%s", password);
		if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
				while(getchar() != '\n');
			}
		else
		{
			printf("请输入多一次你的密码：\n");
			scanf("%s",password1);
			if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
				while(getchar() != '\n');
			}
			else
				break;
		}


	}

	int ret;
	ret =  strcmp(password,password1);
	if(ret != 0)
	{
		printf(FONT_COLOR_RED"两次密码输入不同，请重新输入\n"COLOR_NONE);
		goto password;
	}

	else
		strcpy(new->password, password);



question:
	
	while(1)
	{
		printf("请输入你的密保问题：（用于密码找回）\n");
		scanf("%s",question);
		if(getchar() != '\n')
		{
			printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
			while(getchar() != '\n');
		}
		else
		{
err1:			printf("你输入的密保问题为：%s\n",question );
			printf(FONT_COLOR_YELLOW"是否采用这个问题？（输入y确认，输入n重新输入）\n"COLOR_NONE);
				scanf("%c", &i);
				if(getchar() != '\n')
				{
					printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
					while(getchar() != '\n');
				}
				else
				{	
					if(i == 'y')
					{
						// strcpy(new->question,question);
						break;
					}
					else if(i == 'n')
					{
							goto question;
					}
					else
					{
						printf(FONT_COLOR_RED"指令输入错误(回车继续操作)\\n"COLOR_NONE);
						while(getchar() != '\n');
						goto err1;
					}
				}

		}
	}
key:
while(1)
	{
		printf("请输入你的密保问题答案：\n");
		scanf("%s",key);
		if(getchar() != '\n')
		{
			printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
			while(getchar() != '\n');
		}
		else
		{
			printf("你输入的密保问题的答案为：%s\n",key );
err2:			printf(FONT_COLOR_YELLOW"是否采用这个答案？（输入y确认，输入n重新输入）\n"COLOR_NONE);
				scanf("%c", &i);
				if(getchar() != '\n')
				{
					printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
					while(getchar() != '\n');
				}
				else
				{	
					if(i == 'y')
					{
						// strcpy(new->key,key);
						break;
					}
					else if(i == 'n')
					{
							goto key;
					}
					else
					{
						printf(FONT_COLOR_RED"指令输入错误(回车继续操作)\\n"COLOR_NONE);
						while(getchar() != '\n');
						goto err2;
					}
				}

		}
	}
	
	printf(FONT_COLOR_QINGSE"账号创建成功！\n"COLOR_NONE);
	printf("请牢记你的账号信息!\n");
err3:	printf("是否需要再次查看你的账号信息？（y or n）\n");
	scanf("%c", &i);
		while(1)
		{
			if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
				while(getchar() != '\n');
			}
			else if(i == 'y')
			{
				printf("你的用户名为  ：%s\n", name);
				printf(FONT_COLOR_GREEN"你的密码为    ：%s\n"COLOR_NONE, password);
				printf("你的密保问题为：%s\n", question);
				printf(FONT_COLOR_GREEN"你的密码答案为：%s\n"COLOR_NONE, key);
				break;
			}
			else if(i == 'n')
			{
				break;
			}
			else
					{
						printf(FONT_COLOR_RED"指令输入错误(回车继续操作)\n"COLOR_NONE);
						while(getchar() != '\n');
						goto err3;
					}
		}


	strcpy(new->name,name);
	strcpy(new->password,password);
	strcpy(new->question,question);
	strcpy(new->key,key);
	new->id = 0;

		
	//////////////////////录入信息到文件/////////////////////
	FILE *fp;
	fp = fopen("../image/acount.txt","ab");
    if(fp == NULL)
	{
		printf("erro:file not find!");
		return 0;
	}

	fwrite(new,sizeof(struct acontlist),1,fp);

	fclose(fp);
	printf("写入成功\n");

	return 0;
}

//////////////////////////载入账户信息////////////////////////////////////////////////
//////////////////////////载入账户信息////////////////////////////////////////////////

struct load_acountlist *lodingacount(void)
{
	struct load_acountlist *head = init_list_acount();//内核链表头
	struct load_acountlist *new;//内核链表新增

	if(head == NULL)
	{
		printf("list init err!\n");
		return NULL;
	}

	///////////////////文件打开//////////////////////////
	FILE *fp;
	fp = fopen("../image/acount.txt","rb");
	 if(!fp)
	{
		printf("erro:file not find!\n");
		return NULL;
	}
	//////////////////////读取文件到内核链表//////////////////////////
	struct acontlist p[100];
	struct acontlist *new_file = malloc(sizeof(struct acontlist));
	int countid = 1;
	char namecp[30]={0};
	int turn;
	while(1)            
	{
		
		fread(new_file,sizeof(struct acontlist),1,fp);
		new_file->id = countid++;   ///重置id
		if(!strcmp(namecp,new_file->name))
			break;
		else
			strcpy(namecp,new_file->name);/////载入重复中断

		// strncpy(namecp,new_file->name,2);
		new  = init_node_acount(new_file->name,new_file->password,new_file->question,new_file->key,new_file->id);
		if(new == NULL)
			{
				printf("new node err!\n");
				return NULL;
			}
		list_add(&(new->my_list), &(head->my_list));
	}



	fclose(fp);

	// show_acount(head);
	return head;

}

/////////////////展示账户信息///////////////////////
int show_acountlist(void)
{
	struct load_acountlist *head = lodingacount();
	show_acount(head);
	return 0;
}

/////////////////删除账户信息///////////////////////
struct load_acountlist * del_acountlist(void)
{
	 int ret;
	 struct load_acountlist *data = lodingacount();
	 show_acount(data);
	 int del_id;

	 int r;
	 int rret;
	 while(1)
	 {
	 	printf("1.开始删除用户信息。2.退出。\n");
	 	rret = scanf("%d",&r);
	 	if(rret == 1 && getchar() == '\n')
	 	{
	 		if(r == 1)
	 			break;
	 		else if(r == 2)
	 			return NULL;
	 		else
	 		{
	 			printf(FONT_COLOR_RED"请输入正确指令！(回车继续操作)\n"COLOR_NONE);
	 			while(getchar() != '\n');
	 		}

	 	}
	 	else
	 	{
	 		printf(FONT_COLOR_RED"请输入正确指令！(回车继续操作)\n"COLOR_NONE);
	 		while(getchar() != '\n');
	 	}
	 }


	 while(1)
	 {
		printf("请输入你想要删除用户的id\n");
		 
		 scanf("%d",&del_id);
		 if(getchar() != '\n')
				{
					printf(FONT_COLOR_RED"输入错误请重新输入\n"COLOR_NONE);
					while(getchar() != '\n');
				}
				else
					break;
	}
	struct load_acountlist *locatedel = 
	locate_node_acount(data,del_id);
	if(locatedel == NULL)
		return NULL;
	// ret = strcmp(locatedel->name ,"admin");
	if(locatedel->id == 1)
	{
		printf(FONT_COLOR_RED"无法删除管理员账户！\n"COLOR_NONE);
		return NULL;
	}

	del_node_acount(data,del_id);

	write_acount_txt(data);
	// printf(FONT_COLOR_GREEN"删除成功！\n"COLOR_NONE);
	return NULL;	//  //////////////////更新链表进文件//////////////////
	// char namei[30];
	// struct acontlist p[100];
	// struct acontlist *new = malloc(sizeof(struct acontlist));
	
	// struct load_acountlist *tmp;
	// struct list_head *pos;
	// int i = 0;

	// list_for_each(pos, &(data->my_list))
	// {
	// 	tmp = list_entry(pos, struct load_acountlist, my_list);
	// 	strcpy(p[i].name,tmp->name);
	// 	strcpy(p[i].password,tmp->password);
	// 	strcpy(p[i].question,tmp->question);
	// 	strcpy(p[i].key,tmp->key);
	// 	p[i].id = tmp->id;
	// 	i++;
		
	// }
	// i--;		
 //    ////////////////////////写入文件/////////////////////////
	// FILE *fp;
	// fp = fopen("acount.txt","wb");
 //    if(fp == NULL)
	// {
	// 	printf("erro:file not find!");
	// 	return NULL;
	// }
	
	// // printf("i:%d\n",i);
	
	// for(i;i>=0;i--)
	// {
	// 	new = &p[i];
	// 	fwrite(new,sizeof(struct acontlist),1,fp);
	// 	// printf("i:%d\n",i);
	// }
	
	// fclose(fp);

	//  return NULL;
}


///////////////////////////登录帮助///////////////////////////////////////////////
///////////////////////////登录帮助///////////////////////////////////////////////
int acounthelp(void)
{
	int a;
	int ret;
	while(1)
	{
		printf(FONT_COLOR_GREEN"登录帮助：1.修改密码。2.找回密码。3.修改用户名。4.退出帮助。\n"COLOR_NONE);
		ret = scanf("%d", &a);
		if(ret == 1 && getchar() == '\n')
		{
			if(a == 1)
			{
				password_mod();
			}
			else if(a == 2)
			{
				findyourpassword();
			}
			else if(a == 3)
			{
				name_mod();
			}
			else if(a == 4)
				return 0;
			else
			{
				printf(FONT_COLOR_RED"请输入正确的指令！\n"COLOR_NONE);
			}
		}
		else
		{
			printf(FONT_COLOR_RED"输入有误，请重新输入！\n"COLOR_NONE);
			while(getchar() != '\n');
		}

	}
	

	return 0;
}

///////////////////////////修改密码///////////////////////////////////////////////
///////////////////////////修改密码///////////////////////////////////////////////
int password_mod(void)
{
	struct load_acountlist *data = lodingacount();
	struct load_acountlist *modify_node;
	char name[30];
	int ret;
	int retry;
	char password[30];
	
	int passwordcom;
	int passwordret;
	int paret;

retryname:
	while(1)
	{
		printf("请输入你的用户名称：\n");
		ret = scanf("%s", name);
		if(ret == 1 && getchar() == '\n')
			break;
		else
		{
			printf(FONT_COLOR_RED"你的输入格式有错误，请重新输入！\n"COLOR_NONE);
			while(getchar() != '\n');
		}
	}

	modify_node =locate_resign_name(data,name);

	if(modify_node == NULL)
	{
		printf(FONT_COLOR_RED"对不起，没有此用户。\n"COLOR_NONE);
		
		while(1)
		{
			printf("1.重新输入。2.退出帮助。\n");
			ret = scanf("%d", &retry);
			if(ret == 1 && getchar() == '\n')
			{
				if(retry == 1)
				{
					goto retryname;
				}
				else if(retry == 2)
				{
					return 0;
				}
				else
				{
					printf(FONT_COLOR_RED"请输入正确的指令！\n"COLOR_NONE);
				}
			}
			else
			{
				printf(FONT_COLOR_RED"输入有误，请重新输入！\n"COLOR_NONE);
				while(getchar() != '\n');
			}

		}

	}
	else
	{
rep:		//////////////旧密码输入/////////////////
		while(1)
		{
			printf("请输入你的旧密码：\n");
			ret = scanf("%s", password);
			if(ret == 1 && getchar() == '\n')
				break;
			else
			{
				printf(FONT_COLOR_RED"你的输入格式有错误，请重新输入！\n"COLOR_NONE);
				while(getchar() != '\n');
			}
		}
		/////////////密码匹配////////////////////
		passwordcom = strcmp(modify_node->password,password);
		if(passwordcom != 0)
		{
			printf(FONT_COLOR_RED"你输入的密码错误！\n"COLOR_NONE);
			while(1)
			{
				printf("1.重新输入。2.返回帮助。\n");
				paret = scanf("%d",&passwordret);
				if(paret == 1 && getchar() == '\n')
				{
					if(passwordret == 1)
						{
							goto rep;
						}
					else if(passwordret == 2)
						{
							return 0;
						}
					else
						{
							printf(FONT_COLOR_RED"请输入正确的指令！\n"COLOR_NONE);
						}
				}
				else
				{
					printf(FONT_COLOR_RED"输入有误，请重新输入！\n"COLOR_NONE);
					while(getchar() != '\n');
				}

			}
		}




	}

	/////////////////////录入新密码////////////////
		int passret;
		int passret2;
		char password2[30];
		char password3[30];

passwordfort:

while(1)
	{
		printf("请输入你的新密码：\n");
		passret = scanf("%s", password2);
		if(passret == 1 && getchar() == '\n')
			{
				while(1)
				{
					printf("请再输入一次你的密码：\n");
					passret2 = scanf("%s",password3);
					if(passret2 == 1 && getchar() == '\n')
						break;
					else
					{
						printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
						while(getchar() != '\n');
					}
				}
				break;

			}
		else
			{
				printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
				while(getchar() != '\n');
			}


	}

	int retforp;
	retforp =  strcmp(password2,password3);
	if(retforp != 0)
	{
		printf(FONT_COLOR_RED"两次密码输入不同，请重新输入\n"COLOR_NONE);
		goto passwordfort;
	}
	else
		strcpy(modify_node->password, password2);




    ///////////////////重新录入文件/////////////////////
	write_acount_txt(data);
	printf(FONT_COLOR_GREEN"修改成功！\n"COLOR_NONE);
	return 0;
}


///////////////////////////////////录入文件//////////////////////
///////////////////////////////////录入文件//////////////////////
///////////////////////////////////录入文件//////////////////////
///////////////////////////////////录入文件//////////////////////
///////////////////////////////////录入文件//////////////////////
 int write_acount_txt(struct load_acountlist *head)
 {
 
 	struct acontlist ap[100];
 	// show_acount(head);
	struct acontlist *new = malloc(sizeof(struct acontlist));
 	
 	struct load_acountlist *tmp;
	struct list_head *pos;
 	int i = 0;
 	list_for_each(pos, &(head->my_list))
	{
		tmp = list_entry(pos, struct load_acountlist, my_list);
		strcpy(ap[i].name, tmp->name);
		strcpy(ap[i].password, tmp->password);
		strcpy(ap[i].question, tmp->question);
		strcpy(ap[i].key, tmp->key);
		ap[i].id = tmp->id;
		i++;
		
	}
	i--;




	FILE *p;
	 	p = fopen("../image/acount.txt","wb");
	 	if(p == NULL)
	 	{
	 		printf("文件打开失败!\n");
	 		return 0;
	 	}

	for(i;i>=0;i--)
		{
			new = &ap[i];
			fwrite(new,sizeof(struct acontlist),1,p);
			// printf("i:%d\n",i);
		}
	
	fclose(p);
	printf(FONT_COLOR_GREEN"写入数据成功！\n"COLOR_NONE);



 	return 0;
 }

//////////////////////////////找回密码///////////////////////////////
//////////////////////////////找回密码///////////////////////////////
//////////////////////////////找回密码///////////////////////////////
//////////////////////////////找回密码///////////////////////////////
//////////////////////////////找回密码///////////////////////////////
//////////////////////////////找回密码///////////////////////////////
int findyourpassword(void)
{
	struct load_acountlist *data = lodingacount();
	struct load_acountlist *modify_node;
	char name[30];
	int ret_name;
	char question1[30];
	char key[30];

	int ret_que;
retryfname:
	while(1)   /////////匹配用户
	{
		printf("请输入你的用户名：\n");
		ret_name = scanf("%s",name);
		if(ret_name == 1 && getchar() == '\n')
			break;
		else
		{
			printf(FONT_COLOR_RED"你的输入格式有错误，请重新输入！\n"COLOR_NONE);
			while(getchar() != '\n');
		}

	}

	modify_node =locate_resign_name(data,name);
	int ret_mod;
	int retry;
	if(modify_node == NULL)
	{
		printf(FONT_COLOR_RED"对不起，没有此用户。\n"COLOR_NONE);
		
		while(1)
		{
			printf("1.重新输入。2.退出帮助。\n");
			ret_mod = scanf("%d", &retry);
			if(ret_mod == 1 && getchar() == '\n')
			{
				if(retry == 1)
				{
					goto retryfname;
				}
				else if(retry == 2)
				{
					return 0;
				}
				else
				{
					printf(FONT_COLOR_RED"请输入正确的指令！\n"COLOR_NONE);
				}
			}
			else
			{
				printf(FONT_COLOR_RED"输入有误，请重新输入！\n"COLOR_NONE);
				while(getchar() != '\n');
			}

		}

	}
	else   /////////////////匹配密保问题///////////
	{
retrykey:
		printf("你的密保问题为：%s\n",modify_node->question);
		while(1)
		{
			printf("请输入你的答案：\n");
			ret_que = scanf("%s",key);
			if(ret_que == 1 && getchar() == '\n')
				break;
			else
			{
				printf(FONT_COLOR_RED"你的输入格式有错误，请重新输入！\n"COLOR_NONE);
				while(getchar() != '\n');
			}

		}

	}
		////////////////密保答案匹配////////////////
	int ret_comque = strcmp(key,modify_node->key);
	int rety_key;
	int ret_key;
	if(ret_comque != 0)
		{
			printf(FONT_COLOR_RED"你输入的答案错误！\n"COLOR_NONE);
			while(1)
			{
				printf("1.重新输入。2.返回帮助。\n");
				ret_key = scanf("%d",&rety_key);
				if(ret_key == 1 && getchar() == '\n')
				{
					if(rety_key == 1)
						{
							goto retrykey;
						}
					else if(rety_key == 2)
						{
							return 0;
						}
					else
						{
							printf(FONT_COLOR_RED"请输入正确的指令！\n"COLOR_NONE);
						}
				}
				else
				{
					printf(FONT_COLOR_RED"输入有误，请重新输入！\n"COLOR_NONE);
					while(getchar() != '\n');
				}

			}
		}

		/////////录入新密码///////////
int passret;
		int passret2;
		char password2[30];
		char password3[30];

passwordfort:

while(1)
	{
		printf("请输入你的新密码：\n");
		passret = scanf("%s", password2);
		if(passret == 1 && getchar() == '\n')
			{
				while(1)
				{
					printf("请再输入一次你的密码：\n");
					passret2 = scanf("%s",password3);
					if(passret2 == 1 && getchar() == '\n')
						break;
					else
					{
						printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
						while(getchar() != '\n');
					}
				}
				break;

			}
		else
			{
				printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
				while(getchar() != '\n');
			}


	}

	int retforp;
	retforp =  strcmp(password2,password3);
	if(retforp != 0)
	{
		printf("两次密码输入不同，请重新输入\n");
		goto passwordfort;
	}
	else
		strcpy(modify_node->password, password2);




    ///////////////////重新录入文件/////////////////////
	write_acount_txt(data);


printf(FONT_COLOR_GREEN"修改成功！\n"COLOR_NONE);




	return 0;
}
////////////////////修改用户名////////////////////
////////////////////修改用户名////////////////////
////////////////////修改用户名////////////////////
////////////////////修改用户名////////////////////
////////////////////修改用户名////////////////////
int name_mod(void)
{
	struct load_acountlist *data = lodingacount();
	struct load_acountlist *modify_node;
	char name[30];
	int ret;
	int retry;
	char password[30];
	
	int passwordcom;
	int passwordret;
	int paret;

retryname:
	while(1)
	{
		printf("请输入你的用户名称：\n");
		ret = scanf("%s", name);
		if(ret == 1 && getchar() == '\n')
			break;
		else
		{
			printf(FONT_COLOR_RED"你的输入格式有错误，请重新输入！\n"COLOR_NONE);
			while(getchar() != '\n');
		}
	}

	modify_node =locate_resign_name(data,name);

	if(modify_node == NULL)
	{
		printf(FONT_COLOR_RED"对不起，没有此用户。\n"COLOR_NONE);
		
		while(1)
		{
			printf("1.重新输入。2.退出帮助。\n");
			ret = scanf("%d", &retry);
			if(ret == 1 && getchar() == '\n')
			{
				if(retry == 1)
				{
					goto retryname;
				}
				else if(retry == 2)
				{
					return 0;
				}
				else
				{
					printf(FONT_COLOR_RED"请输入正确的指令！\n"COLOR_NONE);
				}
			}
			else
			{
				printf(FONT_COLOR_RED"输入有误，请重新输入！\n"COLOR_NONE);
				while(getchar() != '\n');
			}

		}

	}
	else
	{
rep:		//////////////密码输入/////////////////
		while(1)
		{
			printf("请输入你的密码：\n");
			ret = scanf("%s", password);
			if(ret == 1 && getchar() == '\n')
				break;
			else
			{
				printf(FONT_COLOR_RED"你的输入格式有错误，请重新输入！\n"COLOR_NONE);
				while(getchar() != '\n');
			}
		}
		/////////////密码匹配////////////////////
		passwordcom = strcmp(modify_node->password,password);
		if(passwordcom != 0)
		{
			printf(FONT_COLOR_RED"你输入的密码错误！\n"COLOR_NONE);
			while(1)
			{
				printf("1.重新输入。2.返回帮助。\n");
				paret = scanf("%d",&passwordret);
				if(paret == 1 && getchar() == '\n')
				{
					if(passwordret == 1)
						{
							goto rep;
						}
					else if(passwordret == 2)
						{
							return 0;
						}
					else
						{
							printf(FONT_COLOR_RED"请输入正确的指令！\n"COLOR_NONE);
						}
				}
				else
				{
					printf(FONT_COLOR_RED"输入有误，请重新输入！\n"COLOR_NONE);
					while(getchar() != '\n');
				}

			}
		}




	}

	/////////////////////录入新用户名////////////////
	char newname[30];
	char i;
	while(1)
	{
name:		
		printf("请输入你想要的账号名称：\n");
		scanf("%s", newname);
		if(getchar() != '\n')
			{
				printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
				while(getchar() != '\n');
			}
		else
		{
			printf("你输入的用户名称为：%s\n", newname);
			while(1)
			{
				printf("是否采用这个名称？（输入y确认，输入n重新输入）\n");
				scanf("%c", &i);
				if(getchar() != '\n')
				{
					printf(FONT_COLOR_RED"格式错误（例如不能存在空格）\n"COLOR_NONE);
					while(getchar() != '\n');
				}
				else
				{	
					if(i == 'y')
					{
						
							struct load_acountlist *head = lodingacount();
							int nameret = locate_node_name(head,newname);
							if(nameret == 0)
							{
								printf(FONT_COLOR_RED"输入的用户名重复，请重新设置！\n"COLOR_NONE);
								goto name;
							}
						strcpy(modify_node->name,newname);
						goto writein_name;
					}
					else if(i == 'n')
						break;
				}

				
			}

		}

	}
		
writein_name:		
    ///////////////////重新录入文件/////////////////////
	write_acount_txt(data);
	printf(FONT_COLOR_GREEN"修改成功！\n"COLOR_NONE);
	return 0;
	
}







///////////////////登录账号///////////////////
///////////////////登录账号///////////////////
///////////////////登录账号///////////////////
///////////////////登录账号///////////////////
///////////////////登录账号///////////////////
///////////////////登录账号///////////////////
///////////////////登录账号///////////////////
///////////////////登录账号///////////////////
///////////////////登录账号///////////////////
int loginacount (void)
{
	struct load_acountlist *data = lodingacount();
	struct load_acountlist *acount;
	char name[30];
	int retname;
	char password[30];

			///////////输入用户名///////////
retryname:
	while(1)
	{
		printf("请输入你的用户名：");
		retname = scanf("%s",name);
		if(retname == 1 && getchar() == '\n')
			break;
		else
		{
			printf(FONT_COLOR_RED"输入格式有误（请重新输入）！\n"COLOR_NONE);
			while(getchar() != '\n');
		}


	}

	int retry_name;
	int retret;
	acount = locate_resign_name(data,name);
	
	if(acount == NULL)
	{
		printf(FONT_COLOR_RED"没有此用户\n"COLOR_NONE);
		while(1)
		{
			printf("1.重新输入。2.进入用户帮助。3.退出。\n");
			// printf("%d\n",__LINE__ );
			retret = scanf("%d",&retry_name);

			switch (retry_name)
			{
				case 1 : goto retryname;

				case 2 : return -2;

				case 3 : return 0;

				default :printf(FONT_COLOR_RED"输入指令错误！\n"COLOR_NONE);while(getchar() != '\n');break;
			}
		}
	}
retrypassword:
			///////////输入密码///////////
		while(1)
		{
			printf("请输入你的用户密码：");
			retname = scanf("%s",password);
			if(retname == 1 && getchar() == '\n')
				break;
			else
			{
				printf(FONT_COLOR_RED"输入格式有误（请重新输入）！\n"COLOR_NONE);
				while(getchar() != '\n');
			}


		}

	int passwordcom;
	passwordcom = strcmp(acount->password,password);
	int retry_password;
	int ret_password;
	int admincom;
	admincom = strcmp(name,"admin");

	if(passwordcom != 0)
	{
		printf(FONT_COLOR_RED"密码错误！\n"COLOR_NONE);
		while(1)
		{
			printf("1.重新输入。2.进入用户帮助。3.退出。\n");
			ret_password = scanf("%d",&retry_password);

			switch (retry_password)
			{
				case 1 : goto retrypassword;

				case 2 : return -2;

				case 3 : return 0;

				default :printf(FONT_COLOR_RED"输入指令错误！\n"COLOR_NONE);while(getchar() != '\n');break;
			}
		}
	}
	else
	{
		/////////////用户登录记录/////////////
		FILE *namep;
		namep = fopen("../image/working.txt","wb");
		if(namep == NULL)
		{
			printf("登录用户记录文件丢失！请重新尝试！\n");
			return 0;
		}
		fwrite(acount->name,sizeof(acount->name),1,namep);
		fclose(namep);
		// printf("id:%ld\n",sizeof(acount->name) );
		/////////////返回登录用户种类////////////
		printf(FONT_COLOR_GREEN"登陆成功！\n"COLOR_NONE);
		if(acount->id == 1)
		{
			printf("管理员你好！\n");
			return 10;
		}
		else
		{
			printf("%s你好！\n",name);
			return 11;
		}
	}



}


///////////////////用户空间////////////////////////////
///////////////////用户空间////////////////////////////
///////////////////用户空间////////////////////////////
///////////////////用户空间////////////////////////////
///////////////////用户空间////////////////////////////
///////////////////用户空间////////////////////////////
///////////////////用户空间////////////////////////////
///////////////////用户空间////////////////////////////
///////////////////用户空间////////////////////////////
///////////////////用户空间////////////////////////////


/////////////////////用户购物车文件创建//////////////////////////////
/////////////////////用户购物车文件创建//////////////////////////////
/////////////////////用户购物车文件创建//////////////////////////////
/////////////////////用户购物车文件创建//////////////////////////////
int creatshoptxt(void)
{
	struct load_acountlist *data = lodingacount();

	struct load_acountlist *tmp;
	struct list_head *pos, *n;
	FILE *fp;
	char adss[80] = {"../image/"};

	list_for_each_safe(pos, n, &(data->my_list))
	{
		
		tmp = list_entry(pos, struct load_acountlist, my_list);
		strcpy(adss,"../image/");
		strcat(adss,tmp->name);
		fp = fopen(adss,"a+");
		if(fp == NULL)
		{
			printf("创建购物车文件失败！\n");
			return 0;
		}
		fclose(fp);
	}




	return 0;
}
//////////////////////////////获取当前账户////////////////////
//////////////////////////////获取当前账户////////////////////
//////////////////////////////获取当前账户////////////////////
//////////////////////////////获取当前账户////////////////////
// char *runningname(void)
// {
// 	char name[50];
// 	FILE *p;
// 	p = fopen("working.txt","rb");
// 	fread(name,50,1,p);
// 	// printf("%s\n",name );
// 	fclose(p);
// 	return &name;

// }



int prit(char *name)
{

	printf("%s\n", name);


	return 0;
}

/////////////////////////用户读取商品/////////////////////////////
///////////////////////用户读取商品/////////////////////////////
struct load_shoplist *showshoptou(void)
{
	// struct load_shoplist *head = show_shoplist();
	struct load_shoplist *data_shoplist = lodinglist();
	// show(head);
	// show_shoplist();
	return data_shoplist;
}
//////////////////用户查看商品///////////////////////
//////////////////用户查看商品///////////////////////
//////////////////用户查看商品///////////////////////
int usershow(struct load_shoplist *head)
{
	show(head);
	return 0;

}



//////////////////////用户商品总数////////////////
//////////////////////用户商品总数////////////////
//////////////////////用户商品总数////////////////
//////////////////////用户商品总数////////////////
int maxshoplist(struct load_shoplist *head)
{
	struct load_shoplist *tmp;
	struct list_head *pos;
	int i = 0;
	list_for_each(pos, &(head->my_list))
	//for (pos = (head)->next; pos != (head);pos = pos->next)
	{
		tmp = list_entry(pos, struct load_shoplist, my_list);
		i++;

		
	}
	return i;
}
//////////////////用户选择商品到购物车/////////////////
//////////////////用户选择商品到购物车/////////////////
//////////////////用户选择商品到购物车/////////////////
int shopcar_in(int max,char *name,struct load_shoplist *head)
{
	// printf("%s\n",name );
	usershow(head);
	int id;
	int retid;
	while(1)
	{
		printf("请输入商品ID：\n");
		retid = scanf("%d",&id);
		if(retid == 1 && getchar() == '\n')
		{
			if(id < 0 || id >max )
			{
				printf(FONT_COLOR_RED"请输入正确的商品ID（如:1）\n"COLOR_NONE);
				continue;
			}
			else
				break;
		}
		else
		{
			printf(FONT_COLOR_RED"请输入正确的商品ID（如:1）\n"COLOR_NONE);
			while(getchar() != '\n');
		}

	}

	int m;
	int retm;
	while(1)
	{
		printf("请输入商品购买数量：\n");
		retm = scanf("%d",&m);
		if(retm == 1 && getchar() == '\n')
		{
			if(m < 0 )
			{
				printf("请输入正确的数量！\n");
				continue;
			}
			else
				break;
		}
		else
		{
			printf(FONT_COLOR_RED"请输入正确的数量！\n"COLOR_NONE);
			while(getchar() != '\n');
		}

	}
	struct load_shoplist *data = locate_node(head, id);
	printf(FONT_COLOR_GREEN"购买数量为%d\n"COLOR_NONE,m );

	struct shopcar *newshop = malloc(sizeof(struct shopcar));
	strcpy(newshop->name,data->name);
	newshop->price = data->price;
	newshop->discounts = data->discounts;
	newshop->m = m;
	newshop->id = id;
	newshop->mp = m * data->price * (data->discounts /100);

	char adss[80] = {"../image/"};
	strcat(adss,name);
	FILE *l;
	l = fopen(adss,"at");
	if(l == NULL)
	{
		printf(FONT_COLOR_RED"加入购物车失败！\n"COLOR_NONE);
		return 0;
	}

	fwrite(newshop,sizeof(struct shopcar),1,l);
	printf(FONT_COLOR_GREEN"加入购物车成功！\n"COLOR_NONE);
	fclose(l);
	return 0;
}

//////////////////////////////载入用户购物车列表///////////////
//////////////////////////////载入用户购物车列表///////////////
//////////////////////////////载入用户购物车列表///////////////
//////////////////////////////载入用户购物车列表///////////////
// int loadshopcar(char *fname)
// {
// 	struct shopcar p[100];
// 	struct shopcar *newshop = malloc(sizeof(struct shopcar));
// 	int i = 0;
// 	char namep[30] = {0};


// 	FILE *ap;
// 	ap = fopen(fname,"rb");
// 	if(ap == NULL)
// 	{
// 		printf("用户购物车文件损坏！\n");
// 		return 0;
// 	}

// 	while(1)
// 	{
// 		fread(newshop,sizeof(struct shopcar),1,ap);
// 		strcpy(p[i].name, newshop->name);
		
// 		if(!strcmp(namep,newshop->name))
// 			break;
// 		else
// 			strcpy(namep,newshop->name);

// 		p[i].price = newshop->price;
// 		p[i].discounts = newshop->discounts;
// 		p[i].m = newshop->m;
// 		p[i].id = newshop->id;
// 		p[i].mp =newshop->mp;
// 		i++;
// 	}
	
// 	double sum = 0;
// 	i--;
// 	printf("\n");
// 	printf("--------------------%s的购物车-------------------\n", fname);

// 	for(i;i>=0;i--)
// 	{
// 		printf("id:%-2d 商品:%-21s 单价:%-6.2lf元 折购:%-6.2lf%% 单计：%-6.2lf元 \n"
// 			,p[i].id,p[i].name,p[i].price,p[i].discounts,p[i].mp);
// 		sum = sum + p[i].mp;
// 	}

// 	printf("合计：%-6.2lf元\n", sum);

// 	return 0;
// }
struct load_shopcar * loadshopcar(char *fname)
{
	struct load_shopcar *head = init_list_car();//内核链表头
	struct load_shopcar *new1= malloc(sizeof(struct load_shopcar));//内核链表新增
	if(head == NULL)
		{
			printf("list init err!\n");
			return NULL;
		}
	/////////////////////////////////////////	
	// struct shopcar p[100];
	struct shopcar *newshop = malloc(sizeof(struct shopcar));
	int i = 0;
	char namep[30] = {0};

////////////////////文件打开//////////////
	char adss[80] = {"../image/"};
	strcat(adss,fname);
	FILE *ap;
	ap = fopen(adss,"rb");
	if(ap == NULL)
	{
		printf("用户购物车文件损坏！\n");
		return NULL;
	}

	while(1)
	{
		fread(newshop,sizeof(struct shopcar),1,ap);
		strcpy(newshop->name, newshop->name);
		
		if(!strcmp(namep,newshop->name))
			break;
		else
			strcpy(namep,newshop->name);

		new1 = init_node_car(newshop->name,newshop->price,newshop->discounts,newshop->id,newshop->m,newshop->mp);
		if(new1 == NULL)
			{
				printf("new node err!\n");
				return NULL;
			}

		list_add(&(new1->my_list), &(head->my_list));

		i++;
	}
	
	// show_car(head);

	return head;
}

/////////////////////////////展示购物车全部///////////////////
/////////////////////////////展示购物车全部///////////////////
/////////////////////////////展示购物车全部///////////////////
/////////////////////////////展示购物车全部///////////////////
/////////////////////////////展示购物车全部///////////////////
int show_my_car(struct load_shopcar *head)
{
	double sum = 0;
	struct load_shopcar *tmp;
	struct list_head *pos;

	list_for_each(pos, &(head->my_list))
	//for (pos = (head)->next; pos != (head);pos = pos->next)
	{
		tmp = list_entry(pos, struct load_shopcar, my_list);
		sum = sum + tmp->mp;

		
	}
	show_car(head);
	if(sum == 0)
	{
		printf(FONT_COLOR_RED"您的购物车为空！\n"COLOR_NONE);
		// return 0;
	}
	else
	{
		printf(FONT_COLOR_GREEN"合计：%6.2lf 元\n"COLOR_NONE,sum );
	}
	return 0;
}

////////////////////////////////删除购物车商品////////////////////
////////////////////////////////删除购物车商品////////////////////
////////////////////////////////删除购物车商品////////////////////
int del_car_shop(struct load_shopcar *head,char *name)
{

	int emp = emptycar(head);
	if(emp == -1)
		return 0;


	show_car(head);
	int id;
	int retid;
rery:
	while(1)
	{
		printf("请输入你想删除的商品ID：\n");
		retid = scanf("%d",&id);
		if(retid == 1 && getchar() == '\n')
		{
			break;
		}
		else
		{
			printf(FONT_COLOR_RED"请输入正确的指令！\n"COLOR_NONE);
			while(getchar() != '\n');
		}
	}
	int delret;
	delret = del_node_car(head,id);
	

	if(delret == -1)
	{
	int ip;
	int ipret;
erro:
	while(1)
	{
		printf("1.重新输入。2.退出。\n");

		printf(FONT_COLOR_RED"请输入操作指令：\n"COLOR_NONE);
		ipret = scanf("%d",&ip);
		if(ipret == 1 && getchar() == '\n')
		{	
			switch (ip)
			{
				case 1:goto rery;
				case 2:return 0;
				default :printf(FONT_COLOR_RED"请输入正确指令！(回车继续)\n"COLOR_NONE);while(getchar() != '\n');goto erro;
			}
			break;


		}
		else
		{
			printf(FONT_COLOR_RED"输入指令错误，请重新输入！\n"COLOR_NONE);
			while(getchar() != '\n');
		}

	}
	}


	//////////////更新链表数据进入结构体/////////////


	struct shopcar pc[100];
	struct shopcar *new = malloc(sizeof(struct shopcar));

	struct load_shopcar *tmp;
	struct list_head *pos;
	int i = 0;

	list_for_each(pos, &(head->my_list))
	{
		tmp = list_entry(pos, struct load_shopcar, my_list);
		strcpy(pc[i].name,tmp->name);
		pc[i].price = tmp->price;
		pc[i].discounts = tmp->discounts;
		pc[i].m = tmp->m;
		pc[i].mp = tmp->mp;
		pc[i].id = tmp->id;
		i++;
		
	}
	i--;		
      /////////////////重新写入文件//////////////
	FILE *fp;
	char adss[80] = {"../image/"};
	strcat(adss,name);
	fp = fopen(adss,"wb");
    if(fp == NULL)
	{
		printf("erro:file not find!");
		return -1;
	}
	
	// printf("i:%d\n",i);
	
	for(i;i>=0;i--)
	{
		new = &pc[i];
		fwrite(new,sizeof(struct shopcar),1,fp);
		// printf("i:%d\n",i);
	}
	
	fclose(fp);
	



	return 0;

}
/////////////////////////修改商品数量////////////////////
/////////////////////////修改商品数量////////////////////
/////////////////////////修改商品数量////////////////////
/////////////////////////修改商品数量////////////////////
/////////////////////////修改商品数量////////////////////
int mo_car_shop(struct load_shopcar *head,char *name)
{

	int emp = emptycar(head);
	if(emp == -1)
		return 0;


	show_car(head);
	int id;
	int retid;
rery:
	while(1)
	{
		printf("请输入你想修改数量的商品ID：\n");
		retid = scanf("%d",&id);
		if(retid == 1 && getchar() == '\n')
		{
			break;
		}
		else
		{
			printf("请输入正确的指令！\n");
			while(getchar() != '\n');
		}
	}
	struct load_shopcar *loca;

	loca = locate_node_car(head,id);
	int ip;
	int retip;

	if(loca == NULL)
	{
		while(1)
		{
			printf("1.重新输入。2.退出。\n");
			retip = scanf("%d",&ip);
			if(retip == 1 && getchar() == '\n')
			{
				if(ip == 1)
					goto rery;
				else if(ip == 2)
					return 0;
				else
					continue;

			}
			else
			{
				printf("请输入正确的指令！\n");
				while(getchar() != '\n');
			}
		}
	}
	

	int m;
	int retm;
	while(1)
	{
		printf("请输入商品购买数量：\n");
		retm = scanf("%d",&m);
		if(retm == 1 && getchar() == '\n')
		{
			if(m < 0 )
			{
				printf("请输入正确的数量！\n");
				continue;
			}
			else
				break;
		}
		else
		{
			printf("请输入正确的数量！\n");
			while(getchar() != '\n');
		}
	}

		loca->m = m;
		// show_car(head);

	


	//////////////更新链表数据进入结构体/////////////


	struct shopcar pc[100];
	struct shopcar *new = malloc(sizeof(struct shopcar));

	struct load_shopcar *tmp;
	struct list_head *pos;
	int i = 0;

	list_for_each(pos, &(head->my_list))
	{
		tmp = list_entry(pos, struct load_shopcar, my_list);
		strcpy(pc[i].name,tmp->name);
		pc[i].price = tmp->price;
		pc[i].discounts = tmp->discounts;
		pc[i].m = tmp->m;
		pc[i].mp = tmp->mp;
		pc[i].id = tmp->id;
		i++;
		
	}
	i--;		
	// show_car(head);
	// printf("%s %d \n", pc[0].name,pc[0].m);
	// printf("%s %d \n", pc[1].name,pc[1].m);
      /////////////////重新写入文件//////////////
	FILE *fp;
		char adss1[80] = {"../image/"};
	strcat(adss1,name);
	// printf("%s\n", adss);
	fp = fopen(adss1,"wb");
	// printf("%d\n",__LINE__ );
    if(fp == NULL)
	{
		printf("erro:file not find!");
		return -1;
	}
	
	// printf("i:%d\n",i);
	
	for(i;i>=0;i--)
	{
		new = &pc[i];
		fwrite(new,sizeof(struct shopcar),1,fp);
		// printf("i:%d\n",i);
	}
	
	fclose(fp);
	
	printf(FONT_COLOR_GREEN"修改成功！\n"COLOR_NONE);


	return 0;

}


/////////////////////////////结账///////////////////
/////////////////////////////结账///////////////////
/////////////////////////////结账///////////////////
/////////////////////////////结账///////////////////
int byebye(struct load_shopcar *head,char *name)
{
	int b;
	int retb;
	printf(FONT_COLOR_RED"结账会清空购物车内容，是否继续结账\n"COLOR_NONE);
	while(1)
	{
		printf("1.结账。2.继续购物。\n");
		retb = scanf("%d",&b);
		if(retb == 1 && getchar() == '\n')
		{
			if(b == 1)
				break;
			else if (b == 2)
				return 0;
			else
			{
				printf(FONT_COLOR_RED"请输入正确的指令！（回车继续操作）\n"COLOR_NONE);
				while(getchar() != '\n');
				continue;
			}
		}
		else
		{
			printf(FONT_COLOR_RED"输入有误，请重新输入！（回车继续操作）\n"COLOR_NONE);
			while(getchar() != '\n');
		}
	}



	double sum = 0;
	struct load_shopcar *tmp;
	struct list_head *pos;

	list_for_each(pos, &(head->my_list))
	//for (pos = (head)->next; pos != (head);pos = pos->next)
	{
		tmp = list_entry(pos, struct load_shopcar, my_list);
		sum = sum + tmp->mp;

		
	}
	// show_car(head);

	printf(FONT_COLOR_GREEN"合计：%6.2lf 元\n"COLOR_NONE,sum );
	printf(FONT_COLOR_GREEN"欢迎%s再次光临！\n"COLOR_NONE,name);
	
	FILE *p;
	char adss[80] = {"../image/"};
	strcat(adss,name);
	p = fopen(adss,"wb");
	if(p == NULL)
	{
		printf("购物车文件损坏！\n");
		return 0;
	}
	fclose(p);
	exit(0);
	return 0;
}

/////////////////清空购物车/////////
/////////////////清空购物车/////////
/////////////////清空购物车/////////
/////////////////清空购物车/////////
int cleancar(char* name)
{
		
	char ao;
	int reta;
	while(1)
	{
		printf(FONT_COLOR_RED"是否确认清空购物车？y or n（此操作将无法恢复）\n"COLOR_NONE);
		reta = scanf("%c",&ao);
		if(reta == 1 && getchar() == '\n')
		{
			if(ao == 'y')
				break;
			else if(ao == 'n')
				return 0;
			else
			{
				printf(FONT_COLOR_RED"请输入正确指令！(回车继续操作)\n"COLOR_NONE);
				while(getchar() != '\n');
				continue;
			}


		}
		else
		{
			printf(FONT_COLOR_RED"请输入正确指令！\n"COLOR_NONE);
				while(getchar() != '\n');
		}
	}






	FILE *p;
	char adss[80] = {"../image/"};
	strcat(adss,name);
	p = fopen(adss,"wb");
	if(p == NULL)
	{
		printf(FONT_COLOR_RED"购物车文件损坏！\n"COLOR_NONE);
		return 0;
	}
	fclose(p);
	printf(FONT_COLOR_GREEN"清空成功！\n"COLOR_NONE);
	return 0;
}

////////////判断购物车是否空//////////////
int emptycar(struct load_shopcar *head)
{
	double sum = 0;
	struct load_shopcar *tmp;
	struct list_head *pos;

	list_for_each(pos, &(head->my_list))
	//for (pos = (head)->next; pos != (head);pos = pos->next)
	{
		tmp = list_entry(pos, struct load_shopcar, my_list);
		sum = sum + tmp->mp;

		
	}
	// show_car(head);
	if(sum == 0)
	{
		printf("您的购物车为空！\n");
		return -1;
	}
	else
	{
		return 0;
	}
	
}





#endif










