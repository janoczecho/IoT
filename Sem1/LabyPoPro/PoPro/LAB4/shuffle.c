//Jan Czechowski

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int ile = 7;
    int ileDobrych = 0;
    char wyrazOryginalny[ile + 1];
    puts("Wprowadz litery");
    for (int i = 0; i < ile; i++) {
        char litera;
        scanf(" %c", &litera);
        if (isalpha(litera))
        {
            wyrazOryginalny[i] = litera;
            ileDobrych += 1;
        }
        else
        {
            puts("Zły znak");
            break;
        }
    }
    if (ileDobrych == ile) {
        wyrazOryginalny[ile] = '\0';
        printf("Wyraz oryginalny: %s\n", wyrazOryginalny);

        srand(time(NULL));
        for (int i = ile - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            char temp = wyrazOryginalny[i];
            wyrazOryginalny[i] = wyrazOryginalny[j];
            wyrazOryginalny[j] = temp;
        }

        printf("Nowy wyraz: %s\n", wyrazOryginalny);
    }

    return 0;
}
