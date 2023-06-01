// Jasjeen Khosa and Ruby Kaur
// CSS 342

#ifndef THREADEDBST_H
#define THREADEDBST_H

// Threaded Binary Search Tree implementation.
class ThreadedBST {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        bool isThreaded; // Flag to distinguish threads from real child pointers

        /**
         * Node constructor.
         * @param k The key value of the node.
         */
        Node(int k) : key(k), left(nullptr), right(nullptr), isThreaded(false) {}
    };

    Node* root;

public:
    ThreadedBST();
    ThreadedBST(const ThreadedBST& other);
    ~ThreadedBST();

    /**
     * Inserts a key into the threaded BST.
     * @param key The key to be inserted.
     */
    void insert(int key);

    /**
     * Removes a key from the threaded BST.
     * @param key The key to be removed.
     */
    void remove(int key);

    class InorderIterator {
    private:
        Node* current;
        Node* getNext(Node* node);

    public:
        /**
         * InorderIterator constructor.
         * @param root The root node of the threaded BST.
         */
        InorderIterator(Node* root);

        /**
         * Dereference operator overload.
         * @return The key value of the current node.
         */
        int operator*();

        /**
         * Pre-increment operator overload.
         * Moves the iterator to the next node in inorder traversal.
         * @return The reference to the updated iterator.
         */
        InorderIterator& operator++();

        /**
         * Inequality operator overload.
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const InorderIterator& other);
    };

    /**
     * Returns an iterator to the beginning of the inorder traversal.
     * @return The iterator to the beginning.
     */
    InorderIterator begin();

    /**
     * Returns an iterator to the end of the inorder traversal.
     * @return The iterator to the end.
     */
    InorderIterator end();

private:
    void insert(Node*& node, int key);
    void remove(Node*& node, int key);
    Node* findMin(Node* node);
    void copyTree(const ThreadedBST& other);
    void destroyTree(Node* node);
};

#endif
