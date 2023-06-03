/// Jasjeen Khosa and Ruby Kaur
// CSS 342 

#ifndef THREADEDBST_H
#define THREADEDBST_H

#include "Node.cpp"

class ThreadedBST {
private:
    Node* root;

public:
    /**
     * Constructs an empty ThreadedBST object.
     * Pre-condition: None.
     * Post-condition: An empty ThreadedBST object is created with a null root.
     */
    ThreadedBST();

    /**
     * Destroys the ThreadedBST object and frees the associated memory.
     * Pre-condition: None.
     * Post-condition: The ThreadedBST object is destroyed, and all the associated memory is freed.
     */
    ~ThreadedBST();

    /**
     * Inserts a new key into the threaded binary search tree.
     * Pre-condition: The key is not already present in the threaded binary search tree.
     * Post-condition: The key is inserted into the threaded binary search tree in the correct position.
     */
    void insert(int key);

    /**
     * Removes a key from the threaded binary search tree.
     * Pre-condition: The key is present in the threaded binary search tree.
     * Post-condition: The key is removed from the threaded binary search tree if found, and the tree is modified accordingly.
     */
    void remove(int key);

    /**
     * Displays the threaded binary search tree in a human-readable format.
     * Pre-condition: None.
     * Post-condition: The threaded binary search tree is displayed on the screen.
     */
    void display();

    /**
     * Performs an inorder traversal of the threaded binary search tree.
     * Pre-condition: None.
     * Post-condition: The keys of the threaded binary search tree are printed in ascending order.
     */
    void inorder();

private:
    /**
     * Finds the successor of a given node in the threaded binary search tree.
     * Pre-condition: The given node is not null.
     * Post-condition: Returns the successor node of the given node, or null if it doesn't have a successor.
     */
    Node* findSuccessor(Node* node);

    /**
     * Finds the parent of the successor of a given node in the threaded binary search tree.
     * Pre-condition: The given node is not null.
     * Post-condition: Returns the parent node of the successor of the given node, or null if it doesn't have a successor.
     */
    Node* findSuccessorParent(Node* node);

    /**
     * Copy constructor for the ThreadedBST class.
     * Pre-condition: The other ThreadedBST object is valid.
     * Post-condition: A deep copy of the other ThreadedBST object is created.
     */
    ThreadedBST(const ThreadedBST& other);

    /**
     * Recursive helper function to copy a subtree rooted at the given node.
     * Pre-condition: The given node is not null.
     * Post-condition: Returns a deep copy of the subtree rooted at the given node.
     */
    Node* copyTree(Node* node);
};

#endif  // THREADEDBST_H
