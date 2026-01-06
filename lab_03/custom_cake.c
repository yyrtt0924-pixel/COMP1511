# include<stdio.h>

int main(void){
    
    int layers;
    printf("How many layers: ");
    scanf("%d", &layers);

   
    printf("Please enter layers: ");

    for (int row=0; row<layers; row++){
         char character;
         scanf(" %c", &character);
    
        for(int col=0; col<layers; col++){
            printf("%c",character);
        
        }printf("\n");
    }

    return 0;
}