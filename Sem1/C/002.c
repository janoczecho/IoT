#include <stdio.h>

int main(void) {
    int myNumber1, myNumber2, wynik;
    char znak;
    wynik = 0;

    printf("Wpisz pierwsza liczbe: \n");
    scanf("%d", &myNumber1);

    printf("Wpisz druga liczbe: \n");
    scanf("%d", &myNumber2);

    printf("Wpisz znak operacyjny (+ lub -): \n");
    scanf(" %c", &znak); // Space before %c to consume any newline left in the buffer

    if (znak == '+') {
        wynik = myNumber1 + myNumber2;
        printf("Wynik operacji tych liczb to %d\n", wynik);
    } 
    else if (znak == '-') {
        wynik = myNumber1 - myNumber2;
        printf("Wynik operacji tych liczb to %d\n", wynik);
    } 
    else {
        printf("Zly znak: %c\n", znak);  // Corrected the format and added printing of `znak`
        return 1;  // Exits with error code 1 for wrong operator
    }

    return 0;
}
#include <stdio.h>
int main(void)
{
	int myNumber1, myNumber2, wynik;
	char znak;
	wynik = 0;
	printf("Wpisz pierwsza liczbe: \n");
	scanf("%d", &myNumber1);
	printf("Wpisz druga liczbe: \n");
	scanf("%d", &myNumber2);
	printf("Wpisz znak operacyjny: \n");
	scanf(" %c", &znak);
	if (znak ==  '+')
	{
		wynik = myNumber1 + myNumber2;
		printf("Wynik operacji tych liczb to %d", wynik);
		return 0;
	}
	else if (znak == '-')
	{
		wynik = myNumber1 - myNumber2;
		printf("Wynik operacji tych liczb to %d", wynik);
		return 0;
	}
	else if (znak == '*')
	{
		wynik = myNumber1 * myNumber2;
		printf("Wynik operacji tych liczb to %d", wynik);
		return 0;
	}
	else if (znak == '/')
	{
		wynik = myNumber1 / myNumber2;
		printf("Wynik operacji tych liczb to %d", wynik);
		return 0;
	}
	else {
		printf("Zly znak: %c\n", znak);
		return 1;
	}
	return 0;
}