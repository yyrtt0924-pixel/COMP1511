// Write your solution for prac_q3.c here!

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    char          data;
};

struct node *insert_alphabet_after(char ch, struct node *head);
struct node *strings_to_list(int len, char *strings[]);
void print_list(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    char value;
    scanf(" %c", &value);
    // create linked list from command line arguments
    struct node *head = NULL;
    if (argc > 1) {
        // list has elements
        head = strings_to_list(argc - 1, &argv[1]);
    }

    struct node *new_head = insert_alphabet_after(value, head);
    print_list(new_head);

    return 0;
}

// Given the `head` of a linked list, insert new node(s) containing the `ch`
// AFTER the node with the character that comes right before `ch` in the alphabet 
// in the linked list.
//
// You should ONLY change this function
struct node *insert_alphabet_after(char ch, struct node *head) {
    // Implement your solution here!
    
    struct node *current = head;
    if (head == NULL) {
        struct node *new = malloc(sizeof(struct node));
        new->data = ch;
        new->next = NULL;
        return new;
    }


    while (current != NULL) {
        
        if (current->data == ch - 1) {
            struct node *new = malloc(sizeof(struct node));
            new->data = ch;
            new->next = NULL;
            new->next = current->next; 
            current->next = new;
        }

        current = current->next;
    }

    return head;
}

// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = strings[i][0];
        head = n;
        i -= 1;
    }   
    return head;
}

// DO NOT CHANGE THIS FUNCTION
// print linked list
void print_list(struct node *head) {
    printf("[");    
    struct node *n = head;
    while (n != NULL) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%c", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
        n = n->next;
    }
    printf("]\n");
}
