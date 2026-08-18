#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_HT_CAPACITY 16

static unsigned long hash_key(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

static char *custom_strdup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *copy = (char *)malloc(len + 1);
    if (copy) {
        strcpy(copy, s);
    }
    return copy;
}

HashTable *ht_create(size_t initial_capacity) {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    if (!ht) return NULL;

    size_t cap = (initial_capacity > 0) ? initial_capacity : DEFAULT_HT_CAPACITY;
    ht->buckets = (HTNode **)calloc(cap, sizeof(HTNode *));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }

    ht->capacity = cap;
    ht->size = 0;
    return ht;
}

void ht_destroy(HashTable *ht) {
    if (!ht) return;

    for (size_t i = 0; i < ht->capacity; i++) {
        HTNode *curr = ht->buckets[i];
        while (curr) {
            HTNode *tmp = curr;
            curr = curr->next;
            free(tmp->key);
            free(tmp);
        }
    }

    free(ht->buckets);
    free(ht);
}

bool ht_insert(HashTable *ht, const char *key, int value) {
    if (!ht || !key) return false;

    unsigned long index = hash_key(key) % ht->capacity;
    HTNode *curr = ht->buckets[index];

    /* Update if key exists */
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            curr->value = value;
            return true;
        }
        curr = curr->next;
    }

    /* Insert new node */
    HTNode *node = (HTNode *)malloc(sizeof(HTNode));
    if (!node) return false;

    node->key = custom_strdup(key);
    if (!node->key) {
        free(node);
        return false;
    }

    node->value = value;
    node->next = ht->buckets[index];
    ht->buckets[index] = node;
    ht->size++;

    return true;
}

bool ht_get(const HashTable *ht, const char *key, int *out_val) {
    if (!ht || !key) return false;

    unsigned long index = hash_key(key) % ht->capacity;
    HTNode *curr = ht->buckets[index];

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            if (out_val) {
                *out_val = curr->value;
            }
            return true;
        }
        curr = curr->next;
    }

    return false;
}

bool ht_contains(const HashTable *ht, const char *key) {
    return ht_get(ht, key, NULL);
}

bool ht_remove(HashTable *ht, const char *key) {
    if (!ht || !key) return false;

    unsigned long index = hash_key(key) % ht->capacity;
    HTNode *curr = ht->buckets[index];
    HTNode *prev = NULL;

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            if (prev) {
                prev->next = curr->next;
            } else {
                ht->buckets[index] = curr->next;
            }
            free(curr->key);
            free(curr);
            ht->size--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    return false;
}

size_t ht_size(const HashTable *ht) {
    return ht ? ht->size : 0;
}
