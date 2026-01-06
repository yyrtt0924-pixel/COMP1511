#include<stdio.h>

int main(void){
    
    double dividend,divisor,quotient;
    printf("Enter the dividend: ");
    scanf("%lf",&dividend);
    printf("Enter the divisor: ");
    scanf("%lf",&divisor);

    if(divisor!=0){
        printf("%.0lf divided by %.0lf\n",dividend,divisor);
        
        quotient=dividend/divisor;
        printf("To the nearest whole number: %.0lf\n",quotient);
        printf("To 1 decimal place: %.1lf\n",quotient);
        printf("To 5 decimal places: %.5lf\n",quotient);
        printf("To 20 decimal places: %.20lf\n",quotient);
    }
    else{
            printf("Don't be silly!\n");
        }

    return 0;
}