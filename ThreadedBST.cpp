// Jasjeen Khosa and Ruby Kaur
// CSS 342

#include "ThreadedBST.h"
#include <iostream>
using namespace std;

// ThreadedBST class constructor
ThreadedBST::ThreadedBST() : root(nullptr) {}

// ThreadedBST class destructor
ThreadedBST::~ThreadedBST() {
    // TODO: Implement tree deallocation (delete all nodes)
}

// Insert a key into the threaded binary search tree
void ThreadedBST::insert(int key) {
    if (root == nullptr) {
        root = new Node(key);
        root->rightThread = true;
    } else {
        Node* newNode = new Node(key);
        Node* current = root;
        Node* parent = nullptr;

        while (true) {
            parent = current;

            if (key < current->key) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    newNode->right = current;
                    newNode->rightThread = true;
                    break;
                } else {
                    current = current->left;
                }
            } else if (key > current->key) {
                if (!current->rightThread) {
                    current = current->right;
                } else {
                    newNode->right = current->right;
                    newNode->rightThread = true;
                    current->right = newNode;
                    current->rightThread = false;
                    break;
                }
            } else {
                delete newNode;  // Duplicate key, ignore and delete the new node
                return;
            }
        }
    }
}

// Remove a key from the threaded binary search tree
void ThreadedBST::remove(int key) {
    Node* target = root;
    Node* parent = nullptr;
    bool found = false;

    while (target != nullptr) {
        if (key < target->key) {
            parent = target;
            target = target->left;
        } else if (key > target->key) {
            if (target->rightThread)
                return;

            parent = target;
            target = target->right;
        } else {
            found = true;
            break;
        }
    }

    if (!found)
        return;

    if (target->left == nullptr && target->right == nullptr) {
        if (target == root) {
            delete root;
            root = nullptr;
        } else if (target == parent->left) {
            parent->left = nullptr;
            parent->rightThread = true;
            delete target;
        } else {
            parent->right = target->right;
            delete target;
        }
    } else if (target->left == nullptr) {
        if (target == root) {
            root = target->right;
        } else if (target == parent->left) {
            parent->left = target->right;
        } else {
            parent->right = target->right;
        }
        Node* successor = findSuccessor(target);
        delete target;
        successor->left = nullptr;
    } else if (target->right == nullptr) {
        if (target == root) {
            root = target->left;
        } else if (target == parent->left) {
            parent->left = target->left;
        } else {
            parent->right = target->left;
        }
        delete target;
    } else {
        Node* successorParent = target;
        Node* successor = target->right;

        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        target->key = successor->key;

        if (successorParent == target) {
            successorParent->right = successor->right;
        } else {
            successorParent->left = successor->right;
        }

        delete successor;
    }
}

// Display the threaded binary search tree in inorder traversal
void ThreadedBST::display() {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }

    Node* current = root;
    while (current->left != nullptr)
        current = current->left;

    while (current != nullptr) {
        cout << current->key << " ";

        if (!current->rightThread) {
            current = current->right;
            while (current->left != nullptr)
                current = current->left;
        } else {
            current = current->right;
        }
    }

    cout << endl;
}

// Perform inorder traversal of the threaded binary search tree
void ThreadedBST::inorder() {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }

    Node* current = root;
    while (current->left != nullptr)
        current = current->left;

    while (current != nullptr) {
        cout << current->key << " ";

        if (!current->rightThread) {
            current = current->right;
            while (current->left != nullptr)
                current = current->left;
        } else {
            current = current->right;
        }
    }

    cout << endl;
}

// Find the inorder successor of a node in the threaded binary search tree
Node* ThreadedBST::findSuccessor(Node* node) {
    if (node->rightThread)
        return node->right;

    Node* current = node->right;
    while (current->left != nullptr)
        current = current->left;

    return current;
}
