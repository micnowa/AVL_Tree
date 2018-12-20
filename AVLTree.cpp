//
// Created by Michał Nowaliński on 14-Dec-18.
//

#include<iostream>
#include <iomanip>
using namespace std;

template<typename T>
class BST {
    struct Node {
        T data;
        Node *left;
        Node *right;
        int height;
    };

    Node *root;

    void makeEmpty(Node *node) {
        if (node == NULL) return;
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }

    Node *insert(T data, Node *node) {
        if (node == NULL) {
            node = new Node;
            node->data = data;
            node->height = 0;
            node->left = node->right = NULL;
        } else if (data < node->data) {
            node->left = insert(data, node->left);
            if (height(node->left) - height(node->right) == 2) {
                if (data < node->left->data)
                    node = singleRightRotate(node);
                else
                    node = doubleRightRotate(node);
            }
        } else if (data > node->data) {
            node->right = insert(data, node->right);
            if (height(node->right) - height(node->left) == 2) {
                if (data > node->right->data)
                    node = singleLeftRotate(node);
                else
                    node = doubleLeftRotate(node);
            }
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        return node;
    }

    Node *singleRightRotate(Node *&node) {
        Node *u = node->left;
        node->left = u->right;
        u->right = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        u->height = max(height(u->left), node->height) + 1;
        return u;
    }

    Node *singleLeftRotate(Node *&node) {
        Node *u = node->right;
        node->right = u->left;
        u->left = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        u->height = max(height(node->right), node->height) + 1;
        return u;
    }

    Node *doubleLeftRotate(Node *&node) {
        node->right = singleRightRotate(node->right);
        return singleLeftRotate(node);
    }

    Node *doubleRightRotate(Node *&node) {
        node->left = singleLeftRotate(node->left);
        return singleRightRotate(node);
    }

    Node *findMin(Node *node) {
        if (node == NULL)
            return NULL;
        else if (node->left == NULL)
            return node;
        else
            return findMin(node->left);
    }

    Node *findMax(Node *node) {
        if (node == NULL)
            return NULL;
        else if (node->right == NULL)
            return node;
        else
            return findMax(node->right);
    }

    Node *remove(T data, Node *node) {
        Node *temp;

        // Element not found
        if (node == NULL) return NULL;
        else if (data < node->data) node->left = remove(data, node->left);
        else if (data > node->data) node->right = remove(data, node->right);

            // Element found
            // With 2 children
        else if (node->left && node->right) {
            temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->data, node->right);
        }
            // With one or zero child
        else {
            temp = node;
            if (node->left == NULL) node = node->right;
            else if (node->right == NULL) node = node->left;
            delete temp;
        }
        if (node == NULL) return node;

        node->height = max(height(node->left), height(node->right)) + 1;

        // If Node is unbalanced
        // If left Node is deleted, right case
        if (height(node->left) - height(node->right) == 2) {
            // right right case
            if (height(node->left->left) - height(node->left->right) == 1)
                return singleLeftRotate(node);
                // right left case
            else
                return doubleLeftRotate(node);
        }
            // If right Node is deleted, left case
        else if (height(node->right) - height(node->left) == 2) {
            // left left case
            if (height(node->right->right) - height(node->right->left) == 1)
                return singleRightRotate(node);
                // left right case
            else
                return doubleRightRotate(node);
        }
        return node;
    }

    int height(Node *node) {
        return node == NULL ? -1 : node->height;
    }

    int getBalance(Node *node) {
        return node == NULL ? 0 : height(node->left) - height(node->right);
    }

    void print(Node *root, int space) {
        // Base case
        int COUNT = 10;
        if (root == NULL) return;
        space += COUNT; // Increase distance between levels
        print(root->right, space); // Process right child first

        // Print current node after space
        // count
        printf("\n");
        for (int i = COUNT; i < space; i++) printf(" ");
        cout<<root->data<<endl;
        print(root->left, space); // Process left child
    }

public:
    BST() {
        root = NULL;
    }

    void insert(T x) {
        root = insert(x, root);
    }

    void remove(T x) {
        root = remove(x, root);
    }

    void print() {
        if (root == nullptr) cout << "Empty tree" << endl;
        print(root, 1);
    }
};