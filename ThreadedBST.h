// Jasjeen Khosa and Ruby Kaur
// CSS 342

#ifndef THREADEDBST_H
#define THREADEDBST_H

#include "Node.cpp"

class ThreadedBST {
private:
    Node* root;

public:
    ThreadedBST();
    ~ThreadedBST();

    void insert(int key);
    void remove(int key);
    void display();
    void inorder();

private:
    Node* findSuccessor(Node* node);
    Node* findSuccessorParent(Node* node);
};

#endif  // THREADEDBST_H
