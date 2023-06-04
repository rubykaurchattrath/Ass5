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

// Finds a node with the specified key in the threaded binary search tree.
// Finds a node with the specified key in the threaded binary search tree.
Node* ThreadedBST::find(Node* root, int key) {
    if (root == nullptr)
        return nullptr;

    Node* current = root;
    while (true) {
        if (current->key == key)
            return current;
        else if (key < current->key) {
            if (current->isThread || current->left == nullptr)
                return nullptr;
            current = current->left;
        } else {
            if (current->isThread || current->right == nullptr)
                return nullptr;
            current = current->right;
        }
    }
}

// Helper function to find the leftmost node in the subtree rooted at 'node'
// Returns the leftmost (smallest) node in the threaded bst.
Node* ThreadedBST::leftmost(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}


// Removes a node with the specified key from the threaded bst.
void ThreadedBST::remove(int key) {
    // Call the recursive remove function and update the root
    root = remove(root, key);
}

// Recursively removes a node with the specified key from the threaded bst.
Node* ThreadedBST::remove(Node*& root, int key) {
    if (root == nullptr) {
        return root;
    }

    // Find the node to remove
    Node* node = find(root, key);
    if (node == nullptr) {
        return root;
    }

    if (node->left == nullptr && node->right == nullptr) {
        // Case 1: Node has no children
        if (node->isThread) {
            // Special case: Root is the only node in the tree
            delete node;
            root = nullptr;
        } else if (node->left != nullptr && node->left->isThread) {
            // Update successor's left thread
            node->left->left = nullptr;
            node->left->isThread = true;

            // Update the root if necessary
            if (root == node)
                root = node->left;

            delete node;
        } else if (node->right != nullptr && node->right->isThread) {
            // Update predecessor's right thread
            node->right->right = nullptr;
            node->right->isThread = true;

            // Update the root if necessary
            if (root == node)
                root = node->right;

            delete node;
        } else {
            // Find the inorder successor of the node
            Node* successor = leftmost(node->right);

            // Replace the node's key with the successor's key
            node->key = successor->key;

            // Remove the successor node
            remove(root, successor->key);
        }
    } else if (node->left == nullptr || node->right == nullptr) {
        // Case 2: Node has one child
        Node* child = (node->left != nullptr) ? node->left : node->right;

        if (node->left != nullptr && node->left->isThread) {
            // Update successor's left thread
            child->left = nullptr;
            child->isThread = true;
        } else if (node->right != nullptr && node->right->isThread) {
            // Update predecessor's right thread
            child->right = nullptr;
            child->isThread = true;
        }

        // Update the root if necessary
        if (root == node)
            root = child;

        delete node;
    } else {
        // Case 3: Node has two children
        // Find the inorder successor of the node
        Node* successor = leftmost(node->right);

        // Replace the node's key with the successor's key
        node->key = successor->key;

        // Remove the successor node
        remove(node->right, successor->key);
    }
    return root;
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
