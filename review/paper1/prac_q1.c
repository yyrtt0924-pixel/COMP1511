#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int sum_divisible(struct node *head1, struct node *head2);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // create two linked lists from command line arguments
    int dash_arg = argc - 1;
    while (dash_arg > 0 && strcmp(argv[dash_arg], "-") != 0) {
        dash_arg = dash_arg - 1;
    }
    struct node *head1 = strings_to_list(dash_arg - 1, &argv[1]);
    struct node *head2 = strings_to_list(argc - dash_arg - 1, &argv[dash_arg + 1]);

    int result = sum_divisible(head1, head2);
    printf("%d\n", result);

    return 0;
}


// sum the elements in list1 that are divisible by the 
// the corresponding element in list2
// if one list is longer than the other, the extra list elements are ignored 
int sum_divisible(struct node *head1, struct node *head2) {

    // PUT YOUR CODE HERE (change the next line!)
    struct node *current_list1 = head1;
    struct node *current_list2 = head2;

    int total_sum = 0;

    while (current_list1 != NULL && current_list2 != NULL) {
        
        if(current_list1->data % current_list2->data == 0) {
            total_sum += current_list1->data;
        }

        current_list1 = current_list1->next;
        current_list2 = current_list2->next;
    }


    return total_sum;
}


// DO NOT CHANGE THIS FUNCTION
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
