#include "ThreadedBST.h"

int main() {
    ThreadedBST tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    std::cout << "Inorder traversal: ";
    tree.inorderTraversal();

    tree.remove(3);
    tree.remove(6);

    std::cout << "Inorder traversal after deletion: ";
    tree.inorderTraversal();

    return 0;
}
