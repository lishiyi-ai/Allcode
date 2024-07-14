#include <iostream>
#include <string.h>

// 结构体类型定下来,内部的成员变量的内存布局已经确定
typedef struct Teacher{
    char name[64];
    int age;
    int id;
}Teacher;


int main(int argc, char *argv[]){

    Teacher t1;
    Teacher *p = NULL;
    p = &t1;

    // int n1 = &(p->age);
    // int n2 = p;
    printf("%d %d\n", p, &p->age);//相对于结构体

    printf("%d\n", &((Teacher *)0)->age);//绝对值0的相对量

    printf("\n");
    system("pause");
    return 0;
}