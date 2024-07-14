#include<stdio.h>
#include <stdlib.h>

int main(){
    char ch = 'C';
    // printf("%d", &ch);
    int a = scanf("%c", &ch);
    printf("%d ", a);
    printf("%c", ch);

    system("pause");
    return 0;
}