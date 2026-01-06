//z5676827

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1024

int main(void){
    char word[MAX_SIZE];
    printf("Input word: ");
    fgets(word, MAX_SIZE, stdin);

    printf("\n");

    word[strcspn(word, "\n")] = '\0';
    int length = strlen(word);

    printf("Word square is:\n");
    for (int i = 0; i < length; i++) {
        printf("%s\n", word);
    }

    return 0;
}
