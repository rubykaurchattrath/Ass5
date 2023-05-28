#ifndef THREADED_BINARY_SEARCH_TREE_H
#define THREADED_BINARY_SEARCH_TREE_H

template <class KeyType>
class ThreadedBSTNode {
public:
    KeyType key;
    ThreadedBSTNode* left;
    ThreadedBSTNode* right;
    bool leftThread;
    bool rightThread;

    ThreadedBSTNode(const KeyType& newKey)
        : key(newKey), left(nullptr), right(nullptr),
          leftThread(false), rightThread(false) {}
};

template <class KeyType>
class ThreadedBST {
private:
    ThreadedBSTNode<KeyType>* root;

public:
    ThreadedBST() : root(nullptr) {}
    ~ThreadedBST() { clear(); }

    bool isEmpty() const { return root == nullptr; }
    void clear() { clear(root); root = nullptr; }

    void insert(const KeyType& key);
    bool remove(const KeyType& key);

    // Inorder traversal iterator
    class InorderIterator {
    private:
        ThreadedBSTNode<KeyType>* current;

        ThreadedBSTNode<KeyType>* findLeftMost(ThreadedBSTNode<KeyType>* node);
        ThreadedBSTNode<KeyType>* findRightMost(ThreadedBSTNode<KeyType>* node);

    public:
        InorderIterator(ThreadedBSTNode<KeyType>* root);

        KeyType operator*();
        InorderIterator& operator++();
        bool operator==(const InorderIterator& other) const;
        bool operator!=(const InorderIterator& other) const;
    };

    InorderIterator begin();
    InorderIterator end();

private:
    void clear(ThreadedBSTNode<KeyType>* node);
    ThreadedBSTNode<KeyType>* insert(ThreadedBSTNode<KeyType>* node, const KeyType& key);
    ThreadedBSTNode<KeyType>* remove(ThreadedBSTNode<KeyType>* node, const KeyType& key);
};

#endif // THREADED_BINARY_SEARCH_TREE_H
