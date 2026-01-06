#include<stdio.h>

int main(void){

    char uppereyes1,uppereyes2,nose,mouth;
    

    printf("How do you want to build a face?: \n");
    int face=scanf(" %c%c%c%c",&uppereyes1,&uppereyes2,&nose,&mouth);//read 4 characters

    if (face==3){
        uppereyes1 = uppereyes2;
        nose = uppereyes1;
        mouth = nose;
    }// read 3 characters

    if (uppereyes1 == 'a') printf("_");
    else if (uppereyes1 == 'b') printf("~");
    else if (uppereyes1 == 'c') printf("\\");
    else if (uppereyes1 == 'd') printf("/");

    if (uppereyes2 == 'a') printf(" _");
    else if (uppereyes2 == 'b') printf(" ~");
    else if (uppereyes2 == 'c') printf(" \\");
    else if (uppereyes2 == 'd') printf(" /");

    printf("\nO O\n");

    if (nose == 'e') printf(" ^\n");
    else if (nose == 'f') printf(" ~\n");

    if (mouth == 'g') printf(" \\_/\n");
    else if (mouth == 'h') printf(" /-\\\n");
    else if (mouth == 'i') printf(" o\n");

    
    return 0;
}