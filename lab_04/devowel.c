//z5676827
#include <stdio.h>

int main(void){
    char input_characters;

    while(scanf("%c", &input_characters) == 1){
        if (input_characters != 'a'&&input_characters !='e'&&input_characters != 
           'i'&&input_characters != 'o'&&input_characters != 'u'){
            printf("%c", input_characters);
        }
    }

    return 0;
}
