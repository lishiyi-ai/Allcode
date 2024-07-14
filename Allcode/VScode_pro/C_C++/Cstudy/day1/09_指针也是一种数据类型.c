#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int *p = 0x11111;
	char ***************q = 0x11;

	printf("sizeof(p) = %d, sizeof(q) =%d\n", sizeof(p), sizeof(q));


	int a = 100;
	int *p1 = NULL;

	//指针指向谁，就把谁的地址赋值给指针
	p1 = &a;
	//*钥匙，通过*可以找到指针指向的内存区域，操作还是内存
	*p1 = 22;

	//*放在=左边，给内存赋值，写内存
	//*放在=右边，取内存的值，读内容
	int b = *p1;
	printf("b = %d\n", b);

	printf("\n");
	system("pause");
	return 0;
}