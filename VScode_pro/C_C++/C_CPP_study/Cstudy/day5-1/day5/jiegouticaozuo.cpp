#include<iostream>
#include<string.h>

using namespace std;


// 定义结构体类型时不要直接给成员赋值
// 结构体只有一个类型，还没有分配空间
typedef struct Teacher{
    char name[50];
    int age;
}Teacher;

void copyTeacher(Teacher *to, Teacher *from){
    *to = *from;
    printf("%s, %d\n", (*to).name, (*to).age);
}
void fun(int to, int from){
    to = from;
    printf("%d\n", to);
}
int main(int argc,char *argv[]){
	
    Teacher t1 = {"liyi", 22};

    // 相同类型的两个结构体变量，可以相互直接赋值
    // 把t1成员变量内存的值拷贝成t2成员变量的内存
    // t1和t2没有关系
    Teacher t2 = t1;
    printf("%s, %d\n", t2.name, t2.age);
    
    int a = 10;
    int b = a;// a的值给了b a，b没有关系
    Teacher t3;
    memset(&t3, 0,sizeof(t3));
    copyTeacher(&t3, &t1);
    printf("%s, %d\n", t3.name, t3.age);

    int c = 10;
    int d = 0;
    fun(d, c);//c的值给d
    printf("%d\n", d);

    printf("\n");
	system("pause");
	return 0;
}