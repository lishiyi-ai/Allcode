#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main01(void)
{
	int a1[3][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12}
	}; 

	int a2[3][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	int a3[][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	int i = 0;
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%d ", a3[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//+16
	//二维数组数组名代表第0行的首地址（区别于第0行首元素地址，虽然值一样）
	//它们步长不一样
	printf("a:%d, a+1:%d\n", a3, a3+1); 
	printf("%d， %d\n", *(a3 + 0), *(a3 + 0)+1); //第0行首元素地址
	printf("%d, %d\n", a3[0], a3[0]+1);

	int a[][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	// a : 代表第0行首地址
	// a+i   ->  &a[i] : 代表第i行首地址
	// *(a+i) -> a[i] : 代表第0行首元素地址
	// *(a+i)+j  -> &a[i][j]: 第i行第j列元素的地址
	// *(*(a+i)+j) -> a[i][j] = 第i行第j列元素的值


	printf("\n");
	system("pause");
	return 0;
}

void printA(int *a, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main02(void)
{
	int a[][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	printA((int *)a, sizeof(a)/sizeof(a[0][0]) );

	printf("\n");
	system("pause");
	return 0;
}

int main03(void)
{
	int a[][10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	//3个 a[4]的一维数组

#if 0
	//定义数组指针变量
	//指向一维数组的整个数组首地址
	int(*p)[10]; 
	//p = &a; //整个二维数组首地址 p = a;
	p = a; //第0行首地址, p等价于二维数组名
	printf("p:%d, p+1:%d\n", p, p+1); //10 * 4= 40
#endif

	//定义数组指针类型，再定义变量
	typedef int(*P)[10];
	P p;
	p = a;

	int i = 0;
	int j = 0;
	int n = sizeof(a) / sizeof(a[0]);
	int nj = sizeof(a[0]) / sizeof(a[0][0]);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < nj; j++)
		{
			//printf("%d ", p[i][j]);
			printf("%d ", *( *(p+i)+j ) );

		}
		printf("\n");
	}


	int t[10];
	//测一维数组长度： sizeof()首行首元素地址
	printf("sizeof(t)= %d, sizeof(&t) %d\n", sizeof(t), sizeof(&t) );

	//int a[2][10]
	printf("sizeof(a[0]):%d, sizeof(&a[0]):%d\n", sizeof(a[0]), sizeof(&a[0]) );
	printf("sizeof( *(a+0) ):%d, sizeof( a+0):%d\n", sizeof( *(a+0) ), sizeof( a+0));


	printf("\n");
	system("pause");
	return 0;
}

//数组做形参都会退化为指针，指针步长不一定一样
void printArray(int a[3][4])//5k
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

//a +1, 一行： 4 * 4 = 16
void printArray2(int a[][4])//7k
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

//指针步长不一样， a+1: 4
void printArray3(int **a)//-7k
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

//数组指针
void printArray4(int (*a)[4])//9k
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

//数组指针类型
typedef int(*P)[4];

void printArray5(P a)//9k
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

int main(void)
{
	int a[3][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	printArray5(a);

	printf("\n");
	system("pause");
	return 0;
}