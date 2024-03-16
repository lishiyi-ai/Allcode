#include<iostream>
#include<string.h>
using namespace std;

/*
1、结构体类型定义
2、结构体变量定义
3、结构体变量的初始化
4、typedef改类型名
5、点运算符和指针发操作结构体
6、结构体也是一种数据类型，复合类型，自定义类型
*/

// struct关键字
// struct Teacher合一起才是类型
struct  Teacher
{
    char name[50];
    int age;
};

// 2、结构体变量定义
// 1、先定义类型，在定义变量(常用)
struct Teacher t1;
// 2、定义类型同时定义变量
struct  Teacher1
{
    char name[50];
    int age;
}t3, t4;
struct Teacher t1;
struct{
    char name[50];
    int age;
}t5,t6;

// 3、结构体变量的初始化
// 定义变量时直接初始化，通过{}
struct Teacher t7 = {"liyi",10};

// 4、typedef改类型名
typedef struct Teacher3
{
    char name[50];
    int age;
}Teacher3;

struct Teacher3 t8;

int main(){
    struct Teacher t2;

    printf("%s %d\n", t7.name, t7.age);

    // 5、点运算符和指针法操作结构体
    strcpy(t2.name, "xiaoming");
    t2.age = 22;
    printf("%s, %d\n", t2.name, t2.age);

    struct Teacher *p = NULL;
    p = &t2;
    strcpy(p->name, "xiaojiang");
    p->age = 22;
    printf("%s, %d\n",p->name, p->age);

    printf("\n");
    system("pause");
    return 0;
}