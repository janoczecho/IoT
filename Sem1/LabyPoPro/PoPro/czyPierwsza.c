#include <stdio.h>
#include <stdbool.h>
bool czyPierwsza(int n)
{
    if (n < 2)
        {
            return false;
        }
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
    
}

int main(void)
{
    int ile;
    scanf("%d", &ile);
    for (int i = 0; i < ile; i++)
    {
        int liczba;
        scanf("%d", &liczba);
        if (czyPierwsza(liczba) == true)
        {
            printf("TAK \n");
        }
        else
        {
            printf("NIE \n");
        }
    }
    return 0;
}