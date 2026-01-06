#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 5

struct coordinate {
    int x;
    int y;
};

double e_dist(struct coordinate p0, struct coordinate p1);
void adjacent_distances(struct coordinate arr[SIZE], int size);

int main(void) {

    // Only your function is called during testing
    // Any changes in this main function will not
    // be used in testing

    struct coordinate array1[SIZE] = {{.x = 1, .y = 1},
                                        {.x = 2, .y = 2},
                                        {.x = 9, .y = 2},
                                        {.x = 2, .y = 9},
                                        {.x = 0, .y = 0}};

    adjacent_distances(array1, SIZE);

    return 0;
}

void adjacent_distances(struct coordinate arr[SIZE], int size) {
    // TODO: Print the distances between adjacent coordinates
    double distance = 0;


    for (int i = 0; i < size - 1; i++) {
        distance = e_dist(arr[i], arr[i + 1]);
        printf("Dist: %lf\n", distance);
    }

    // Your function should NOT return anything
    // Your function SHOULD print the distances
}

double e_dist(struct coordinate p0, struct coordinate p1) {

    return sqrt((p1.x - p0.x)*(p1.x - p0.x)*1.0 +  (p1.y - p0.y)*(p1.y - p0.y)*1.0);
}

