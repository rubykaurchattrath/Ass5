// Jasjeen Khosa and Ruby Kaur
// CSS 342

#include "ThreadedBST.h"
#include <iostream>

// Constructor
template<class ItemType>
ThreadedBST<ItemType>::ThreadedBST() : rootPtr(nullptr) {}

// Destructor
template<class ItemType>
ThreadedBST<ItemType>::~ThreadedBST() {
    clear();
}

// Public methods for inserting, deleting, and traversing the tree

template<class ItemType>
void ThreadedBST<ItemType>::insert(const ItemType& item) {
    BinaryNode* newNode = new BinaryNode(item);

    if (rootPtr == nullptr) {
        rootPtr = newNode;
    } else {
        insertInorder(rootPtr, newNode);
    }
}

template<class ItemType>
void ThreadedBST<ItemType>::deleteItem(const ItemType& target) {
    bool found = false;
    BinaryNode* targetNode = findNode(rootPtr, target, found);

    if (found) {
        deleteNode(targetNode);
    }
}

template<class ItemType>
void ThreadedBST<ItemType>::inorderTraversal() const {
    BinaryNode* current = findLeftmostNode(rootPtr);

    while (current != nullptr) {
        std::cout << current->getItem() << " ";

        if (current->hasRightThread()) {
            current = current->getRightChildPtr();
        } else {
            current = findLeftmostNode(current->getRightChildPtr());
        }
    }
}

// Private Helper Methods

template<class ItemType>
typename ThreadedBST<ItemType>::BinaryNode* ThreadedBST<ItemType>::findNode(BinaryNode* subTreePtr,
    const ItemType& target, bool& found) const {
    if (subTreePtr == nullptr) {
        found = false;
        return nullptr;
    } else if (subTreePtr->getItem() == target) {
        found = true;
        return subTreePtr;
    } else if (subTreePtr->getItem() > target && !subTreePtr->hasLeftThread()) {
        return findNode(subTreePtr->getLeftChildPtr(), target, found);
    } else if (subTreePtr->getItem() < target && !subTreePtr->hasRightThread()) {
        return findNode(subTreePtr->getRightChildPtr(), target, found);
    } else {
        found = false;
        return nullptr;
    }
}

template<class ItemType>
typename ThreadedBST<ItemType>::BinaryNode* ThreadedBST<ItemType>::findLeftmostNode(BinaryNode* node) const {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->getLeftChildPtr() != nullptr && !node->hasLeftThread()) {
        node = node->getLeftChildPtr();
    }

    return node;
}

template<class ItemType>
void ThreadedBST<ItemType>::insertInorder(BinaryNode* subTreePtr, BinaryNode* newNode) {
    if (newNode->getItem() < subTreePtr->getItem()) {
        if (subTreePtr->hasLeftThread()) {
            newNode->setLeftChildPtr(subTreePtr->getLeftChildPtr());
            newNode->setRightChildPtr(subTreePtr);
            subTreePtr->setLeftChildPtr(newNode);
            subTreePtr->setLeftThread(false);
        } else {
            insertInorder(subTreePtr->getLeftChildPtr(), newNode);
        }
    } else {
        if (subTreePtr->hasRightThread()) {
            newNode->setRightChildPtr(subTreePtr->getRightChildPtr());
            newNode->setLeftChildPtr(subTreePtr);
            subTreePtr->setRightChildPtr(newNode);
            subTreePtr->setRightThread(false);
        } else {
            insertInorder(subTreePtr->getRightChildPtr(), newNode);
        }
    }
}

template<class ItemType>
void ThreadedBST<ItemType>::deleteNode(BinaryNode* node) {
    // Case 1: Node has no children
    if (node->isLeaf()) {
        BinaryNode* parent = findParent(rootPtr, node);
        if (parent == nullptr) {
            rootPtr = nullptr;
        } else if (parent->getLeftChildPtr() == node) {
            parent->setLeftChildPtr(node->getLeftChildPtr());
            parent->setLeftThread(true);
        } else {
            parent->setRightChildPtr(node->getRightChildPtr());
            parent->setRightThread(true);
        }
        delete node;
    }
    // Case 2: Node has one child
    else if (node->getLeftChildPtr() == nullptr || node->getRightChildPtr() == nullptr) {
        BinaryNode* parent = findParent(rootPtr, node);
        BinaryNode* child = nullptr;
        if (node->getLeftChildPtr() != nullptr) {
            child = node->getLeftChildPtr();
        } else {
            child = node->getRightChildPtr();
        }
        if (parent == nullptr) {
            rootPtr = child;
        } else if (parent->getLeftChildPtr() == node) {
            parent->setLeftChildPtr(child);
        } else {
            parent->setRightChildPtr(child);
        }
        delete node;
    }
    // Case 3: Node has two children
    else {
        BinaryNode* successor = findSuccessor(node);
        ItemType successorValue = successor->getItem();
        deleteNode(successor);
        node->setItem(successorValue);
    }
}

template<class ItemType>
typename ThreadedBST<ItemType>::BinaryNode* ThreadedBST<ItemType>::findParent(BinaryNode* subTreePtr, BinaryNode* node) const {
    if (subTreePtr == nullptr) {
        return nullptr;
    } else if ((subTreePtr->hasLeftThread() && subTreePtr->getLeftChildPtr() == node) ||
               (subTreePtr->hasRightThread() && subTreePtr->getRightChildPtr() == node)) {
        return subTreePtr;
    } else if (node->getItem() < subTreePtr->getItem()) {
        return findParent(subTreePtr->getLeftChildPtr(), node);
    } else {
        return findParent(subTreePtr->getRightChildPtr(), node);
    }
}

template<class ItemType>
typename ThreadedBST<ItemType>::BinaryNode* ThreadedBST<ItemType>::findSuccessor(BinaryNode* node) const {
    if (node->hasRightThread()) {
        return node->getRightChildPtr();
    } else {
        BinaryNode* current = node->getRightChildPtr();
        while (!current->hasLeftThread()) {
            current = current->getLeftChildPtr();
        }
        return current;
    }
}

template<class ItemType>
void ThreadedBST<ItemType>::clear() {
    clearTree(rootPtr);
    rootPtr = nullptr;
}

template<class ItemType>
void ThreadedBST<ItemType>::clearTree(BinaryNode* subTreePtr) {
    if (subTreePtr != nullptr) {
        if (!subTreePtr->hasLeftThread()) {
            clearTree(subTreePtr->getLeftChildPtr());
        }

        if (!subTreePtr->hasRightThread()) {
            clearTree(subTreePtr->getRightChildPtr());
        }

        delete subTreePtr;
    }
}

template<class ItemType>
typename ThreadedBST<ItemType>::BinaryNode* ThreadedBST<ItemType>::copyTree(const BinaryNode* treePtr) const {
    if (treePtr == nullptr) {
        return nullptr;
    }

    BinaryNode* newNode = new BinaryNode(treePtr->getItem());
    newNode->setLeftThread(treePtr->hasLeftThread());
    newNode->setRightThread(treePtr->hasRightThread());

    if (!treePtr->hasLeftThread()) {
        newNode->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
    }

    if (!treePtr->hasRightThread()) {
        newNode->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
    }

    return newNode;
}

template<class ItemType>
void ThreadedBST<ItemType>::copyThreadedNodes(BinaryNode* newTreePtr, const BinaryNode* treePtr) {
    if (newTreePtr == nullptr || treePtr == nullptr) {
        return;
    }

    if (!treePtr->hasLeftThread()) {
        BinaryNode* leftChild = newTreePtr->getLeftChildPtr();
        const BinaryNode* leftChildThreaded = treePtr->getLeftChildPtr();
        leftChild->setRightChildPtr(leftChildThreaded);
        copyThreadedNodes(leftChild, leftChildThreaded);
    }

    if (!treePtr->hasRightThread()) {
        BinaryNode* rightChild = newTreePtr->getRightChildPtr();
        const BinaryNode* rightChildThreaded = treePtr->getRightChildPtr();
        rightChild->setLeftChildPtr(rightChildThreaded);
        copyThreadedNodes(rightChild, rightChildThreaded);
    }
}
