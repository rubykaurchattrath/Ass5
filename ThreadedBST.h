/// Jasjeen Khosa and Ruby Kaur
// CSS 342 

#ifndef THREADEDBST_H
#define THREADEDBST_H

#include "Node.cpp"
class ThreadedBST {

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
     * Removes a node with the specified key from the threaded binary search tree.
     * @param key The key of the node to be removed.
     * @pre The tree is not empty.
     * @post The node with the specified key is removed from the tree, if present.
     *       The tree remains a valid threaded binary search tree.
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
    
    /**
     * Finds a node with the specified key in the threaded binary search tree.
     * @param root The root node of the tree to search.
     * @param key The key to search for.
     * @return The node with the specified key if found, nullptr otherwise.
     * @pre The tree rooted at 'root' is not empty.
     * @post If a node with the specified 'key' is found in the tree rooted at 'root',
     * the return value is a pointer to that node; otherwise, the return value is nullptr.
     */
    Node* find(Node* root, int key);


private:
   
    Node* root;
    
    /**
     * Finds the successor of a given node in the threaded binary search tree.
     * Pre-condition: The given node is not null.
     * Post-condition: Returns the successor node of the given node, or null if it doesn't have a successor.
     */
    Node* findSuccessor(Node* node);

    /**
     * Recursively removes a node with the specified key from the threaded binary search tree.
     * @param node The root of the current subtree.
     * @param key The key of the node to be removed.
     * @return The root of the updated subtree after removing the node with the specified key.
     * @pre The subtree rooted at 'node' is a valid threaded binary search tree.
     * @post The node with the specified key is removed from the subtree rooted at 'node', if present.
     *       The subtree rooted at 'node' remains a valid threaded binary search tree.
     */
    Node* remove(Node*& root, int key);

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

    /** 
     * Helper function to find the leftmost node in the subtree rooted at 'node'
     * Pre-condition: The threaded binary search tree is non-empty.
     * Post-conditions: The function returns a pointer to the leftmost node in the tree.
     * If the tree is empty, i.e., there are no nodes, the function returns nullptr.
     */
    Node* leftmost(Node* node);
};

#endif  // THREADEDBST_H
