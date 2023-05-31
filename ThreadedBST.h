// Jasjeen Khosa and Ruby Kaur
// CSS 342

#ifndef ASS5_THREADEDBINARYSEARCHTREE_H
#define ASS5_THREADEDBINARYSEARCHTREE_H

#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
  bool isThreaded;
  Node(int value)
      : data(value), left(nullptr), right(nullptr), isThreaded(false) {}
};

class ThreadedBinarySearchTree {

  // Overloads the cout << operator
  friend ostream &operator<<(ostream &out,
                             const ThreadedBinarySearchTree &other);
  // overloads the cin >> operator
  friend istream &operator>>(istream &input, ThreadedBinarySearchTree &other);

private:
  Node *root;

public:
  ThreadedBinarySearchTree();
  ThreadedBinarySearchTree(const ThreadedBinarySearchTree &other);
  ~ThreadedBinarySearchTree();

  /** Tests whether this binary tree is empty.
  @return True if the binary tree is empty, or false if not. */
  bool isEmpty() const;

  /** Gets the height of this binary tree.
  @return The height of the binary tree. */
  int getHeight() const;

  /** Gets the number of nodes in this binary tree.
  @return The number of nodes in the binary tree. */
  int getNumberOfNodes() const;

  /** Gets the data that is in the root of this binary tree.
  @pre The binary tree is not empty.
  @post The root’s data has been returned, and the binary tree is unchanged.
  @return The data in the root of the binary tree. */
  int getRootData() const;

  /** Replaces the data item in the root of this binary tree with the given
  data, if the tree is not empty. However, if the tree is empty, inserts a new
  root node containing the given data into the tree.
  @pre None.
  @post The data in the root of the binary tree is as given.
  @param newData The data for the root. */
  void setRootData(int data);

  /** Adds a new node containing the given data to this binary tree.
  @param newData The data for the new node.
  @post The binary tree contains a new node.
  @return True if the addition is successful, or false not. */
  void add(int value);

  /** Removes the node containing the given data item from this binary tree.
  @param data The data value to remove from the binary tree.
  @return True if the removal is successful, or false not. */
  void remove(int value);

  /** Removes all nodes from this binary tree. */
  void clear();

  /** Tests whether a given entry occurs in this binary tree.
  @post The binary search tree is unchanged.
  @param anEntry The entry to find.
  @return True if the entry occurs in the tree, or false if not. */
  bool contains(int data) const;
};
#endif



/**
#ifndef _THREADED_BINARY_SEARCH_TREE
#define _THREADED_BINARY_SEARCH_TREE

#include <ostream>
using namespace std;

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
    
    // Operator overloads
    template <class ItemType>
    friend ostream& operator<<(ostream& os, const ThreadedBST<ItemType>& tree);

private:
    // Helper methods
    void insertInorder(BinaryNode* subTreePtr, BinaryNode* newNode);
    BinaryNode* findInorderSuccessor(BinaryNode* node) const;
};

#include "ThreadedBST.cpp"
#endif

