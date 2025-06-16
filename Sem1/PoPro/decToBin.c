#include <stdio.h>

int DecToBin(int n)
{
    int binarny = 0;
    int mnozenie = 1;
    while (n>0)
    {
        int element = n % 2;
        binarny += element * mnozenie;
        n /= 2;
        mnozenie *=10;
    }
    return binarny;
}

int main(void)
{
    int liczba = 19;
    printf("Liczba binarna: %d", DecToBin(liczba));
}