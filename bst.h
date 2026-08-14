#ifndef BST_H
#define BST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct BSTNode {
    int key;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef struct {
    BSTNode *root;
    size_t size;
} BST;

/* BST Operations */
BST *bst_create(void);
void bst_destroy(BST *tree);
bool bst_insert(BST *tree, int key);
bool bst_search(const BST *tree, int key);
bool bst_remove(BST *tree, int key);
size_t bst_size(const BST *tree);
size_t bst_height(const BST *tree);
void bst_inorder(const BST *tree, void (*visit)(int key));

#endif /* BST_H */
