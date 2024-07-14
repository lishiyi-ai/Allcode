#include<iostream>

using namespace std;

int main(){

// 一维数组
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    // 定义时必须初始化
    int a1[100] = {1, 2, 3, 4};
    int n = 0;
    // sizeof求的是所占的空间(变量所对应类型的空)
    // sizeof(a) = type * length
    n = sizeof(a) / sizeof(a[0]);

    for(int i=0;i<n;i++){
        // *(a+i):a+i代表第i元素地址
        printf("%d ",a[i]);
    }
    printf("\n");

    // 数组类型
    // a 代表首元素地址
    // &a代表整个数组首地址， 他和首元素地址一样的，但是，他们的步长不一样
    printf("a:%d, a+1:%d ", a, a+1);
    printf("&a:%d, &a+1:%d\n", &a, &a+1);

    // 数组类型：由元素个数 和元素类型对应 int [8]
    // 通过typedef定义一个数组类型
    // 有typedef是类型，没有类型
    
    typedef int A[8];//代表数组类型
    A b;// int b[8],去了typedef, b替换到A的位置

    for(int i=0;i<8;i++){
        b[i] = 2*i+1;
    }

    for(int i=0;i<8;i++){
        printf("%d",b[i]);
    }
    printf("\n");
    printf("b:%d, b+1:%d ", b, b+1);
    printf("&b:%d, &b+1:%d\n", &b, &b+1);
    printf("\n");
    system("pause");
    return 0;
} 