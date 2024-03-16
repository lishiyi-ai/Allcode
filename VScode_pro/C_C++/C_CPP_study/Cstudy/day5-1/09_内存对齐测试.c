#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	struct
	{
		
		int a;
		double c;
		short b;
	}A;

	/*
	a: 4 * 0 = 0
	c: 8*1
	b: 2 * 8 = 16
	
	 a a  a a
	 c c c c c c c c
	 b b * 8
	
	*/
	printf("%d\n", sizeof(A) );

	printf("\n");
	system("pause");
	return 0;
}