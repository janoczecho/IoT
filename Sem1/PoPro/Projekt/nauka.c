#include <stdio.h>
int main(void){
    int a = 5;
    int b = 9;
    printf("%d \t %d\n",a,b);
    zamiana(&a, &b);
    printf("%d \t %d",a,b);
    return 0;
}

void zamiana(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}