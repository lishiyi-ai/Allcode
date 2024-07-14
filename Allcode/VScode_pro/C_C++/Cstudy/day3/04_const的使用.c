#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyStruct
{
	int a;
	int b;
}MyStruct;

void fun(MyStruct *p)
{
	//指针能变
	//p = NULL;
	//指针指向的内存也可以变
	//p->a = 10; //ok
}

void fun1(MyStruct const *p)
{
	//p = NULL; //ok
	//p->a = 10; //err
}

void fun2(MyStruct  * const p)
{
	//p = NULL; //err
	p->a = 10;//ok
}

//p只读
void fun3(MyStruct const * const p)
{
	MyStruct tmp;
	tmp.a = p->a;
}

int main(void)
{
	//const修饰一个变量为只读
	const int a = 10;
	//a = 100; //err

	//指针变量， 指针指向的内存， 2个不同概念
	char buf[] = "aklgjdlsgjlkds";

	//从左往右看，跳过类型，看修饰哪个字符
	//如果是*， 说明指针指向的内存不能改变
	//如果是指针变量，说明指针的指向不能改变，指针的值不能修改
	const char *p = buf;
	// 等价于上面 char const *p1 = buf;
	//p[1] = '2'; //err
	p = "agdlsjaglkdsajgl"; //ok

	char * const p2 = buf;
	p2[1] = '3';
	//p2 = "salkjgldsjaglk"; //err

	//p3为只读，指向不能变，指向的内存也不能变
	const char * const p3 = buf;

	//如何引用另外.c中const变量，了解
	extern const int aa; //不能再赋值，只能声明
	printf("aa = %d\n", aa);

	//const修饰的变量，定义时初始化

	//在c语言中, const是一个冒牌货
	const int b = 10;
	//b = 100; //err
	int *q = &b;
	*q = 22;
	printf("%d, %d\n", b, *q);


	printf("\n");
	system("pause");
	return 0;
}