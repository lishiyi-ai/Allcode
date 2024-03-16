#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_fprintf(char *path)
{
	FILE *fp = NULL;
	//读写方式打开
	fp = fopen(path, "w+");
	if (fp == NULL)
	{
		perror("my_fprintf fopen");
		return;
	}

	//printf("hello, i am pig, mike = %d\n", 250);

	//fprintf(stdout, "hello, i am pig, mike = %d\n", 250);
	fprintf(fp, "%d %d %d\n", 1, 2, 3);

	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
}

void my_fscanf(char *path)
{
	FILE *fp = NULL;
	//读写方式打开
	fp = fopen(path, "r+");
	if (fp == NULL)
	{
		perror("my_fprintf fopen");
		return;
	}

	//printf("hello, i am pig, mike = %d\n", 250);

	//fprintf(stdout, "hello, i am pig, mike = %d\n", 250);
	int a = 0;
	int b = 0;
	int c = 0;
	fscanf(fp, "%d %d %d\n", &a, &b,&c);
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
}

int main(void)
{
	my_fprintf("../06.txt");
	my_fscanf("../06.txt");


	printf("\n");
	system("pause");
	return 0;
}