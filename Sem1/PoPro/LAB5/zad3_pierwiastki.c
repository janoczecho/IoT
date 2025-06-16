#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int pierwiastki(double a, double b, double c, double *wsk_x1, double *wsk_x2) {
    double delta = b * b - 4 * a * c;

    if (a == 0) {
        if (b == 0)
        {
            return 0;
        }
        else
        {
            *wsk_x1 = *wsk_x2 = -c / b;
            return 1;
        }
    }

    if (delta > 0) {
        *wsk_x1 = (-b - sqrt(delta)) / (2 * a);
        *wsk_x2 = (-b + sqrt(delta)) / (2 * a);
        return 2;
    }
    else if (delta == 0) {
        *wsk_x1 = *wsk_x2 = -b / (2 * a);
        return 1;
    }
    else {
        return 0;
    }
}

int main(void) {
    double a, b, c, x1, x2;
    int liczba;
    printf("Podaj wspolczynniki a, b i c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    liczba = pierwiastki(a, b, c, &x1, &x2);

    if (liczba == 2) {
        printf("Rownanie ma 2 pierwiastki: x1 = %lf, x2 = %lf\n", x1, x2);
    } else if (liczba == 1) {
        printf("Rownanie ma 1 pierwiastek: x1 = x2 = %lf\n", x1);
    } else {
        puts("Rownanie nie ma pierwiastkow");
    }

    return 0;
}
