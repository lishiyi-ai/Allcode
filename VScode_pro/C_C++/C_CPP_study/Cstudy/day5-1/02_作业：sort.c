#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sort(char **array1, int num1,
	char(*array2)[30], int num2,
	char ***myp3 /*out*/, int *num3)
{
	if (array1 == NULL || array2 == NULL
		|| myp3 == NULL || num3 == NULL)
	{
		return -1;
	}

	//打造一个指针数组 char *tmp[num1 + num2]
	char **tmp = (char **)malloc(sizeof(char *)*(num1 + num2));
	if (tmp == NULL)
	{
		return -2;
	}

	int i = 0;
	int j = 0;

	//char *array1[] = { "aa", "ccccccc", "bbbbbb" };
	//char array2[][30] = { "111111", "3333333", "222222" }
	//给每个指针分配内存（指向堆区）
	for (i = 0; i < num1; i++)
	{
		//tmp[i] = (char *)malloc(sizeof(char)* (strlen(array1[i]) + 1));
		tmp[i] = (char *)malloc(sizeof(char)* 30);
		strcpy(tmp[i], array1[i]);
	}

	//char array2[][30] = { "111111", "3333333", "222222" }
	//i的初始条件从num1开始，重要,还有一个变量j
	for (i = num1, j = 0; i < num1 + num2; i++, j++)
	{
		//array2[j]是j不是i
		//tmp[i] = (char *)malloc(sizeof(char)* (strlen(array2[j]) + 1));
		tmp[i] = (char *)malloc(sizeof(char)* 30);
		strcpy(tmp[i], array2[j]);
	}


#if 0
	//排序
	int n = num1 + num2;
	char *p = NULL;
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(tmp[i], tmp[j]) > 0)//升序
			{//交换是指针指向
				p = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = p;
			}
		}
	}
#endif
	//排序
	int n = num1 + num2;
	char p[50] = { 0 };
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			//if (strcmp(tmp[i], tmp[j]) > 0)//升序
			if (strcmp(*(tmp + i), *(tmp+j)) > 0)
			{//交换是内存块
				strcpy(p, tmp[i]);
				strcpy(tmp[i], tmp[j]);
				strcpy(tmp[j], p);
			}
		}
	}


	//间接赋值是指针存在最大意义
	*myp3 = tmp;
	*num3 = num1 + num2;

	return 0;
}

void free_buf(char ***p3, int n)
{
	if (p3 == NULL)
	{
		return;
	}

	char **tmp = *p3;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (tmp[i] != NULL)
		{
			free(tmp[i]);
			tmp[i] = NULL;
		}
	}

	if (tmp != NULL)
	{
		free(tmp);
		*p3 = NULL;
	}


}

int main(void)
{
	int ret = 0;
	char *p1[] = { "aa", "ccccccc", "bbbbbb" };
	char buf2[][30] = { "111111", "3333333", "222222" };
	char **p3 = NULL;
	int len1, len2, len3, i = 0;

	len1 = sizeof(p1) / sizeof(*p1);
	len2 = sizeof(buf2) / sizeof(buf2[0]);

	for (i = 0; i < len1; i++)
	{
		printf("%s, ", p1[i]);
	}
	for (i = 0; i < len2; i++)
	{
		printf("%s, ", buf2[i]);
	}
	printf("\n\n");

	/*
	功能：1、把指针数组p1的字符串取出来，
	2、把二维数组buf2的字符取出来，
	3、上面的字符串放在 p3，p3 是在堆区分配的二维内存
	4、对 p3 中字符串进行排序，通过 strcmp() 进行排序
	参数：
	p1： 指针数组首地址，char *p1[] = {"aa", "ccccccc", "bbbbbb"};
	len1：p1元素个数
	buf2：二维数组首元素地址，char buf2[][30] = {"111111", "3333333", "222222"};
	len2：buf2字符串的行数
	p3：二级指针的地址，需要在函数内分配二维内存，保存p1和buf2的字符串，还需要排序
	len3：保存p3中的字符串个数
	返回值：
	*/
	ret = sort(p1, len1, buf2, len2, &p3, &len3);
	if (ret != 0)
	{
		printf("sort err: %d\n", ret);
		system("pause");

		return ret;
	}

	for (i = 0; i < len3; i++)
	{
		printf("%s, ", p3[i]);
	}
	printf("\n");

	//释放p3所指向内存
	//在函数内部把p3的值赋值为NULL
	free_buf(&p3, len3);

	printf("\n");
	system("pause");
	return 0;
}