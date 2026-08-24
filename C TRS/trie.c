#include "trie.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int char_to_index(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    return -1;
}

static TrieNode *trie_create_node(void) {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (!node) {
        return NULL;
    }
    node->is_end_of_word = false;
    node->frequency = 0;
    for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

static void trie_free_node(TrieNode *node) {
    if (!node) {
        return;
    }
    for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            trie_free_node(node->children[i]);
        }
    }
    free(node);
}

Trie *trie_create(void) {
    Trie *trie = (Trie *)malloc(sizeof(Trie));
    if (!trie) {
        return NULL;
    }
    trie->root = trie_create_node();
    if (!trie->root) {
        free(trie);
        return NULL;
    }
    trie->word_count = 0;
    trie->node_count = 1;
    return trie;
}

void trie_clear(Trie *trie) {
    if (!trie || !trie->root) {
        return;
    }
    for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
        if (trie->root->children[i] != NULL) {
            trie_free_node(trie->root->children[i]);
            trie->root->children[i] = NULL;
        }
    }
    trie->root->is_end_of_word = false;
    trie->root->frequency = 0;
    trie->word_count = 0;
    trie->node_count = 1;
}

void trie_destroy(Trie *trie) {
    if (!trie) {
        return;
    }
    trie_free_node(trie->root);
    free(trie);
}

size_t trie_word_count(const Trie *trie) {
    return trie ? trie->word_count : 0;
}

size_t trie_node_count(const Trie *trie) {
    return trie ? trie->node_count : 0;
}

bool trie_is_empty(const Trie *trie) {
    return !trie || trie->word_count == 0;
}

bool trie_insert(Trie *trie, const char *word) {
    if (!trie || !trie->root || !word || *word == '\0') {
        return false;
    }
    TrieNode *curr = trie->root;
    for (size_t i = 0; word[i] != '\0'; i++) {
        int idx = char_to_index(word[i]);
        if (idx < 0) {
            return false;
        }
        if (curr->children[idx] == NULL) {
            curr->children[idx] = trie_create_node();
            if (curr->children[idx] == NULL) {
                return false;
            }
            trie->node_count++;
        }
        curr = curr->children[idx];
    }

    if (!curr->is_end_of_word) {
        curr->is_end_of_word = true;
        trie->word_count++;
    }
    curr->frequency++;
    return true;
}

bool trie_search(const Trie *trie, const char *word) {
    if (!trie || !trie->root || !word || *word == '\0') {
        return false;
    }
    TrieNode *curr = trie->root;
    for (size_t i = 0; word[i] != '\0'; i++) {
        int idx = char_to_index(word[i]);
        if (idx < 0 || curr->children[idx] == NULL) {
            return false;
        }
        curr = curr->children[idx];
    }
    return curr != NULL && curr->is_end_of_word;
}

bool trie_starts_with(const Trie *trie, const char *prefix) {
    if (!trie || !trie->root || !prefix) {
        return false;
    }
    if (*prefix == '\0') {
        return trie->word_count > 0;
    }
    TrieNode *curr = trie->root;
    for (size_t i = 0; prefix[i] != '\0'; i++) {
        int idx = char_to_index(prefix[i]);
        if (idx < 0 || curr->children[idx] == NULL) {
            return false;
        }
        curr = curr->children[idx];
    }
    return curr != NULL;
}
