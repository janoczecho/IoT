// Lab. 7, zadanie 2
//
//Jan Czechowski
//337066
//25.11.2024


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct my_ints
{
	uint8_t abyte;
	uint16_t aword;
	uint32_t anint;
	uint64_t alongestint;
}my_ints_t;

//1. Remove memory leakage from the program
int main()
{
	printf("\n\n\nSize of my_ints_t is %lu\n",(unsigned long)sizeof(my_ints_t));
	//2. Comment the result of the above command
	/*
	Powyższa komenda printuje sume rozmiarow elementow ze struktury i wynik moze byc rozny w zaleznosci od kompilatora
	*/
	my_ints_t *m=NULL;
	int howmany=-1;
	unsigned int tries=0;

	for(;;) //preferred infinite loop in C  
	{
		tries++;
		printf("Type a number of structs in the array or 0 to exit:\n");
		
		howmany=-1;
		if ((scanf("%d",&howmany)!=1)||(howmany<0))
		{
			printf("Invalid input, try again!\n\n");
			continue;
		}
		if (howmany==0) break;

		printf("Allocating %u bytes\n",sizeof(my_ints_t)*howmany);

		
		m=(my_ints_t*)malloc(sizeof(my_ints_t)*howmany);
		if (m==NULL)
		{
			printf("Bad alloc!\n");
			break;
		}

		for (uint64_t ii=0;ii<howmany;ii++) m[ii].anint=tries;
		free(m);
		m = NULL;
	}
	
	if (m!=NULL)
	{
		printf("In all array elements an .aint filed is set to %u\n",m[0].anint);
	}

	char e=0;
	printf("Type 'e' to exit\n");
	for(;;)
	{
		scanf("%c",&e);
		if (e=='e') break;
	}
	return 0;
}
