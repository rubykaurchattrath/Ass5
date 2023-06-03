// Jasjeen Khosa and Ruby Kaur
// CSS 342

#include <iostream>

class Node {
public:
    int key;
    Node* left;
    Node* right;
    bool isThread; // flag to distinguish threads

    Node(int k) : key(k), left(nullptr), right(nullptr), isThread(false) {}
};
