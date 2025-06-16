#include <stdio.h>
int main(void)
{
	int myNumber1, myNumber2, wynik;
	wynik = 0;
	printf("Wpisz pierwsz¹ liczbê: \n");
	scanf("%d", &myNumber1);
	printf("Wpisz drug¹ liczbê: \n");
	scanf("%d", &myNumber2);
	wynik = myNumber1 * myNumber2;
	printf("Wynik mno¿enia tych liczb to %d", wynik);
	return 0;
}
