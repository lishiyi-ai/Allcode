#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
5. 有字符串有以下特征（“abcd11111abcd2222abcdqqqqq”）,求写一个函数接口，输出以下结果。
把字符串替换成（dcba11111dcba2222dcbaqqqqq），并把结果传出。
要求：
1. 正确实现接口和功能
2. 编写测试用例
*/

/*
src:    原字符串
dst:    生成的或需要填充的字符串
sub:    需要查找的子字符串
new_sub:提换的新子字符串

return : 0 成功
-1 失败
*/
int replaceSubstr(/* in */char *src, /* out */char** dst,
	/* in */char *sub,  /* in */char *new_sub)
{
	if (src == NULL || dst == NULL ||
		sub == NULL || new_sub == NULL)
	{
		return -1;
	}

	/*
	src = "dddddabcd11111abcd2222abcdqqqqq";
	sub = "abcd"
	new_sub = "aaaaaa"
	*/

	char *start = src;
	char *p = NULL;
	char tmp[512] = { 0 };
	int len = 0;

	do 
	{
		/*
		src = "dddddabcd11111abcd2222abcdqqqqq";
		sub = "abcd"
		new_sub = "aaaaaa"
		*/
		p = strstr(start, sub); 
		if (p != NULL)
		{
			len = 0;
			len = p - start;
			if (len > 0)
			{
				strncat(tmp, start, len); //tmp = "ddddd"
			}

			strncat(tmp, new_sub, strlen(new_sub)); //tmp = "dddddaaaaaa"

			//重新设置起点位置
			start = p + strlen(sub);
		}
		else
		{
			strcat(tmp, start);
			break;
		}

	} while (*start != '\0'); //start[i]  != 0

	char *buf = (char *)malloc(strlen(tmp) + 1);
	strcpy(buf, tmp);

	//间接赋值，是指针存在最大意义
	*dst = buf;


	return 0;
}

void freeBuf(char *buf)
{
	free(buf);
	buf = NULL;
}

void freeBuf2(char **buf)
{
	char *tmp = *buf;

	if (tmp != NULL)
	{
		free(tmp);
	}

	*buf = NULL;

}

int main(void)
{
	char *p = "dddddabcd11111abcd2222abcdqqqqq";
	char *buf = NULL; //在replaceSubstr函数中分配空间
	int ret = 0;

	ret = replaceSubstr(p, &buf, "abcd", "cccc");
	if (ret != 0)
	{
		printf("replaceSubstr err: %d\n", ret);

		system("pause");
		return ret;
	}
	printf("p = %s\n", p);
	printf("buf = %s\n", buf);

	/*
	if (buf != NULL)
	{
		free(buf);
		buf = NULL;
	}
	*/

// 	freeBuf(buf);
// 	free(buf);
// 	buf = NULL;

	freeBuf2(&buf);

	if (buf != NULL)
	{
		free(buf);
	}

	printf("\n");
	system("pause");
	return 0;
}