#include <iostream>
#include <string.h>

struct
{
    double c;
	int a;
    // double c;
	short b;
}A;


struct A
{
	int a;
	double b;
	float c;
};

struct
{
	char e[2];
	int f;
	double g;
	short h;
	struct A i;
}B;

int main(int argc,char *argv[]){


    printf("%d\n", sizeof(A));



    printf("\n");
    system("pause");
    return 0;
}