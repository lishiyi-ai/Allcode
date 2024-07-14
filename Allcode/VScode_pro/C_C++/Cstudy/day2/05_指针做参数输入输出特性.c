#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fun(char *p /* in */)
{
	//给p指向的内存区域拷贝
	strcpy(p, "abcddsgsd");
}

void fun2(char *p)
{
	if (p == NULL)
	{
		return;
	}

	//给p指向的内存区域拷贝
	strcpy(p, "abcddsgsd");
}

void fun3(char **p /* out */, int *len)
{
	if (p == NULL)
	{
		return;
	}

	char *tmp = (char *)malloc(100);
	if (tmp == NULL)
	{
		return;
	}
	strcpy(tmp, "adlsgjldsk");

	//间接赋值
	*p = tmp;
	*len = strlen(tmp);


}

int main(void)
{
	//输入，主调函数分配内存
	char buf[100] = { 0 };
	fun(buf);
	printf("buf  = %s\n", buf);

	char *str = NULL;
	fun2(str);

	//输出，被调用函数分配内存，地址传递
	char *p = NULL;
	int len = 0;
	fun3(&p, &len);
	if (p != NULL)
	{
		printf("p = %s, len = %d\n", p, len);
	}



	printf("\n");
	system("pause");
	return 0;
}