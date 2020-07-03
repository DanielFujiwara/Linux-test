
#include "shop.h"
#include "readdata.h"
int main(int argc, char const *argv[])
{
	int i = acount();////登录模块
	creatshoptxt(); //创建所有用户购物车文件
	while(1)      //判断登录操作
	{
		switch (i)
		{
			case 1:break;
			case 2:break;
			default : printf(FONT_COLOR_RED"登录失败！\n"COLOR_NONE);return 0;
		}
		break;

	}
/////////////选择空间/////////////////////////
	if(i == 1)//管理员空间
		admindesk();
	else//普通用户空间
		useracount();
	return 0;
}