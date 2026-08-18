#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct HTNode {
    char *key;
    int value;
    struct HTNode *next;
} HTNode;

typedef struct {
    HTNode **buckets;
    size_t capacity;
    size_t size;
} HashTable;

/* Hash Table Operations */
HashTable *ht_create(size_t initial_capacity);
void ht_destroy(HashTable *ht);
bool ht_insert(HashTable *ht, const char *key, int value);
bool ht_get(const HashTable *ht, const char *key, int *out_val);
bool ht_contains(const HashTable *ht, const char *key);
bool ht_remove(HashTable *ht, const char *key);
size_t ht_size(const HashTable *ht);

#endif /* HASH_TABLE_H */
