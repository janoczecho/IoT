#include <stdio.h>
int main(void)
{
	int myNumber1, myNumber2, wynik;
	char* znak;
	wynik = 0;
	printf("Wpisz pierwszą liczbę: \n");
	scanf("%d", &myNumber1);
	printf("Wpisz drugą liczbę: \n");
	scanf("%d", &myNumber2);
	printf("Wpisz znak operacyjny: \n");
	scanf("%c", &znak);
	if (znak == '+')
	{
		wynik = myNumber1 + myNumber2;
	}
	printf("Wynik operacji tych liczb to %d", wynik);
	return 0;
}