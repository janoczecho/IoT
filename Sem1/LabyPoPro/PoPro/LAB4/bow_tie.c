//Jan Czechowski

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    for (int i = 0; i < M / 2; i++) {
        for (int j = 0; j < N; j++) {
            if (j < i + 1 || j >= N - i - 1) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }

    for (int j = 0; j < N; j++) {
        printf("*");
    }
    printf("\n");

    for (int i = M / 2 - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            if (j < i + 1 || j >= N - i - 1) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }

    return 0;
}
