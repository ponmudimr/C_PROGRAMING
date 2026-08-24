#ifndef TRIE_H
#define TRIE_H

#include <stddef.h>
#include <stdbool.h>

#define TRIE_ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[TRIE_ALPHABET_SIZE];
    bool is_end_of_word;
    int frequency;
} TrieNode;

typedef struct Trie {
    TrieNode *root;
    size_t word_count;
    size_t node_count;
} Trie;

/* Core Trie API */
Trie *trie_create(void);
void trie_destroy(Trie *trie);
void trie_clear(Trie *trie);

bool trie_insert(Trie *trie, const char *word);
bool trie_search(const Trie *trie, const char *word);
bool trie_starts_with(const Trie *trie, const char *prefix);
bool trie_delete(Trie *trie, const char *word);

size_t trie_word_count(const Trie *trie);
size_t trie_node_count(const Trie *trie);
bool trie_is_empty(const Trie *trie);

/* Advanced Trie operations */
size_t trie_get_words_with_prefix(const Trie *trie, const char *prefix, char **results, size_t max_results, size_t max_word_len);
bool trie_longest_common_prefix(const Trie *trie, char *buffer, size_t buffer_size);

#endif /* TRIE_H */
