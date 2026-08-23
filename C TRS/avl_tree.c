#include "avl_tree.h"
#include <stdlib.h>

static int max_int(int a, int b) {
    return (a > b) ? a : b;
}

static int get_height(const AVLNode *node) {
    if (!node) return 0;
    return node->height;
}

static int get_balance(const AVLNode *node) {
    if (!node) return 0;
    return get_height(node->left) - get_height(node->right);
}

static AVLNode *create_avl_node(int key) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    if (!node) return NULL;
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void free_avl_nodes(AVLNode *node) {
    if (!node) return;
    free_avl_nodes(node->left);
    free_avl_nodes(node->right);
    free(node);
}

static AVLNode *rotate_right(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max_int(get_height(y->left), get_height(y->right));
    x->height = 1 + max_int(get_height(x->left), get_height(x->right));

    return x;
}

static AVLNode *rotate_left(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max_int(get_height(x->left), get_height(x->right));
    y->height = 1 + max_int(get_height(y->left), get_height(y->right));

    return y;
}

static AVLNode *insert_node(AVLNode *node, int key, bool *inserted) {
    if (!node) {
        *inserted = true;
        return create_avl_node(key);
    }

    if (key < node->key) {
        node->left = insert_node(node->left, key, inserted);
    } else if (key > node->key) {
        node->right = insert_node(node->right, key, inserted);
    } else {
        *inserted = false; /* Duplicate key */
        return node;
    }

    node->height = 1 + max_int(get_height(node->left), get_height(node->right));

    int balance = get_balance(node);

    /* Left Left Case */
    if (balance > 1 && key < node->left->key) {
        return rotate_right(node);
    }

    /* Right Right Case */
    if (balance < -1 && key > node->right->key) {
        return rotate_left(node);
    }

    /* Left Right Case */
    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    /* Right Left Case */
    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

AVLTree *avl_create(void) {
    AVLTree *tree = (AVLTree *)malloc(sizeof(AVLTree));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void avl_destroy(AVLTree *tree) {
    if (!tree) return;
    free_avl_nodes(tree->root);
    free(tree);
}

bool avl_insert(AVLTree *tree, int key) {
    if (!tree) return false;
    bool inserted = false;
    tree->root = insert_node(tree->root, key, &inserted);
    if (inserted) {
        tree->size++;
    }
    return inserted;
}

bool avl_search(const AVLTree *tree, int key) {
    if (!tree) return false;
    const AVLNode *curr = tree->root;
    while (curr) {
        if (key == curr->key) {
            return true;
        } else if (key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return false;
}

bool avl_contains(const AVLTree *tree, int key) {
    return avl_search(tree, key);
}

size_t avl_size(const AVLTree *tree) {
    if (!tree) return 0;
    return tree->size;
}

int avl_height(const AVLTree *tree) {
    if (!tree) return 0;
    return get_height(tree->root);
}

bool avl_min(const AVLTree *tree, int *out_min) {
    if (!tree || !tree->root || !out_min) return false;
    const AVLNode *curr = tree->root;
    while (curr->left) {
        curr = curr->left;
    }
    *out_min = curr->key;
    return true;
}

bool avl_max(const AVLTree *tree, int *out_max) {
    if (!tree || !tree->root || !out_max) return false;
    const AVLNode *curr = tree->root;
    while (curr->right) {
        curr = curr->right;
    }
    *out_max = curr->key;
    return true;
}

/* Stubs for deletion, traversals, and balance checking */
bool avl_remove(AVLTree *tree, int key) {
    (void)tree; (void)key;
    return false;
}

bool avl_is_balanced(const AVLTree *tree) {
    (void)tree;
    return true;
}

void avl_inorder(const AVLTree *tree, void (*visit)(int key)) {
    (void)tree; (void)visit;
}

void avl_preorder(const AVLTree *tree, void (*visit)(int key)) {
    (void)tree; (void)visit;
}

void avl_postorder(const AVLTree *tree, void (*visit)(int key)) {
    (void)tree; (void)visit;
}
