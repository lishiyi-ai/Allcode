#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	//�������ʣ�һ�������ڴ�ռ����
	//�����൱�����ƺţ��ڴ��൱�ڷ���
	int a; 
	int *p;

	//ֱ�Ӹ�ֵ
	a = 10;

	printf("a = %d\n", a);


	//��Ӹ�ֵ
	printf("&a: %d\n", &a);
	p = &a;
	printf("p = %d\n", p);

	*p = 22;
	printf("*p = %d, a = %d\n", *p, a);

	printf("\n");
	system("pause");
	return 0;
}