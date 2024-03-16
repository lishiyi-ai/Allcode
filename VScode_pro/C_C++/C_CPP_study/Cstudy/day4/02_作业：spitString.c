#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//有一个字符串符合以下特征（“abcdef,acccd,eeee,aaaa,e3eeee,ssss,”）

int spitString(const char *str, char c, char buf[10][30], int *count)
{
	if (str == NULL || count == NULL)
	{
		return -1;
	}
	// str = "abcdef,acccd,eeee,aaaa,e3eeee,ssss"
	const char *start = str;
	char * p = NULL;
	int i = 0;

	do 
	{
		p = strchr(start, c);
		if (p != NULL)
		{
			int len = p - start;
			strncpy(buf[i], start, len);
			//结束符
			buf[i][len] = 0;

			i++;

			//重新设置起点位置
			start = p + 1;
		}
		else
		{
			//printf("start = %s\n", start);
			strcpy(buf[i], start);
			i++;

			break;
		}

	} while (*start != 0);

	if (i == 0)
	{
		return -2;
	}


	*count = i;

	return 0;
}

int main01(void)
{
	const char *p = "abcdef,acccd,eeee,aaaa,e3eeee,ssss";
	char buf[10][30] = { 0 };
	int n = 0;
	int i = 0;
	int ret = 0;

	ret = spitString(p, ',', buf, &n);
	if (ret != 0)
	{
		printf("spitString err:%d\n", ret);

		system("pause");
		return ret;
	}

	for (i = 0; i < n; i++)
	{
		printf("%s\n", buf[i]);
	}

	printf("\n");
	system("pause");
	return 0;
}

char **getMem(int n)
{
	char **buf = NULL; //char *buf[n]
	buf = (char **)malloc(n * sizeof(char *)); //char *
	if (buf == NULL)
	{
		return NULL;
	}

	int i = 0;
	for (i = 0; i < n; i++)
	{
		buf[i] = (char *)malloc(30);
		memset(buf[i], 0, 30);
	}
	
	return buf;
}

int getMem2(char ***tmp, int n)
{
	char **buf = NULL; //char *buf[n]
	buf = (char **)malloc(n * sizeof(char *)); //char *
	if (buf == NULL)
	{
		return -1;
	}

	int i = 0;
	for (i = 0; i < n; i++)
	{
		buf[i] = (char *)malloc(30);
		memset(buf[i], 0, 30);
	}

	//间接赋值是指针存在最大意义
	*tmp = buf;

	return 0;
}

int spitString2(const char *str, char c, char **buf, int *count)
{
	if (str == NULL || count == NULL)
	{
		return -1;
	}
	// str = "abcdef,acccd,eeee,aaaa,e3eeee,ssss,"
	const char *start = str;
	char * p = NULL;
	int i = 0;

	do
	{
		p = strchr(start, c);
		if (p != NULL)
		{
			int len = p - start;
			strncpy(buf[i], start, len);
			//结束符
			buf[i][len] = 0;

			i++;

			//重新设置起点位置
			start = p + 1;

		}
		else
		{
			strcpy(buf[i], start);
			i++;

			break;
		}

	} while (*start != 0);

	if (i == 0)
	{
		return -2;
	}


	*count = i;

	return 0;
}

void freeBuf3(char **buf, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		free(buf[i]);
		buf[i] = NULL;
	}

	if (buf != NULL)
	{
		free(buf);
		buf = NULL;
	}
}

void freeBuf4(char ***tmp, int n)
{
	char **buf = *tmp;

	int i = 0;
	for (i = 0; i < n; i++)
	{
		free(buf[i]);
		buf[i] = NULL;
	}

	if (buf != NULL)
	{
		free(buf);
		buf = NULL;
	}

	*tmp = NULL;
}

int main(void)
{

	const char *p = "abcdef,acccd,eeee,aaaa,e3eeee,ssss";
	char **buf = NULL;
	int n = 0;
	int i = 0;
	int ret = 0;

#if 0
	buf = getMem(6);
	if (buf == NULL)
	{
		return -1;
	}
#endif
	ret = getMem2(&buf, 6);
	if (ret != 0)
	{
		return ret;
	}




	ret = spitString2(p, ',', buf, &n);
	if (ret != 0)
	{
		printf("spitString err:%d\n", ret);

		system("pause");
		return ret;
	}

	for (i = 0; i < n; i++)
	{
		printf("%s\n", buf[i]);
	}


// 	freeBuf3(buf, n);
// 	buf = NULL;

	freeBuf4(&buf, n);
	if(buf != NULL)
	{
		free(buf);
		buf = NULL;
	}

#if 0
	for (i = 0; i < n; i++)
	{
		free(buf[i]);
		buf[i] = NULL;
	}

	if (buf != NULL)
	{
		free(buf);
		buf = NULL;
	}
#endif

	printf("\n");
	system("pause");
	return 0;
}