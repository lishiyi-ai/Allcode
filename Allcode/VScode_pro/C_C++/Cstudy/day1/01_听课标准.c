#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main01(void)
{
	int a[] = { 10, 7, 1, 9, 4, 6, 7, 3, 2, 0 };
	int n;
	int i = 0;
	int j = 0;
	int tmp = 0;

	n = sizeof(a) / sizeof(a[0]); //Ԫ�ظ���

	printf("����ǰ\n");
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");


	//ѡ������
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (a[i] > a[j]) //����
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}

	printf("�����\n");
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	//��ο������㷨�ĳ���
	/*
	1������
	2��ÿ����书��
	3������
	4������
	5��ģ�¸�
	6����������д
	*/








	printf("\n");
	system("pause");
	return 0;
}

//���������Ϊ���������������β��˻�Ϊָ��
//void print_array(int a[1], int n)
//void print_array(int a[], int n)
void print_array(int *a, int n)
{
	// a, ����ָ���ã�ָ�����ͣ�32λ������4���ֽ�

	n = sizeof(a) / sizeof(a[0]); //Ԫ�ظ���
	printf("print_array: n = %d\n", n);

	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void sort_array(int a[10], int n)
{
	int i, j, tmp;

	//ѡ������
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (a[i] > a[j]) //����
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}

int main(void)
{
	int a[] = { 10, 7, 1, 9, 4, 6, 7, 3, 2, 0 };
	int n;
	int i = 0;
	int j = 0;
	int tmp = 0;

	n = sizeof(a) / sizeof(a[0]); //Ԫ�ظ���
	printf("n = %d\n", n);

	printf("����ǰ��\n");
	print_array(a, n);

	sort_array(a, n);

	printf("�����\n");
	print_array(a, n);

	printf("\n");
	system("pause");
	return 0;
}