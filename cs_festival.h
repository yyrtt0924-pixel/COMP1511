// Assignment 2 25T3 COMP(1511|1911): CS Festival
// cs_festival.h
//
// This program was written by <Yaru Yang> <z5676827>
// on <10.30>
//
// <PROGRAM DESCRIPTION>

///////////////////////////////////////////////////////////////////////////////
// Provided Constants
///////////////////////////////////////////////////////////////////////////////

#define MAX_SIZE 100

///////////////////////////////////////////////////////////////////////////////
// Your Constants
///////////////////////////////////////////////////////////////////////////////

#define QUIT 'q'
#define HELP '?'
#define ADD 'a'
#define STAGE 's'
#define PRINT 'p'
#define PERFORMANCE 'p'
#define INSERT 'i'
#define SONG 'g'
#define PRINT_MOST_POPULAR_PERFORMANCE '*'
#define PRINT_BAN_SUMMARY 'P'
#define REMOVE 'x'
#define UPDATE_PERFORMANCE_DURATION 'u'
#define MOVE_PERFORMANCE 'm'
#define JOIN_PERFORMANCE 'j'

#define NO_PERFORMANCE -1
#define REST_TIME 10

///////////////////////////////////////////////////////////////////////////////
// Provided Enums
///////////////////////////////////////////////////////////////////////////////

enum genre {
    ROCK,
    POP,
    COUNTRY,
    JAZZ,
    METAL,
    HIPHOP,
    INVALID_GENRE
};

///////////////////////////////////////////////////////////////////////////////
// Provided Structs
///////////////////////////////////////////////////////////////////////////////

struct festival {
    // The name of your festival
    char name[MAX_SIZE];
    // The list of stages in the festival
    struct stage *stages;
};

struct stage {
    // The name of the stage
    char name[MAX_SIZE];
    // The list of performances on the stage
    struct performance *performances;
    // The next stage in the festival
    struct stage *next;
};

struct performance {
    // The name of the band performing
    char band_name[MAX_SIZE];
    // The start time of the performance
    // (in minutes from the start of the festival)
    int start_time;
    // The end time of the performance
    // (in minutes from the start of the festival)
    int end_time;
    // The maximum duration allowed for the performance (in minutes)
    int max_duration;
    // The genre of the performance
    enum genre genre;
    // The setlist of songs for the performance
    struct song *setlist;
    // The next performance in the list
    struct performance *next;
};

struct song {
    // The title of the song
    char title[MAX_SIZE];
    // The duration of the song (in minutes)
    double duration;
    // The popularity rating of the song (1-10)
    int popularity;
    // The next song in the setlist
    struct song *next;
};

///////////////////////////////////////////////////////////////////////////////
// Provided Function Prototypes
///////////////////////////////////////////////////////////////////////////////

void print_welcome_banner();
void scan_name(char name[MAX_SIZE]);
enum genre scan_genre();
void print_help(void);
void print_festival(struct festival *festival);
void print_performance_header(struct performance *performance);
void print_stage_title(struct stage *stage);
void print_setlist(struct song *setlist);
void print_performance(struct performance *performance);
void print_song(struct song *song, int song_num);
void print_conflict_group_header(int conflict_time);
void print_conflict_performance(
    char stage_name[MAX_SIZE],
    struct performance *performance
);

// Additional provided function prototypes
// You won't need to use these functions!
// We use them to implement some of the provided helper functions.
void format_time(int minutes, char buffer[MAX_SIZE]);
void get_genre_name(enum genre genre, char buffer[MAX_SIZE]);
int scan_token(char buffer[MAX_SIZE], int buffer_size);
enum genre string_to_genre(char genre_str[MAX_SIZE]);

///////////////////////////////////////////////////////////////////////////////
// Your Function Prototypes
///////////////////////////////////////////////////////////////////////////////

// Stage 1
struct festival *create_festival(char name[MAX_SIZE]);
struct stage *create_stage(char name[MAX_SIZE]);
struct performance *create_performance(
    char band_name[MAX_SIZE],
    int start_time,
    int max_duration,
    enum genre genre
);
struct song *create_song(
    char title[MAX_SIZE],
    double duration,
    int popularity
);
void command_loop(struct festival *festival);
void add_stage(struct festival *festival);

// Add your function prototypes below
//2.1
void append_performance(struct festival *festival);
//2.2
void insert_song(struct festival *festival);
//2.3
void the_most_popular_performance(struct festival *festival);
//2.4
void print_band_summary(struct festival *festival);
//3.1
void free_festival(struct festival *festivals);
//3.2
//command 1
void remove_performance(struct festival *festivals);
//command 2
void remove_stage(struct festival *festival);
//3.3
void remove_song(struct festival *festival);
//3.4
void update_performance_duration(struct festival *festival);
//3.5
void move_performance(struct festival *festival);
//4.1
void join_performances(struct festival *festival);