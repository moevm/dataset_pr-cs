#ifndef BST_H
#define BST_H

#include <wchar.h>

typedef struct Node {
    wchar_t* key;
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    Node* root;
} Bst;

Bst* createBst();
void insert(Bst*, wchar_t*);
int find(Bst*, wchar_t*);
void InorderTraversal(Bst*);

#endif