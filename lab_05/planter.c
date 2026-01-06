// Name of Exercise
// planter.c
//
// This program was written by YARU YANG (z5676827)
// on 10.20
//
// One line summary of what this exercise does.

/*

*/
#include <stdio.h>

#define GARDEN_ROWS 5
#define GARDEN_COLS 5
#define TRUE 1
#define FALSE 0

/*
Provided enum flowers
DO NOT MODIFY THIS ENUM
*/
enum flowers {
    EMPTY,
    DAISY,
    ROSE,
    TULIP
};

/*
Provided struct garden 
DO NOT MODIFY THIS STRUCT
*/
struct garden {
    enum flowers flower;
    int bloom_countdown;
    int is_gardener;
};

/*
provided function prototypes
DO NOT MODIFY THESE FUNCTION PROTOTYPES
*/
void print_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]);
int grow_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]);


int main(void) {
    struct garden garden[GARDEN_ROWS][GARDEN_COLS] = {0};
    int all_bloomed = 0;

    // Initialize all positions as empty
    for (int row = 0; row < GARDEN_ROWS; row++) {
        for (int col = 0; col < GARDEN_COLS; col++) {
            garden[row][col].flower = EMPTY;
            garden[row][col].bloom_countdown = 0;
            garden[row][col].is_gardener = 0;
        }
    }

    printf("Welcome to the planter!\n");

    garden[0][0].is_gardener = 1;
    print_garden(garden);

    for (int row = 0; row < GARDEN_ROWS; row++) {
        for (int i = 0; i < GARDEN_ROWS; i++) {
            for (int j = 0; j < GARDEN_COLS; j++) {
                garden[i][j].is_gardener = 0;
            }
        }

        garden[row][0].is_gardener = 1;

        printf(
            "0. Nothing\n"
            "1. Daisy\n"
            "2. Rose\n"
            "3. Tulip\n"
            "Which flower would you like to plant in this row? "
        );

        int choice;
        scanf("%d", &choice);

        // Plant the chosen flower in the current row
        for (int col = 0; col < GARDEN_COLS; col++) {
            if (choice == 0) {
                garden[row][col].flower = EMPTY;
                garden[row][col].bloom_countdown = 0;
            } else if (choice == 1) {
                garden[row][col].flower = DAISY;
                garden[row][col].bloom_countdown = 3;
            } else if (choice == 2) {
                garden[row][col].flower = ROSE;
                garden[row][col].bloom_countdown = 3;
            } else if (choice == 3) {
                garden[row][col].flower = TULIP;
                garden[row][col].bloom_countdown = 3;
            } else {
                garden[row][col].flower = EMPTY;
                garden[row][col].bloom_countdown = 0;
            }
        }

        for (int prev_row = 0; prev_row < row; prev_row++) {
            for (int col = 0; col < GARDEN_COLS; col++) {
                if (garden[prev_row][col].bloom_countdown > 0) {
                    garden[prev_row][col].bloom_countdown--;
                }
            }
        }

        if (row < GARDEN_ROWS - 1) {
            garden[row][0].is_gardener = 0;
            garden[row + 1][0].is_gardener = 1;
        } else {
            garden[row][0].is_gardener = 0;
        }

        print_garden(garden);
    }

    // Remove gardener after planting all rows
    for (int i = 0; i < GARDEN_ROWS; i++) {
        garden[i][0].is_gardener = 0;
    }

    int has_flowers_to_bloom = 0;
    for (int row = 0; row < GARDEN_ROWS; row++) {
        for (int col = 0; col < GARDEN_COLS; col++) {
            if (garden[row][col].flower != EMPTY && 
                garden[row][col].bloom_countdown > 0) {
                has_flowers_to_bloom = 1;
                break;
            }
        }
        if (has_flowers_to_bloom) break;
    }
    // Wait for all flowers to bloom
    while (!all_bloomed && has_flowers_to_bloom) {
        printf("Waiting for flowers to bloom...\n");
        grow_garden(garden);
        print_garden(garden);
        
        all_bloomed = 1;
        for (int row = 0; row < GARDEN_ROWS; row++) {
            for (int col = 0; col < GARDEN_COLS; col++) {
                if (garden[row][col].flower != EMPTY && 
                    garden[row][col].bloom_countdown > 0) {
                    all_bloomed = 0;
                    break;
                }
            }
            if (!all_bloomed) break;
        }
    }
    return 0;
}


/*
    Decreases the bloom_countdown for all flowers in the garden
    Parameters:
        garden: a 2D array of struct garden
    Returns:
        int: returns 1 if a flower has grown, 0 otherwise
*/
int grow_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]) {
    int grew = 0;
    for (int row = 0; row < GARDEN_ROWS; row++) {
        for (int col = 0; col < GARDEN_COLS; col++) {
            if (garden[row][col].bloom_countdown > 0) {
                garden[row][col].bloom_countdown--;
                grew = 1;
            }
        }
    }
    return grew;
}


////////////////////////////////////////////////////////////////////////////////
//////////////////// DO NOT MODIFY ANYTHING BELOW THIS LINE ////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
    Prints the garden to the terminal
    Parameters:
        garden: a 2D array of struct garden
    Returns:
        void
*/
void print_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]) {
    printf("\n");
    for (int i = 0; i < GARDEN_ROWS; i++) {
        for (int j = 0; j < GARDEN_COLS; j++) {
            if (garden[i][j].is_gardener) {
                printf("# ");
            } else if (garden[i][j].flower == EMPTY) {
                printf(". ");
            } else if (garden[i][j].bloom_countdown > 0) {
                printf("%d ", garden[i][j].bloom_countdown);
            } else if (garden[i][j].flower == DAISY) {
                printf("D ");
            } else if (garden[i][j].flower == ROSE) {
                printf("R ");
            } else if (garden[i][j].flower == TULIP) {
                printf("T ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}