#include <stdlib.h>
#include <wchar.h>

#include "bst.h"

Node* createNode() {
    Node* node = (Node*) malloc(sizeof(Node));
    node->key = NULL;
    node->data = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Bst* createBst() {
    Bst* bst = (Bst*) malloc(sizeof(Bst));
    bst->root = NULL;
    return bst;
}

void insertByNode(Node* node, wchar_t* key) {
    if (wcscmp(node->key, key) < 0) {
        if (node->right == NULL) {
            Node* newNode = createNode();
            newNode->key = key;
            newNode->data = 1;
            node->right = newNode;
        } else {
            insertByNode(node->right, key);
        }
    } else if (wcscmp(node->key, key) > 0) {
        if (node->left == NULL) {
            Node* newNode = createNode();
            newNode->key = key;
            newNode->data = 1;
            node->left = newNode;
        } else {
            insertByNode(node->left, key);
        }
    } else {
        node->data++;
    }
}

void insert(Bst* bst, wchar_t* key) {
    if (bst->root == NULL) {
        bst->root = createNode();
        bst->root->key = key;
        bst->root->data = 1;
        return;
    }
    insertByNode(bst->root, key);
}

int findByNode(Node* node, wchar_t* key) {
	if (node == NULL) {
		return 0;
	}
	if (wcscmp(node->key, key) < 0) {
		return findByNode(node->right, key);
	} else if (wcscmp(node->key, key) > 0) {
		return findByNode(node->left, key);
	}
	return node->data;
}

int find(Bst* bst, wchar_t* key) {
	return findByNode(bst->root, key);
}

void inorderTraversalByNode(Node* node) {
	if (node == NULL) {
		return;
	}
	inorderTraversalByNode(node->left);
	wprintf(L"%ls %d\n", node->key, node->data);
	inorderTraversalByNode(node->right);
}

void InorderTraversal(Bst* bst) {
	inorderTraversalByNode(bst->root);
}
