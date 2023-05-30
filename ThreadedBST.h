// Jasjeen Khosa and Ruby Kaur
// CSS 342

#ifndef _THREADED_BINARY_SEARCH_TREE
#define _THREADED_BINARY_SEARCH_TREE

template <class ItemType>
class ThreadedBST {
private:
    class BinaryNode {
    private:
        ItemType item; // Data portion
        BinaryNode* leftChildPtr; // Pointer to left child
        BinaryNode* rightChildPtr; // Pointer to right child
        bool leftThread; // true if left child is a thread
        bool rightThread; // true if right child is a thread

    public:
        BinaryNode();
        BinaryNode(const ItemType& anItem);
        BinaryNode(const ItemType& anItem, BinaryNode* leftPtr, BinaryNode* rightPtr);
        void setItem(const ItemType& anItem);
        ItemType getItem() const;
        bool isLeaf() const;
        BinaryNode* getLeftChildPtr() const;
        BinaryNode* getRightChildPtr() const;
        void setLeftChildPtr(BinaryNode* leftPtr);
        void setRightChildPtr(BinaryNode* rightPtr);
        bool hasLeftThread() const;
        bool hasRightThread() const;
        void setLeftThread(bool isThread);
        void setRightThread(bool isThread);
    };

    BinaryNode* rootPtr; // Pointer to the root node

public:
    // Constructors and destructor
    ThreadedBST();
    ThreadedBST(const ThreadedBST<ItemType>& tree);
    ~ThreadedBST();

    // Public methods for inserting, deleting, and traversing the tree
    void insert(const ItemType& newEntry);
    void deleteItem(const ItemType& target);
    void inorderTraversal() const;

private:
    // Helper methods
    void insertInorder(BinaryNode* subTreePtr, BinaryNode* newNode);
    BinaryNode* findInorderSuccessor(BinaryNode* node) const;
};

#include "ThreadedBST.cpp"
#endif

