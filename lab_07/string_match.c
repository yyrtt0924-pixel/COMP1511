//z56768227
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 128

int main(void) {
    char search_term[MAX_LENGTH];
    printf("Enter the search term: ");
    fgets(search_term, MAX_LENGTH, stdin);
    search_term[strcspn(search_term, "\n")] = '\0';

    int count = 0;
    char list_of_string[MAX_LENGTH];
    printf("Enter the list of strings:\n");
    while (fgets(list_of_string, MAX_LENGTH, stdin) != NULL) {
        list_of_string[strcspn(list_of_string, "\n")] = '\0';
        if (strcmp(search_term, list_of_string) == 0) {
            count++;
        }
    }

    printf("There was %d occurrence(s) of the search term in the input.\n"
        , count);
    return 0;
}