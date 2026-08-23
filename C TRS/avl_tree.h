#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

typedef struct {
    AVLNode *root;
    size_t size;
} AVLTree;

/* Core AVL Tree API */
AVLTree *avl_create(void);
void avl_destroy(AVLTree *tree);

bool avl_insert(AVLTree *tree, int key);
bool avl_remove(AVLTree *tree, int key);
bool avl_search(const AVLTree *tree, int key);
bool avl_contains(const AVLTree *tree, int key);

size_t avl_size(const AVLTree *tree);
int avl_height(const AVLTree *tree);
bool avl_is_balanced(const AVLTree *tree);

bool avl_min(const AVLTree *tree, int *out_min);
bool avl_max(const AVLTree *tree, int *out_max);

void avl_inorder(const AVLTree *tree, void (*visit)(int key));
void avl_preorder(const AVLTree *tree, void (*visit)(int key));
void avl_postorder(const AVLTree *tree, void (*visit)(int key));

#endif /* AVL_TREE_H */
