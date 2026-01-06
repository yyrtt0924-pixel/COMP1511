#include <stdio.h>

#define MAX_ROWS 100

int vowels_exactly_balanced(int size, char *array[MAX_ROWS]);

// This is a simple main function which could be used 
// to test your vowels_exactly_balanced function.
// It will not be marked.
// Only your vowels_exactly_balanced function will be marked.

int main(int argc, char *argv[]) {
  char *test_arrray[MAX_ROWS] = {
      "abUUcd",
      "abcdUU",
      "Abaa",
      "asdaa",
  };

  char *test_arrray_2[MAX_ROWS] = {
      "abcdaa",
      "abcda",
      "babau",
  };

  int result = vowels_exactly_balanced(4, test_arrray);
  printf("The vowels_exactly_balanced function returned: %d\n", result);

  result = vowels_exactly_balanced(3, test_arrray_2);
  printf("The vowels_exactly_balanced function returned: %d\n", result);

  return 0;
}

// Return 1 if each string has the same number of vowels. Return 0 otherwise.
int vowels_exactly_balanced(int size, char *array[MAX_ROWS]) {
    // Your code goes here. You should change the return value.
    if (size <= 1) {
        return 1;
    }
    int total_vowel = 0;
    int target = -1;
    for (int i = 0; i < size; i++) {
        total_vowel = 0;
        for (int j = 0; array[i][j] != '\0'; j++) {
            if (array[i][j] == 'a' || array[i][j] == 'e' || array[i][j] == 'i'|| array[i][j] == 'o'|| array[i][j] == 'u'||
                array[i][j] == 'A'|| array[i][j] == 'E'|| array[i][j] == 'I'|| array[i][j] == 'O'|| array[i][j] == 'U') {
                total_vowel++;
            }
        }
        if (target == -1) {
            if (total_vowel > 0) {
                target = total_vowel;
            }
        } else if (target != total_vowel) {
            return 0;
        }
    }
    

    return 1;
}
