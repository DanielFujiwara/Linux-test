#include "shop.h"
// #include "kernellist.h"

int useracount(void)
{
	char name[50];
	FILE *p;
	p = fopen("../image/working.txt","rb");
	fread(name,50,1,p);
	// printf("helle:%s\n",name );
	fclose(p);

	// prit(name);//测试名称
	// FILE *s;
	// s = fopen(name,"a+");
	// fwrite("123",50,1,s);
	// fclose(s);
	struct load_shoplist *head = showshoptou();//展示用户商品返回指针
	int max = maxshoplist(head);// 获取商品总数
	// printf("%d\n",max );


	// show(head);
	int ip;
	int ipret;
	while(1)
	{
		printf("----------------1.查看商品---------------------\n");
		printf("----------------2.选择商品加入购物车------------\n");
		printf("----------------3.管理我的购物车----------------\n");
		printf("----------------4.修改用户名和密码--------------\n");
		printf(FONT_COLOR_RED"----------------0.退出-------------------------\n"COLOR_NONE);
		printf("请输入操作指令：\n");
		ipret = scanf("%d",&ip);
		if(ipret == 1 && getchar() == '\n')
		{	
			switch (ip)
			{
				case 1:usershow(head);break;
				case 2:shopcar_in(max,name,head);break;
				case 3:carjob(name);break;
				case 4:acounthelp();break;
				case 0:return 0;break;
			}

		}
		else
		{
			printf(FONT_COLOR_RED"输入指令错误，请重新输入！\n"COLOR_NONE);
			while(getchar() != '\n');
		}

	}






	return 0;
}