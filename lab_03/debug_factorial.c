// debug_factorial.c
//
// Write a C program that takes a positive integer as input, calculates the
// factorial of that number and prints it out.
//
// This program was written by YOUR-NAME-HERE (z5676827)
// on INSERT-DATE-HERE

#include <stdio.h>

int main (void) {
    int num = 0;
    int factorial =1;

    printf("Enter a number: ");
    scanf("%d", &num);

    int counter = num;

    while (counter > 0){
        factorial *= counter;
        counter--;
    }

    printf("The factorial of %d is %d\n",num,factorial);

    return 0;
}
