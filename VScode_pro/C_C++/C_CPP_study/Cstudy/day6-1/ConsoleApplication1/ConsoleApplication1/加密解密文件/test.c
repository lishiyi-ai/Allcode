#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des.h"

#define  SIZE 1024*4

int main01(void)
{
	unsigned char buf[] = "153u532i4uodsjgldsjlgkjsd";
	int srcLen = strlen(buf);
	unsigned char dst[100] = { 0 }; //密文
	int dstLen = 0; //密文的长度
	int ret = 0;

	//加密
	ret = DesEnc(buf, srcLen, dst, &dstLen);
	if (ret != 0)
	{
		printf("加密失败， err: %d\n", ret);
		return -1;
	}
	printf("%s加密后：%s\n", buf, dst);


	memset(buf, 0, sizeof(buf));
	int len = 0;
	//解密
	ret = DesDec(dst,dstLen, buf, &len);
	if (ret != 0)
	{
		printf("解密失败， err: %d\n", ret);
		return -1;
	}

	if (srcLen != len)
	{
		printf("解密后的长度和原来的不一致\n");
		return -2;
	}

	printf("%s  解密后 : %s\n", dst, buf);


	printf("\n");
	system("pause");
	return 0;
}

void menu()
{
	printf("=====================\n");
	printf("1 加密文件\n");
	printf("2 解密文件\n");
	printf("3 清屏\n");
	printf("4 退出\n");
	printf("=====================\n");
}

//加密文件
void EncFile()
{
	//以4k大小读文件, srcBuf
	//srcBuf 加密-> dstBuf
	//dstBuf -> 写文件

	FILE *rFd = NULL;
	FILE *wFd = NULL;
	char rPath[512] = { 0 }; //源文件路径， 需要加密文件路
	char wPath[512] = { 0 }; //目标路径， 保存加密后的文件
	unsigned char srcBuf[SIZE] = { 0 }; //4k
	int rLen = 0;
	unsigned char dstBuf[SIZE] = { 0 }; //4k
	int wLen = 0;
	int ret = 0;

	printf("请输入需要加密的文件：");
	scanf("%s", rPath);

	printf("请输入加密后的文件：");
	scanf("%s", wPath);

	//读方式打开需要加密的文件rPath
	rFd = fopen(rPath, "rb+");
	if (rFd == NULL)
	{
		perror("EncFile fopen rPath");
		return;
	}

	//写方式打开加密后的文件wPath
	wFd = fopen(wPath, "wb+");
	if (wFd == NULL)
	{
		perror("EncFile fopen wPath");
		goto End;
		return;
	}

	//循环读取文件
	while (1)
	{
		rLen = fread(srcBuf, 1, SIZE, rFd);
		//printf("rLen = %d\n", rLen);
		if (rLen < SIZE)//小于4k
		{
			break;
		}
		
		//srcBuf 加密 -> dstBuf
		ret = DesEnc_raw(srcBuf, rLen, dstBuf, &wLen);
		if (ret != 0)
		{
			printf("DesEnc_raw 加密=4k数据失败\n");
			goto End;
			return;
		}

		//写加密后的文件
		ret = fwrite(dstBuf, 1, wLen, wFd);
		if (ret != wLen)
		{
			printf("写加密后的文件=4k数据失败\n");
			goto End;
			return;
		}

	}

	//小于4k大小读文件, srcBuf
	//srcBuf 加密-> dstBuf
	//srcBuf 加密 -> dstBuf
	ret = DesEnc(srcBuf, rLen, dstBuf, &wLen);
	if (ret != 0)
	{
		printf("DesEnc_raw 加密<4k数据失败\n");
		goto End;
		return;
	}

	//写加密后的文件
	ret = fwrite(dstBuf, 1, wLen, wFd);
	if (ret != wLen)
	{
		printf("写加密后的文件<4k数据失败\n");
		goto End;
		return;
	}

End:
	if (rFd != NULL)
	{
		fclose(rFd);
	}

	if (wFd != NULL)
	{
		fclose(wFd);
	}


}

//解密文件
void DecFile()
{

}

int main(void)
{
	int cmd;
	while (1)
	{
		menu();
		printf("cmd:");
		scanf("%d", &cmd);

		switch (cmd)
		{
		case 1:
			EncFile();
			break;
		case 2:
			DecFile();
			break;
		case 3:
			system("cls");
			break;
		default:
			exit(0);
			break;
		}

	}

	printf("\n");
	system("pause");
	return 0;
}