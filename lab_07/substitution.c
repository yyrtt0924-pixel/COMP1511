//z5676827
#include <stdio.h>
#include <ctype.h>

char cipher_print(char user_print, char *cipher);

int main(int argc, char *argv[]){
    char user_print;
    char *cipher = argv[1];
    printf("Enter text:\n");
    while (scanf("%c", &user_print) != EOF) {
        printf("%c", cipher_print(user_print, cipher));
    }
    return 0;
}

char cipher_print(char user_print, char *cipher) {

    if (islower(user_print)) {
        return cipher[user_print - 'a'];
    } else if (isupper(user_print)) {
        return toupper(cipher[user_print - 'A']);
    } else {
        return user_print;
    }
}