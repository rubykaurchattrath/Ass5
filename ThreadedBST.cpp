// Jasjeen Khosa and Ruby Kaur
// CSS 342

#include "ThreadedBST.h"

ThreadedBST::ThreadedBST() : root(nullptr) {}

ThreadedBST::ThreadedBST(const ThreadedBST& other) : root(nullptr) {
    copyTree(other);
}

ThreadedBST::~ThreadedBST() {
    destroyTree(root);
}

void ThreadedBST::insert(int key) {
    insert(root, key);
}

void ThreadedBST::remove(int key) {
    remove(root, key);
}

void ThreadedBST::insert(Node*& node, int key) {
    if (node == nullptr) {
        node = new Node(key);
        return;
    }

    if (key < node->key) {
        if (node->left == nullptr) {
            node->left = new Node(key);
            node->left->right = node;
            node->left->isThreaded = true;
        } else {
            insert(node->left, key);
        }
    } else if (key > node->key) {
        if (node->right == nullptr) {
            node->right = new Node(key);
            node->right->left = node;
            node->right->isThreaded = true;
        } else {
            insert(node->right, key);
        }
    }
}

void ThreadedBST::remove(Node*& node, int key) {
    if (node == nullptr) {
        return;
    }

    if (key < node->key) {
        remove(node->left, key);
    } else if (key > node->key) {
        remove(node->right, key);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* minNode = findMin(node->right);
            node->key = minNode->key;
            remove(node->right, minNode->key);
        }
    }
}

ThreadedBST::Node* ThreadedBST::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void ThreadedBST::copyTree(const ThreadedBST& other) {
    if (other.root == nullptr) {
        return;
    }

    insert(other.root->key);

    if (other.root->left != nullptr) {
        copyTreeHelper(root, other.root->left);
    }

    if (other.root->right != nullptr) {
        copyTreeHelper(root, other.root->right);
    }
}

void ThreadedBST::copyTreeHelper(Node* current, Node* other) {
    if (current->key > other->key) {
        if (current->left == nullptr) {
            current->left = new Node(other->key);
            current->left->right = current;
            current->left->isThreaded = true;
        } else {
            copyTreeHelper(current->left, other);
        }
    } else if (current->key < other->key) {
        if (current->right == nullptr) {
            current->right = new Node(other->key);
            current->right->left = current;
            current->right->isThreaded = true;
        } else {
            copyTreeHelper(current->right, other);
        }
    }
}

void ThreadedBST::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        if (!node->isThreaded) {
            destroyTree(node->right);
        }
        delete node;
    }
}

ThreadedBST::InorderIterator::InorderIterator(Node* root) : current(root) {
    if (current != nullptr) {
        while (current->left != nullptr) {
            current = current->left;
        }
    }
}

int ThreadedBST::InorderIterator::operator*() {
    return current->key;
}

ThreadedBST::InorderIterator& ThreadedBST::InorderIterator::operator++() {
    if (current->isThreaded) {
        current = current->right;
    } else {
        current = getNext(current->right);
    }
    return *this;
}

bool ThreadedBST::InorderIterator::operator!=(const InorderIterator& other) {
    return current != other.current;
}

ThreadedBST::InorderIterator ThreadedBST::begin() {
    return InorderIterator(root);
}

ThreadedBST::InorderIterator ThreadedBST::end() {
    return InorderIterator(nullptr);
}

ThreadedBST::Node* ThreadedBST::InorderIterator::getNext(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
