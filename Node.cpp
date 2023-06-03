// Jasjeen Khosa and Ruby Kaur
// CSS 342

#include <iostream>

class Node {
public:
    int key;
    Node* left;
    Node* right;
    bool rightThread;

    Node(int k) : key(k), left(nullptr), right(nullptr), rightThread(false) {}
};
