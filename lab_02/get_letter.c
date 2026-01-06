// Name of Exercise
// name.c
//
// This program was written by YOUR-NAME-HERE (z5676827)
// on INSERT-DATE-HERE
//
// One line summary of what this exercise does.

#include <stdio.h>

int main(void) {

   char is_uppercase;
    printf("Uppercase: ");
    scanf("%c",&is_uppercase);
    // TODO: scan is_uppercase

 int Index=0;
 if (is_uppercase=='y'){
    printf("Index: ");
    scanf("%d",&Index);
    printf("The letter is %c\n",65+Index);
    }
 else if(is_uppercase=='n'){
    printf("Index: ");
    scanf("%d",&Index);
    printf("The letter is %c\n",97+Index);
}

    return 0;
}