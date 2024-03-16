#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{


	int a1[100] = { 1, 2, 3, 4 }; 

	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8};

	int n = 0;
	int i = 0;

	n = sizeof(a) / sizeof(a[0]); //n = 8

	for (i = 0; i < n; i++)
	{

		printf("%d ", *(a + i));
	}
	printf("\n");


	printf("a:%d, a+1:%d\n", a, a+1); //+4
	printf("&a: %d, &a+1:%d\n", &a, &a + 1); //+32


	typedef int A[8]; 

	A b;

	for (i = 0; i < 8; i++)
	{
		b[i] = 2*i + 1;
	}

	for (i = 0; i < 8; i++)
	{
		//printf("%d ", b[i]);
		printf("%d ", *(b+i));
	}
	printf("\n");

	printf("b: %d, b+1:%d\n", b, b+1);
	printf("&b: %d, &b+1:%d\n", &b, &b + 1);
 



	printf("\n");
	system("pause");
	return 0;
}