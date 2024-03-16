#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main01(void)
{
	char *p = "11abcd111122abcd333abcd3322abcd3333322qqq";
	int n = 0;

	do 
	{
		p = strstr(p, "abcd");
		if (p != NULL)
		{
			n++; //累计个数

			//重新设置查找的起点
			p = p + strlen("abcd");

		}
		else //如果没有匹配的字符串，跳出循环
		{
			break;
		}


	} while (*p != 0); //如果没有到结尾

	printf("n = %d\n", n);

	printf("\n");
	system("pause");
	return 0;
}

int main02(void)
{
	char *p = "11abcd111122abcd333abcd3322abcd3333322qqq";
	int n = 0;

	while (  ( p = strstr(p, "abcd") ) != NULL )
	{
		//能进来，肯定有匹配的子串

		//重新设置起点位置
		p = p + strlen("abcd");
		n++;

		if (*p == 0) //如果到结束符
		{
			break;
		}
		
	}

	printf("n = %d\n", n);

	printf("\n");
	system("pause");
	return 0;
}

int my_strstr(char *p, int *n)
{
	//辅助变量
	int i = 0;
	char *tmp = p;

	while ((tmp = strstr(tmp, "abcd")) != NULL)
	{
		//能进来，肯定有匹配的子串

		//重新设置起点位置
		tmp = tmp + strlen("abcd");
		i++;

		if (*tmp == 0) //如果到结束符
		{
			break;
		}

	}

	//间接赋值
	*n = i;

	return 0;
}

int main(void)
{
	
	char *p = "11abcd111122abcd333abcd3322abcd3333322qqq";
	int n = 0;
	int ret = 0;

	ret = my_strstr(p, &n);
	if (ret != 0)
	{
		return ret;
	}
	printf("n = %d\n", n);



	printf("\n");
	system("pause");
	return 0;
}