#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// compare_tens should return -1 if list1 has less tens than list2
// compare_tens should return  1 if list1 has more tens than list2
// compare_tens should return  0 if list1 has the same tens as list2
// This function has some bugs, it is your job to find and fix them
int compare_tens(struct node *head1, struct node *head2) {
    
    struct node *current1 = head1;
    struct node *current2 = head2;
    int count1 = 0;
    int count2 = 0;
    
    while (current1 != NULL) {
        if (current1->data >= 10 && current1->data <= 99) {
            count1++;
        } 
        current1 = current1->next;
    }

    while (current2 != NULL) {
        if (current2->data >= 10 && current2->data <= 99) {  
            count2++;
        } 
        current2 = current2->next;
    }

    if (count1 > count2) {
        return 1;  
    } else if (count1 < count2) {
        return -1;  
    } 

    return 0;
}



// DO NOT MODIFY THE CODE BELOW THIS LINE, THIS CODE ALLOWS YOU TO 
// TAKE IN A LIST OF NUMBERS TO TEST WHETHER YOUR FUNCTION IS WORKING

struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS FUNCTION
int main(int argc, char *argv[]) {
    // create two linked lists from command line arguments
    int dash_arg = argc - 1;
    while (dash_arg > 0 && strcmp(argv[dash_arg], "-") != 0) {
        dash_arg = dash_arg - 1;
    }
    struct node *head1 = strings_to_list(dash_arg - 1, &argv[1]);
    struct node *head2 = strings_to_list(argc - dash_arg - 1, &argv[dash_arg + 1]);

    int result = compare_tens(head1, head2);
    printf("%d\n", result);

    return 0;
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
