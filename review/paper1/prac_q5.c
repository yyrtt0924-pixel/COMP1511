// This program scans in an integer representing a month of the year.
// It prints out a message to say what season the month is in Australia.
//
// Unfortunately, this code contains a number of errors. Please help fix it!

#include <stdio.h>

int main(void) {
    int month;
    printf("Enter the month number (1-12): ");
    scanf("%d", &month);

    if (month < 1 || month > 12) {
        printf("Invalid month entered.\n");
    } else if (month >= 3 && month <= 5) { 
        printf("It's autumn in Australia.\n");
    } else if (month >= 6 && month <= 8) {
        printf("It's winter in Australia.\n");
    } else if (month >= 9 && month <= 11) {
        printf("It's spring in Australia.\n");
    } else if ((month >= 1 && month <= 2)|| month == 12) {
        printf("It's summer in Australia.\n");
    } 
    
    return 0;
}
