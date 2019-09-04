#include <stdio.h>
#include <stdlib.h>

#define bool unsigned char
#define true 1
#define false 0

struct Node {
    int value;
    struct Node *next;
};

// Creates linked list with one element: passed int.
struct Node *createList(int value) {
    struct Node *node = malloc(sizeof(struct Node));
    node->value = value;
    node->next = 0;
    return node;
}

// Returns the size of a passed linked list
int listSize(struct Node *head) {
    if (head->next == 0)
        return 1;
    else
        return 1 + listSize(head->next);
}

// Prints the elements of a passed linked list
void print_list(struct Node *head) {
    // Check if we are tring to print null list
    if (head == 0) {
        printf("null\n");
        return;
    }

    // Print the current element
    printf("%d", head->value);

    // Print the continuation of the linked list
    if (head->next != 0) {
        printf(", ");
        print_list(head->next);
    } else {
        printf("\n");
    }
}

// Inserts node into the passed linked list by index
// Returns pointer to the new head after insert.
// If error occurred, 0 is returned (i.e. there is impossible to insert element
// with such an index).
struct Node *insert_node(struct Node *head, int index, int value) {
    struct Node *prev = 0;
    struct Node *cur = head;

    // Handle the case when the head is updated
    if (index == 0) {
        struct Node *newNode = malloc(sizeof(struct Node));
        newNode->value = value;
        newNode->next = head;
        return newNode;
    }

    for (int i = 0; i < index; i++) {
        // Check if we still have nodes
        if (cur == 0)
            return 0;

        prev = cur;
        cur = cur->next;
    }

    // Create new node;
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = cur;
    // Update previous node to link to this one
    prev->next = newNode;

    return head;
}

// Deleted a node at a given index from a given linked list.
// Returns pointer to the new head after delete.
// If error occurred, 0 is returned (i.e. there is impossible to delete element
// with such an index).
struct Node *delete_node(struct Node *head, int index) {
    struct Node *prev = 0;
    struct Node *cur = head;

    // Handle the case when the head is updated
    if (index == 0) {
        return head->next;
    }

    for (int i = 0; i < index; i++) {
        prev = cur;
        cur = cur->next;

        // Check if we still have nodes
        if (cur == 0)
            return 0;
    }

    // Link previous node to the next
    prev->next = cur->next;

    return head;
}

// Some tests for a linked list implementation
int main() {
    struct Node *head = createList(1);
    print_list(head);
    head = insert_node(head, 0, 2);
    print_list(head);
    head = insert_node(head, 1, 4);
    print_list(head);
    head = insert_node(head, 3, 6);
    print_list(head);

    head = delete_node(head, 0);
    print_list(head);
    head = delete_node(head, 2);
    print_list(head);

    return 0;
}