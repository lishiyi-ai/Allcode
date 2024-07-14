#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	void *p = 0x1122;

	char buf[1024] = "aglsdjglkdsj";

	p = buf; //指向这个指针，使用时转化为实际类型指针
	printf("p = %s\n", (char *)p);

	int a[100] = { 1, 2, 3, 4 };

	p = a; 

	int i = 0;
	for (i = 0; i < 4; i++)
	{
		printf("%d ", *( (int *)p + i ) );
	}
	printf("\n");

	int b[3] = { 1, 2, 3 };
	int c[3];
	memcpy(c, b, sizeof(b));
	for (i = 0; i < 3; i++)
	{
		printf("%d ", c[i]);
	}
	printf("\n");

	char str[] = "dfslgajdsl";
	char dst[100];
	memcpy(dst, str, sizeof(str));

	printf("dst = %s\n", dst);

	char *q = 0x1122;

	char str2[100] = { 0 };
	q = str2;


	//给q指向的内存区域赋值
	strcpy(q, "1234");
	printf("q = %s\n", q);



	printf("\n");
	system("pause");
	return 0;
}