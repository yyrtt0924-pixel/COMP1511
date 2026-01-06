#include <stdio.h>

int main(void){

    char starting_letter, target_letter, case_of_letters = 0 ;
    int forward,backward;
    
    printf("Please enter starting letter: ");
    scanf(" %c", &starting_letter);
    printf("Please enter target letter: ");
    scanf(" %c", &target_letter);

    //decide wheather print uppercase or lowercase
    if (starting_letter >= 'a' && starting_letter <= 'z'){
        case_of_letters = 'a';
    }else if (starting_letter >= 'A' && starting_letter <= 'Z'){
        case_of_letters = 'A';
    }

    //calculate the distance
    forward = (target_letter - starting_letter + 26)%26;
    backward = (starting_letter - target_letter + 26)%26;

    //start=target
    if (starting_letter == target_letter){
        printf("%c\n", starting_letter);
    }

    //start!=target
    else if (forward <= backward){
        for (int i = 0; i <= forward; i++){
            char letter_between = (starting_letter - case_of_letters + i) %26 + case_of_letters;
            printf("%c", letter_between);
        }
        printf("\n");
    }else if (forward > backward){
        for (int i = 0; i <= backward; i++){
            char letter_between = (starting_letter - case_of_letters - i + 26) %26 + case_of_letters;
            printf("%c", letter_between);
        }
        printf("\n");
    }
        
    
    return 0;
}