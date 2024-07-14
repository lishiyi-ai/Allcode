#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Teacher
{
	char name[50];
	//char *name;
	int age;
}Teacher;

int main(void)
{
	Teacher a[3] = {
		{ "a", 18 },
		{ "a", 18 },
		{ "a", 18 }
	};

	//¾²Ì¬
	Teacher a2[3] = { "a", 18, "b", 28, "c", 38 };
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		printf("%s, %d\n", a2[i].name, a2[i].age);
	}

	//int a[3]
	//int *, sprintf()

	int b[3] = { 0 };
	int *pB = (int *)malloc(3 * sizeof(int));
	free(pB);

	//Teacher p[3]
	Teacher *p = (Teacher *)malloc(3 * sizeof(Teacher));
	if (p == NULL)
	{
		return -1;
	}

	char buf[50];
	for (i = 0; i < 3; i++)
	{
		sprintf(buf, "name%d%d%d", i, i, i);
		strcpy(p[i].name, buf);
		p[i].age = 20 + i;
	}

	for (i = 0; i < 3; i++)
	{
		printf("µÚ%d¸ö£º%s, %d\n", i+1, p[i].name, p[i].age);
	}
	printf("\n");

	if (p != NULL)
	{
		free(p);
		p = NULL;
	}




	printf("\n");
	system("pause");
	return 0;
}