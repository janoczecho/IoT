#include <stdio.h>
void zamianaLiczb(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void){
    int liczba1;
    int liczba2;
    puts("Podaj pierwsza liczbe");
    scanf("%d",&liczba1);
    puts("Podaj fruga liczbe");
    scanf("%d",&liczba2);
    printf("Liczby przed zamiana to: %d i %d\n", liczba1, liczba2);
    zamianaLiczb(&liczba1,&liczba2);
    printf("Liczby po zamianie to: %d i %d", liczba1, liczba2);
    return 0;
}