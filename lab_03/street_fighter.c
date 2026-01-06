// Name of Exercise
// file_name.c
//
// This program was written by YOUR-NAME-HERE (zXXXXXXX)
// on INSERT-DATE-HERE
//
// One line summary of what this exercise does.

#include <stdio.h>

#define MAX_HEALTH 50.0
#define MAX_ATTACK 10

// Define a struct called fighter
struct fighter {
    double health;
    double attack;
    char attack_command;
 };
int main(void) {

    printf("Welcome to Street Fighter!\n");
    ////////////////////////////////////////////////////////////////////////////
    ///////////////////////// Fighter 1 Creation ///////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    struct fighter fighter1;
    fighter1.health = MAX_HEALTH;
    // TODO: prompt and scan for fighter1's attack power and command.
    //       Initialise fighter1's health to MAX_HEALTH

    ////////////////////////////////////////////////////////////////////////////
    ///////////////////////// Fighter 2 Creation ///////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    // TODO: declare fighter2's struct and repeat the above for fighter2
    struct fighter fighter2;
    fighter2.health =  MAX_HEALTH;

    printf("\n");
    printf("Enter Fighter 1's attack power (1-10): ");
    scanf("%lf", &fighter1.attack);
    printf("Enter an ascii character for Fighter 1's attack command: ");
    scanf(" %c", &fighter1.attack_command);
    printf("\n");
    printf("Enter Fighter 2's attack power (1-10): ");
    scanf("%lf", &fighter2.attack);
    printf("Enter an ascii character for Fighter 2's attack command: ");
    scanf(" %c", &fighter2.attack_command);
    printf("\nFIGHT!\n\n");
    ////////////////////////////////////////////////////////////////////////////
    //////////////////////////////// Fight Loop ////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    // TODO: create a loop until one of the fighters loses all their health
    //       prompt the fighter to attack and print remaining health after
    //       each round

    while(fighter1.health >0 && fighter2.health >0) {
        char user_command1 = 0;
        char user_command2 = 0;


        //Fighter 1 attack
        printf("Fighter 1, press %c to attack: ", fighter1.attack_command);
        scanf(" %c",&user_command1);

        if(user_command1 == fighter1.attack_command) {
            printf("Fighter 1 attacks!");
            printf("\n");
            if (fighter1.health < (MAX_HEALTH/2)) {
                fighter2.health -= fighter1.attack*1.5;
            } else {
                fighter2.health -= fighter1.attack;
            }
        }

        //Fighter 2 attack
        printf("Fighter 2, press %c to attack: ", fighter2.attack_command);
        scanf(" %c",&user_command2);

        if(user_command2 == fighter2.attack_command){
            printf("Fighter 2 attacks!");
            printf("\n\n");
            if (fighter2.health < (MAX_HEALTH/2)) {
                fighter1.health -= fighter2.attack*1.5;
            } else {
                fighter1.health -= fighter2.attack;
            }
        }
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////// Fight Results ///////////////////////////////
        ////////////////////////////////////////////////////////////////////////////

        //  TODO: Print the results of the fight
        //health
        printf("Fighter 1's health: %.1lf\n", fighter1.health);
        printf("Fighter 2's health: %.1lf\n", fighter2.health);
    }

    //results
    if (fighter1.health > 0) {
        printf("\nFighter 1 wins!\n");
    }else if (fighter2.health > 0) {
        printf("\nFighter 2 wins!\n");
    }else{
        printf("\nIt's a draw!\n");
    }
    printf("GAME OVER\n");
    return 0;
}