// Jasjeen Khosa and Ruby Kaur
// CSS 342

#ifndef THREADEDBST_H
#define THREADEDBST_H

#include "Node.cpp"

class ThreadedBST {
private:
    Node* root;

public:
    ThreadedBST(); // constructor
    ~ThreadedBST(); // destructor

    void insert(int key);
    void remove(int key);
    void display();
    void inorder();

private:
    Node* findSuccessor(Node* node);
    Node* findSuccessorParent(Node* node);
    ThreadedBST(const ThreadedBST& other); // copy constructor
    Node* copyTree(Node* node); // recursive helper function to copy the tree
};

#endif  // THREADEDBST_H
