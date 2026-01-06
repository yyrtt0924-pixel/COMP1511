// CS Festival
// main.c
//
// Written by <Yaru Yang> <z5676827>
// on <10.30>
//
// <PROGRAM DESCRIPTION>

#include <stdio.h>

#include "cs_festival.h"

int main(void) {
    // Welcome banner
    print_welcome_banner();

    // Festival plan setup
    printf("Enter the name of your festival: ");
    char festival_name[MAX_SIZE];
    scan_name(festival_name);
    struct festival *my_festival = create_festival(festival_name);

    // Command loop
    command_loop(my_festival);

    // End message
    printf("Goodbye!\n");
    
    return 0;
}
