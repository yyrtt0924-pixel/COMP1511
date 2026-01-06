//z5676827
#include <stdio.h>

int power(int num1, int num2) {
    int  result = 1;
    for (int i = 0; i < num2; i++) {
        result *= num1;
    }
    return result;
}


int main(void){
    char instruction;
    int num1, num2;
    int input;
    
    while (1) {
        printf("Enter instruction: ");
        input = scanf(" %c", &instruction);
        if (input != 1) {
            break;
        }
        
        if (instruction == 's') {
            scanf("%d", &num1);
            printf("%d\n", num1 * num1);
        } else if (instruction == 'p') {
            scanf("%d %d", &num1, &num2);
            printf("%d\n", power(num1, num2));
        }
    }

    
    return 0;
}