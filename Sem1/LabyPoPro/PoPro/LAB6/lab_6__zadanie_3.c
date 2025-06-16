// Autorzy: Jan Czechowski, Kinga Konieczna

#include <stdio.h>
#include <math.h>

struct Punkt {
    double x;
    double y;
};
typedef struct Punkt Punkt;

void rysujWykres(const Punkt tablica[], int rozmiar) {
    double max_y = 0.0;
    for (int i = 0; i < rozmiar; i++) {
        if (tablica[i].y > max_y) {
            max_y = tablica[i].y;
        }
    }

    for (double poziom_y = max_y; poziom_y >= 0; poziom_y -= 0.50) {
        printf("%6.2f | ", poziom_y);

        for (int i = 0; i < rozmiar; i++) {
            if (fabs(tablica[i].y - poziom_y) < 0.25) {
                printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }

    printf("       +");
    for (int i = 0; i < rozmiar; i++) {
        printf("--");
    }
    printf("\n        ");
    for (int i = 0; i < rozmiar; i++) {
        printf("%2.0f", tablica[i].x);
    }
    printf("\n");
}

int main() {
    Punkt punkty[20];

    for (int i = 0; i < 20; i++) {
        punkty[i].x = i;
        punkty[i].y = 0.5 * i;
    }

    printf(" Wykres punktów (y = 0.5x):\n\n");

    rysujWykres(punkty, 20);

    return 0;
}
