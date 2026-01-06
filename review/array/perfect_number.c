#include <stdio.h>

int is_perfect_number(int number) {

    int total = 0;
    for (int i = 1; i < number; i++) {
        if (number % i == 0) {
            total += i;
        }
    }

    if (total == number) {
        return 1;
    }

    return 0;
}

int main(void) {

    for (int i = 1; i <= 10000; i++) {
        if (is_perfect_number(i)) {
            printf("%d is a perfrect number\n", i);
        } 
    }
    return 0;
}