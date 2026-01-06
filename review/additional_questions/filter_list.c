#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

struct passenger {
    double height;
    int num_bags;
};

int main(void) {

    struct passenger my_array[SIZE];
    for (int i = 0; i < SIZE; i++) {
        printf("Enter height & number of bags: ");
        scanf("%lf %d", &my_array[i].height, &my_array[i].num_bags);
    }

    double target_height = 0.0;
    printf("Select height: ");
    scanf("%lf", &target_height);

    int total_bags = 0;
    for (int i = 0; i < SIZE; i++) {
        if (my_array[i].height > target_height) {
            total_bags += my_array[i].num_bags;
        }
    }
    
    printf("Total of %d bags from people over %lf\n", total_bags, target_height);

    return 0;
}