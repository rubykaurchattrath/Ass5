#include "ThreadedBST.h"
#include <iostream>

ThreadedBST::ThreadedBST() {
    root = nullptr;
}

ThreadedBST::~ThreadedBST() {
    // TODO: Implement destructor to release memory
}

void ThreadedBST::insert(int value) {
    Node* newNode = new Node(value);
    Node* parent = nullptr;
    Node* current = root;
    bool isLeftChild = false;

    if (root == nullptr) {
        root = newNode;
        return;
    }

    while (current != nullptr) {
        parent = current;

        if (value < current->data) {
            if (!current->isThreaded)
                current = current->left;
            else
                break;
            isLeftChild = true;
        } else {
            if (!current->isThreaded)
                current = current->right;
            else
                break;
            isLeftChild = false;
        }
    }

    if (isLeftChild) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->isThreaded = false;
        parent->left = newNode;
    } else {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->isThreaded = false;
        parent->right = newNode;
    }
}

void ThreadedBST::remove(int value) {
    if (root == nullptr)
        return;

    Node* current = root;
    Node* parent = nullptr;
    bool isLeftChild = false;

    while (current != nullptr) {
        if (value == current->data)
            break;

        parent = current;

        if (value < current->data) {
            if (!current->isThreaded)
                current = current->left;
            else
                return;  // Value not found
            isLeftChild = true;
        } else {
            if (!current->isThreaded)
                current = current->right;
            else
                return;  // Value not found
            isLeftChild = false;
        }
    }

    if (current == nullptr)
        return;  // Value not found

    if (current->isThreaded) {
        if (current->left == nullptr) {
            if (isLeftChild)
                parent->left = current->left;
            else
                parent->right = current->right;
            delete current;
        } else {
            Node* successor = findLeftmost(current->right);
            if (isLeftChild)
                parent->left = successor;
            else
                parent->right = successor;
            successor->left = current->left;
            delete current;
        }
    } else {
        if (current->left == nullptr && current->right == nullptr) {
            if (current == root)
                root = nullptr;
            else if (isLeftChild)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            delete current;
        } else if (current->left == nullptr) {
            if (current == root)
                root = current->right;
            else if (isLeftChild)
                parent->left = current->right;
            else
                parent->right = current->right;
            delete current;
        } else if (current->right == nullptr) {
            if (current == root)
                root = current->left;
            else if (isLeftChild)
                parent->left = current->left;
            else
                parent->right = current->left;
            delete current;
        } else {
            Node* successor = findLeftmost(current->right);
            Node* successorParent = current;
            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            current->data = successor->data;
            if (successor->isThreaded) {
                if (successorParent == current)
                    successorParent->right = successor->right;
                else
                    successorParent->left = successor->right;
                delete successor;
            } else {
                if (successorParent == current)
                    successorParent->right = nullptr;
                else
                    successorParent->left = nullptr;
                delete successor;
            }
        }
    }
}

void ThreadedBST::inorderTraversal() {
    if (root == nullptr) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }

    Node* current = findLeftmost(root);

    while (current != nullptr) {
        std::cout << current->data << " ";

        if (current->isThreaded)
            current = current->right;
        else
            current = findLeftmost(current->right);
    }

    std::cout << std::endl;
}

Node* ThreadedBST::findLeftmost(Node* node) {
    if (node == nullptr)
        return nullptr;

    while (node->left != nullptr)
        node = node->left;

    return node;
}

Node* ThreadedBST::findRightmost(Node* node) {
    if (node == nullptr)
        return nullptr;

    while (node->right != nullptr && !node->isThreaded)
        node = node->right;

    return node;
}
