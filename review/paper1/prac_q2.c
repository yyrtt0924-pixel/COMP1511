#include <stdio.h>
#include <ctype.h>

#define MAX_COLS 100

char min_lowercase(int size, char array[MAX_COLS]);

// This is a simple main function which can be used to test your function.
// It will not be marked.
// Only your min_lowercase function will be marked.
int main(int argc, char *argv[]) {
    char test_array[MAX_COLS] = {'a', 'B', 'c', 'D', '!'};

    int result = min_lowercase(5, test_array);
    printf("%c\n", result);

    return 0;
}

// Returns the character with the lowest ASCII value from the array.
char min_lowercase(int size, char array[MAX_COLS]) {

    // You should replace this return statement with your own
    char min_lowercase ='z';
    for (int i = 0; i < size; i++) {
        if ('a' <= array[i] && array[i] <= 'z'){
            if(array[i] < min_lowercase) {
                min_lowercase = array[i];
            }
        }
    }
    return min_lowercase;
}
