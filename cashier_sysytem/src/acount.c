#include "shop.h"

int acount(void)


{
login:

	printf(FONT_COLOR_YELLOW"欢迎来到我的商店！\n"COLOR_NONE);
	printf("\n");
	int loginch;
	int retlo;
	while(1)
	{
		printf("1.我已有账户。2.创建新用户。\n");
		retlo = scanf("%d",&loginch);
		if(retlo == 1 && getchar() == '\n')
		{
			// printf("%d\n",loginch );
			switch (loginch)
			{
				case 1 : break;

				case 2 : createacount(); break;

				default :printf(FONT_COLOR_RED"请输入正确指令！(回车继续)\n"COLOR_NONE);while(getchar() != '\n');goto login;
			}
			break;
			
		}
		else
		{
			printf(FONT_COLOR_RED"请输入正确指令！\n"COLOR_NONE);
			while(getchar() != '\n');
		}
	}



printf("请登录您的账号：\n");

// acountlo:

	int ret = loginacount();

	while(1)
	{	
		switch (ret)
		{
			case -2 : acounthelp(); 
						goto login;
			
			case 10 : return 1;
			
			case 11 : return 2;
			
			case 0 : return 0;
			
			default : return 0;
		}
	}
	
	// acount();
	return 0;







}