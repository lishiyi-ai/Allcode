#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_mem(int size)
{
	char *p2 = NULL;            //分配4个字节的内存 栈区也叫临时区
	p2 = (char *)malloc(size);

	return p2;
}

int main(void)
{
	char buf[100];
	int a = 10;     //分配4个字节的内存 栈区也叫临时区
	int *p;         //分配4个字节的内存
	p = &a;

	*p = 20;

	char *mp = get_mem(100);
	strcpy(mp, "ABCDEFG");

	if (mp != NULL)
	{
		printf("before = %d\n", mp);
		free(mp); //告诉系统，mp原来指向内存可以被别人使用

		printf("after = %d\n", mp);
		//释放完，mp就是野指针，还是保存之前的地址，最好赋值为NULL
		mp = NULL;
	}

	printf("\n");
	system("pause");
	return 0;
}
