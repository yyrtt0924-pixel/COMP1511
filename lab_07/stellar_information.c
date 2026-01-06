// stellar_information.c
//
// This program simulates a star system in space
//
// Written by YARU YANG, z5676827
// on 10.31

#include <stdio.h>
#include <stdlib.h>

#define CONVERSION_CONSTANT 9.461e12
#define LIGHT_SPEED 299792.458

// TODO: TASK 1
struct star{
    char name[50];
    double distance;
    char spectral_type;
};

void print_star_information(struct star *star);
void input_star_information(struct star *star);
double time_travel(struct star *star);

int main() {
    // TODO: TASK 2
    struct star my_star;
    struct star *star_ptr = &my_star;
    input_star_information(star_ptr);
    print_star_information(star_ptr);
    return 0;
}

// Takes in the stars information
void input_star_information(struct star *star) {
    // TODO: TASK 3
    printf("Enter the star's name: ");
    fgets(star->name, 50, stdin);
    printf("Enter the star's distance from Earth (in light-years): ");
    scanf("%lf", &star->distance);
    printf("Enter the star's spectral type: ");
    scanf(" %c", &star->spectral_type);
}

// Estimate travel time from Earth to the star based on star's distance
double time_travel(struct star *star) {
    // TODO: TASK 4
    double distance_km = star->distance * CONVERSION_CONSTANT;
    double time_travel = distance_km / LIGHT_SPEED;
    return time_travel;
}

// Prints the stars information
void print_star_information(struct star *star) {
    // TODO: TASK 5
    printf("\nStar's Information:\n");
    printf("Name: %s", star->name);
    printf("Distance: %.6lf light-years\n", star->distance);
    printf("Spectral Type: %c\n", star->spectral_type);
    printf("Estimated travel time from Earth: %.2lf seconds\n"
        , time_travel(star));
}