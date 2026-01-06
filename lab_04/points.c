// PROGRAM NAME
//
// 10.10.2025
// By INSERT-AUTHOR-HERE
//z5676827
// INSERT-DESCRIPTION-HERE
//

#include <stdio.h>

#define MAX_POINTS 10

struct point {
    // TODO: fill this in so that the struct can hold an x and y position
    //
    // i.e. This struct should contain:
    //      the x-coordinate and y-coordinate (doubles).

    double x_coordinate;
    double y_coordinate;
};

// Prints a point out.
void print_point(int point_no, double x, double y);

int main(void) {
    // TODO: Declare an array of points of size MAX_POINTS
    struct point shape[MAX_POINTS];

    int numbers_of_points = 0;
    printf("How many points in the shape? ");
    // TODO: scan in number of points in the shape
    scanf("%d", &numbers_of_points);

    printf("Enter points:\n");
    // TODO: scan in the details of each point into the array
    for (int i = 0; i < numbers_of_points; i++) {
        scanf("%lf %lf", &shape[i].x_coordinate, &shape[i].y_coordinate);
    }

    printf("\nShape Points:\n");
    // TODO: print all the points
    for (int i = 0; i < numbers_of_points; i++) {
        print_point(i + 1, shape[i].x_coordinate, shape[i].y_coordinate);
    }

    return 0;
}

//  Prints a single point in the correct format.
//
// Parameters:
// - `point_no` -- The point number
// - `x`        -- The x-coordinate of the point
// - `y`        -- The y-coordinate of the point
//
// Returns: nothing.
void print_point(int point_no, double x, double y) {
    printf("%2d: x = %.3lf, y = %.3lf\n", point_no, x, y);
}
