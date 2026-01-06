#include <stdio.h>
#define MAX_SIZE 100

int main(void) {
    int arr[MAX_SIZE];
    int num;
    int i = -1;
    printf("Enter numbers forwards:\n");
    while (scanf("%d", &num) != EOF) { 
        i++;
        arr[i] = num;
    }
    int index = i;

    printf("Reversed:\n");
    for (int j = index; j > -1; j--) {
        printf("%d\n", arr[j]);
    }


    return 0;
}