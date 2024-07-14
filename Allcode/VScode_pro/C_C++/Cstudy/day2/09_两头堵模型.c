#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main01(void)
{
	char *p = "      abcdefg      ";
	int begin = 0;
	int end = strlen(p) - 1;
	int n = 0;

	//从左边开始
	//如果当前字符为空，而且没有结束
	while ( p[begin] == ' ' && p[begin] != 0)
	{
		begin++; //位置从右移动一位
	}

	//如果当前字符为空，而且没有结束
	while ( p[end] == ' ' && p[end] != 0)
	{
		end--; //往左移动
	}

	n = end - begin + 1;
	printf("n = %d\n", n);

	printf("\n");
	system("pause");
	return 0;
}

int fun(char *p, int *n)
{
	if (p == NULL || n == NULL)
	{
		return -1;
	}

	int begin = 0;
	int end = strlen(p) - 1;

	//从左边开始
	//如果当前字符为空，而且没有结束
	while (p[begin] == ' ' && p[begin] != 0)
	{
		begin++; //位置从右移动一位
	}

	//如果当前字符为空，而且没有结束
	while (p[end] == ' ' && p[end] != 0)
	{
		end--; //往左移动
	}

	*n = end - begin + 1;

	return 0;
}

int fun2(char *p, char *buf)
{
	if (p == NULL || buf == NULL)
	{
		return -1;
	}

	int begin = 0;
	int end = strlen(p) - 1;
	int n = 0;

	//从左边开始
	//如果当前字符为空，而且没有结束
	while (p[begin] == ' ' && p[begin] != 0)
	{
		begin++; //位置从右移动一位
	}

	//如果当前字符为空，而且没有结束
	while (p[end] == ' ' && p[end] != 0)
	{
		end--; //往左移动
	}

	n = end - begin + 1; //非空元素个数


	strncpy(buf, p + begin, n);
	buf[n] = 0;

	return 0;
}

int main(void)
{
	char *p = "      abcddsgadsgefg      ";
	int ret = 0;
	char buf[100] = { 0 };

	ret = fun2(p, buf);
	if (ret != 0)
	{
		return ret;
	}
	printf("buf = %s\n", buf);


	printf("\n");
	system("pause");
	return 0;
}