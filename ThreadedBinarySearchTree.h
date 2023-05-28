#ifndef THREADED_BINARY_SEARCH_TREE_H
#define THREADED_BINARY_SEARCH_TREE_H

template <class KeyType>
class ThreadedBST {
public:
    KeyType key;
    ThreadedBST* left;
    ThreadedBST* right;
    bool leftThread;
    bool rightThread;

    ThreadedBST(const KeyType& newKey)
        : key(newKey), left(nullptr), right(nullptr),
          leftThread(false), rightThread(false) {}
};

template <class KeyType>
class ThreadedBST {
private:
    ThreadedBST<KeyType>* root;

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
        ThreadedBST<KeyType>* current;

        ThreadedBST<KeyType>* findLeftMost(ThreadedBST<KeyType>* node);
        ThreadedBST<KeyType>* findRightMost(ThreadedBST<KeyType>* node);

    public:
        InorderIterator(ThreadedBST<KeyType>* root);

        KeyType operator*();
        InorderIterator& operator++();
        bool operator==(const InorderIterator& other) const;
        bool operator!=(const InorderIterator& other) const;
    };

    InorderIterator begin();
    InorderIterator end();

private:
    void clear(ThreadedBST<KeyType>* node);
    ThreadedBST<KeyType>* insert(ThreadedBST<KeyType>* node, const KeyType& key);
    ThreadedBST<KeyType>* remove(ThreadedBST<KeyType>* node, const KeyType& key);
};

#endif // THREADED_BINARY_SEARCH_TREE_H
