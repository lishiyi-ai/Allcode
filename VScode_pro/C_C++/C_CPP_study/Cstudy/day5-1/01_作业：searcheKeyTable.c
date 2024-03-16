#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM(a) (sizeof(a)/sizeof(*a))


/*
功能：找到数组中指定字符串的位置
参数：
table：字符串数组（指针数组）首地址
size：数组元素个数
key：匹配字符串，如"do"
pos: 匹配字符串在数组中的位置，如果"do"在keywords[]中位置为4
返回值：
成功：0
失败：非0
*/
int searcheKeyTable(const char* table[], const int size,
	const char* key, int *pos)
{
	if (table == NULL || key == NULL || pos == NULL)
	{
		return -1;
	}

	int i = 0;
	int n = -1;

	for (i = 0; i < size; i++)
	{
		if (strcmp(table[i], key) == 0)
		{
			n = i;
			break;
		}
	}

	if (n == -1) //没有匹配字符串
	{
		return -2;
	}

	*pos = n + 1;

	return 0;
}

int main(void)
{
	const char* keywords[] = {
		"while",
		"case",
		"static",
		"do"
	};

	int pos = 0;
	int ret = 0;

	ret = searcheKeyTable(keywords, NUM(keywords), "do", &pos);
	if (ret != 0)
	{
		printf("searcheKeyTable err: %d\n", ret);
		system("pause");
		return ret;
	}

	printf("%s在keywords位置为：%d\n", "do", pos);


	printf("\n");
	system("pause");
	return 0;
}