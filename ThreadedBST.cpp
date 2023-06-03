// Jasjeen Khosa and Ruby Kaur
// CSS 342

#include "ThreadedBST.h"
#include <iostream>
using namespace std;

// Constructor
ThreadedBST::ThreadedBST() : root(nullptr) {}

// Copy constructor
ThreadedBST::ThreadedBST(const ThreadedBST& other) {
    // Call the recursive helper function to copy the tree
    root = copyTree(other.root);
}

// Recursive helper function to copy the tree
Node* ThreadedBST::copyTree(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    Node* newNode = new Node(node->key);
    newNode->isThread = node->isThread;
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
}

// Destructor
ThreadedBST::~ThreadedBST() {
    if (root != nullptr) {
        // Start from the leftmost node and deallocate each node
        Node* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }

        while (current != nullptr) {
            Node* temp = current;
            current = findSuccessor(current);
            delete temp;
        }
    }
}

// Insert a key into the threaded binary search tree
void ThreadedBST::insert(int key) {
    if (root == nullptr) {
        root = new Node(key);
        root->isThread = true;
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
                    newNode->isThread = true;
                    break;
                } else {
                    current = current->left;
                }
            } else if (key > current->key) {
                if (!current->isThread) {
                    current = current->right;
                } else {
                    newNode->right = current->right;
                    newNode->isThread = true;
                    current->right = newNode;
                    current->isThread = false;
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
            if (target->isThread)
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
            parent->isThread = true;
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

        if (!current->isThread) {
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

        if (!current->isThread) {
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
    if (node->isThread)
        return node->right;

    Node* current = node->right;
    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Find the parent of the inorder successor of a node in the threaded binary search tree
Node* ThreadedBST::findSuccessorParent(Node* node) {
    Node* current = node->right;
    while (current->left != node) {
        current = current->left;
    }
    return current;
}
