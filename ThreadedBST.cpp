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
        // Create a new node and set its key
        node = new Node(key);
        return;
    }

    if (key < node->key) {
        if (node->left == nullptr) {
            // If the left child is nullptr, create a new node as the left child
            node->left = new Node(key);
            // Set the right pointer of the new left child to the current node
            node->left->right = node;
            // Set the threaded flag to indicate that it is a thread
            node->left->isThreaded = true;
        } else {
            // Recursively insert into the left subtree
            insert(node->left, key);
        }
    } else if (key > node->key) {
        if (node->right == nullptr) {
            // If the right child is nullptr, create a new node as the right child
            node->right = new Node(key);
            // Set the left pointer of the new right child to the current node
            node->right->left = node;
            // Set the threaded flag to indicate that it is a thread
            node->right->isThreaded = true;
        } else {
            // Recursively insert into the right subtree
            insert(node->right, key);
        }
    }
}

void ThreadedBST::remove(Node*& node, int key) {
    if (node == nullptr) {
        return;
    }

    if (key < node->key) {
        // Key is smaller, go to the left subtree
        remove(node->left, key);
    } else if (key > node->key) {
        // Key is larger, go to the right subtree
        remove(node->right, key);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            // Case 1: Node has no children
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            // Case 2: Node has only right child
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            // Case 3: Node has only left child
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            // Case 4: Node has both left and right children
            Node* minNode = findMin(node->right);
            node->key = minNode->key;
            remove(node->right, minNode->key);
        }
    }
}

ThreadedBST::Node* ThreadedBST::findMin(Node* node) {
    while (node->left != nullptr) {
        // Traverse to the leftmost node in the subtree
        node = node->left;
    }
    return node;
}

void ThreadedBST::copyTree(const ThreadedBST& other) {
    if (other.root == nullptr) {
        return;
    }

    // Insert the root node of the other tree
    insert(other.root->key);

    if (other.root->left != nullptr) {
        // Recursively insert nodes from the left subtree of the other tree
        copyTreeHelper(root, other.root->left);
    }

    if (other.root->right != nullptr) {
        // Recursively insert nodes from the right subtree of the other tree
        copyTreeHelper(root, other.root->right);
    }
}

void ThreadedBST::copyTreeHelper(Node* current, Node* other) {
    if (current->key > other->key) {
        if (current->left == nullptr) {
            // Create a new node as the left child and link the right pointer
            current->left = new Node(other->key);
            current->left->right = current;
            current->left->isThreaded = true;
        } else {
            // Recursively insert into the left subtree
            copyTreeHelper(current->left, other);
        }
    } else if (current->key < other->key) {
        if (current->right == nullptr) {
            // Create a new node as the right child and link the left pointer
            current->right = new Node(other->key);
            current->right->left = current;
            current->right->isThreaded = true;
        } else {
            // Recursively insert into the right subtree
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
        // Move to the leftmost node in the tree
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
        // If it is a thread, move to the right node
        current = current->right;
    } else {
        // Otherwise, move to the next node in inorder traversal
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

    // Traverse to the leftmost node in the subtree
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
