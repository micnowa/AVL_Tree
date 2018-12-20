//
// Created by Michał Nowaliński on 20-Dec-18.
//

#include<iostream>
#include <iomanip>

using namespace std;


/**
 * AVL Tree is an extension to Binary Search Tree. Nodes are added and kept in the same way
 * as in BST(Binary Search Tree). AVL is found to be significant improvement to BST. It is
 * called self-organising BST, due to the fact it is balanced. By that we understand that
 * we avoid situation when data is structured into a list. Balanced in that case means that
 * every two subtrees whose root is same node have heights different at the most by 1. It
 * is achieved via adding operation of balancing after adding or removing a node.
 * @tparam T type of data in nodes, it needs to have overwritten operators: >, <, =, ==, !=
 */
template<typename T>
class AVLTree {
    /**
     * Structure symbolizing a node in the trees
     */
    struct Node {
        /**
         * data in Node
         */
        T data;
        /**
         * left subtree root
         */
        Node *left;
        /**
         * right subtree root
         */
        Node *right;
        /**
         * height of tree
         */
        int height;
    };

    /**
     * Root node
     */
    Node *root;

    /**
     * Clears tree
     * @param node root of tree
     */
    void makeEmpty(Node *node) {
        if (node == NULL) return;
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }

    /**
     * Inserts data into tree and performs balancing
     * @param data data to be inserted
     * @param node root ot tree
     * @return node with data that was created
     */
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

    /**
     * Single right rotation of subtree
     * @param node node root of subtree
     * @return
     */
    Node *singleRightRotate(Node *&node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        tmp->height = max(height(tmp->left), node->height) + 1;
        return tmp;
    }

    /**
     * Single left rotation of subtree
     * @param node node root of subtree
     * @return
     */
    Node *singleLeftRotate(Node *&node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        tmp->height = max(height(node->right), node->height) + 1;
        return tmp;
    }

    /**
     * Double left rotation of subtree
     * @param node node root of subtree
     * @return
     */
    Node *doubleLeftRotate(Node *&node) {
        node->right = singleRightRotate(node->right);
        return singleLeftRotate(node);
    }

    /**
     * Double right rotation of subtree
     * @param node
     * @return
     */
    Node *doubleRightRotate(Node *&node) {
        node->left = singleLeftRotate(node->left);
        return singleRightRotate(node);
    }

    /**
     * Returns min value of subtree
     * @param node root of subtree
     * @return Min value of subtree
     */
    Node *findMin(Node *node) {
        if (node == NULL) return NULL;
        else if (node->left == NULL) return node;
        else return findMin(node->left);
    }

    /**
     * Returns max value of subtree
     * @param node root of subtree
     * @return Max value of subtree
     */
    Node *findMax(Node *node) {
        if (node == NULL) return NULL;
        else if (node->right == NULL) return node;
        else return findMax(node->right);
    }

    /**
     * Removes node with data from subtree
     * @param data data with which node shall be removed
     * @param node root of subtree
     * @return node on which the function stopped looking for wanted node
     */
    Node *remove(T data, Node *node) {
        Node *temp;

        if (node == NULL) return NULL;
        else if (data < node->data) node->left = remove(data, node->left);
        else if (data > node->data) node->right = remove(data, node->right);

        else if (node->left && node->right) {
            temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->data, node->right);
        }
        else {
            temp = node;
            if (node->left == NULL) node = node->right;
            else if (node->right == NULL) node = node->left;
            delete temp;
        }
        if (node == NULL) return node;

        node->height = max(height(node->left), height(node->right)) + 1;

        if (height(node->left) - height(node->right) == 2) {
            if (height(node->left->left) - height(node->left->right) == 1) return singleLeftRotate(node);
            else return doubleLeftRotate(node);
        }
        else if (height(node->right) - height(node->left) == 2) {
            if (height(node->right->right) - height(node->right->left) == 1) return singleRightRotate(node);
            else return doubleRightRotate(node);
        }
        return node;
    }

    /**
     * Returns height of given subtree or -1 if root is equal to null pointer
     * @param node root of subtree
     * @return height of given subtree or -1 if root is equal to null pointer
     */
    int height(Node *node) {
        return node == NULL ? -1 : node->height;
    }

    /**
     * Return balance of given node, which means difference between height of right and left subtrees
     * @param node
     * @return
     */
    int getBalance(Node *node) {
        return node == NULL ? 0 : height(node->left) - height(node->right);
    }

    /**
     * Prints subtree to standard output
     * @param root root of subtree
     * @param space indent between data printed
     */
    void print(Node *root, int space) {
        int COUNT = 10;
        if (root == NULL) return;
        space += COUNT;
        print(root->right, space);

        printf("\n");
        for (int i = COUNT; i < space; i++) printf(" ");
        cout << root->data << endl;
        print(root->left, space); // Process left child
    }

public:
    /**
     * Default constructor
     */
    AVLTree() {
        root = NULL;
    }

    /**
     * Inserts node with given data.
     * @param x data with which node shall be inserted
     */
    void insert(T x) {
        root = insert(x, root);
    }

    /**
     * Removes node with given data, if tree does not have such node nothing happens
     * @param x data with which node shall be removed
     */
    void remove(T x) {
        root = remove(x, root);
    }

    /**
     * Prints tree to standard output
     */
    void print() {
        if (root == nullptr) cout << "Empty tree" << endl;
        print(root, 1);
    }
};