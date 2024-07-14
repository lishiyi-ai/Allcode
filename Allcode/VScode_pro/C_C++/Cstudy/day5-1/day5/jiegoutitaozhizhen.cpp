#include<iostream>
#include<string.h>

using namespace std;


typedef struct Teacher{
    // char name[50];
    char *name;
    int age;
}Teacher;

void showTeacher(Teacher *q, int n){
    for(int i = 0;i < n; i++){
        printf("%s, %d\n", q[i].name, q[i].age);
    }
}

void freeTeacher(Teacher *q, int n){
    for(int i = 0;i < n; i++){
        if(q[i].name != NULL){
            free(q[i].name);
            q[i].name = NULL;
        }
    }

    if(q != NULL){
        free(q);
        q = NULL;
    }
}

Teacher *getMem(int n){
    
    Teacher *q = NULL;
    q = (Teacher *)malloc(3 * sizeof(Teacher));

    for(int i = 0;i < 3;i++){
        q[i].name = (char *)malloc(30);
        strcpy(q[i].name, "liyi");
        q[i].age = 20 + i; 
    }
    return q;
}

int getMem1(Teacher **tmp, int n){
    
    if(tmp ==NULL){
        return -1;
    }
    Teacher *q = NULL;
    q = (Teacher *)malloc(3 * sizeof(Teacher));

    for(int i = 0;i < 3;i++){
        q[i].name = (char *)malloc(30);
        strcpy(q[i].name, "liyi");
        q[i].age = 20 + i; 
    }
    *tmp = q;

    return 0;
}

int main(int argc,char *argv[]){
#if 0
    char *name = NULL;
    name = (char *)malloc(30);
    strcpy(name, "liyi");
    printf("name = %s \n", name);
    if(name != NULL){
        free(name);
        name = NULL;
    }
#endif

    //1
    Teacher t;
    t.name = (char *)malloc(30);
    strcpy(t.name, "liyi");
    t.age = 22;
    printf("name = %s, age = %d\n",t.name, t.age);
    if(t.name !=NULL){
        free(t.name);
        t.name = NULL;
    }
    //2
    Teacher *p = NULL;
    p = (Teacher *)malloc(sizeof(Teacher));
    p->name = (char *)malloc(30);
    strcpy(p->name, "liyi");
    p->age = 22;
    printf("name = %s, age = %d\n",p->name,p->age);
    if(p->name !=NULL){
        free(p->name);
        p->name = NULL;
    }
    if(p !=NULL){
        free(p);
        p = NULL;
    }

    //3
    Teacher *q = NULL;

    // q = getMem(3);

    int ret = 0;
    ret = getMem1(&q, 3);

    if(ret != 0){
        return ret;
    }
    q = (Teacher *)malloc(3 * sizeof(Teacher));

    for(int i = 0;i < 3;i++){
        q[i].name = (char *)malloc(30);
        strcpy(q[i].name, "liyi");
        q[i].age = 20 + i; 
    }

    showTeacher(q, 3);

    freeTeacher(q, 3);
    q = NULL;

    printf("\n");
    system("pause");
    return 0;
}