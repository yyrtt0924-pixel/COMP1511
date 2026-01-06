// Assignment 2 25T3 COMP(1511|1911): CS Festival
// cs_festival.c
//
// This program was written by <Yaru Yang> <z5676827>
// on <10.30>
//
// <PROGRAM DESCRIPTION>
//This program is called CS Festival
//which is a comprehensive festival planning system to manage stages,
//performances, and setlists seamlessly.
//Linked lists are mainly used.

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "cs_festival.h"

// Stage 1.1
// Function to create and initialise a festival
// Params:
//      name - the name of the festival
// Returns:
//      A pointer to the newly created festival
struct festival *create_festival(char name[MAX_SIZE]) {
    // TODO: implement this function
    //allocate the memory
    struct festival *new_festival = malloc(sizeof(struct festival));
    if (new_festival == NULL) {
        return NULL;
    }
    //copy the name of string
    strcpy(new_festival->name, name);

    new_festival->stages = NULL;

    return new_festival;
}

// Function to create and initialise a stage
// Params:
//      name - the name of the stage
// Returns:
//      A pointer to the newly created stage
struct stage *create_stage(char name[MAX_SIZE]) {
    // TODO: implement this function
    struct stage *new_stage = malloc(sizeof(struct stage));
    if (new_stage == NULL) {
        return NULL;
    }

    //copy the name of string
    strcpy(new_stage->name, name);

    new_stage->performances = NULL;
    new_stage->next = NULL;

    return new_stage;
}

// Function to create and initialise a performance
// Params:
//      band_name   - the name of the band
//      start_time  - the start time of the performance
//                    (in minutes from the start of the festival)
//      max_duration- the maximum duration allowed for the performance
//                    (in minutes)
//      genre       - the genre of the performance
// Returns:
//      A pointer to the newly created performance
struct performance *create_performance(
    char band_name[MAX_SIZE],
    int start_time,
    int max_duration,
    enum genre genre
) {
    // TODO: implement this function
    struct performance *new_performance = malloc(sizeof(struct performance));
    if (new_performance == NULL) {
        return NULL;
    }

    strcpy(new_performance->band_name, band_name);

    new_performance->start_time = start_time;
    new_performance->max_duration = max_duration;
    new_performance->end_time = start_time + max_duration;
    new_performance->genre = genre;
    new_performance->setlist = NULL;
    new_performance->next = NULL;

    return new_performance;
}

// Function to create and initialise a song
// Params:
//      title      - the title of the song
//      duration   - the duration of the song (in minutes)
//      popularity - the popularity rating of the song
// Returns:
//      A pointer to the newly created song
struct song *create_song(
    char title[MAX_SIZE],
    double duration,
    int popularity
) {
    // TODO: implement this function
    struct song *new_song = malloc(sizeof(struct song));
    if (new_song == NULL) {
        return NULL;
    }

    strcpy(new_song->title, title);

    new_song->duration = duration;
    new_song->popularity = popularity;
    new_song->next = NULL;

    return new_song;
}

// Stage 1.2
// Function to run the main command loop for the program
// Params:
//      festival - a pointer to the festival
// Returns: None
void command_loop(struct festival *festival) {
    // TODO: implement this function
    char user_command;
    char user_command2;
    int running = 1;

    while (running) {
        printf("Enter command: ");
        scanf(" %c", &user_command);
        if (user_command == QUIT) {
            running = 0;
        } else if (user_command == HELP) {
            print_help();
        } else if (user_command == ADD) {
            scanf(" %c", &user_command2);
            if (user_command2 == STAGE) {
                add_stage(festival);
            } else if (user_command2 == PERFORMANCE) {
                append_performance(festival);
            }
        } else if (user_command == PRINT) {
            print_festival(festival);
        } else if (user_command == INSERT) {
            scanf(" %c", &user_command2);
            if (user_command2 == SONG) {
                insert_song(festival);
            }
        } else if (user_command == PRINT_MOST_POPULAR_PERFORMANCE) {
            the_most_popular_performance(festival);
        } else if (user_command == PRINT_BAN_SUMMARY) {
            print_band_summary(festival);
        } else if (user_command == REMOVE) {
            scanf(" %c", &user_command2);
            if (user_command2 == PERFORMANCE) {
                remove_performance(festival);
            } else if (user_command2 == STAGE) {
                remove_stage(festival);
            } else if (user_command2 == SONG) {
                remove_song(festival);
            }
        } else if (user_command == UPDATE_PERFORMANCE_DURATION) {
            update_performance_duration(festival);
        } else if (user_command == MOVE_PERFORMANCE) {
            move_performance(festival);
        } else if (user_command == JOIN_PERFORMANCE) {
            join_performances(festival);
        } else {
            printf("ERROR: Invalid command.\n");
        }
    }
    free_festival(festival);
    return;
}

// Stage 1.3
// Function to add a stage to the festival
// Params:
//      festival - a pointer to the festival
// Returns: None
void add_stage(struct festival *festival) {
    // TODO: implement this function
    char name[MAX_SIZE];
    scan_name(name);

    struct stage *current = festival->stages;
    //check if there already exists a same name
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("ERROR: Stage with name '%s' already exists.\n", name);
            return;
        }
        current = current->next;
    }

    struct stage *new_stage = create_stage(name);
    if (new_stage == NULL) {
        return;
    }

    new_stage->next = festival->stages;
    festival->stages = new_stage;

    //if there is no same stage name, print it
    printf("Stage '%s' added.\n", name);
    return;
}

// Stage 1.4 Part 1
// Function to print the setlist of a performance
// Params:
//      setlist - a pointer to the first song in the setlist
// Returns: None
void print_setlist(struct song *setlist) {
    // TODO: implement this function
    struct song *current = setlist;
    if (current == NULL) {
        printf("  (no songs yet)\n");
        return;
    }
    //the position of the song
    int song_num = 1;
    while (current != NULL) {
        print_song(current, song_num);
        current = current->next;
        song_num++;
    }
    return;
}

// Stage 1.4 Part 2
// Function to print the entire festival, including stages and performances
// Params:
//      festival - a pointer to the festival
// Returns: None
void print_festival(struct festival *festival) {
    // TODO: implement this function
    printf("Festival: %s\n", festival->name);
    //if there is no stage
    if (festival->stages == NULL) {
        printf("  (no stages yet)\n");
        return;
    }

    struct stage *current_stage = festival->stages;
    while (current_stage != NULL) {
        print_stage_title(current_stage);

        //if there is no performance
        if (current_stage->performances == NULL) {
            printf("  (no performances yet)\n");
            printf("\n");
        } else {
            printf("\n");
            struct performance *current_performance
                    = current_stage->performances;
            //traversing all add_stage commands and printing them out
            while (current_performance != NULL) {
                print_performance_header(current_performance);
                print_setlist(current_performance->setlist);
                printf("\n");
                current_performance = current_performance->next;
            }
        }
        current_stage = current_stage->next;
    }
    return;
}

// Add your function definitions below this line
//2.1
// Params:
//        a pointer to match stage name
//Return: NULL->do not find
struct stage *match_stage_name(
    struct festival *festival, char stage_name[MAX_SIZE]) {
    struct stage *current = festival->stages;
    while (current != NULL) {
        if (strcmp(stage_name, current->name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//2.1
// Params:
//        a pointer to match stage name
//Return:
//        integer-if match-return 1
//               -if not match-return 0
int match_band_name(
    struct stage *stages, char band_name[MAX_SIZE]) {
    if (stages == NULL) {
        return 0;
    }

    struct performance *current = stages->performances;

    //the band has already got a performance
    while (current != NULL) {
        if (strcmp(band_name, current->band_name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

//2.1
// Params:
//        find the last performance
//Return:
//        pointer_current performance
struct performance *get_last_performance(struct stage *stages) {
    if (stages == NULL) {
        return NULL;
    }

    if (stages->performances == NULL) {
        return NULL;
    }
    struct performance *current = stages->performances;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

//2.1
// Params:
//       add new performances
// Returns: None
void append_performance(struct festival *festival) {
    char stage_name[MAX_SIZE], band_name[MAX_SIZE];
    int max_duration;
    scan_name(stage_name);
    scan_name(band_name);
    enum genre new_genre = scan_genre();
    scanf("%d", &max_duration);
    int start_time;

    struct stage *target_stage = match_stage_name(festival, stage_name);
    if (target_stage == NULL) {
        printf("ERROR: No stage with name '%s' found.\n", stage_name);
        return;
    }
    if (new_genre == INVALID_GENRE) {
        printf("ERROR: Invalid genre.\n");
        return;
    }
    if (max_duration <= 0) {
        printf("ERROR: Duration must be positive.\n");
        return;
    }
    int result = match_band_name(target_stage, band_name);
    if (result == 1) {
        printf(
"ERROR: Performance for band '%s' already exists on stage '%s'.\n"
            , band_name, stage_name);
        return;
    }

    struct performance *last_performance = get_last_performance(target_stage);
    //whether start_time is 0
    if (last_performance == NULL) {
        start_time = 0;
    } else {
        start_time = last_performance->end_time + REST_TIME;
    }
    //create new performance
    struct performance *new_performance =
    create_performance(band_name, start_time, max_duration, new_genre);
    if (new_performance == NULL) {
        return;
    }
    if (target_stage->performances == NULL) {
        target_stage->performances = new_performance;
    } else {
        last_performance->next = new_performance;
    }
    printf("Performance for band '%s' added to stage '%s'.\n"
        , band_name, stage_name);
    return;
}

//2.2
// Params:
//        compare the title, duration
//        and popularity of the new song with the previous song
//Return :
//        pointer->current song
struct song *match_message_setlist(
    struct song *songs,
    char title[MAX_SIZE],
    double duration,
    int popularity) {
    struct song *current = songs;
    while (current != NULL) {
        if (strcmp(title, current->title) == 0
        && duration == current->duration
        && popularity == current->popularity) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//2.2
// Params:
//        find whether there is a performance(use the band_name)
//Return :
//        pointer->current performance
struct performance *find_performance(
    struct stage *stages,
    char band_name[MAX_SIZE]) {
    struct performance *current = stages->performances;
    while (current != NULL) {
        if (strcmp(band_name, current->band_name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//2.2
// Params:
//        calculate current setlist's total duration
//Return:
//        double-total duration(without the new song)
double total_duration(struct song *songs) {
    struct song *current = songs;
    double total_duration = 0.0;

    while (current != NULL) {
        total_duration += current->duration;
        current = current->next;
    }
    return total_duration;
}

//2.2
// Params:
//        current total number of songs
//Return:
//         integer-total number of the songs
int total_songs(struct song *setlist) {
    int total_number = 0;
    struct song *current = setlist;
    while (current != NULL) {
        total_number++;
        current = current->next;
    }
    return total_number;
}

//2.2
// Params:
//        use the position to inset new song
//Return:
//        None
void insert_new_song(struct festival *festival, char stage_name[MAX_SIZE],
    char band_name[MAX_SIZE],
    char title[MAX_SIZE], double duration, int popularity, int position) {
    struct stage *target_stage = match_stage_name(festival, stage_name);
    struct performance *target_performance =
    find_performance(target_stage, band_name);
    struct song *new_song = create_song(title, duration, popularity);
    if (new_song == NULL) {
        return;
    }
    int insert_position = 0;
    int number_total_songs = total_songs(target_performance->setlist);
    if (position <= 1) {
        insert_position = 1;
    } else if (position > number_total_songs) {
        insert_position = number_total_songs + 1;
    } else {
        insert_position = position;
    }

    if (insert_position == 1) {
        new_song->next = target_performance->setlist;
        target_performance->setlist = new_song;
    } else {
        struct song *current = target_performance->setlist;
        for (int i = 1; i < insert_position - 1; i++) {
            current = current->next;
        }
        new_song->next = current->next;
        current->next = new_song;
    }
    return;
}

//2.2
// Params:
//        core part of 2.2: insert new songs in performance
//Return:
//        None
void insert_song(struct festival *festival) {
    char stage_name[MAX_SIZE], band_name[MAX_SIZE], title[MAX_SIZE];
    scan_name(stage_name);
    scan_name(band_name);
    scan_name(title);
    double duration = 0.0;
    scanf(" %lf", &duration);
    int popularity;
    scanf(" %d", &popularity);
    int position = 0;
    scanf("%d", &position);
    struct stage *target_stage = match_stage_name(festival, stage_name);
    if (target_stage == NULL) {
        printf("ERROR: No stage with name '%s' found.\n", stage_name);
        return;
    }
    struct performance *target_performance =
    find_performance(target_stage, band_name);
    if (target_performance == NULL) {
        printf("ERROR: No performance for band '%s' found on"
            " stage '%s'.\n", band_name, stage_name);
        return;
    }
    if (popularity < 1 || popularity > 10) {
        printf("ERROR: Song popularity must be"
            " between 1 and 10 (inclusive).\n");
        return;
    }
    if (duration <= 0) {
        printf("ERROR: Duration must be positive.\n");
        return;
    }
    struct song *target_message_setlist = match_message_setlist(
        target_performance->setlist, title, duration, popularity);
    if (target_message_setlist != NULL) {
        printf("ERROR: Song '%s' with duration '%.1lf' and popularity '%d'"
            " already exists in the setlist.\n", title, duration, popularity);
        return;
    }
    double current_total_duration = total_duration(target_performance->setlist);
    if (current_total_duration + duration > target_performance->max_duration) {
        printf("ERROR: Adding song would exceed max duration"
            " of performance for band '%s'.\n", band_name);
        return;
    }

    insert_new_song(festival, stage_name, band_name,
    title, duration, popularity, position);
    printf("Song '%s' added to performance for band '%s' on stage '%s'.\n",
           title, band_name, stage_name);
}

//2.3
// Params:
//        count average
//Return:
//        double-average popularity
double calculate_average(struct performance *performances) {
    int sum_popularity = 0;
    int count_popularity = 0;
    struct song *current_song = performances->setlist;

    if (current_song == NULL) {
        return 0.0;
    }
    while (current_song != NULL) {
        sum_popularity += current_song->popularity;
        count_popularity++;
        current_song = current_song->next;
    }
    double average = (double) sum_popularity / count_popularity;

    return average;
}

//2.3
// Params:
//        find the highest popularity(number)
//Return:
//       double-highest_popularity
double find_highest_popularity(struct festival *festival) {
    double highest_average = NO_PERFORMANCE;

    struct stage *current_stage = festival->stages;
    while (current_stage != NULL) {
        struct performance *current_performance = current_stage->performances;
        while (current_performance != NULL) {
            double average = calculate_average(current_performance);
            if (average > highest_average) {
                highest_average = average;
            }

            current_performance = current_performance->next;
        }
        current_stage = current_stage->next;
    }
    return highest_average;
}

//2.3
// Params:
//        find the highest popularity(position)
//Return:
//       None
void print_highest_popularity_position(
    struct festival *festival,
    double highest_average_popularity) {
    struct stage *current_stage = festival->stages;
    while (current_stage != NULL) {
        struct performance *current_performance = current_stage->performances;
        while (current_performance != NULL) {
            double average = calculate_average(current_performance);

            if (average == highest_average_popularity) {
                print_stage_title(current_stage);
                print_performance_header(current_performance);
                print_setlist(current_performance->setlist);
                printf("\n");
            }
            current_performance = current_performance->next;
        }
        current_stage = current_stage->next;
    }
    return;
}

//2.3
// Params:
//        core part of 2.3: print out the most_popular_performance
//        by using command * in the command loop
//Return:
//       None
void the_most_popular_performance(struct festival *festival) {
    //If there are no performances in the festival plan yet

    struct stage *current_stage = festival->stages;
    if (current_stage == NULL) {
        printf("No performances found.\n");
        return;
    }

    double highest_popularity = find_highest_popularity(festival);

    if (highest_popularity < 0) {
        printf("No performances found.\n");
        return;
    }

    // First pass: find the highest average popularity
    printf("======== Popular performances ========\n");
    print_highest_popularity_position(festival, highest_popularity);
}

//2.4
// Params:
//       total performances
//Return:
//       None
int count_band_performances(
    struct festival *festival,
    char band_name[MAX_SIZE]) {
    int total = 0;

    struct stage *current_stage = festival->stages;
    while (current_stage != NULL) {
        struct performance *current_performance = current_stage->performances;
        while (current_performance != NULL) {
            if (strcmp(band_name, current_performance->band_name) == 0) {
                total++;
            }
            current_performance = current_performance->next;
        }
        current_stage = current_stage->next;
    }
    return total;
}

//2.4
// Params:
//       print band performance
//Return:
//       None
void print_band_performances(
    struct festival *festival,
    char band_name[MAX_SIZE]) {
    struct stage *current_stage = festival->stages;
    while (current_stage != NULL) {
        struct performance *current_performance = current_stage->performances;
        while (current_performance != NULL) {
            if (strcmp(band_name, current_performance->band_name) == 0) {
                print_stage_title(current_stage);
                print_performance_header(current_performance);
                print_setlist(current_performance->setlist);
                printf("\n");
            }
            current_performance = current_performance->next;
        }
        current_stage = current_stage->next;
    }
}

//2.4
// Params:
//        Print a summary of all performances for a given band.
//        core part of 2.4
//Return:
//       None
void print_band_summary(struct festival *festival) {
    //If there are no performances for the given band
    char band_name[MAX_SIZE];
    scan_name(band_name);

    if (count_band_performances(festival, band_name) == 0) {
        printf("No performances found for band '%s'.\n", band_name);
        return;
    }

    int total_band_performances = count_band_performances(festival, band_name);

    printf("Band: %s\n", band_name);
    printf("Total Performances: %d\n", total_band_performances);
    printf("\n");
    print_band_performances(festival, band_name);
}

///////////////////////////////////////////
////             stage 3              ////
///////////////////////////////////////////

//stage3.1
// Params:
//        this four function are all used to free memory
//Return:
//       None
void free_song_list(struct song *setlist) {
    struct song *current = setlist;
    while (current != NULL) {
        struct song *temp = current;
        current = current->next;
        free(temp);
    }
}
void free_performance_list(struct performance *performances) {
    struct performance *current = performances;
    while (current != NULL) {
        struct performance *temp = current;
        free_song_list(current->setlist);
        current = current->next;
        free(temp);
    }
}
void free_stage_list(struct stage *stages) {
    struct stage *current = stages;
    while (current != NULL) {
        struct stage *temp = current;
        free_performance_list(current->performances);
        current = current->next;
        free(temp);
    }
}
void free_festival(struct festival *festival) {
    if (festival == NULL) {
        return;
    }
    free_stage_list(festival->stages);
    free(festival);
}
//3.2
// Params:
//     use the band name to search the performance and then delete performance
//Return:
//       None
void delete_performance(struct stage *stages, char band_name[MAX_SIZE]) {
    struct performance *prev = NULL;
    struct performance *current = stages->performances;
    while (current != NULL) {
        if (strcmp(current->band_name, band_name) == 0) {

            if (prev == NULL) {
                stages->performances = current->next;
            } else {
                prev->next = current->next;
            }

            free_song_list(current->setlist);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    return;
}
//3.2
// Params:
//       count new time
//Return:
//       None
void new_time(struct stage *stages) {
    struct performance *current_performance = stages->performances;

    int current_start_time = 0;
    while (current_performance != NULL) {
        current_performance->start_time = current_start_time;
        current_performance->end_time =
        current_performance->start_time + current_performance->max_duration;
        current_start_time = current_performance->end_time + REST_TIME;
        current_performance = current_performance->next;
    }
    return;
}
//stage 3.2
// Params:
//        core part of 3.2
//        Command 1: Remove Performance
//Return:
//       None
void remove_performance(struct festival *festival) {
    char stage_name[MAX_SIZE];
    char band_name[MAX_SIZE];
    scan_name(stage_name);
    scan_name(band_name);

    struct stage *target_stage= match_stage_name(festival, stage_name);
    if (target_stage == NULL) {
        printf("ERROR: No stage with name '%s' found.\n", stage_name);
        return;
    }
    struct performance *find_performances =
    find_performance(target_stage, band_name);
    if (find_performances == NULL) {
        printf("ERROR: No performance for band '%s' "
            "found on stage '%s'.\n",
            band_name, stage_name);
        return;
    }

    delete_performance(target_stage, band_name);

    new_time(target_stage);

    printf("Performance for band '%s' removed from stage '%s'.\n",
        band_name, stage_name);
}
//3.2
// Params:
//        use the stage name to search the stage and then delete stage
//Return:
//       None
void delete_stage(struct festival *festival, char stage_name[MAX_SIZE]) {
    struct stage *current = festival->stages;

    struct stage *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, stage_name) == 0) {

            if (prev == NULL) {
                festival->stages = current->next;
            } else {
                prev->next = current->next;
            }
            free_performance_list(current->performances);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
//3.2
// Params:
//        core part of 3.2
//        Command 2: Remove Stage
//Return:
//       None
void remove_stage(struct festival *festival) {
    char stage_name[MAX_SIZE];
    scan_name(stage_name);

    struct stage *target_stage = match_stage_name(festival, stage_name);
    if (target_stage == NULL) {
        printf("ERROR: No stage with name '%s' found.\n", stage_name);
        return;
    }

    delete_stage(festival, stage_name);
    printf("Stage '%s' removed.\n", stage_name);
}

//3.3
// Params:
//       find the song that need to delete from performance
//Return:
//       pointer-target song
struct song *delete_target_song(
    struct performance *performance,
    int position) {
    struct song *current = performance->setlist;
    if (current == NULL) {
        return NULL;
    }
    struct song *prev = NULL;

    for (int i = 1; i < position; i++) {
        prev = current;
        current = current->next;
    }

    //delete the first song
    if (prev == NULL) {
        performance->setlist = current->next;
    } else {
        prev->next = current->next;
    }

    return current;
}
//3.3
// Params:
//        core part of 3.3
//        remove song
//Return:
//       None
void remove_song(struct festival *festival) {
    char stage_name[MAX_SIZE];
    char band_name[MAX_SIZE];
    scan_name(stage_name);
    scan_name(band_name);

    int position = 1;
    scanf("%d", &position);
    //1. find stage
    struct stage *target_stage = match_stage_name(festival, stage_name);
    if (target_stage == NULL) {
        printf("ERROR: No stage with name '%s' found.\n", stage_name);
        return;
    }
    //2. use band name find the performance
    struct performance *target_performances =
    find_performance(target_stage, band_name);
    if (target_performances == NULL) {
        printf("ERROR: No performance for band '%s' "
            "found on stage '%s'.\n",
            band_name, stage_name);
        return;
    }
    //3. check if there is any song
    if (target_performances->setlist == NULL) {
        printf("ERROR: Performance for band '%s' has no songs to remove.\n",
             band_name);
        return;
    }
    //4. check whether the position is valid
    int total = total_songs(target_performances->setlist);
    if (position <= 0 || position > total) {
        printf("ERROR: Invalid song position '%d' "
            "for performance of band '%s'.\n",
            position, band_name);
        return;
    }
    struct song *target_song =
    delete_target_song(target_performances, position);
    if (target_song == NULL) {
        return;
    } else {
        printf("Song '%s' removed from performance for "
            "band '%s' on stage '%s'.\n",
            target_song->title, band_name, stage_name);
        free(target_song);
    }
    return;
}
//3.4
// Params:
//      if is decrease the duration
//      the last song need to be deleted
//      until the maximum duration fits within the new duration
//Return:
//       None
void delete_last_song(struct performance *performance, int new_duration) {
    double current_total = total_duration(performance->setlist);
    if (current_total <= new_duration) {
        return;
    }
    while (new_duration < current_total && performance->setlist != NULL) {
        //if there is only one song
        if (performance->setlist->next == NULL) {
            free(performance->setlist);
            performance->setlist = NULL;
            current_total = 0.0;
            //return;
        } else {
            struct song *current = performance->setlist;
            //find the last second song
            while (current->next->next != NULL) {
                current = current->next;
            }
            free(current->next);
            current->next = NULL;
            current_total = total_duration(performance->setlist);
        }
    }

}
//3.4
// Params:
//       core part of 3.4
//       update performance duration
//Return:
//       None
void update_performance_duration(struct festival *festival) {
    char stage_name[MAX_SIZE];
    char band_name[MAX_SIZE];
    scan_name(stage_name);
    scan_name(band_name);

    int new_duration = 0;
    scanf("%d", &new_duration);

    struct stage *target_stage = match_stage_name(festival, stage_name);
    if (target_stage == NULL) {
        printf("ERROR: No stage with name '%s' found.\n", stage_name);
        return;
    }
    struct performance *target_performances =
    find_performance(target_stage, band_name);
    if (target_performances == NULL) {
        printf("ERROR: No performance for band '%s' found on stage '%s'.\n",
            band_name, stage_name);
        return;
    }

    if (new_duration <= 0) {
        printf("ERROR: Duration must be positive.\n");
        return;
    }

    int old_duration = target_performances->max_duration;
    target_performances->max_duration = new_duration;
    if (new_duration < old_duration) {
        delete_last_song(target_performances, new_duration);
    }

    new_time(target_stage);

    printf("Performance for band '%s' on "
        "stage '%s' updated to max duration '%d' minutes.\n",
        band_name, stage_name, new_duration);
}
//3.5
// Params:
//       delete the source of the performance(but do not free it)
//Return:
//       pointer-source performance(which need to remove)
struct performance *remove_source_performance(
    struct stage *stage,
    char band_name[MAX_SIZE]) {
    struct performance *current = stage->performances;
    struct performance *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->band_name, band_name) == 0) {
            //only one performance
            if (prev == NULL) {
                stage->performances = current->next;
            } else {
                prev->next = current->next;
            }
            current->next = NULL;
            return current;
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}
//3.5
// Params:
//        put the source performance into the destination position
//Return:
//        int-the actual insert position
int insert_position(
    struct stage *stage,
    struct performance *performance,
    int position) {
    //if the destination do not have performance yet
    //just put the source performance directly into the stage.
    if (stage->performances == NULL) {
        stage->performances = performance;
        return 1;
    }

    int number_total_performances = 0;

    struct performance *current = stage->performances;
    while (current != NULL) {
        number_total_performances++;
        current = current->next;
    }

    int insert_position = 0;
    if (position <= 1) {
        insert_position = 1;
    } else if (position > number_total_performances) {
        insert_position = number_total_performances + 1;
    } else {
        insert_position = position;
    }

    if (insert_position == 1) {
        performance->next = stage->performances;
        stage->performances = performance;
    } else {
        struct performance *current_performance = stage->performances;
        for (int i = 1; i < insert_position - 1; i++) {
            current_performance = current_performance->next;
        }
        performance->next = current_performance->next;
        current_performance->next = performance;
    }
    return insert_position;
}
//3.5
// Params:
//        move performance from one stage to another stage
//       core part of 3.5
//Return:
//       None
void move_performance(struct festival *festival) {
    char src_stage_name[MAX_SIZE];
    char dest_stage_name[MAX_SIZE];
    char band_name[MAX_SIZE];
    scan_name(src_stage_name);
    scan_name(dest_stage_name);
    scan_name(band_name);
    int position;
    scanf("%d", &position);

    struct stage *src_stage = match_stage_name(festival, src_stage_name);
    if (src_stage == NULL) {
        printf("ERROR: No stage with name '%s' found.\n", src_stage_name);
        return;
    }
    struct stage *dest_stage = match_stage_name(festival, dest_stage_name);
    if (dest_stage == NULL) {
        printf("ERROR: No stage with name '%s' found.\n", dest_stage_name);
        return;
    }
    struct performance *performance_to_move =
    find_performance(src_stage, band_name);
    if (performance_to_move == NULL) {
        printf("ERROR: No performance for band '%s' found on stage '%s'.\n",
            band_name, src_stage_name);
        return;
    }
    if (match_band_name(dest_stage, band_name) && src_stage != dest_stage) {
        printf("ERROR: Performance for band '%s'"
            " already exists on stage '%s'.\n",
               band_name, dest_stage_name);
        return;
    }

    struct performance *removed_performance =
    remove_source_performance(src_stage, band_name);
    if (src_stage->performances != NULL) {
        new_time(src_stage);
    }

    int actual_position = insert_position(
        dest_stage, removed_performance, position);
    new_time(dest_stage);

    printf("Performance for band '%s' moved from stage"
        " '%s' to stage '%s' at position '%d'.\n",
           band_name, src_stage_name, dest_stage_name, actual_position);
}

///////////////////////////////////////////
////             stage 4               ////
///////////////////////////////////////////
//4.1
// Params:
//        Identifying the headliner
struct performance *find_the_headliner(
    struct festival *festival,
    char stage_name1[MAX_SIZE],
    char band_name1[MAX_SIZE],
    char stage_name2[MAX_SIZE],
    char band_name2[MAX_SIZE]) {
    //1. via match stage to match performance(by using band name)
    struct performance *performance1 = NULL;
    struct stage *stage1 =  match_stage_name(festival, stage_name1);
    if (stage1 != NULL) {
        performance1 = find_performance(stage1, band_name1);
    }
    struct performance *performance2 = NULL;
    struct stage *stage2 =  match_stage_name(festival, stage_name2);
    if (stage2 != NULL) {
        performance2 = find_performance(stage2, band_name2);
    }
    //2. calculate the average popularity for every performance
    double average_popularity1 = calculate_average(performance1);
    double average_popularity2 = calculate_average(performance2);

    //3. define the headliner
    if (average_popularity1 < average_popularity2) {
        return performance2;
    }
    return performance1;
}
//4.1
// Params:
//        Determine whether it is a vowel
int is_vowel(char letter) {
    letter = tolower(letter);
    if (strchr("aeiou", letter) != NULL) {
        return 1;
    }
    return 0;
}
//4.1
// Params:
//        Determine whether it is a consonant
int is_consonant(char letter) {
    if (!is_vowel(letter) && isalpha(letter)) {
        return 1;
    }
    return 0;
}
//4.1
// Params:
//        the new band name
void joined_band_name(
    char *headliner_name, 
    char *supporting_name, 
    char *result) {
    int headliner_len = (strlen(headliner_name) + 1) / 2;
    char joined_first_half[headliner_len + 1];
    strncpy(joined_first_half, headliner_name, headliner_len);
    joined_first_half[headliner_len] = '\0';

    int last_vowel = -1;
    for (int i = 0; i < headliner_len; i++ ) {
        if (is_vowel(joined_first_half[i])) {
            last_vowel = i;
        }
    }
    //calculate the actual length of the joined band name(first half)
    int head_part_length;
    if (last_vowel != -1) {
        head_part_length = last_vowel + 1;
    } else {
        head_part_length = headliner_len;
    }
    char headliner_part[head_part_length + 1];
    strncpy(headliner_part, joined_first_half, head_part_length);
    headliner_part[head_part_length ] = '\0';

    int supporting_len = strlen(supporting_name) / 2;
    char joined_second_half[strlen(supporting_name) - supporting_len + 1];
    strncpy(joined_second_half, 
        supporting_name + supporting_len, 
        strlen(supporting_name) - supporting_len);
    joined_second_half[strlen(supporting_name) - supporting_len] = '\0';

    int first_consonant = -1;
    for (int i = 0; i < strlen(joined_second_half); i++) {
        if (is_consonant(joined_second_half[i])) {
            first_consonant = i;
            break;
        }
    }
    //calculate the actual length of the joined band name(second half)
    char *support_part;
    if (first_consonant != -1) {
        support_part = joined_second_half + first_consonant;
    } else {
        support_part = joined_second_half;
    }

    strcpy(result, headliner_part);
    strcat(result, support_part);
}
//4.1
// Params:
//        merging to performance together
//Return:
//       pointer->song
struct song *merging_the_setlists(
    struct performance *head, 
    struct performance *support,
    double head_avg, double support_avg) {
    if (!head->setlist && !support->setlist) return NULL;

    struct song *merged = NULL;
    struct song **current = &merged;
    struct song *headliner = head->setlist;
    struct song *supporting = support->setlist;

    int ratio;
    if (support_avg == 0) {
        ratio = 1;
    } else {
        ratio = ceil(head_avg / support_avg);
    }

    while (headliner || supporting) {
        if (supporting) {
            *current = create_song(
                supporting->title, 
                supporting->duration, 
                supporting->popularity);
            current = &((*current)->next);
            supporting = supporting->next;
        }

        int count = 0;
        while (headliner && count < ratio) {
            *current = create_song(
                headliner->title, 
                headliner->duration, 
                headliner->popularity);
            current = &((*current)->next);
            headliner = headliner->next;
            count++;
        }
    }

    return merged;
}

//4.1
// Params:
//     Join Performances
//     core part of 4.1
//Return:
//      None
void join_performances(struct festival *festival){
    char stage_name1[MAX_SIZE];
    char band_name1[MAX_SIZE];
    char stage_name2[MAX_SIZE];
    char band_name2[MAX_SIZE];
    scan_name(stage_name1);
    scan_name(band_name1);
    scan_name(stage_name2);
    scan_name(band_name2);
    struct stage *target_stage1 = match_stage_name(festival, stage_name1);
    if (target_stage1 == NULL) {
        printf("ERROR: No stage with name '%s' found.\n", stage_name1);
        return;
    }
    struct stage *target_stage2 = match_stage_name(festival, stage_name2);
    if (target_stage2 == NULL) {
        printf("ERROR: No stage with name '%s' found.\n", stage_name2);
        return;
    }
    struct performance *performance1 =
    find_performance(target_stage1, band_name1);
    if (performance1 == NULL) {
        printf("ERROR: No performance for band '%s' found on stage '%s'.\n",
            band_name1, stage_name1);
        return;
    }
    struct performance *performance2 =
    find_performance(target_stage2, band_name2);
    if (performance2 == NULL) {
        printf("ERROR: No performance for band '%s' found on stage '%s'.\n",
            band_name2, stage_name2);
        return;
    }
    if (performance1->genre != performance2->genre) {
        printf("ERROR: Joint performances can only be of the same genre.\n");
        return;
    }
    struct stage *head_stage;
    //calculate the average popularity
    double average_popularity1 = calculate_average(performance1);
    double average_popularity2 = calculate_average(performance2);
    //define which performance is headliner and which is supporting act
    struct performance *headliner = NULL;
    struct performance *supporting = NULL;
    if (average_popularity1 < average_popularity2) {
        headliner = performance2;
        supporting = performance1;
        head_stage = target_stage2;
    } else {
        headliner = performance1;
        supporting = performance2;
        head_stage = target_stage1;
    }
    char new_band_name[MAX_SIZE];
    joined_band_name(headliner->band_name, 
        supporting->band_name, new_band_name);
    int new_max_duration = headliner->max_duration + supporting->max_duration;
    struct song *new_joined_song = merging_the_setlists(headliner, supporting,
                                    calculate_average(headliner), 
                                    calculate_average(supporting));
    struct performance *prev_head = head_stage->performances;
    struct performance *before_head = NULL;
    while (prev_head && prev_head != headliner) {
        before_head = prev_head;
        prev_head = prev_head->next;
    }
    int saved_start_time = headliner->start_time;
    enum genre saved_genre = headliner->genre;
    //delet two target performance
    delete_performance(target_stage1, band_name1);
    delete_performance(target_stage2, band_name2);
    //insert the new joint performance
    struct performance *joint_perf = create_performance(
    new_band_name,
    saved_start_time,
    new_max_duration,
    saved_genre
    );
    joint_perf->setlist = new_joined_song;
    if (!before_head) {
        joint_perf->next = head_stage->performances;
        head_stage->performances = joint_perf;
    } else {
        joint_perf->next = before_head->next;
        before_head->next = joint_perf;
    }
    //calculate new time 
    if (target_stage1->performances) new_time(target_stage1);
    if (target_stage2->performances) new_time(target_stage2);
    if (head_stage->performances) new_time(head_stage);
    printf("Joint performance '%s' created on stage '%s'.\n", 
        new_band_name, head_stage->name);
}

///////////////////////////////////////////////////////////////////////////////
// Provided Function Definitions
///////////////////////////////////////////////////////////////////////////////

// Scans a name string into the provided buffer, placing '\0' at the end.
//
// Params:
//      name - a char array of length MAX_SIZE, where the name should be stored
// Returns: None
// Usage example:
// ```
//      char name[MAX_SIZE];
//      scan_name(name);
// ```
void scan_name(char name[MAX_SIZE]) {
    scan_token(name, MAX_SIZE);
}

// Scans a string and converts it to a genre enum.
//
// Params: None
// Returns:
//      The corresponding genre enum, if the string was valid,
//      Otherwise, returns INVALID_GENRE.
//
// Usage example:
// ```
//      enum genre genre = scan_genre();
// ```
enum genre scan_genre() {
    char genre[MAX_SIZE];
    scan_token(genre, MAX_SIZE);
    return string_to_genre(genre);
}

// Function to print a stage title banner
// Params: None
// Returns: None
// Usage example:
// ```
//      print_stage_title(stage);
// ```
void print_stage_title(struct stage *stage) {
    printf("==========================================\n[%s]\n", stage->name);
}

// Function to print a performance header, including its start and end time
// (formatted as hours:minutes from the start of the festival),
// band name, and genre
// Params: None
// Returns: None
// Usage example:
// ```
//      print_performance_header(performance);
// ```
void print_performance_header(struct performance *performance) {
    char start_buf[MAX_SIZE];
    char end_buf[MAX_SIZE];
    char genre_buf[MAX_SIZE];
    get_genre_name(performance->genre, genre_buf);
    format_time(performance->start_time, start_buf);
    format_time(performance->end_time, end_buf);

    printf("%-5s - %-5s | %s (%s)\n",
           start_buf,
           end_buf,
           performance->band_name,
           genre_buf
    );
}


// Function to print a single song for a setlist
// Params: None
// Returns: None
// Usage example:
// ```
//      print_song(song, 1);
// ```
void print_song(struct song *song, int song_num) {
    printf("  %d. %s (%.1f mins, %d)\n",
           song_num,
           song->title,
           song->duration,
           song->popularity
    );
}

// Function to print a conflict group header
// Params:
//      conflict_time - the start time of the conflict group
//                      (in minutes from the start of the festival)
// Returns: None
// Usage example:
// ```
//      print_conflict_group_header(conflict_time);
// ```
void print_conflict_group_header(int conflict_time) {
    char buffer[MAX_SIZE];
    format_time(conflict_time, buffer);
    printf(
        "\nConflicts found from %s:\n-------------------------------------"
        "-----\n", buffer
    );
}

// Function to print a conflicting performance with its stage name
// Params:
//      stage_name  - the name of the stage the performance is on
//      performance - a pointer to the performance
// Returns: None
// Usage example:
// ```
//      print_conflict_performance(stage_name, performance);
// ```
void print_conflict_performance(
    char stage_name[MAX_SIZE],
    struct performance *performance
) {
    printf("    - [%s] ", stage_name);
    print_performance_header(performance);
}

// Function to print help information
// '?' command
// Params: None
// Returns: None
// Usage:
// ```
//      print_help();
// ```
void print_help(void) {
    printf(
        "*********************[     Usage Info     ]********************* \n"
        "  a s [name]                                                     \n"
        "    Add a stage with unique name                                 \n"
        "  a p [stage_name] [band_name] [genre] [max_duration]            \n"
        "    Append a performance to a stage                              \n"
        "  i g [stage_name] [band_name] [title] [duration] [popularity] "
        "[position]\n"
        "    Insert a song at [position] in a performance                 \n"
        "  p                                                              \n"
        "    Print the festival with all stages and performances          \n"
        "  *                                                              \n"
        "    Print the most popular performance(s)                        \n"
        "  P [band_name]                                                  \n"
        "    Print schedule and setlists for [band_name], plus summary    \n"
        "  x s [stage_name]                                               \n"
        "    Close a stage and free all its performances                  \n"
        "  x p [stage_name] [band_name]                                   \n"
        "    Remove a performance from a stage                            \n"
        "  x g [stage_name] [band_name] [position]                        \n"
        "    Remove the nth song from a performance                       \n"
        "  u [stage_name] [band_name] [new_duration]                      \n"
        "    Update performance max duration, trimming songs if shorter   \n"
        "  m [src_stage] [dest_stage] [band_name] [position]              \n"
        "    Move a performance to [dest_stage] at [position]             \n"
        "  j [stage_name1] [band_name1] [stage_name2] [band_name2]        \n"
        "    Join two performances                                        \n"
        "  c v [band_name]                                                \n"
        "    View all conflicting performances for [band_name]            \n"
        "  c r [band_name]                                                \n"
        "    Resolve all conflicting performances for [band_name]         \n"
        "  ?                                                              \n"
        "    Show this help information                                   \n"
        "  q                                                              \n"
        "    Quit the program                                             \n"
        "**************************************************************** \n"
    );
}

///////////////////////////////////////////////////////////////////////////////
// Additional Provided Functions
///////////////////////////////////////////////////////////////////////////////

// You don't need to use any of these, or understand how they work!
// We use them to implement some of the provided helper functions.

void print_welcome_banner() {
    printf("Welcome to CS Festival!\n");
    printf("♪┏(・o･)┛┗ ( ･o･) ┓♪\n");
}

void format_time(int minutes, char buffer[MAX_SIZE]) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    sprintf(buffer, "%02d:%02d", hours, mins);
}

enum genre string_to_genre(char genre_str[MAX_SIZE]) {
    if (strcmp(genre_str, "ROCK") == 0) {
        return ROCK;
    } else if (strcmp(genre_str, "POP") == 0) {
        return POP;
    } else if (strcmp(genre_str, "COUNTRY") == 0) {
        return COUNTRY;
    } else if (strcmp(genre_str, "JAZZ") == 0) {
        return JAZZ;
    } else if (strcmp(genre_str, "METAL") == 0) {
        return METAL;
    } else if (strcmp(genre_str, "HIPHOP") == 0) {
        return HIPHOP;
    }
    return INVALID_GENRE;
}

void get_genre_name(enum genre genre, char buffer[MAX_SIZE]) {
    if (genre == ROCK) {
        strcpy(buffer, "Rock");
    } else if (genre == POP) {
        strcpy(buffer, "Pop");
    } else if (genre == COUNTRY) {
        strcpy(buffer, "Country");
    } else if (genre == JAZZ) {
        strcpy(buffer, "Jazz");
    } else if (genre == METAL) {
        strcpy(buffer, "Metal");
    } else if (genre == HIPHOP) {
        strcpy(buffer, "Hip Hop");
    } else {
        strcpy(buffer, "Invalid Genre");
    }
}

int scan_token(char buffer[MAX_SIZE], int buffer_size) {
    if (buffer_size == 0) {
        return 0;
    }

    char c;
    int i = 0;
    int num_scanned = 0;

    scanf(" ");

    while (i < buffer_size - 1 && (num_scanned = scanf("%c", &c)) == 1 &&
           !isspace(c)) {
        buffer[i++] = c;
    }

    if (i > 0) {
        buffer[i] = '\0';
    }

    return num_scanned;
}