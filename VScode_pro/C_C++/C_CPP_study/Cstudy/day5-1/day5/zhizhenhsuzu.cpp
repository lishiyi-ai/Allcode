#include<iostream>
#include<string>

using namespace std;

// argc:传参数的个数（包含可执行程序）
// argv:指针数组， 指向输入的参数

int main(int argc, char *argv[]){
    // 数组指针，指针数组
    
    //指针数组，他是数组，每个元素都是指针
    // [] 比 * 优先级高
    char *a[] = {"aaaaa","bbbbbb","cccccccccc"};
    int i = 0;

    printf("argc = %d\n", argc);
    
    for(i = 0;i < argc;i++){
        printf("%s\n",argv[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}