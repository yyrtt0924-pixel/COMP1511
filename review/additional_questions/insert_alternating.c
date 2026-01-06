#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

// Provided Functions
struct node *create_node(int data);
void print_list(struct node *head);

struct node *insert_head(struct node *head, struct node *new) {
    new->next = head;
    head = new;
    return head;
}

struct node *insert_tail(struct node *head , struct node *new) {
    if (head == NULL) {
       return new;
    }

    struct node *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = new;
    return head;

}

int main(void) {

    struct node *head = NULL;

    // TODO: Read integers until EOF
    // For each integer, alternate inserting at tail 
    //      and inserting at head
    int data;
    int count = 0;
    while (scanf("%d", &data) != EOF) {
        struct node *new = create_node(data);
        count++;
        
        //positoin是奇数使用头插
        if (count % 2 != 0) {
            head = insert_head(head, new);
        } else if (count % 2 == 0) {
            head = insert_tail(head, new);
        }
    }

    print_list(head);
    return 0;
}

// Mallocs a new node and returns a pointer to it
struct node *create_node(int data) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->next = NULL;
    new_node->data = data;
    return new_node;
}

// Prints a linked list
void print_list(struct node *head) {
    struct node *curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("X\n");
}

