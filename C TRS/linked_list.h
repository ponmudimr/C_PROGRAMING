#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} LinkedList;

// Creates a new empty linked list.
LinkedList* list_create(void);

// Prepends an element to the front of the list.
bool list_push_front(LinkedList *list, int data);

// Appends an element to the end of the list.
bool list_push_back(LinkedList *list, int data);

// Removes the element from the front of the list and stores its data in *out_val.
bool list_pop_front(LinkedList *list, int *out_val);

// Checks if target value exists in the list.
bool list_find(const LinkedList *list, int target);

// Reverses the linked list in-place.
void list_reverse(LinkedList *list);

// Returns the number of nodes in the list.
size_t list_size(const LinkedList *list);

// Frees all memory allocated for the list and its nodes.
void list_free(LinkedList *list);

#endif // LINKED_LIST_H
