// Create a list from Command Line Arguments
// list_create.c
//
// This program was written by YARY YANG (z5676827)
// on ??/??/??
//
// A program which creates and prints a linked list 
// from command line arguments!

#include <stdio.h>
#include <stdlib.h>

struct node {
    char *data;
    struct node *next;
};

struct node *arguments_to_list(int argc, char *argv[]);
void free_list(struct node *head);
void print_list(struct node *head);

int main(int argc, char **argv) {
    struct node *head = arguments_to_list(argc, argv);
    print_list(head);
    free_list(head);

    return 0;
}

// Create linked list from argument values
struct node *arguments_to_list(int argc, char *argv[]) {
    // TODO: Complete this function and change the line below
    struct node *head = NULL;
    struct node *tail = NULL;

    for (int i = 1; i < argc; i++) {
        struct node *new_tail = malloc(sizeof(struct node));
        if (new_tail == NULL) {
            return NULL;
        }

        new_tail->data = argv[i];
        new_tail->next = NULL;

        if (head == NULL) {
            head = new_tail;
            tail = new_tail;
        } else {
            tail->next = new_tail;
            tail = new_tail;
        }
    }
    return head;
}

// Free the linked list from memory
void free_list(struct node *head) {
    // TODO: Complete this function
    struct node *current = head;
    struct node *temp = NULL;
    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }
}

// Print the values of the linked list
void print_list(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("X\n");
}