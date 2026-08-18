#include "bst.h"
#include <stdlib.h>

static BSTNode *create_node(int key) {
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    if (!node) return NULL;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void free_nodes(BSTNode *node) {
    if (!node) return;
    free_nodes(node->left);
    free_nodes(node->right);
    free(node);
}

BST *bst_create(void) {
    BST *tree = (BST *)malloc(sizeof(BST));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void bst_destroy(BST *tree) {
    if (!tree) return;
    free_nodes(tree->root);
    free(tree);
}

static BSTNode *insert_node(BSTNode *node, int key, bool *inserted) {
    if (!node) {
        *inserted = true;
        return create_node(key);
    }
    if (key < node->key) {
        node->left = insert_node(node->left, key, inserted);
    } else if (key > node->key) {
        node->right = insert_node(node->right, key, inserted);
    } else {
        *inserted = false; /* Duplicate key */
    }
    return node;
}

bool bst_insert(BST *tree, int key) {
    if (!tree) return false;
    bool inserted = false;
    tree->root = insert_node(tree->root, key, &inserted);
    if (inserted) {
        tree->size++;
    }
    return inserted;
}

bool bst_search(const BST *tree, int key) {
    if (!tree) return false;
    BSTNode *curr = tree->root;
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

static BSTNode *find_min(BSTNode *node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

static BSTNode *remove_node(BSTNode *node, int key, bool *removed) {
    if (!node) return NULL;

    if (key < node->key) {
        node->left = remove_node(node->left, key, removed);
    } else if (key > node->key) {
        node->right = remove_node(node->right, key, removed);
    } else {
        *removed = true;
        if (!node->left) {
            BSTNode *temp = node->right;
            free(node);
            return temp;
        } else if (!node->right) {
            BSTNode *temp = node->left;
            free(node);
            return temp;
        }

        /* Node with two children: replace with inorder successor */
        BSTNode *successor = find_min(node->right);
        node->key = successor->key;
        bool dummy = false;
        node->right = remove_node(node->right, successor->key, &dummy);
    }
    return node;
}

bool bst_remove(BST *tree, int key) {
    if (!tree || !tree->root) return false;
    bool removed = false;
    tree->root = remove_node(tree->root, key, &removed);
    if (removed) {
        tree->size--;
    }
    return removed;
}

size_t bst_size(const BST *tree) {
    if (!tree) return 0;
    return tree->size;
}

static size_t node_height(const BSTNode *node) {
    if (!node) return 0;
    size_t left_h = node_height(node->left);
    size_t right_h = node_height(node->right);
    return 1 + (left_h > right_h ? left_h : right_h);
}

size_t bst_height(const BST *tree) {
    if (!tree) return 0;
    return node_height(tree->root);
}

static void inorder_traversal(const BSTNode *node, void (*visit)(int key)) {
    if (!node) return;
    inorder_traversal(node->left, visit);
    visit(node->key);
    inorder_traversal(node->right, visit);
}

void bst_inorder(const BST *tree, void (*visit)(int key)) {
    if (!tree || !visit) return;
    inorder_traversal(tree->root, visit);
}
