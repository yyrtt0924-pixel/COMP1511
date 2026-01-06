// The following code is meant to read in integers and print out the 
// factorial of that integer until the user enters Ctrl + D. 
// However, it contains a number of errors that you need to fix. Good luck!

// Note: the factorial of a number is the product of all positive 
// integers less than or equal to that number.

#include <stdio.h>

// DO NOT MODIFY THIS FUNCTION PROTOTYPE
void compute_factorial(int number, int *factorial); 

int main(void) {
    int num1;
    int factorial;

    printf("Enter a number: ");
    while (scanf("%d", &num1) != EOF) {
        compute_factorial(num1, &factorial); 
        printf("The factorial of %d is %d\n", num1, factorial);
        printf("Enter a number: ");
    }

    return 0;
}

void compute_factorial(int number, int *factorial) {
    int result = 1;
    for (int i = number; i > 0; i--) {
        result = result * i;
    }

    *factorial = result;
    return;
}
