
#ifndef THREADED_BINARY_SEARCH_TREE_H
#define THREADED_BINARY_SEARCH_TREE_H

template <class KeyType>

class ThreadedBSTNode {
public:
    KeyType key;
    ThreadedBSTNode* left;
    ThreadedBSTNode* right;
    bool leftThread;
    bool rightThread; 

    ThreadedBSTNode(const KeyType& newKey) //constructors 
        : key(newKey), left(nullptr), right(nullptr),
          leftThread(false), rightThread(false) {}
};

template <class KeyType>
class ThreadedBST {
private:
    ThreadedBSTNode<KeyType>* root;

public:
    ThreadedBST() : root(nullptr) {}
    ~ThreadedBST() { clear(); }

    bool isEmpty() const { return root == nullptr; }
    void clear() { clear(root); root = nullptr; }

    void insert(const KeyType& key);
    bool remove(const KeyType& key);

    // Inorder traversal iterator
    class InorderIterator {
    private:
        ThreadedBSTNode<KeyType>* current;

        ThreadedBSTNode<KeyType>* findLeftMost(ThreadedBSTNode<KeyType>* node);
        ThreadedBSTNode<KeyType>* findRightMost(ThreadedBSTNode<KeyType>* node);

    public:
        InorderIterator(ThreadedBSTNode<KeyType>* root);

        KeyType operator*();
        InorderIterator& operator++();
        bool operator==(const InorderIterator& other) const;
        bool operator!=(const InorderIterator& other) const;
    };

    InorderIterator begin();
    InorderIterator end();

private:
    void clear(ThreadedBSTNode<KeyType>* node);
    ThreadedBSTNode<KeyType>* insert(ThreadedBSTNode<KeyType>* node, const KeyType& key);
    ThreadedBSTNode<KeyType>* remove(ThreadedBSTNode<KeyType>* node, const KeyType& key);
};

#endif // THREADED_BINARY_SEARCH_TREE_H


/**
 * 
 * /** A class of nodes for a link-based binary tree.
@file BinaryNode.h 
#ifndef _BINARY_NODE
#define _BINARY_NODE
template < class ItemType>
class BinaryNode
{
private :
ItemType item; // Data portion
BinaryNode<ItemType>* leftChildPtr; // Pointer to left child
BinaryNode<ItemType>* rightChildPtr; // Pointer to right child

public :
BinaryNode();
BinaryNode( const ItemType& anItem);
BinaryNode( const ItemType& anItem, BinaryNode<ItemType>* leftPtr, BinaryNode<ItemType>* rightPtr);
void setItem( const ItemType& anItem);
ItemType getItem() const ;
bool isLeaf() const ;
BinaryNode<ItemType>* getLeftChildPtr() const ;
BinaryNode<ItemType>* getRightChildPtr() const ;
void setLeftChildPtr(BinaryNode<ItemType>* leftPtr);
void setRightChildPtr(BinaryNode<ItemType>* rightPtr);
}; // end BinaryNode
#include "BinaryNode.cpp"
#endif
*/