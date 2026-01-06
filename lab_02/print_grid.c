#include<stdio.h>

int main(void){

    int n=0;

    printf("Enter size: ");
    scanf("%d",&n);

    for(int row=0;row < n;row++){
        for(int col=0;col < n;col++){
            printf("(%d,%d)",row,col);
        }
        printf("\n");
    }
    

    return 0;
}