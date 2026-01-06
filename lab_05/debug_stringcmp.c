// debug_stringcmp.c
//
// This program takes in two strings as input and checks if they are the same
// Wrriten by YARU YANG, z5676827
// on 10.17

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

int main(void) {
    char str1[MAX_SIZE];
    char str2[MAX_SIZE];

    // Read input from user
    printf("Enter the first string: ");
    fgets(str1, MAX_SIZE, stdin);

    printf("Enter the second string: ");
    fgets(str2, MAX_SIZE, stdin);

    // Check if the strings are equal
    if (strcmp(str1, str2) == 0) {
        printf("The strings are equal!\n");
    } else {
        printf("The strings are not equal!\n");
    }

    return 0;
}