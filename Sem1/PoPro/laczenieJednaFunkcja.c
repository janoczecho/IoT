#include <stdio.h>

int main(void) {
    char tab1[] = "19876";
    char tab2[] = "2134";

    int lenTablicy1 = sizeof(tab1) / sizeof(tab1[0]) - 1;
    int lenTablicy2 = sizeof(tab2) / sizeof(tab2[0]) - 1;

    char Polaczona[lenTablicy1 + lenTablicy2 + 1];

    for (int i = 0; i < lenTablicy1; i++) {
        Polaczona[i] = tab1[i];
    }
    for (int j = 0; j < lenTablicy2; j++) {
        Polaczona[j + lenTablicy1] = tab2[j];
    }
    Polaczona[lenTablicy1 + lenTablicy2] = '\0';

    int lenPolaczonej = lenTablicy1 + lenTablicy2;
    for (int i = 0; i < lenPolaczonej; i++) {
        for (int j = 0; j < lenPolaczonej - 1; j++) {
            if (Polaczona[j] > Polaczona[j + 1]) {
                char temp = Polaczona[j];
                Polaczona[j] = Polaczona[j + 1];
                Polaczona[j + 1] = temp;
            }
        }
    }

    puts(Polaczona);

    return 0;
}
