// Autorzy: Jan Czechowski i Kinga Konieczna

#include <stdio.h>

struct Fuel {
    float distance;
    float volume;
    float performance;
};

typedef struct Fuel Fuel;

Fuel obliczPerformance(Fuel fuel) {
    if (fuel.volume != 0) {
        fuel.performance = fuel.distance / fuel.volume;
    } else {
        printf("Błąd: objętość paliwa nie może wynosić 0.\n");
        fuel.performance = 0;
    }
    return fuel;
}

void obliczPerformancePointer(Fuel* fuel) {
    if (fuel -> volume != 0) {
        fuel -> performance = fuel -> distance / fuel -> volume;
    } else {
        printf("Błąd: objętość paliwa nie może wynosić 0.\n");
        fuel -> performance = 0;
    }
}

void przeliczJednostki(Fuel* fuel) {
    if (fuel -> volume != 0) {
        float distanceInMiles = fuel -> distance / 1.6;
        float volumeInGallons = fuel -> volume / 3.8;
        fuel -> performance = distanceInMiles / volumeInGallons;
    } else {
        printf("Błąd: objętość paliwa nie może wynosić 0.\n");
        fuel -> performance = 0;
    }
}

int main(void) {
    Fuel myFuel = {400.0, 20.0, 0.0};

    myFuel = obliczPerformance(myFuel);
    printf("Performance (km/l): %.2f\n", myFuel.performance);

    obliczPerformancePointer(&myFuel);
    printf("Performance (km/l) ze wskaznika: %.2f\n", myFuel.performance);

    przeliczJednostki(&myFuel);
    printf("Performance (mil/galon): %.2f\n", myFuel.performance);

    return 0;
}
