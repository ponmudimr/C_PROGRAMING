#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList* list_create(void) {
    LinkedList *list = (LinkedList*) malloc(sizeof(LinkedList));
    if (!list) return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

bool list_push_front(LinkedList *list, int data) {
    if (!list) return false;

    Node *new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) return false;

    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    return true;
}

bool list_push_back(LinkedList *list, int data) {
    if (!list) return false;

    Node *new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) return false;

    new_node->data = data;
    new_node->next = NULL;

    if (!list->head) {
        list->head = new_node;
    } else {
        Node *curr = list->head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
    list->size++;
    return true;
}

bool list_pop_front(LinkedList *list, int *out_val) {
    if (!list || !list->head) return false;

    Node *temp = list->head;
    if (out_val) {
        *out_val = temp->data;
    }
    list->head = temp->next;
    free(temp);
    list->size--;
    return true;
}

bool list_find(const LinkedList *list, int target) {
    if (!list) return false;

    Node *curr = list->head;
    while (curr) {
        if (curr->data == target) return true;
        curr = curr->next;
    }
    return false;
}

void list_reverse(LinkedList *list) {
    if (!list || !list->head) return;

    Node *prev = NULL;
    Node *curr = list->head;
    Node *next = NULL;

    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head = prev;
}

size_t list_size(const LinkedList *list) {
    return list ? list->size : 0;
}

void list_free(LinkedList *list) {
    if (!list) return;

    Node *curr = list->head;
    while (curr) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}
