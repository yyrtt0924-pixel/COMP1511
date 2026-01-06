#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// DO NOT MODIFY THIS STRUCT
struct node {
    struct node *next;
    int          data;
};

////////////////////////////////////////////////////////////////////////////////
// DO NOT CHANGE THESE FUNCTION PROTOTYPES
////////////////////////////////////////////////////////////////////////////////
struct node *delete_nth_even(struct node *head, int n);
struct node *strings_to_list(int len, char *strings[]);
void print_list(struct node *head);
void free_list(struct node *head);


//##############################################################################
// TODO: IMPLEMENT THIS FUNCTION
//##############################################################################

// This function should delete the even node at position n 
// from the start of the list.
struct node *delete_nth_even(struct node *head, int n) {
    // PUT YOUR CODE HERE (change the next line!)
    if (head == NULL) {
        return head;
    }

    struct node *prev = NULL;
    struct node *curr = head;

    struct node *first_even = NULL;
    struct node *first_even_prev = NULL;

    int count_even = 0;

    while (curr != NULL) {
        if (curr->data % 2 == 0) {
            count_even++;
            if (count_even == 1) {
                first_even = curr;
                first_even_prev = prev;
            }
            if (count_even == n) {
                if (prev == NULL) {
                    head = curr->next;
                } else {
                    prev->next = curr->next;
                }
                
                free(curr);
                return head;
            }
        } 
        prev = curr;
        curr = curr->next;
    }

    if (first_even != NULL) {
        if (first_even_prev == NULL) {
            head = first_even->next;
        } else {
            first_even_prev->next = first_even->next;
        }
        free(first_even);
    }
    return head;
}


///////////////////////////////////////////////////////////////////////////////
// DO NOT EDIT MAIN
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    int n = atoi(argv[1]);
    struct node *head = strings_to_list(argc - 2, &argv[2]);

    struct node *new_head = delete_nth_even(head, n);
    print_list(new_head);
    free_list(new_head);

    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// DO NOT CHANGE BELOW HERE INCLUDING THIS FUNCTION OR THE FUNCTIONS BELOW
////////////////////////////////////////////////////////////////////////////////

// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}

// print linked list
void print_list(struct node *head) {
    printf("[");

    for (struct node *n = head; n != NULL; n = n->next) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

// free linked list
void free_list(struct node *head) {
    struct node *curr = head;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr->next;
        free(temp);
    }
}