// Written by YOUR-NAME (z5676827), on 10.31

#include <stdio.h>

void increment(int *ptr);

int main(void) {
    int num;
    printf("Please enter a number: ");
    scanf("%d", &num);
    int *ptr = &num;

    printf("Before increment: %d\n", *ptr);
    increment(ptr);
    printf("After increment: %d\n", *ptr);

    return 0;
}

void increment(int *ptr) {
    (*ptr)++;
}