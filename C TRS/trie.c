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

static char index_to_char(int index) {
    return (char)('a' + index);
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

static bool has_children(const TrieNode *node) {
    if (!node) {
        return false;
    }
    for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            return true;
        }
    }
    return false;
}

static int count_children(const TrieNode *node, int *single_child_index) {
    if (!node) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            count++;
            if (single_child_index) {
                *single_child_index = i;
            }
        }
    }
    return count;
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

static TrieNode *trie_delete_helper(TrieNode *node, const char *word, size_t depth, bool *deleted, size_t *nodes_freed) {
    if (!node) {
        return NULL;
    }

    if (word[depth] == '\0') {
        if (node->is_end_of_word) {
            node->is_end_of_word = false;
            node->frequency = 0;
            *deleted = true;
        }

        if (!has_children(node)) {
            free(node);
            (*nodes_freed)++;
            return NULL;
        }
        return node;
    }

    int idx = char_to_index(word[depth]);
    if (idx < 0 || node->children[idx] == NULL) {
        return node;
    }

    node->children[idx] = trie_delete_helper(node->children[idx], word, depth + 1, deleted, nodes_freed);

    if (!node->is_end_of_word && !has_children(node)) {
        free(node);
        (*nodes_freed)++;
        return NULL;
    }
    return node;
}

bool trie_delete(Trie *trie, const char *word) {
    if (!trie || !trie->root || !word || *word == '\0') {
        return false;
    }

    bool deleted = false;
    size_t nodes_freed = 0;

    TrieNode *new_root_child = trie_delete_helper(trie->root, word, 0, &deleted, &nodes_freed);
    (void)new_root_child;

    if (deleted) {
        trie->word_count--;
        trie->node_count -= nodes_freed;
    }
    return deleted;
}

static void collect_words_dfs(TrieNode *node, char *buffer, size_t depth, char **results, size_t *count, size_t max_results, size_t max_word_len) {
    if (!node || *count >= max_results || depth >= max_word_len) {
        return;
    }

    if (node->is_end_of_word) {
        buffer[depth] = '\0';
        strncpy(results[*count], buffer, max_word_len - 1);
        results[*count][max_word_len - 1] = '\0';
        (*count)++;
    }

    for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            buffer[depth] = index_to_char(i);
            collect_words_dfs(node->children[i], buffer, depth + 1, results, count, max_results, max_word_len);
            if (*count >= max_results) {
                return;
            }
        }
    }
}

size_t trie_get_words_with_prefix(const Trie *trie, const char *prefix, char **results, size_t max_results, size_t max_word_len) {
    if (!trie || !trie->root || !results || max_results == 0 || max_word_len == 0) {
        return 0;
    }

    TrieNode *curr = trie->root;
    size_t prefix_len = 0;

    if (prefix && *prefix != '\0') {
        for (; prefix[prefix_len] != '\0'; prefix_len++) {
            int idx = char_to_index(prefix[prefix_len]);
            if (idx < 0 || curr->children[idx] == NULL) {
                return 0;
            }
            curr = curr->children[idx];
        }
    }

    char *buffer = (char *)malloc(max_word_len * sizeof(char));
    if (!buffer) {
        return 0;
    }

    if (prefix && prefix_len > 0) {
        for (size_t i = 0; i < prefix_len && i < max_word_len - 1; i++) {
            buffer[i] = (char)tolower((unsigned char)prefix[i]);
        }
    }

    size_t count = 0;
    collect_words_dfs(curr, buffer, prefix_len, results, &count, max_results, max_word_len);

    free(buffer);
    return count;
}

bool trie_longest_common_prefix(const Trie *trie, char *buffer, size_t buffer_size) {
    if (!trie || !trie->root || !buffer || buffer_size == 0 || trie->word_count == 0) {
        if (buffer && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return false;
    }

    TrieNode *curr = trie->root;
    size_t idx_buf = 0;

    while (curr && !curr->is_end_of_word && idx_buf < buffer_size - 1) {
        int child_index = -1;
        if (count_children(curr, &child_index) != 1) {
            break;
        }
        buffer[idx_buf++] = index_to_char(child_index);
        curr = curr->children[child_index];
    }

    buffer[idx_buf] = '\0';
    return idx_buf > 0;
}
