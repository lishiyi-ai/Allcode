#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_str1()
{
	char *p = "abcdef1"; //���ֳ�����

	return p;
}

char *get_str2()
{
	char *q = "abcdef2"; //���ֳ�����

	return q;
}

int main(void)
{
	char *p = NULL;
	char *q = NULL;

	p = get_str1();
	//%s�� ָ��ָ���ڴ����������
	//%d: ��ӡp�����ֵ
	printf("p = %s�� p = %d", p, p);

	q = get_str2();
	printf("q = %s�� q = %d", q, q);

	printf("\n");
	system("pause");
	return 0;
}