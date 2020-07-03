#include "shop.h"

int carjob(char *name)
{
	struct load_shopcar *head =  loadshopcar(name);

	// printf("%s\n",name );
	int ip;
	int ipret;
erro:
	while(1)
	{
		printf("----------------1.查看购物车---------------------\n");
		printf("----------------2.删除购物车商品-----------------\n");
		printf("----------------3.修改商品数量-------------------\n");
		printf("----------------4.清空购物车--------------------\n");
		printf(FONT_COLOR_GREEN"----------------5.结账--------------------------\n"COLOR_NONE);
		printf(FONT_COLOR_RED"----------------0.返回上一层--------------------\n"COLOR_NONE);
		printf("请输入操作指令：\n");
		ipret = scanf("%d",&ip);
		if(ipret == 1 && getchar() == '\n')
		{	
			head =  loadshopcar(name);
			switch (ip)
			{
				case 1:show_my_car(head);break;
				case 2:del_car_shop(head,name);break;
				case 3:mo_car_shop(head,name);break;
				case 4:cleancar(name);break;
				case 5:byebye(head,name);break;
				case 0:return 0;break;
				default :printf("请输入正确指令！\n");while(getchar() != '\n');goto erro;
			}

		}
		else
		{
			printf("输入指令错误，请重新输入！\n");
			while(getchar() != '\n');
		}

	}
}