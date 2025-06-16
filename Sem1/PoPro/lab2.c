#include <stdio.h>

int main(int argc, char *argv[]) {
    // Sprawdzenie, czy podano wystarczającą liczbę argumentów
    if (argc < 3) {
        printf("Usage: %s <name> <nickname>\n", argv[0]);
        return 1; // Zwracamy kod błędu
    }

    // Wypisanie powitania z imieniem i pseudonimem
    printf("Hello world, %s (%s)!\n", argv[1], argv[2]);

    return 0;
}
