//Jan Czechowski

#include <stdio.h>
#include <math.h>

double triSide(double ax, double ay, double bx, double by)
{
    double bok;
    bok = sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
    return bok;
}

double triPeri(double a, double b, double c)
{
    double obwod;
    obwod = a + b + c;
    return obwod;
}

double triArea(double ax, double ay, double bx, double by, double cx, double cy)
{
    double pole;
    double a = triSide(ax,ay,bx,by);
    double b = triSide(ax,ay,cx,cy);
    double c = triSide(cx,cy,bx,by);
    double obwod = triPeri(a, b, c);
    double p = obwod/2;
    pole = sqrt(p*(p-a)*(p-b)*(p-c));
    return pole;
}

int main(void)
{
    double ax, ay, bx, by, cx, cy;
    printf("Podaj wspolrzedne punktu A (ax ay): ");
    scanf("%lf %lf", &ax, &ay);
    printf("Podaj wspolrzedne punktu B (bx by): ");
    scanf("%lf %lf", &bx, &by);
    printf("Podaj wspolrzedne punktu C (cx cy): ");
    scanf("%lf %lf", &cx, &cy);
    double pole = triArea(ax, ay, bx, by, cx, cy);
    printf("Pole trojkata wynosi: %lf", pole);
    return 0;
}