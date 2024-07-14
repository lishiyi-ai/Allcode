#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *p = NULL; 
	char buf[] = "abcdef";

	printf("p1 = %d\n", p);
	//改变指针变量的值
	p = buf; 
	printf("p2 = %d\n", p);

	//指针变量，和指向指向的内存是两个不同的概念
	p = p + 1; //改变了指向变量的值，改变了指针的指向
	printf("p2 = %d\n", p);
	printf("buf = %s\n", buf);

	printf("*p = %c\n", *p);

	//改变指针指向的内存，并不会影响到指针的值
	printf("改变指针指向的内存，并不会影响到指针的值\n");
	buf[1] = '1';
	printf("p3 = %d\n", p);
	printf("buf2 = %s\n", buf);

	*p = 'm';
	printf("p4 = %d\n", p);
	printf("buf3 = %s\n", buf);

	//写内存时，一定要确保内存可写
	char *buf2 = "sadgkdsjlgjlsdk"; //文字常量区，内存不可改
	//buf2[2] = '1'; //err

	char buf3[] = "skgjkdsjgjds";
	buf3[1] = '1'; //ok

	char *p3 = NULL;
	//给p3指向的内存区域拷贝内存
	p3 = buf3;
	strcpy(p3, "1111"); //err

	printf("\n");
	system("pause");
	return 0;
}