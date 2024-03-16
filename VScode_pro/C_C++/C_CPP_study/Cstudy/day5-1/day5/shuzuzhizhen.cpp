#include<iostream>
#include<string>

using namespace std;

// argc:传参数的个数（包含可执行程序）
// argv:指针数组， 指向输入的参数

int main1(int argc, char *argv[]){
    // 数组指针，指针数组
    
    //数组指针，它是指针，指向一个数组的指针
    // 数组指针指向整个数组，而不是数组的首元素
    // 定义数组指针变量

    int a[10] = {0};

    //1.先定义数组类型，根据类型定义指针变量
    typedef int A[10];
    A *p = NULL;//p数组指针类型变量

    // p = a;有警告

    p = &a;

    printf("p: %d p+1: %d\n", p, p+1);

    for(int i=0;i<10;i++){
        (*p)[i] = i+1;
    }

    for(int i=0; i<10; i++){
        printf("%d ", (*p)[i]);

    }
    printf("\n");

    printf("\n");
    system("pause");
    return 0;
}

int main2(void){

    int a[10]={0};
    // 2.定义数组指针类型，根据类型定义变量
    // 和指针数组写法很类似，多了()
    // ()和[]优先级一样，从左往右
    // ()有指向数组的指针，他有typedef，所以他是一个数组指针类型
    typedef int (*P)[10];
    P q;
    q = &a;
        for(int i=0;i<10;i++){
        (*q)[i] = i*2+1;
    }

    for(int i=0; i<10; i++){
        printf("%d ", (*q)[i]);

    }
    printf("\n");
    system("pause");
    return 0;
}

void fun(void *a){
    printf("%lld\n", (long long)a);
}

int main3(void){
    // 小尝试
    long long a1 = 10;
    void *b;
    printf("sizoef(b):%d \n",sizeof(b));
    fun((void *)a1);
    
    
    int a[10]={0};
    // 2.直接定义数组指针变量
    // 和指针数组写法很类似，多了()
    // ()和[]优先级一样，从左往右
    // ()有指向数组的指针，没有typedef，所以他是一个数组指针类型
    int (*q)[10];
    q = &a;
        for(int i=0;i<10;i++){
        (*q)[i] = i*2+3;
    }

    for(int i=0; i<10; i++){
        printf("%d ", (*q)[i]);

    }
    printf("\n");
    system("pause");
    return 0;
}

int main4(void){

    // int a[3][4] = {
    //     {1, 2, 3, 4},
    //     {5, 6, 7, 8},
    //     {9, 10, 11, 12}
    // };

    int a2[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    int a3[][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    int i = 0;
    int j = 0;
    for(i = 0;i < 3;i++){
        for(j = 0;j < 4;j++){
            printf("%d ", a2[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    
    int a[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    // +16
    // 二维数组名a表示 代表第0行的首地址(区别于第0行首元素地址，虽然值一样)
    // 他们步长不一样
    // 二维数组a代表一维首行地址
    printf("a:%d, a+1:%d\n",a, a+1);
    printf("%d, %d \n", *(a+0), *(a+0)+1 ); //第0行首元素地址, 第0行第二个元素
    printf("%d, %d \n",a[0],a[0]+1);

    // a ： 代表首行首地址
    // a+i -> &a[i] : 代表第i行首地址
    // *(a+i) ->  a[i] : 代表第i行首元素地址
    // *(a+i) + j -> &a[i][j] : 代表第i行第j列元素地址
    // *(*(a+i)+j) -> a[i][j] : 第i行第j列元素的值

    printf("\n");
    system("pause");
    return 0;
}
void printA(int *a, int n){
    int i = 0;
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}
int main5(){
    int a[][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    printf("%d \n", sizeof(a));
    printA((int *)a, sizeof(a)/sizeof(a[0][0]));
    
    printf("\n");
    system("pause");
    return 0;

}

int main6(){
    int a[][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    // 3个a[4]的一维素组

    // 定义数组指针类型，在定义变量
    // typedef int(*P)[4];
    // P p;
    // p = a;

    // 定义数组指针变量
    // 指向一维数组的整个数组首地址
    int (*p)[4];
    //p=&a[0]; //整个二维数组首地址 p = a;
    p = a; //第0行首地址
    printf("p:%d,p+1:%d\n", p, p+1); // 4*4

    int n = sizeof(a) / sizeof(a[0]);
    int nj = sizeof(a[0]) / sizeof(a[0][0]);

    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 4;j++){
            // printf("%d ", p[i][j]);
            printf("%d ", *(*(p+i)+j));
        }
        printf("\n");
    }

    int t[2][10];
    // 测一维数组长度：sizeof()首行首元素地址
    printf("sizeof(t) = %d, sizeof(&t) %d\n", sizeof(t), sizeof(&t));

    // int a[2][j];
    printf("sizeof(a[0]):%d, sizeof(&a[0]): %d\n", sizeof(a[0]), sizeof(&a[0]));
    printf("sizeof(*(a+0)):%d, sizeof(a+0): %d\n", sizeof(*(a+0)), sizeof(a+0)); 

    printf("\n");
    system("pause");
    return 0;
}

void printArray(int a[3][4]){
    for(int i = 0; i < 3;i++){
        for(int j = 0;j < 4;j++){
            printf("%d ", a[i][j]);
        }
    }
}

void printArray2(int a[][4]){
    for(int i = 0; i < 3;i++){
        for(int j = 0;j < 4;j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void printArray3(int **a){
    for(int i = 0; i < 3;i++){
        for(int j = 0;j < 4;j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void printArray4(int (*a)[4]){
    for(int i = 0; i < 3;i++){

        for(int j = 0;j < 4;j++){
            
            printf("%d ", a[i][j]);
        
        }
        printf("\n");
    }   
}

int main(){
    
    int a[][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    printArray(a);
    printArray2(a);
    printArray3(a);
    printArray4(a);
    printf("\n");
    system("pause");
    return 0;
}
