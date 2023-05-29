// NEEDS TO BE EDITED COMPLETELY

#include "ThreadedBinarySearchTree.h"

template <class KeyType>
typename ThreadedBST<KeyType>::ThreadedBSTNode* ThreadedBST<KeyType>::InorderIterator::findLeftMost(ThreadedBSTNode<KeyType>* node) {
    while (node != nullptr && !node->leftThread)
        node = node->left;
    return node;
}

template <class KeyType>
typename ThreadedBST<KeyType>::ThreadedBSTNode* ThreadedBST<KeyType>::InorderIterator::findRightMost(ThreadedBSTNode<KeyType>* node) {
    while (node != nullptr && !node->rightThread)
        node = node->right;
    return node;
}

template <class KeyType>
ThreadedBST<KeyType>::InorderIterator::InorderIterator(ThreadedBSTNode<KeyType>* root) {
    current = findLeftMost(root);
}

template <class KeyType>
KeyType ThreadedBST<KeyType>::InorderIterator::operator*() {
    return current->key;
}

template <class KeyType>
typename ThreadedBST<KeyType>::InorderIterator& ThreadedBST<KeyType>::InorderIterator::operator++() {
    if (current->rightThread)
        current = current->right;
    else
        current = findLeftMost(current->right);
    return *this;
}

template <class KeyType>
bool ThreadedBST<KeyType>::InorderIterator::operator==(const InorderIterator& other) const {
    return current == other.current;
}

template <class KeyType>
bool ThreadedBST<KeyType>::InorderIterator::operator!=(const InorderIterator& other) const {
    return !(*this == other);
}

template <class KeyType>
typename ThreadedBST<KeyType>::InorderIterator ThreadedBST<KeyType>::begin() {
    return InorderIterator(root);
}

template <class KeyType>
typename ThreadedBST<KeyType>::InorderIterator ThreadedBST<KeyType>::end() {
    return InorderIterator(nullptr);
}

template <class KeyType>
void ThreadedBST<KeyType>::clear(ThreadedBSTNode<KeyType>* node) {
    if (node == nullptr)
        return;
    if (!node->leftThread)
        clear(node->left);
    if (!node->rightThread)
        clear(node->right);
    delete node;
}

template <class KeyType>
typename ThreadedBST<KeyType>::ThreadedBSTNode* ThreadedBST<KeyType>::insert(ThreadedBSTNode<KeyType>* node, const KeyType& key) {
    if (node == nullptr)
        return new ThreadedBSTNode<KeyType>(key);

    if (key < node->key) {
        if (node->leftThread) {
            node->left = new ThreadedBSTNode<KeyType>(key);
            node->left->right = node;
            node->leftThread = false;
        } else {
            node->left = insert(node->left, key);
        }
    } else if (key > node->key) {
        if (node->rightThread) {
            node->right = new ThreadedBSTNode<KeyType>(key);
            node->right->left = node;
            node->rightThread = false;
        } else {
            node->right = insert(node->right, key);
        }
    }
    return node;
}

template <class KeyType>
void ThreadedBST<KeyType>::insert(const KeyType& key) {
    root = insert(root, key);
}

template <class KeyType>
typename ThreadedBST<KeyType>::ThreadedBSTNode* ThreadedBST<KeyType>::remove(ThreadedBSTNode<KeyType>* node, const KeyType& key) {
    if (node == nullptr)
        return nullptr;

    if (key < node->key) {
        if (!node->leftThread)
            node->left = remove(node->left, key);
    } else if (key > node->key) {
        if (!node->rightThread)
            node->right = remove(node->right, key);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left == nullptr) {
            ThreadedBSTNode<KeyType>* successor = findLeftMost(node->right);
            node->key = successor->key;
            node->right = remove(node->right, successor->key);
        } else if (node->right == nullptr) {
            ThreadedBSTNode<KeyType>* predecessor = findRightMost(node->left);
            node->key = predecessor->key;
            node->left = remove(node->left, predecessor->key);
        } else {
            ThreadedBSTNode<KeyType>* successor = findLeftMost(node->right);
            node->key = successor->key;
            node->right = remove(node->right, successor->key);
        }
    }
    return node;
}

template <class KeyType>
bool ThreadedBST<KeyType>::remove(const KeyType& key) {
    if (isEmpty())
        return false;

    root = remove(root, key);
    return true;
}

