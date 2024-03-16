#include<iostream>
#include<string.h>

using namespace std;


typedef struct Teacher{
    char name[50];
    // char *name;
    int age;
}Teacher;
int main(int argc, char *agrv[]){

    Teacher a[3] = {
        {"a", 18},
        {"b", 19},
        {"c", 20},
    };

    // 静态
    Teacher a2[3] = {"a", 18, "a", 18, "a", 18};
    int i = 0;
    for(int i = 0;i < 3; i++){
        printf("%s, %d\n", a2[i].name, a2[i].age);
    }

    int b[3] = {0};
    int *pB = (int *)malloc(3 * sizeof(int));
    free(pB);
    // 动态
    Teacher *p = (Teacher *)malloc(3 * sizeof(Teacher));
    if(p == NULL){
        return -1;
    }
    char buf[50];
    for(int i = 0;i < 3; i++){
        sprintf(buf, "name%d%d%d", i, i, i);
        strcpy(p[i].name, buf);
        p[i].age = 20 + i;
    }

    for(int i = 0;i < 3; i++){
        printf("第%d个: %s, %d\n", i+1, a2[i].name, a2[i].age);
    }

    if(p != NULL){
        free(p);
        p = NULL;
    }
    printf("\n");
	system("pause");
	return 0;

}