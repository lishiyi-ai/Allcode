#include <iostream>
#include <string.h>


typedef struct Teacher{
    char *name;
    int age;
}Teacher;
// 结构体中嵌套指针，而且动态分配空间
// 同类型结构体变量赋值
// 不同结构体成因指针变量主席昂同一块内存

int main1(int argc,char *argv[]){

// 浅拷贝
    Teacher t1;
    t1.name = (char *)malloc(30);
    strcpy(t1.name, "liyi");
    t1.age = 22;

    Teacher t2;
    t2 = t1;
    printf("[t2]%s, %d\n", t2.name, t2.age);

    if( t1.name != NULL){
        free(t1.name);
        t1.name = NULL;
    }

    if( t2.name != NULL){
        free(t2.name);
        t2.name = NULL;
    }


    printf("\n");
    system("pause");
    return 0;
}

int main(int argc,char *argv[]){

// 深拷贝
    Teacher t1;
    t1.name = (char *)malloc(30);
    strcpy(t1.name, "liyi");
    t1.age = 22;

    Teacher t2;
    t2 = t1;
    // 人为增加内存，重新拷贝一次
    t2.name = (char *)malloc(30);
    strcpy(t2.name, t1.name);
    printf("[t2]%s, %d\n", t2.name, t2.age);
    printf("%d, %d",&t1.age, &t2.age);
    if( t1.name != NULL){
        free(t1.name);
        t1.name = NULL;
    }

    if( t2.name != NULL){
        free(t2.name);
        t2.name = NULL;
    }


    printf("\n");
    system("pause");
    return 0;
}