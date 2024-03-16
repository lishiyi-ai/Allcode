#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{

	//int b[]; //定义时必须初始化
	int a1[100] = { 1, 2, 3, 4 }; //没有赋值的都为0

	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8};
	//sizeof()测变量所占的空间（变量所对应类型的空间）

	int n = 0;
	int i = 0;
	// sizeof(a) = 4 * 8 = 32 数组类型：由元素个数 和元素类型对应 int [8]
	//sizeof(a[0]) 首元素大小，每个元素4个字节
	n = sizeof(a) / sizeof(a[0]); //n = 8

	for (i = 0; i < n; i++)
	{
		//*(a+i) : a+i代表第I元素地址, *(a+i)指针指向的内存（取值）
		//[] * 等级
		printf("%d ", *(a + i));
	}
	printf("\n");

	//数组类型
	//a代表首元素地址
	//&a代表整个数组首地址，它和首元素地址一样的，但是，它们步长不一样
	printf("a:%d, a+1:%d\n", a, a+1); //+4
	printf("&a: %d, &a+1:%d\n", &a, &a + 1); //+32

	//数组类型：由元素个数 和元素类型对应 int [8]
	//通过typedf定义一个数组类型
	//有typedef是类型，没有是变量
	typedef int A[8]; //代表数组类型，它是一类型，不是变量
	//typedef int (A)[8];

	A b; // int b[8], 去了typedef, b替换到A的位置

	for (i = 0; i < 8; i++)
	{
		b[i] = 2*i + 1;
	}

	for (i = 0; i < 8; i++)
	{
		//printf("%d ", b[i]);
		printf("%d ", *(b+i));
	}
	printf("\n");

	printf("b: %d, b+1:%d\n", b, b+1);
	printf("&b: %d, &b+1:%d\n", &b, &b + 1);
 



	printf("\n");
	system("pause");
	return 0;
}