#include <stdio.h>
/// @brief 
/// @param  
/// @return 
int main(void)
{
    int liczbaOperacji;
    printf("Podaj liczbe operacji: \n");
    scanf("%d", &liczbaOperacji);
    for(int i = 1; i <= liczbaOperacji; i++)
        {
            int myNumber1, myNumber2, wynik;
            char znak;
            wynik = 0;
            printf("Wpisz pierwsza liczbe: \n");
            scanf("%d", &myNumber1);
            printf("Wpisz druga liczbe: \n");
            scanf("%d", &myNumber2);
            printf("Wpisz znak operacyjny: \n");
            scanf(" %c", &znak);
            if (znak ==  '+')
            {
                wynik = myNumber1 + myNumber2;
                printf("Wynik operacji tych liczb to %d \n", wynik);
            }
            else if (znak == '-')
            {
                wynik = myNumber1 - myNumber2;
                printf("Wynik operacji tych liczb to %d \n", wynik);
            }
            else if (znak == '*')
            {
                wynik = myNumber1 * myNumber2;
                printf("Wynik operacji tych liczb to %d \n", wynik);
            }
            else if (znak == '/')
            {
                if (myNumber2 == 0)
                {
                    printf("Nie mozna dzielic przez 0\n");
                }
                else
                {
                    wynik = myNumber1 / myNumber2;
                    printf("Wynik operacji tych liczb to %d \n", wynik);
                    }
            }
            else {
                printf("Zly znak: %c \n", znak);
            }
        }
    return 0;
}