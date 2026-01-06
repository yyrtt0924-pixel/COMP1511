#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

int main(void) {
    char user_input[MAX_SIZE];
    printf("Enter string: ");

    while(fgets(user_input, MAX_SIZE, stdin) != NULL) {
        user_input[strcspn(user_input, "\n")] = '\0';
        printf("Input received: %s\n", user_input);
        printf("Enter string: ");
    }
    printf("\n");
    return 0;
}