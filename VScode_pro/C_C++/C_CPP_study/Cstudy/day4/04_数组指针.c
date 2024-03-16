#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//argc: 传参数的个数（包含可执行程序）
//argv：指针数组，指向输入的参数
int main01(int argc, char *argv[])
{
	//数组指针，指针数组

	//指针数组，它是数组，每个元素都是指针
	//[] 比 * 优先级高
	char *a[] = { "aaaaaaa", "bbbbbbbbbb", "ccccccc" };
	int i = 0;

	printf("argc = %d\n", argc);

	for (i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}


	printf("\n");
	system("pause");
	return 0;
}

int main02(void)
{
	//数组指针，它是指针，指向一个数组的指针
	//数组指针，指向一维数组的整个数组，而不是首元素地址
	//定义数组指针变量

	int a[10] = { 0 };
	int i = 0;

	//1、先定义数组类型，根据类型定义指针变量
	typedef int A[10]; //A数组类型, [10]代表步长
	A *p = NULL; //p数组指针类型变量
	//p = a; //a代表首元素地址， a 和 &a 一样，最终也是当做&a，警告
	p = &a; //&a代表整个数组首地址

	printf("p:%d, p+1:%d\n", p, p + 1);

	for (i = 0; i < 10; i++)
	{
		//a[]
		// p = &a;
		// *p = *&a -> a
		(*p)[i] = i + 1;
	}

	for (i = 0; i < 10; i++)
	{
		printf("%d ", (*p)[i] );
	}
	printf("\n");



	printf("\n");
	system("pause");
	return 0;
}

int main03(void)
{
	int a[10] = { 0 };
	int i = 0;

	//2、先定义数组指针类型，根据类型定义变量
	//和指针数组写法很类似，多了()
	//() 和 []优先级一样，从左往右
	//()有指针，它是一个指针， []
	//指向数组的指针，它有typedef，所以它是一个数组指针类型
	typedef int(*P)[10];
	P q; //数组指针变量
	q = &a;

	for (i = 0; i < 10; i++)
	{
		(*q)[i] = 2*i + 1;
	}

	for (i = 0; i < 10; i++)
	{
		printf("%d ", (*q)[i]);
	}
	printf("\n");


	printf("\n");
	system("pause");
	return 0;
}

void fun(void * a)
{
	printf("%d\n", (int)a);
}

int main(void)
{
	int t = 10;
	fun((void *)t);


	int a[10] = { 0 };
	//a[11] = 10;

	int i = 0;

	//2、直接定义数组指针变量
	//和指针数组写法很类似，多了()
	//() 和 []优先级一样，从左往右
	//()有指针，它是一个指针， []
	//指向数组的指针， 没有typedef，所以它是一个数组指针变量
	int(*q)[10]; //q数组指针变量
	q = &a; //q指向a数组

	for (i = 0; i < 10; i++)
	{
		(*q)[i] = 3 * i + 1;
	}

	for (i = 0; i < 10; i++)
	{
		printf("%d ", (*q)[i]);
	}
	printf("\n");

	

	printf("\n");
	system("pause");
	return 0;
}
