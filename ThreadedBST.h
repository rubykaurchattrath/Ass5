// Jasjeen Khosa and Ruby Kaur
// CSS 342

#ifndef THREADEDBST_H
#define THREADEDBST_H

class ThreadedBST {
public:
    // Constructor
    ThreadedBST();

    // Copy constructor
    ThreadedBST(const ThreadedBST& other);

    // Destructor
    ~ThreadedBST();

    // Insert a key into the threaded binary search tree
    void insert(int key);

    // Remove a key from the threaded binary search tree
    void remove(int key);

    // Iterator class for inorder traversal
    class InorderIterator {
    public:
        // Constructor
        InorderIterator(Node* root);

        // Dereference operator
        int operator*();

        // Prefix increment operator
        InorderIterator& operator++();

        // Inequality operator
        bool operator!=(const InorderIterator& other);

    private:
        Node* current; // Current node in the traversal
        Node* getNext(Node* node); // Helper function to find the next node in inorder traversal
    };

    // Get the iterator to the first element in inorder traversal
    InorderIterator begin();

    // Get the iterator to the end sentinel in inorder traversal
    InorderIterator end();

private:
    // Node structure for threaded binary search tree
    struct Node {
        int key;
        Node* left;
        Node* right;
        bool isThreaded;

        // Constructor
        Node(int key) : key(key), left(nullptr), right(nullptr), isThreaded(false) {}
    };

    Node* root; // Root node of the threaded binary search tree

    // Private helper functions

    // Recursive insertion function
    void insert(Node*& node, int key);

    // Recursive removal function
    void remove(Node*& node, int key);

    // Helper function to find the minimum node in a subtree
    Node* findMin(Node* node);

    // Helper function to copy the tree
    void copyTree(const ThreadedBST& other);

    // Helper function to destroy the tree
    void destroyTree(Node* node);
};

#endif
