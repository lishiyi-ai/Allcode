#include <iostream>
#include <string.h>
using namespace std;

// 一个导师， 有n个学生
typedef struct Teacher
{
    int age;
    char **stu; // 二维内存
} Teacher;

void sortTeacher(Teacher *p, int n)
{
    if (p == NULL)
    {
        return;
    }
    Teacher tmp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].age < p[j].age)
            {
                tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }
}

void showTeacher(Teacher *q, int n1, int n2);
// n1老师，n2学生
int createTeacher(Teacher **tmp, int n1, int n2)
{
    if (tmp == NULL)
    {
        return -1;
    }
    Teacher *q = NULL;
    q = (Teacher *)malloc(sizeof(Teacher) * n1);
    for (int i = 0; i < n1; i++)
    {
        q[i].stu = (char **)malloc(sizeof(char *) * n2);
        // char *stu[3]
        for (int j = 0; j < n2; j++)
        {
            q[i].stu[j] = (char *)malloc(30);
            char buf[30];
            sprintf(buf, "name%d%d%d%d", i, i, j, j);
            strcpy(q[i].stu[j], buf);
        }
        printf("%d \n", rand());
        q[i].age = 20 + (rand() % 10);
    }
    // showTeacher(q, n1, n2);
    // 间接赋值是指针存在最大意义
    *tmp = q;
    return 0;
}

void showTeacher(Teacher *q, int n1, int n2)
{
    // printf("yes");
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            printf("student:%s age:%d ", q[i].stu[j], q[i].age);
        }
        printf("\n");
    }
}

void freeTeacher(Teacher **tmp, int n1, int n2)
{
    if (tmp == NULL)
    {
        return;
    }
    Teacher *q = *tmp;
    for (int i = 0; i < n1; i++){
        for (int j = 0; j < n2; j++){
            if (q[i].stu[j] != NULL)
            {
                free(q[i].stu[j]);
                q[i].stu[j] = NULL;
            }
        }
        if (q[i].stu != NULL){
            free(q[i].stu);
            q[i].stu = NULL;
        }
    }
    if (q != NULL)
    {
        free(q);
        q = NULL;
    }
}

int main(int argc, char *argv[])
{

#if 1
    char **name = NULL;
    // char *name[3]
    int n = 3;
    name = (char **)malloc(n *sizeof(char *));
    // char buf[30]
    for(int i = 0;i < n; i++){
        name[i] = (char *)malloc(30);
        strcpy(name[i], "liyi");
    }

    for(int i = 0; i < n ;i++){
        printf("%s\n", name[i]);
    }

    for(int i =0 ; i < n ; i++){
        if(name[i] != NULL){
            free(name[i]);
            name[i] = NULL;
        }
    }

    if(name !=NULL){
        free(name);
        name =NULL;
    }
// #endif
    //1
    Teacher t;
    //t.stu[3];
    // char *name[3]
    int n = 3;
    t.stu = (char **)malloc(n *sizeof(char *));
    // char buf[30]
    for(int i = 0;i < n; i++){
        t.stu[i] = (char *)malloc(30);
        strcpy(t.stu[i], "liyi");
    }

    for(int i = 0; i < n ;i++){
        printf("%s\n", t.stu[i]);
    }

    for(int i =0 ; i < n ; i++){
        if(t.stu[i] != NULL){
            free(t.stu[i]);
            t.stu[i] = NULL;
        }
    }
    if(t.stu !=NULL){
        free(t.stu);
        t.stu =NULL;
    }
    //2
    Teacher *p = NULL;
    // p.stu[3]
    p = (Teacher *)malloc(sizeof(Teacher));
    // char *name[3]
    p->stu = (char **)malloc(n *sizeof(char *));
    for(int i = 0;i < n; i++){
        p->stu[i] = (char *)malloc(30);
        strcpy(p->stu[i], "liyi");
    }
    for(int i = 0; i < n ;i++){
        printf("%s\n", p->stu[i]);
    }
    for(int i =0 ; i < n ; i++){
        if(p->stu[i] != NULL){
            free(p->stu[i]);
            p->stu[i] = NULL;
        }
    }
    if(p->stu !=NULL){
        free(p->stu);
        p->stu =NULL;
    }
    if(p != NULL){
        free(p);
        p = NULL;
    }
#endif
    // 3
    Teacher *q = NULL;
    int ret = 0;
    int n = 3;
    // ret = createTeacher(&q, n, n);
    // Teacher *q[3]
    q = (Teacher *)malloc(sizeof(Teacher) * 3);
    for(int i = 0; i < n ; i++){
        q[i].stu = (char **)malloc(sizeof(char *) * 3);
        // char *stu[3]
        for(int j = 0; j < n; j++){
            q[i].stu[j] = (char *)malloc(30);
            char buf[30];
            sprintf(buf, "name%d%d%d%d", i, i, j, j);
            strcpy(q[i].stu[j], buf);
        }
    }
    // 排序前
    // showTeacher(q, n, n);
    // sortTeacher(q, n);
    // printf("\n");
    // 排序后
    // showTeacher(q, n, n);
    for(int i = 0; i < 3; i++){
        printf("%s, %s, %s\n",q[i].stu[0], q[i].stu[1], q[i].stu[2]);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%s ", q[i].stu[j]);
        }
        printf("\n");
    }
    // freeTeacher(&q, n, n);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0; j < n;j++){
            if(q[i].stu[j] != NULL){
               free(q[i].stu[j]);
               q[i].stu[j] = NULL;
            }
        }
        if(q[i].stu != NULL){
            free(q[i].stu);
            q[i].stu = NULL;
        }
    }
    if(q != NULL){
        free(q);
        q = NULL;
    }

    printf("\n");
    system("pause");
    return 0;
}