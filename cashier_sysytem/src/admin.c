#include "shop.h"

int admindesk(void)
{


	int i;
	int ret;
	retey:
	while(1)
	{
		printf("------------1.添加商品-----------------\n"COLOR_NONE);
		printf("------------2.移除商品-----------------\n"COLOR_NONE);
		printf("------------3.查看商品-----------------\n"COLOR_NONE);
		printf("------------4.查找商品-----------------\n"COLOR_NONE);
		printf("------------5.修改商品价格或折购--------\n"COLOR_NONE);
		printf("------------6.修改用户名和密码----------\n"COLOR_NONE);
		printf("------------7.查看所有用户账户信息------\n"COLOR_NONE);
		printf("------------8.删除用户账户信息----------\n"COLOR_NONE);
		printf(FONT_COLOR_RED"------------0.退出---------------------\n"COLOR_NONE);
		printf("请输入操作指令：\n");
		ret = scanf("%d",&i);
		if(ret == 1 && getchar() == '\n')
		{	
			switch (i)
			{
				case 1:input_shoplist();break;
				case 2:del_shoplist();break;
				case 3:show_shoplist();break;
				case 4:findshoplist();break;
				case 5:modify_data();break;
				case 6:acounthelp();break;
				case 7:show_acountlist();break;
				case 8:del_acountlist();break;
				case 0:return 0;break;
				default: printf(FONT_COLOR_RED"指令输入错误！(回车继续)\n"COLOR_NONE);while(getchar() != '\n');goto retey;
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