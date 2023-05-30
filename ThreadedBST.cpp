// Jasjeen Khosa and Ruby Kaur
// CSS 342

#include "ThreadedBST.h"
#include <iostream>
using namespace std;

// Constructor
template<class ItemType>
ThreadedBST<ItemType>::ThreadedBST() : rootPtr(nullptr) {}

// Destructor
template<class ItemType>
ThreadedBST<ItemType>::~ThreadedBST() {
    clear();
}

// Public methods for inserting, deleting, and traversing the tree

/**
 * Inserts a new item into the threaded bst.
 * @param item The item to be inserted.
 */
template<class ItemType>
void ThreadedBST<ItemType>::insert(const ItemType& item) {
    // Create a new node with the given item
    BinaryNode* newNode = new BinaryNode(item);

    if (rootPtr == nullptr) {
        // If the tree is empty, set the new node as the root
        rootPtr = newNode;
    } else {
        // If the tree is not empty, insert the new node in the appropriate position
        insertInorder(rootPtr, newNode);
    }
}

/**
 * Deletes the specified item from the threaded bst.
 * @param target The item to be deleted.
 */
template<class ItemType>
void ThreadedBST<ItemType>::deleteItem(const ItemType& target) {
    bool found = false;
    // Find the node containing the target item
    BinaryNode* targetNode = findNode(rootPtr, target, found);

    if (found) {
        // If the target item is found, delete the node
        deleteNode(targetNode);
    }
}

/**
 * Performs an inorder traversal of the threaded bst
 * and outputs the items in ascending order.
 */
// Performs an inorder traversal of the threaded bst
// and outputs the items to the given ostream.
template<class ItemType>
void ThreadedBST<ItemType>::inorderTraversal(std::ostream& os) const {
    // Start from the leftmost node of the tree
    BinaryNode* current = findLeftmostNode(rootPtr);

    while (current != nullptr) {
        // Output the item in the current node
        os << current->getItem() << " ";

        if (current->hasRightThread()) {
            // If the right thread is present, move to the successor node
            current = current->getRightChildPtr();
        } else {
            // If the right thread is not present, move to the leftmost node of the right subtree
            current = findLeftmostNode(current->getRightChildPtr());
        }
    }
}

// Overloaded ostream operator for printing the threaded BST
template<class ItemType>
ostream& operator<<(ostream& os, const ThreadedBST<ItemType>& tree) {
    tree.inorderTraversal(os);
    return os;
}

// Private Helper Methods

/**
 * Recursively searches for a node containing the specified target item in the threaded bst.
 * @param subTreePtr A pointer to the root of the subtree to search in.
 * @param target The target item to search for.
 * @param found A boolean flag indicating whether the target item is found.
 * @return A pointer to the node containing the target item if found, nullptr otherwise.
 */
template<class ItemType>
typename ThreadedBST<ItemType>::BinaryNode* ThreadedBST<ItemType>::findNode(BinaryNode* subTreePtr,
    const ItemType& target, bool& found) const {
    if (subTreePtr == nullptr) {
        // Base case: Subtree is empty, target item is not found
        found = false;
        return nullptr;
    } else if (subTreePtr->getItem() == target) {
        // Base case: Target item is found in the current node
        found = true;
        return subTreePtr;
    } else if (subTreePtr->getItem() > target && !subTreePtr->hasLeftThread()) {
        // Recursive case: Target item is smaller than the current node's item,
        // and the left child is not a thread, continue searching in the left subtree
        return findNode(subTreePtr->getLeftChildPtr(), target, found);
    } else if (subTreePtr->getItem() < target && !subTreePtr->hasRightThread()) {
        // Recursive case: Target item is greater than the current node's item,
        // and the right child is not a thread, continue searching in the right subtree
        return findNode(subTreePtr->getRightChildPtr(), target, found);
    } else {
        // Base case: Target item is not found
        found = false;
        return nullptr;
    }
}

/**
 * Finds and returns the leftmost node in the threaded bst.
 * @param node The starting node for the search.
 * @return Pointer to the leftmost node.
 */
template<class ItemType>
typename ThreadedBST<ItemType>::BinaryNode* ThreadedBST<ItemType>::findLeftmostNode(BinaryNode* node) const {
    if (node == nullptr) {
        // If the starting node is nullptr, return nullptr
        return nullptr;
    }

    while (node->getLeftChildPtr() != nullptr && !node->hasLeftThread()) {
        // Traverse to the leftmost node by following the left child pointers
        node = node->getLeftChildPtr();
    }

    return node;
}

/**
 * Inserts a new node into the threaded bst in the correct position according to the inorder traversal order.
 * @param subTreePtr A pointer to the root of the subtree.
 * @param newNode A pointer to the new node to be inserted.
 */
template<class ItemType>
void ThreadedBST<ItemType>::insertInorder(BinaryNode* subTreePtr, BinaryNode* newNode) {
    if (newNode->getItem() < subTreePtr->getItem()) {
        // If the item in the new node is less than the item in the current node
        if (subTreePtr->hasLeftThread()) {
            // If the left child is a thread, insert the new node to the left of the current node
            newNode->setLeftChildPtr(subTreePtr->getLeftChildPtr());
            newNode->setRightChildPtr(subTreePtr);
            subTreePtr->setLeftChildPtr(newNode);
            subTreePtr->setLeftThread(false);
        } else {
            // If the left child is not a thread, recursively insert the new node in the left subtree
            insertInorder(subTreePtr->getLeftChildPtr(), newNode);
        }
    } else {
        // If the item in the new node is greater than or equal to the item in the current node
        if (subTreePtr->hasRightThread()) {
            // If the right child is a thread, insert the new node to the right of the current node
            newNode->setRightChildPtr(subTreePtr->getRightChildPtr());
            newNode->setLeftChildPtr(subTreePtr);
            subTreePtr->setRightChildPtr(newNode);
            subTreePtr->setRightThread(false);
        } else {
            // If the right child is not a thread, recursively insert the new node in the right subtree
            insertInorder(subTreePtr->getRightChildPtr(), newNode);
        }
    }
}

/**
 * Deletes a node from the threaded bst.
 * @param node A pointer to the node to be deleted.
 */
template<class ItemType>
void ThreadedBST<ItemType>::deleteNode(BinaryNode* node) {
    // Case 1: Node has no children
    if (node->isLeaf()) {
        // Find the parent of the node
        BinaryNode* parent = findParent(rootPtr, node);
        if (parent == nullptr) {
            // If the node is the root, set the root to nullptr
            rootPtr = nullptr;
        } else if (parent->getLeftChildPtr() == node) {
            // If the node is the left child of its parent, update the parent's left child pointer and thread flag
            parent->setLeftChildPtr(node->getLeftChildPtr());
            parent->setLeftThread(true);
        } else {
            // If the node is the right child of its parent, update the parent's right child pointer and thread flag
            parent->setRightChildPtr(node->getRightChildPtr());
            parent->setRightThread(true);
        }
        delete node;
    }
    
    // Case 2: Node has one child
    else if (node->getLeftChildPtr() == nullptr || node->getRightChildPtr() == nullptr) {
        // Find the parent of the node
        BinaryNode* parent = findParent(rootPtr, node);
        BinaryNode* child = nullptr;
        if (node->getLeftChildPtr() != nullptr) {
            // If the node has a left child, set the child as the node's child
            child = node->getLeftChildPtr();
        } else {
            // If the node has a right child, set the child as the node's child
            child = node->getRightChildPtr();
        }
        if (parent == nullptr) {
            // If the node is the root, set the child as the new root
            rootPtr = child;
        } else if (parent->getLeftChildPtr() == node) {
            // If the node is the left child of its parent, update the parent's left child pointer
            parent->setLeftChildPtr(child);
        } else {
            // If the node is the right child of its parent, update the parent's right child pointer
            parent->setRightChildPtr(child);
        }
        delete node;
    }
    
    // Case 3: Node has two children
    else {
        // Find the successor of the node
        BinaryNode* successor = findSuccessor(node);
        ItemType successorValue = successor->getItem();
        deleteNode(successor);
        node->setItem(successorValue);
    }
}

/**
 * Finds the parent of a given node in the threaded bst.
 * @param subTreePtr A pointer to the root of the subtree to search in.
 * @param node A pointer to the node whose parent needs to be found.
 * @return A pointer to the parent node, or nullptr if the parent is not found.
 */
template<class ItemType>
typename ThreadedBST<ItemType>::BinaryNode* ThreadedBST<ItemType>::findParent(BinaryNode* subTreePtr, BinaryNode* node) const {
    if (subTreePtr == nullptr) {
        // Base case: Subtree is empty, return nullptr
        return nullptr;
    } else if ((subTreePtr->hasLeftThread() && subTreePtr->getLeftChildPtr() == node) ||
               (subTreePtr->hasRightThread() && subTreePtr->getRightChildPtr() == node)) {
        // Check if the current node is the parent of the given node
        return subTreePtr;
    } else if (node->getItem() < subTreePtr->getItem()) {
        // If the given node's value is less than the current node's value, search in the left subtree
        return findParent(subTreePtr->getLeftChildPtr(), node);
    } else {
        // If the given node's value is greater than the current node's value, search in the right subtree
        return findParent(subTreePtr->getRightChildPtr(), node);
    }
}

/**
 * Finds the successor of a given node in the threaded bst
 * @param node A pointer to the node whose successor needs to be found.
 * @return A pointer to the successor node.
 */
template<class ItemType>
typename ThreadedBST<ItemType>::BinaryNode* ThreadedBST<ItemType>::findSuccessor(BinaryNode* node) const {
    if (node->hasRightThread()) {
        // If the right thread is present, the successor is the right child
        return node->getRightChildPtr();
    } else {
        // Otherwise, find the leftmost node in the right subtree
        BinaryNode* current = node->getRightChildPtr();
        while (!current->hasLeftThread()) {
            current = current->getLeftChildPtr();
        }
        return current;
    }
}

// Clears the threaded binary search tree.
template<class ItemType>
void ThreadedBST<ItemType>::clear() {
    clearTree(rootPtr);
    rootPtr = nullptr;
}

/**
 * Recursively clears the tree starting from the given node.
 * @param subTreePtr A pointer to the root of the subtree to clear.
 */
template<class ItemType>
void ThreadedBST<ItemType>::clearTree(BinaryNode* subTreePtr) {
    if (subTreePtr != nullptr) {
        if (!subTreePtr->hasLeftThread()) {
            // Clear the left subtree
            clearTree(subTreePtr->getLeftChildPtr());
        }

        if (!subTreePtr->hasRightThread()) {
            // Clear the right subtree
            clearTree(subTreePtr->getRightChildPtr());
        }

        // Delete the current node
        delete subTreePtr;
    }
}

/**
 * Copies the tree rooted at the given node.
 * @param treePtr A pointer to the root of the tree to copy.
 * @return A pointer to the root of the copied tree.
 */
template<class ItemType>
typename ThreadedBST<ItemType>::BinaryNode* ThreadedBST<ItemType>::copyTree(const BinaryNode* treePtr) const {
    if (treePtr == nullptr) {
        // Base case: Empty tree, return nullptr
        return nullptr;
    }

    // Create a new node with the same item and thread status as the current node
    BinaryNode* newNode = new BinaryNode(treePtr->getItem());
    newNode->setLeftThread(treePtr->hasLeftThread());
    newNode->setRightThread(treePtr->hasRightThread());

    if (!treePtr->hasLeftThread()) {
        // Recursively copy the left subtree
        newNode->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
    }

    if (!treePtr->hasRightThread()) {
        // Recursively copy the right subtree
        newNode->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
    }

    return newNode;
}

/**
 * Copies the threaded nodes from the source tree to the destination tree.
 * @param newTreePtr A pointer to the corresponding node in the destination tree.
 * @param treePtr A pointer to the corresponding node in the source tree.
 */
template<class ItemType>
void ThreadedBST<ItemType>::copyThreadedNodes(BinaryNode* newTreePtr, const BinaryNode* treePtr) {
    if (newTreePtr == nullptr || treePtr == nullptr) {
        // Base case: Either the new tree or the source tree is empty
        return;
    }

    if (!treePtr->hasLeftThread()) {
        // If the source node has a left child, copy the left child and its threaded nodes
        BinaryNode* leftChild = newTreePtr->getLeftChildPtr();
        const BinaryNode* leftChildThreaded = treePtr->getLeftChildPtr();
        leftChild->setRightChildPtr(leftChildThreaded);
        copyThreadedNodes(leftChild, leftChildThreaded);
    }

    if (!treePtr->hasRightThread()) {
        // If the source node has a right child, copy the right child and its threaded nodes
        BinaryNode* rightChild = newTreePtr->getRightChildPtr();
        const BinaryNode* rightChildThreaded = treePtr->getRightChildPtr();
        rightChild->setLeftChildPtr(rightChildThreaded);
        copyThreadedNodes(rightChild, rightChildThreaded);
    }
}

