#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *p = NULL;
	char *q = NULL;
	int i = 0;

	char buf[100] = "akgjdksjg";

	p = &buf[0];
	printf("p1 = %d, %c\n", p, *p);

	p = &buf[1];
	printf("p2 = %d, %c\n\n", p, *p);

	for (i = 0; i < strlen(buf); i++)
	{
		//p = &buf[i];
		p = buf + i;
		printf("p3 = %d, %c\n", p, *p);
	}

	q = (char *)malloc(100);
	if (q == NULL)
	{
		return -1;
	}
	strcpy(q, "abcdefg");



	printf("\n");
	for (i = 0; i < strlen(q); i++)
	{
		p = q + i;
		printf("%c ", *p);
	}


	printf("\n");
	system("pause");
	return 0;
}