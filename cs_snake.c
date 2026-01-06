// cs_snake.c
// Written by <YARU YANG> <z5676827> on <Oct,12>
//
// Description: <INSERT DESCRIPTION OF PROGRAM>

// Provided Libraries
#include <stdio.h>
#include <ctype.h>

// Add your own #include statements below this line
#include <string.h>

// Provided constants
#define ROWS 10
#define COLS 10

#define NO_SNAKE -1

// Add your own #define constants below this line
# define APPLE_NORMAL_POINT 5
# define APPLE_REVERSE_POINT 10
# define APPLE_SPLIT_POINT 20
# define MAX_PORTAL_PAIRS 5
// Provided enums
// Enum for features on the game board
enum entity {
    BODY_SEGMENT,
    EXIT_LOCKED,
    EXIT_UNLOCKED,
    WALL,
    APPLE_NORMAL,
    APPLE_REVERSE,
    APPLE_SPLIT,
    APPLE_EXPLODE,
    EXPLOSION,
    PASSAGE_UP,
    PASSAGE_DOWN,
    PASSAGE_LEFT,
    PASSAGE_RIGHT,
    PORTAL,
    EMPTY
};

// Add your own enums below this line
enum direction {
    UP = 'w',
    DOWN = 's',
    LEFT = 'a',
    RIGHT = 'd'
};

// Provided structs
// Represents a tile/cell on the game board
struct tile {
    enum entity entity;
};

// Add your own structs below this line
struct snake_body {
    int snake_x;
    int snake_y;
};

struct portal_pair {
    int row1;
    int col1;
    int row2;
    int col2;
};

struct find_portal {
    int find;
    int another_row;
    int another_col;
};


// Provided Function Prototypes
void initialise_board(struct tile board[ROWS][COLS]);

void print_board(
    struct tile board[ROWS][COLS],
    int snake_row,
    int snake_col
);

void print_game_statistics(
    int points,
    int moves_made,
    int num_apples_eaten,
    int num_apples_remaining,
    double completion_percentage,
    int maximum_points_remaining
);

void print_game_statistics_with_rival(
    int original_points,
    int original_moves_made,
    int original_num_apples_eaten,
    int rival_points,
    int rival_moves_made,
    int rival_num_apples_eaten,
    int num_apples_remaining,
    double completion_percentage,
    int maximum_points_remaining
);

void print_board_line(void);

void print_tile_spacer(void);

void print_board_header(void);

// Add your function prototypes below this line
void map_setup(struct tile board[ROWS][COLS],
               struct portal_pair portal_pairs[MAX_PORTAL_PAIRS],
               int count_portals_pairs[1]);

void spawn_snake(struct tile board[ROWS][COLS], int snake_position[2]);

void gameplay_phase(struct tile board[ROWS][COLS],
                    int snake_position[2],
                    struct portal_pair portal_pairs[MAX_PORTAL_PAIRS],
                    int count_portals_pairs[1], int head[2]);

int count_apple_num(struct tile board[ROWS][COLS]);

void lock(struct tile board[ROWS][COLS]);

void wins_or_loses(struct tile board[ROWS][COLS], int head_row,
                   int head_col, int game_ended_or_win[2]);

void reverse_snake(struct snake_body snake_body[], int snake_length);

void clear_body_segments(struct tile board[ROWS][COLS], int snake_length,
                         struct snake_body snake_body[]);

void print_body(struct tile board[ROWS][COLS], int snake_length,
                struct snake_body snake_body[]);

int cal_maximum_points_remaining(struct tile board[ROWS][COLS]);

int is_out_of_bounds(int row, int col);

void one_way_passage(struct tile board[ROWS][COLS], char user_input,
                     int game_ended_or_win[0], int head_row, int head_col);

int snake_split(int snake_length);

struct find_portal find_another_portal_pair(int count_portals_pairs[1],
    int head_row, int head_col, 
    struct portal_pair portal_pairs[MAX_PORTAL_PAIRS]);

void add_wall(struct tile board[ROWS][COLS]);

void add_exit(struct tile board[ROWS][COLS]);

void add_wall(struct tile board[ROWS][COLS]);

void add_exit(struct tile board[ROWS][COLS]);

void add_apple(struct tile board[ROWS][COLS]);

void add_long_wall(struct tile board[ROWS][COLS]);

void add_passage(struct tile board[ROWS][COLS]);

void add_portal(struct tile board[ROWS][COLS],
                struct portal_pair portal_pairs[MAX_PORTAL_PAIRS],
                int count_portals_pairs[1]);

void print_statistics(struct tile board[ROWS][COLS],
                      int points, int moves_made, int num_apples_eaten,
                      int num_initial_apples);

void reset_map(struct tile board[ROWS][COLS],
               struct tile original_board[ROWS][COLS],
               struct snake_body snake_body[100],
               int points[1], int moves_made[1],
               int num_apples_eaten[1], int snake_length[1],
               int num_initial_apples[1], int original_apples[1],
               int original_snake_row[1], int original_snake_col[1]);

void move_snake_body(struct snake_body snake_body[100], int snake_length[1],
                     int head_row, int head_col, int moves_made[1]);

void check_game_end(struct tile board[ROWS][COLS], int points[1],
                    int moves_made[1], int num_apples_eaten[1], 
                    int num_initial_apples[1]);

void handle_apples(struct tile board[ROWS][COLS], struct snake_body snake_body[100],
                   int points[1], int num_apples_eaten[1], int snake_length[1],
                   int head_row, int head_col);

void process_portal(int head[2], char commands,
                    int count_portals_pairs[1],
                    struct portal_pair portal_pairs[MAX_PORTAL_PAIRS]);

void update_head_position(int head[2], char commands);

void handle_gameplay(struct tile board[ROWS][COLS], struct snake_body snake_body[100],
                    int points[1], int moves_made[1], int num_apples_eaten[1],
                    int snake_length[1], int num_initial_apples[1], 
                    int head[2], char commands,
                    int count_portals_pairs[1], 
                    struct portal_pair portal_pairs[MAX_PORTAL_PAIRS],
                    int *running);

// Provided sample main() function (you will need to modify this)
int main(void) {
    printf("Welcome to CS Snake!\n\n");

    struct tile board[ROWS][COLS];
    initialise_board(board);

    struct portal_pair portal_pairs[MAX_PORTAL_PAIRS];
    int num_portals_pairs[1] = {0};
    map_setup(board, portal_pairs, num_portals_pairs);
    print_board(board, NO_SNAKE, NO_SNAKE);

    int snake_position[2];
    spawn_snake(board, snake_position);
    print_board(board, snake_position[0], snake_position[1]);

    int head[2];
    gameplay_phase(board, snake_position, portal_pairs, 
        num_portals_pairs, head);
    return 0;
}

// Add your function definitions below this line
void map_setup(struct tile board[ROWS][COLS],
               struct portal_pair portal_pairs[MAX_PORTAL_PAIRS],
               int count_portals_pairs[1]) {
    printf("--- Map Setup ---\n");

    char user_input;
    int running = 1;
    while (running) {
        scanf(" %c", &user_input);
        if (user_input == 's') {
            running = 0;
        } else if (user_input == 'w') {
            add_wall(board);
        } else if (user_input == 'e') {
            add_exit(board);
        } else if (user_input == 'a') {
            add_apple(board);
        } else if (user_input == 'W') {
            add_long_wall(board);
        } else if (user_input == 'p') {
            add_passage(board);
        } else if (user_input == 't') {
            add_portal(board, portal_pairs, count_portals_pairs);
        }
    }
}


void spawn_snake(struct tile board[ROWS][COLS], int snake_position[2]) {
    printf("--- Spawning Snake ---\n");
    int snake_row, snake_col;

    int running = 1;

    while (running) {
        running = 0;
        printf("Enter the snake's starting position: ");
        scanf("%d %d", &snake_row, &snake_col);

        if (is_out_of_bounds(snake_row, snake_col)) {
            printf("ERROR: Invalid position, %d %d is out of bounds!\n",
                   snake_row, snake_col);
            running = 1;
        } else if (board[snake_row][snake_col].entity != EMPTY) {
            printf("ERROR: Invalid tile, %d %d is occupied!\n",
                   snake_row, snake_col);
            running = 1;
        }

        snake_position[0] = snake_row;
        snake_position[1] = snake_col;
    }
}

void gameplay_phase(struct tile board[ROWS][COLS], int snake_position[2],
                    struct portal_pair portal_pairs[MAX_PORTAL_PAIRS],
                    int count_portals_pairs[1], int head[2]) {
    printf("--- Gameplay Phase ---\n");
    struct snake_body snake_body[100];
    int points[1], moves_made[1], num_apples_eaten[1], num_initial_apples[1];
    int original_apples[1], original_snake_row[1], original_snake_col[1];
    int snake_length[1];
    snake_length[0] = 1;
    //record the original state
    original_snake_row[0] = snake_position[0];
    original_snake_col[0] = snake_position[1];
    struct tile original_board[ROWS][COLS];
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            original_board[row][col] = board[row][col];
        }
    }
    original_apples[0] = count_apple_num(original_board);
    //save the head's position
    snake_body[0].snake_x = snake_position[0];
    snake_body[0].snake_y = snake_position[1];
    char commands;
    points[0] = 0;
    moves_made[0] = 0;
    num_apples_eaten[0] = 0;
    num_initial_apples[0] = count_apple_num(board);
    int running = 1;

    while (running) {
        //exist by using Control+D
        if (scanf(" %c", &commands) == EOF) {
            printf("--- Quitting Game ---\n");
            running = 0;
        } else {
            //points and statistics
            if (commands == 'p') {
                print_statistics(board, points[0], moves_made[0],
                    num_apples_eaten[0], num_initial_apples[0]);
            } else if (commands == 'r') {
                reset_map(board, original_board, snake_body, points, moves_made,
                    num_apples_eaten, snake_length, num_initial_apples,
                    original_apples, original_snake_row, original_snake_col);
            } else {
                handle_gameplay(board, snake_body, points, moves_made, 
                    num_apples_eaten, snake_length, num_initial_apples, 
                    head, commands, count_portals_pairs, portal_pairs, 
                    &running);
            }
        }
    }
}

void handle_gameplay(struct tile board[ROWS][COLS], 
    struct snake_body snake_body[100],
    int points[1], int moves_made[1], int num_apples_eaten[1],
    int snake_length[1], int num_initial_apples[1], 
    int head[2], char commands,
    int count_portals_pairs[1], 
    struct portal_pair portal_pairs[MAX_PORTAL_PAIRS],
    int *running) {
    head[0] = snake_body[0].snake_x;
    head[1] = snake_body[0].snake_y;

    //direction
    update_head_position(head, commands);
    process_portal(head, commands, count_portals_pairs, portal_pairs);

    //move all the elements to the next index position
    move_snake_body(snake_body, snake_length, head[0], head[1], moves_made);

    //cheak the result
    int game_ended_or_win[2] = {0, 0};
    int game_ended = game_ended_or_win[0];
    int is_win = game_ended_or_win[1];
    wins_or_loses(board, head[0], head[1], game_ended_or_win);
    one_way_passage(board, commands, game_ended_or_win, head[0], head[1]);

    //update the result
    game_ended = game_ended_or_win[0];
    is_win = game_ended_or_win[1];

    //the logic about eating apple
    handle_apples(board, snake_body, points, num_apples_eaten, 
        snake_length, head[0], head[1]);

    //check whether the lock is opened
    lock(board);

    //print map
    print_board(board, snake_body[0].snake_x, snake_body[0].snake_y);
    if (game_ended == 1) {
        if (is_win == 1) {
            printf("--- Game Over ---\n");
            printf("Ssslithered out with a full stomach!\n");
        } else {
            printf("--- Game Over ---\n");
            printf("Guessss I was the prey today.\n");
        }

        //cheak if the game is end
        check_game_end(board, points, moves_made, 
            num_apples_eaten, num_initial_apples);
        *running = 0;
    }
}

void update_head_position(int head[2], char commands) {
    if (commands == UP) {
        head[0]--;
    } else if (commands == DOWN) {
        head[0]++;
    } else if (commands == LEFT) {
        head[1]--;
    } else if (commands == RIGHT) {
        head[1]++;
    }
}

void check_game_end(struct tile board[ROWS][COLS],
                    int points[1], int moves_made[1], int num_apples_eaten[1],
                    int num_initial_apples[1]) {
    double completion_percentage = 0.0;
    int num_apples_remaining = count_apple_num(board);
    int maximum_points_remaining = cal_maximum_points_remaining(board);

    if (num_initial_apples[0] == 0) {
        completion_percentage = 100.0;
    } else {
        completion_percentage = 
        100.0 * num_apples_eaten[0] / num_initial_apples[0];
    }

    print_game_statistics(points[0], moves_made[0], num_apples_eaten[0],
                          num_apples_remaining, completion_percentage,
                          maximum_points_remaining);
}

void handle_apples(struct tile board[ROWS][COLS], 
    struct snake_body snake_body[100],
    int points[1], int num_apples_eaten[1], int snake_length[1],
    int head_row, int head_col) {
    int ate_reverse_apple = 0;
    int ate_split_apple = 0;

    if (board[head_row][head_col].entity == APPLE_NORMAL) {
        board[head_row][head_col].entity = EMPTY;
        points[0] += APPLE_NORMAL_POINT;
        num_apples_eaten[0]++;
    } else if (board[head_row][head_col].entity == APPLE_REVERSE) {
        board[head_row][head_col].entity = EMPTY;
        points[0] += APPLE_REVERSE_POINT;
        num_apples_eaten[0]++;
        ate_reverse_apple = 1;
    } else if (board[head_row][head_col].entity == APPLE_SPLIT) {
        board[head_row][head_col].entity = EMPTY;
        points[0] += APPLE_SPLIT_POINT;
        num_apples_eaten[0]++;
        ate_split_apple = 1;
    }

    if (ate_reverse_apple) {
        clear_body_segments(board, snake_length[0], snake_body);
        reverse_snake(snake_body, snake_length[0]);
    }

    if (ate_split_apple) {
        clear_body_segments(board, snake_length[0], snake_body);
        snake_length[0] = snake_split(snake_length[0]);
    }

    print_body(board, snake_length[0], snake_body);
}

void process_portal(int head[2], char commands,
    int count_portals_pairs[1],
    struct portal_pair portal_pairs[MAX_PORTAL_PAIRS]) {
    struct find_portal result_portal 
    = find_another_portal_pair(count_portals_pairs, 
    head[0], head[1], portal_pairs);
    if (result_portal.find) {
        if (commands == UP) {
            head[0] = result_portal.another_row - 1;
            head[1] = result_portal.another_col;
        } else if (commands == DOWN) {
            head[0] = result_portal.another_row + 1;
            head[1] = result_portal.another_col;
        } else if (commands == LEFT) {
            head[0] = result_portal.another_row;
            head[1] = result_portal.another_col - 1;
        } else if (commands == RIGHT) {
            head[0] = result_portal.another_row;
            head[1] = result_portal.another_col + 1;
        }
    }
}

int is_out_of_bounds(int row, int col) {
    if (row < 0) {
        return 1;
    }
    if (row >= ROWS) {
        return 1;
    }
    if (col < 0) {
        return 1;
    }
    if (col >= COLS) {
        return 1;
    }
    return 0;
}

int count_apple_num(struct tile board[ROWS][COLS]) {
    int count = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].entity == APPLE_NORMAL || 
                board[i][j].entity == APPLE_REVERSE
                || board[i][j].entity == APPLE_SPLIT) {
                count++;
            }
        }
    }
    return count;
}

void lock(struct tile board[ROWS][COLS]) {
    int num_apples_remaining = count_apple_num(board);
    if (num_apples_remaining != 0) {
        return;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].entity == EXIT_LOCKED) {
                board[i][j].entity = EXIT_UNLOCKED;
            }
        }
    }
}

void wins_or_loses(struct tile board[ROWS][COLS], int head_row,
                   int head_col, int game_ended_or_win[2]) {
    //wins

    if (board[head_row][head_col].entity == EXIT_UNLOCKED) {
        game_ended_or_win[1] = 1;
        game_ended_or_win[0] = 1;
    }
    //loses
    //1. Moves onto a non-consumable entity 2. Moves off the map
    if (is_out_of_bounds(head_row, head_col)) {
        game_ended_or_win[0] = 1;
    } else if (board[head_row][head_col].entity == EXIT_LOCKED ||
               board[head_row][head_col].entity == BODY_SEGMENT ||
               board[head_row][head_col].entity == WALL) {
        game_ended_or_win[0] = 1;
        game_ended_or_win[1] = 0;
    }
}

void reverse_snake(struct snake_body snake_body[], int snake_length) {
    int left = 0;
    int right = snake_length - 1;
    struct snake_body temp;
    while (left < right) {
        temp = snake_body[left];
        snake_body[left] = snake_body[right];
        snake_body[right] = temp;
        left++;
        right--;
    }
}

int cal_maximum_points_remaining(struct tile board[ROWS][COLS]) {
    int total_points = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].entity == APPLE_NORMAL) {
                total_points += APPLE_NORMAL_POINT;
            } else if (board[i][j].entity == APPLE_REVERSE) {
                total_points += APPLE_REVERSE_POINT;
            } else if (board[i][j].entity == APPLE_SPLIT) {
                total_points += APPLE_SPLIT_POINT;
            }
        }
    }

    return total_points;
}

void one_way_passage(struct tile board[ROWS][COLS], char user_input,
                     int game_ended_or_win[0], int head_row, int head_col) {
    if (board[head_row][head_col].entity == PASSAGE_UP) {
        if (user_input != 'w') {
            game_ended_or_win[0] = 1;
        }
    } else if (board[head_row][head_col].entity == PASSAGE_DOWN) {
        if (user_input != 's') {
            game_ended_or_win[0] = 1;
        }
    } else if (board[head_row][head_col].entity == PASSAGE_LEFT) {
        if (user_input != 'a') {
            game_ended_or_win[0] = 1;
        }
    } else if (board[head_row][head_col].entity == PASSAGE_RIGHT) {
        if (user_input != 'd') {
            game_ended_or_win[0] = 1;
        }
    }
}

int snake_split(int snake_length) {
    int body_segments = snake_length - 1;
    int body_segment_split;
    int body_segment_new;
    if (body_segments % 2 == 0) {
        body_segment_split = body_segments / 2;
    } else {
        body_segment_split = (body_segments + 1) / 2;
    }
    body_segment_new = snake_length - body_segment_split;
    return body_segment_new;
}

void clear_body_segments(struct tile board[ROWS][COLS], int snake_length, 
    struct snake_body snake_body[]) {
    for (int i = 0; i < snake_length; i++) {
        board[snake_body[i].snake_x][snake_body[i].snake_y].entity = EMPTY;
    }
}

void print_body(struct tile board[ROWS][COLS], int snake_length, 
    struct snake_body snake_body[]) {
    for (int i = 0; i < snake_length; i++) {
        board[snake_body[i].snake_x][snake_body[i].snake_y].entity = 
        BODY_SEGMENT;
    }
}

struct find_portal find_another_portal_pair(int count_portals_pairs[1], 
    int head_row, int head_col,
    struct portal_pair portal_pairs[MAX_PORTAL_PAIRS]) {
    struct find_portal result = {0, 0, 0};

    //Transfer every single portal to match portals in pair
    for (int i = 0; i < count_portals_pairs[0]; i++) {
        if (head_row == portal_pairs[i].row1 && 
            head_col == portal_pairs[i].col1) {
            result.find = 1;
            result.another_row = portal_pairs[i].row2;
            result.another_col = portal_pairs[i].col2;
            return result;
        } else if (head_row == portal_pairs[i].row2 && 
            head_col == portal_pairs[i].col2) {
            result.find = 1;
            result.another_row = portal_pairs[i].row1;
            result.another_col = portal_pairs[i].col1;
            return result;
        }
    }
    return result;
}

void add_wall(struct tile board[ROWS][COLS]) {
    int row, col;
    scanf("%d %d", &row, &col);

    if (!is_out_of_bounds(row, col)) {
        if (board[row][col].entity == EMPTY) {
            board[row][col].entity = WALL;
        } else {
            printf("ERROR: Invalid tile, %d %d is occupied!\n", row, col);
        }
    } else {
        printf("ERROR: Invalid position, %d %d is out of bounds!\n", row, col);
    }
}

void add_exit(struct tile board[ROWS][COLS]) {
    int row, col;
    scanf("%d %d", &row, &col);

    if (!is_out_of_bounds(row, col)) {
        if (board[row][col].entity == EMPTY) {
            board[row][col].entity = EXIT_LOCKED;
        } else {
            printf("ERROR: Invalid tile, %d %d is occupied!\n", row, col);
        }
    } else {
        printf("ERROR: Invalid position, %d %d is out of bounds!\n", row, col);
    }
}

void add_apple(struct tile board[ROWS][COLS]) {
    int row, col;
    char apple_type;
    scanf(" %c %d %d", &apple_type, &row, &col);

    if (!is_out_of_bounds(row, col)) {
        if (board[row][col].entity == EMPTY) {
            if (apple_type == 'n') {
                board[row][col].entity = APPLE_NORMAL;
            } else if (apple_type == 'r') {
                board[row][col].entity = APPLE_REVERSE;
            } else if (apple_type == 's') {
                board[row][col].entity = APPLE_SPLIT;
            } else {
                printf("ERROR: Invalid apple type '%c'!\n", apple_type);
            }
        } else {
            printf("ERROR: Invalid tile, %d %d is occupied!\n", row, col);
        }
    } else {
        printf("ERROR: Invalid position, %d %d is out of bounds!\n", row, col);
    }
}

void add_long_wall(struct tile board[ROWS][COLS]) {
    int row, col, length;
    char direction_wall;
    scanf(" %c %d %d %d", &direction_wall, &row, &col, &length);

    if (is_out_of_bounds(row, col)) {
        printf("ERROR: Invalid position, %d %d is out of bounds!\n", row, col);
        return;
    }

    int out_of_bounds = 0;
    if (direction_wall == 'h') {
        if (col + length > COLS) {
            out_of_bounds = 1;
        }
    } else if (direction_wall == 'v') {
        if (row + length > ROWS) {
            out_of_bounds = 1;
        }
    }

    if (out_of_bounds) {
        printf("ERROR: Invalid position, part of the wall is out of bounds!\n");
        return;
    }

    int occupied = 0;
    if (direction_wall == 'h') {
        for (int col_c = col; col_c < col + length; col_c++) {
            if (board[row][col_c].entity != EMPTY) {
                occupied = 1;
            } 
        }
    } else if (direction_wall == 'v') {
        for (int row_r = row; row_r < row + length; row_r++) {
            if (board[row_r][col].entity != EMPTY) {
                occupied = 1;
            }
        }
    }

    if (occupied) {
        printf("ERROR: Invalid tile, part of the wall is occupied!\n");
        return;
    }

    if (direction_wall == 'h') {
        for (int col_c = col; col_c < col + length; col_c++) {
            board[row][col_c].entity = WALL;
        }
    } else if (direction_wall == 'v') {
        for (int row_r = row; row_r < row + length; row_r++) {
            board[row_r][col].entity = WALL;
        }
    }
}

void add_passage(struct tile board[ROWS][COLS]) {
    int row, col;
    char direction;
    scanf(" %c %d %d", &direction, &row, &col);

    if (!is_out_of_bounds(row, col)) {
        if (board[row][col].entity == EMPTY) {
            if (direction == '^') board[row][col].entity = PASSAGE_UP;
            else if (direction == 'v') board[row][col].entity = PASSAGE_DOWN;
            else if (direction == '<') board[row][col].entity = PASSAGE_LEFT;
            else if (direction == '>') board[row][col].entity = PASSAGE_RIGHT;
            else printf("ERROR: Invalid passage direction '%c'!\n", direction);
        } else {
            printf("ERROR: Invalid tile, %d %d is occupied!\n", row, col);
        }
    } else {
        printf("ERROR: Invalid position, %d %d is out of bounds!\n", row, col);
    }
}

void add_portal(struct tile board[ROWS][COLS],
                struct portal_pair portal_pairs[MAX_PORTAL_PAIRS],
                int count_portals_pairs[1]) {
    int row1, col1, row2, col2;
    scanf("%d %d %d %d", &row1, &col1, &row2, &col2);

    if (count_portals_pairs[0] >= MAX_PORTAL_PAIRS) {
        printf(
 "ERROR: Invalid placement, maximum number of portal pairs already reached!\n");
        return;
    }

    if (is_out_of_bounds(row1, col1)) {
        printf(
 "ERROR: Invalid position for first portal in pair, %d %d is out of bounds!\n"
    , row1, col1);
        return;
    }

    if (is_out_of_bounds(row2, col2)) {
        printf(
 "ERROR: Invalid position for second portal in pair, %d %d is out of bounds!\n"
    , row2, col2);
        return;
    }

    if (board[row1][col1].entity != EMPTY) {
        printf(
    "ERROR: Invalid tile for first portal in pair, %d %d is occupied!\n", 
            row1, col1);
        return;
    }

    if (board[row2][col2].entity != EMPTY) {
        printf(
    "ERROR: Invalid tile for second portal in pair, %d %d is occupied!\n"
            , row2, col2);
        return;
    }

    board[row1][col1].entity = PORTAL;
    board[row2][col2].entity = PORTAL;
    portal_pairs[count_portals_pairs[0]].row1 = row1;
    portal_pairs[count_portals_pairs[0]].col1 = col1;
    portal_pairs[count_portals_pairs[0]].row2 = row2;
    portal_pairs[count_portals_pairs[0]].col2 = col2;
    count_portals_pairs[0]++;
}

void print_statistics(struct tile board[ROWS][COLS],
                      int points, int moves_made, int num_apples_eaten,
                      int num_initial_apples) {
    double completion_percentage = 0.0;
    int num_apples_remaining = count_apple_num(board);
    int maximum_points_remaining = 0;

    if (num_initial_apples == 0) {
        completion_percentage = 100.0;
    } else {
        completion_percentage = 100.0 * num_apples_eaten / num_initial_apples;
    }

    maximum_points_remaining = cal_maximum_points_remaining(board);

    print_game_statistics(points, moves_made, num_apples_eaten, 
        num_apples_remaining, completion_percentage, maximum_points_remaining);
}

void reset_map(struct tile board[ROWS][COLS],
               struct tile original_board[ROWS][COLS],
               struct snake_body snake_body[100],
               int points[1], int moves_made[1],
               int num_apples_eaten[1], int snake_length[1],
               int num_initial_apples[1], int original_apples[1],
               int original_snake_row[1], int original_snake_col[1]) {
    printf("--- Resetting Map ---\n");
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col] = original_board[row][col];
        }
    }
    points[0] = 0;
    moves_made[0] = 0;
    num_apples_eaten[0] = 0;
    num_initial_apples[0] = original_apples[0];
    snake_body[0].snake_x = original_snake_row[0];
    snake_body[0].snake_y = original_snake_col[0];
    snake_length[0] = 1;
    print_board(board, snake_body[0].snake_x, snake_body[0].snake_y);
}

void move_snake_body(struct snake_body snake_body[100], int snake_length[1],
                     int head_row, int head_col, int moves_made[1]) {
    for (int i = snake_length[0] - 1; i >= 0; i--) {
        snake_body[i + 1] = snake_body[i];
    }
    snake_length[0]++;
    snake_body[0].snake_x = head_row;
    snake_body[0].snake_y = head_col;
    moves_made[0]++;
}


// =============================================================================
// EDITABLE Provided Functions
// =============================================================================

// Given a 2D board array, initialise all tiles to EMPTY.
void initialise_board(struct tile board[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col].entity = EMPTY;
        }
    }
}

// Prints the game board, showing the snake's head position on the board.
void print_board(
    struct tile board[ROWS][COLS],
    int snake_row,
    int snake_col
) {
    print_board_line();
    print_board_header();
    print_board_line();
    for (int row = 0; row < ROWS; row++) {
        print_tile_spacer();
        for (int col = 0; col < COLS; col++) {
            printf(" ");
            struct tile tile = board[row][col];
            if (row == snake_row && col == snake_col) {
                printf("^~^");
            } else if (tile.entity == WALL) {
                printf("|||");
            } else if (tile.entity == BODY_SEGMENT) {
                printf("###");
            } else if (tile.entity == EXIT_LOCKED) {
                printf("[X]");
            } else if (tile.entity == EXIT_UNLOCKED) {
                printf("[ ]");
            } else if (tile.entity == APPLE_NORMAL) {
                printf("(`)");
            } else if (tile.entity == APPLE_REVERSE) {
                printf("(R)");
            } else if (tile.entity == APPLE_SPLIT) {
                printf("(S)");
            } else if (tile.entity == PASSAGE_UP) {
                printf("^^^");
            } else if (tile.entity == PASSAGE_DOWN) {
                printf("vvv");
            } else if (tile.entity == PASSAGE_LEFT) {
                printf("<<<");
            } else if (tile.entity == PASSAGE_RIGHT) {
                printf(">>>");
            } else if (tile.entity == PORTAL) {
                printf("~O~");
            } else if (tile.entity == EXPLOSION) {
                printf("***");
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
    print_tile_spacer();
}

// =============================================================================
// DO NOT EDIT Provided Functions
// =============================================================================

// Prints statistics about the game
void print_game_statistics(
    int points,
    int moves_made,
    int num_apples_eaten,
    int num_apples_remaining,
    double completion_percentage,
    int maximum_points_remaining
) {
    printf("============ Game Statistics ============\n");
    printf("Totals:\n");
    printf("  - Points: %d\n", points);
    printf("  - Moves Made: %d\n", moves_made);
    printf("  - Number of Apples Eaten: %d\n", num_apples_eaten);
    printf("Completion:\n");
    printf("  - Number of Apples Remaining: %d\n", num_apples_remaining);
    printf("  - Apple Completion Percentage: %.1f%%\n", completion_percentage);
    printf("  - Maximum Points Remaining: %d\n", maximum_points_remaining);
    printf("=========================================\n");
}

// Prints statistics about the game for both snakes when there are two players
void print_game_statistics_with_rival(
    int original_points,
    int original_moves_made,
    int original_num_apples_eaten,
    int rival_points,
    int rival_moves_made,
    int rival_num_apples_eaten,
    int num_apples_remaining,
    double completion_percentage,
    int maximum_points_remaining
) {
    printf("============ Game Statistics ============\n");
    printf("Original Snake Totals:\n");
    printf("  - Points: %d\n", original_points);
    printf("  - Moves Made: %d\n", original_moves_made);
    printf("  - Number of Apples Eaten: %d\n", original_num_apples_eaten);
    printf("Rival Snake Totals:\n");
    printf("  - Points: %d\n", rival_points);
    printf("  - Moves Made: %d\n", rival_moves_made);
    printf("  - Number of Apples Eaten: %d\n", rival_num_apples_eaten);
    printf("Completion:\n");
    printf("  - Number of Apples Remaining: %d\n", num_apples_remaining);
    printf("  - Apple Completion Percentage: %.1f%%\n", completion_percentage);
    printf("  - Maximum Points Remaining: %d\n", maximum_points_remaining);
    printf("=========================================\n");
}

// Helper function for print_board().
void print_board_header(void) {
    printf("|            C S _ S N A K E            |\n");
}

// Helper function for print_board().
void print_board_line(void) {
    printf("+");
    for (int col = 0; col < COLS; col++) {
        printf("---+");
    }
    printf("\n");
}

// Helper function for print_board().
void print_tile_spacer(void) {
    printf("+");
    for (int col = 0; col < COLS; col++) {
        printf("   +");
    }
    printf("\n");
}
