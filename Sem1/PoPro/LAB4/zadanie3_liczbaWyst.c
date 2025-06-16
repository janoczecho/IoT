//Jan Czechowski

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int liczba_wystapien[10] = {0};
    char *input = argv[1];
    for (int i = 0; input[i] != '\0'; i++) {
        if (isdigit(input[i])) {
            int digit = input[i] - '0';
            liczba_wystapien[digit]++;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (liczba_wystapien[i] > 0) {
            printf("%d: %d\n", i, liczba_wystapien[i]);
        }
    }

    return 0;
}
