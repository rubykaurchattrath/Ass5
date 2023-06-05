#ifndef THREADEDBST_H
#define THREADEDBST_H

struct Node {
    int data;
    Node* left;
    Node* right;
    bool isThreaded;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        isThreaded = false;
    }
};

class ThreadedBST {
private:
    Node* root;

public:
    ThreadedBST();
    ~ThreadedBST();

    void insert(int value);
    void remove(int value);
    void inorderTraversal();
    Node* findLeftmost(Node* node);
    Node* findRightmost(Node* node);
};

#endif
