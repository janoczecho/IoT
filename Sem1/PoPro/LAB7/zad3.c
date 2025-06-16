// Lab. 7, zadanie 3
//Jan Czechowski
//337066
//25.11.2024
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M (4)
#define N (5)

/*
//allocates memory for a 2D array of given dimensions
//returns NULL on bad alloc or invalid user input
//no printf or scanf inside!
int* alloc2D(some_in){} 
*/
int* alloc2D(int rows, int cols) {
    int* array = (int*)malloc(rows * cols * sizeof(int));  
    if (array == NULL) {
        return NULL;
    }
    return array;
}
/*
//fills a 2D array of given dimensions so that array[i][j]=10*i+j;
//no printf or scanf inside!
void fill2D(some_in){} 
*/
void fill2D(int* array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i * cols + j] = 10 * i + j;
        }
    }
}

/*
//prints a 2D array in a pretty way!
//no scanf inside!
void print2D(some_in){} 
*/
// Prints a 2D array in a pretty way!
// No scanf inside!
void print2D(int* array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i * cols + j]);
        }
        printf("\n");
    }
}

int main()
{
    int array2D_stat[M][N];
    int *array2D_dyn = NULL;

    // Allocate array2D_dyn using 'alloc2D' so that it is equivalent to array2D_stat
    array2D_dyn = alloc2D(M, N);
    if (array2D_dyn == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Fill array2D_stat using 'fill2D'
    fill2D((int*)array2D_stat, M, N);

    // Fill array2D_dyn using 'fill2D'
    fill2D(array2D_dyn, M, N);

    // Print array2D_stat using 'print2D'
    printf("Static Array2D:\n");
    print2D((int*)array2D_stat, M, N);

    // Print array2D_dyn using 'print2D'
    printf("Dynamic Array2D:\n");
    print2D(array2D_dyn, M, N);

    // Explain the result of 'printf'
    // Warning! Do not do such things unless you have a very good reason!
    char *h = (char*)array2D_stat;
    h[5] = 2;
    printf("Element array2D_stat[0][1] is now: %d\n", array2D_stat[0][1]);
	// Wynik printf pokazuje zmodyfikowaną wartość array2D_stat[0][1] po zmianie najmniej znaczącego bajtu tej wartości za pomocą wskaźnika char*, co powoduje zmianę wartości całej liczby całkowitej z powodu sposobu przechowywania liczb całkowitych w pamięci.
    free(array2D_dyn);

    return 0;
}

