#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int a;
	int b;

	printf("&a = %d, &b = %d\n", &a, &b);


	int buf[100];
	printf("buf: %d, buf+1:%d\n", buf, buf+1);


	printf("\n");
	system("pause");
	return 0;
}