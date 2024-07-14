#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;

//typedef和结构体结合使用
struct MyStruct
{
	int a;
	int b;
};

typedef struct MyStruct2
{
	int a;
	int b;
}TMP;

/* void, 无类型
1、函数参数为空，定义函数时，可以用void修饰:  int fun(void)
2、函数没有返回值：void fun(void);
3、不能定义void类型的普通变量： void a; //err,无法确定类型,不同类型分配空间不一样
4、可以定义void *变量： void *p; //ok， 32永远4字节，64永远8字节
5、数据类型本质：固定内存块大小别名
6、void *p万能指针，函数返回值，函数参数

*/

int main(void)
{
	u32 t; // unsigned int

	//定义结构体变量，一定要加上struct关键字
	struct MyStruct m1;
	//MyStruct m2; //err

	TMP m3;
	struct MyStruct2 m4;

	char buf[1024];
	strcpy(buf, "1111111111");


	printf("\n");
	system("pause");
	return 0;
}