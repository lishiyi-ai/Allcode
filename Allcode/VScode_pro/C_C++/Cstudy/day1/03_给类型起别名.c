#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;

//typedef�ͽṹ����ʹ��
struct MyStruct
{
	int a;
	int b;
};

typedef struct MyStruct2
{
	int a;
	int b;
}TMP;

/* void, ������
1����������Ϊ�գ����庯��ʱ��������void����:  int fun(void)
2������û�з���ֵ��void fun(void);
3�����ܶ���void���͵���ͨ������ void a; //err,�޷�ȷ������,��ͬ���ͷ���ռ䲻һ��
4�����Զ���void *������ void *p; //ok�� 32��Զ4�ֽڣ�64��Զ8�ֽ�
5���������ͱ��ʣ��̶��ڴ���С����
6��void *p����ָ�룬��������ֵ����������

*/

int main(void)
{
	u32 t; // unsigned int

	//����ṹ�������һ��Ҫ����struct�ؼ���
	struct MyStruct m1;
	//MyStruct m2; //err

	TMP m3;
	struct MyStruct2 m4;

	char buf[1024];
	strcpy(buf, "1111111111");


	printf("\n");
	system("pause");
	return 0;
}