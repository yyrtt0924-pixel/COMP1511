// This program should create and scan in the elements of a 3x3 2d array, 
// then multiply all the odd numbers in the 2d array by 100.
//
// Although this code compiles, it prints the wrong output. Please help fix it!

#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int main(void) {

    printf("Enter your numbers:\n");

    int array[SIZE][SIZE];
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            scanf(" %d", &array[row][col]);
        }
    }

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++)  {
            if (array[row][col] % 2 != 0) {
                array[row][col] = array[row][col] * 100; 
            }
        }
    }

    // ==================== DO NOT NEED TO EDIT BELOW HERE =====================
    // There are no bugs in here, this is simply to assist in printing out
    // the contents of the 2D array
    printf("Converted:\n");
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            printf("%d ", array[row][col]);
        }
        printf("\n");
    }

    return 0;
}
