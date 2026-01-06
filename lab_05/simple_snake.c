// A simpler version of the famous Snake game!
//
// Written by Rory Golledge (z5308772) on 3/3/23
// Modified by YOUR-NAME (z5676827) on 18-10-25
//

#include <stdio.h>

#define SIZE 8

enum land {
    NOT_VISITED,
    VISITED,
    SNAKE,
    APPLE
};

void initialise_map(enum land map[SIZE][SIZE]);
void print_map(enum land map[SIZE][SIZE]);

int main(void) {
    enum land map[SIZE][SIZE];
    initialise_map(map);
 
    int apple_col, apple_row;
    int snake_col, snake_row;
    printf("Welcome to Snake!\n");

    printf("Please enter apple location: ");
    scanf("%d %d", &apple_row, &apple_col);
    map[apple_row][apple_col] = APPLE; 

    printf("Please enter snake location: ");
    scanf("%d %d", &snake_row, &snake_col);
    map[snake_row][snake_col] = SNAKE; 

    print_map(map); 
    // TODO: Complete the program
    char direction;
    while (1) {
        scanf(" %c", &direction);

        int start_row = snake_row;
        int start_col = snake_col;

        if (direction == 'u') {
            snake_row--;
        } else if (direction == 'd') {
            snake_row++;
        } else if (direction == 'l') {
            snake_col--;
        } else if (direction == 'r') {
            snake_col++;
        }

        if (snake_row < 0 || snake_row >= SIZE || snake_col < 0 
            ||snake_col >= SIZE) {
            break;
        }
        
        map[start_row][start_col] = VISITED;
        if (map[snake_row][snake_col] == APPLE) {
            map[snake_row][snake_col] = SNAKE;
            print_map(map);
            printf("Chomp!\n");
            break;
        } else {
            map[snake_row][snake_col] = SNAKE;
            print_map(map);
        }
    }
    return 0;
}

/**
 * Initialises the given `map` such that all tiles are `NOT_VISITED`
 * 
 * Parameters:
 *     map - The map to initialise
 * 
 * Returns:
 *     Nothing
 */
void initialise_map(enum land map[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            map[row][col] = NOT_VISITED;
        }
    }
}

/**
 * Prints the given `map` such that all enum values are printed as nice
 * characters.
 * 
 * Parameters:
 *     map - The map to print out
 * 
 * Returns:
 *     Nothing
 */
void print_map(enum land map[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (map[row][col] == NOT_VISITED) {
                printf(". ");
            } else if (map[row][col] == VISITED) {
                printf("- ");
            } else if (map[row][col] == SNAKE) {
                printf("S ");
            } else if (map[row][col] == APPLE) {
                printf("A ");
            }
        }
        printf("\n");
    }
}