#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10000

int main(void) {
    int number;
    int array[MAX_SIZE];
    int index = 0;

    while (scanf("%d", &number) == 1 && number != 0) {
        array[index] = number;
        index++;
    }
    
    for (int i = 0; i < index; i += 2) {
        printf("%d ", array[i]);
    }
    for (int i = 1; i < index; i += 2) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}