#include <stdio.h>
void laczenie(char tablica1[], char tablica2[], int len1, int len2, char PolaczonaTablica[])
{
    for (int i = 0; i < len1; i++)
    {
        PolaczonaTablica[i] = tablica1[i];
    }
    for (int j = 0; j < len2; j++)
    {
        PolaczonaTablica[j+len1]=tablica2[j];
    }
    PolaczonaTablica[len1+len2] = '\0';
}

void BubbleSort(char tablica[], int lenTablicy)
{
    for (int i = 0; i < lenTablicy; i++)
    {
        for (int j = 0; j < (lenTablicy - 1); j++)
        {
            if (tablica[j]>tablica[j+1])
            {
                char temp =tablica[j+1];
                tablica[j+1] = tablica[j];
                tablica[j] = temp;
            }
            else
            {
                continue;
            }         
        }
        
    }
}

int main(void)
{
    char tab1[]="72126";
    char tab2[]="346511087";
    int lenTablicy1 = sizeof(tab1)/sizeof(tab1[0])-1;
    int lenTablicy2 = sizeof(tab2)/sizeof(tab2[0])-1;
    char Polaczona[lenTablicy1+lenTablicy2+1];
    laczenie(tab1,tab2,lenTablicy1,lenTablicy2,Polaczona);
    BubbleSort(Polaczona,lenTablicy1+lenTablicy2);
    puts(Polaczona);
    return 0;

}
