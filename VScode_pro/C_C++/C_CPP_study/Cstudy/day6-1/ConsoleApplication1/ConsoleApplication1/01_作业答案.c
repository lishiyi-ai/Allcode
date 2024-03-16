#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//结构体类型，每个导师有三个学生
typedef struct Teacher
{
	char *tName; //导师
	char **stu;  //三个学生
	int age;
}Teacher;

//在createTeacher中分配空间
int createTeacher(Teacher **p/*out*/, int n1, int n2)
{
	if (p == NULL)
	{
		return -1;
	}

	Teacher *tmp = NULL; //Teacher tmp[3]
	int i = 0;
	int j = 0;
	tmp = (Teacher *)malloc(n1 * sizeof(Teacher));
	if (tmp == NULL)
	{
		return -2;
	}

	for (i = 0; i < n1; i++)
	{
		//导师
		tmp[i].tName = (char *)malloc(30);

		//学生
		char **s = (char **)malloc(n2 * sizeof(char *));
		for (j = 0; j < n2; j++)
		{
			s[j] = (char *)malloc(30);
		}

		//直接赋值
		tmp[i].stu = s;

	}
	
	//间接赋值是指针存在最大意义
	*p = tmp;

	return 0;
}

//给成员赋值
void initTeacher(Teacher *p, int n1, int n2)
{
	if (p == NULL)
	{
		return;
	}

	int i = 0;
	int j = 0;
	char buf[30];
	for (i = 0; i < n1; i++)
	{
		//导师名字
		sprintf(buf, "teacher%d%d%d", i, i, i);
		strcpy(p[i].tName, buf);

		//年龄
		p[i].age = 30 + 2 * i;


		//n2学生
		for (j = 0; j < n2; j++)
		{
			sprintf(buf, "stu%d%d%d%d", i, i, j, j);
			strcpy(p[i].stu[j], buf);
		}
	}
}

//打印结构体成员信息
void printTeacher(Teacher *p, int n1, int n2)
{
	if (p == NULL)
	{
		return;
	}

	int i;
	int j;
	for (i = 0; i < n1; i++)
	{
		//导师名字
		//年龄
		printf("%s[%d]\n", p[i].tName, p[i].age);


		//学生
		for (j = 0; j < n2; j++)
		{
			printf("\t%s", p[i].stu[j]);
		}
		printf("\n");

	}

}


//根据导师名字排序, 降序
void sortTeacher(Teacher *p, int n)
{
	if (p == NULL)
	{
		return;
	}

	int i = 0;
	int j = 0;

	Teacher tmp;

	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(p[i].tName, p[j].tName) < 0)
			{
				tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
		}
	}

}


//释放空间，在函数内部把p赋值为NULL
void freeTeacher(Teacher **p, int n1, int n2)
{
	if (p == NULL)
	{
		return;
	}

	Teacher *tmp = *p;

	int i = 0;
	int j = 0;
	for (i = 0; i < n1; i++)
	{
		//可以释放导师
		if (tmp[i].tName != NULL)
		{
			free(tmp[i].tName);
			tmp[i].tName = NULL;
		}


		//学生
		for (j = 0; j < n2; j++)
		{
			if (tmp[i].stu[j] != NULL)
			{
				free(tmp[i].stu[j]);
				tmp[i].stu[j] = NULL;
			}
			
		}

		if (tmp[i].stu != NULL)
		{
			free(tmp[i].stu);
			tmp[i].stu = NULL;
		}
	}

	if (tmp != NULL)
	{
		free(tmp);
		*p = NULL;
	}

}

int main(void)
{
	int ret = 0;
	int n1 = 3; //导师个数
	int n2 = 3; //学生
	Teacher *p = NULL;

	ret = createTeacher(&p, n1, n2);
	if (ret != 0)
	{
		printf("createTeacher err:%d\n", ret);
		return ret;
	}

	initTeacher(p, n1, n2); //给成员赋值

	//打印成员，排序前
	printf("排序前：\n");
	printTeacher(p, n1, n2);


	//根据导师名字排序, 降序
	sortTeacher(p, n1);

	//打印成员，排序后
	printf("\n排序后：\n");
	printTeacher(p, n1, n2);

	//释放空间，在函数内部把p赋值为NULL
	freeTeacher(&p, n1, n2);

	printf("\n");
	system("pause");
	return 0;
}