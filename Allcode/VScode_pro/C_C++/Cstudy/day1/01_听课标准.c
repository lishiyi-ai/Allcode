#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main01(void)
{
	int a[] = { 10, 7, 1, 9, 4, 6, 7, 3, 2, 0 };
	int n;
	int i = 0;
	int j = 0;
	int tmp = 0;

	n = sizeof(a) / sizeof(a[0]); //元素个数

	printf("排序前\n");
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");


	//选择法排序
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (a[i] > a[j]) //升序
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}

	printf("排序后\n");
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	//如何看懂带算法的程序
	/*
	1、流程
	2、每个语句功能
	3、试数
	4、调试
	5、模仿改
	6、不看代码写
	*/








	printf("\n");
	system("pause");
	return 0;
}

//如果数组作为函数参数，数组形参退化为指针
//void print_array(int a[1], int n)
//void print_array(int a[], int n)
void print_array(int *a, int n)
{
	// a, 当做指针用，指针类型，32位，长度4个字节

	n = sizeof(a) / sizeof(a[0]); //元素个数
	printf("print_array: n = %d\n", n);

	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void sort_array(int a[10], int n)
{
	int i, j, tmp;

	//选择法排序
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (a[i] > a[j]) //升序
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}

int main(void)
{
	int a[] = { 10, 7, 1, 9, 4, 6, 7, 3, 2, 0 };
	int n;
	int i = 0;
	int j = 0;
	int tmp = 0;

	n = sizeof(a) / sizeof(a[0]); //元素个数
	printf("n = %d\n", n);

	printf("排序前：\n");
	print_array(a, n);

	sort_array(a, n);

	printf("排序后：\n");
	print_array(a, n);

	printf("\n");
	system("pause");
	return 0;
}