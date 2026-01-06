#include<stdio.h>

int main(void){
    int n;
    printf("Enter number:");
    scanf("%d", &n);

    if(n>=0){
        int i=0;
        while(i<=n){
            printf("%d\n",i);
            i++;
        }
    }else{
        int i=0;
        while(i>=n){
            printf("%d\n",i);
            i--;
        }
    }

    return 0;
}