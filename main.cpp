// Jasjeen Khosa and Ruby Kaur
// CSS 342

#include "ThreadedBST.h"
#include <iostream>
using namespace std;

 int main() {
    ThreadedBST tree;

    // Insert some keys into the tree
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    // Display the tree
    cout << "Displaying the tree: ";
    tree.display();
    cout << "Expected: 2 3 4 5 6 7 8" << endl;

    // Perform inorder traversal
    cout << "Inorder traversal: ";
    tree.inorder();
    cout << "Expected: 2 3 4 5 6 7 8" << endl;

    // Remove a key from the tree
    tree.remove(4);

    // Display the updated tree
    cout << "Displaying the updated tree: ";
    tree.display();
    cout << "Expected: 2 3 5 6 7 8" << endl;

    // Perform inorder traversal again
    cout << "Inorder traversal: ";
    tree.inorder();
    cout << "Expected: 2 3 5 6 7 8" << endl;

    // Test copying the tree
    ThreadedBST treeCopy(tree);
    cout << "Displaying the copied tree: ";
    treeCopy.display();
    cout << "Expected: 2 3 5 6 7 8" << endl;

    // Test removing even numbers from the copied tree
    treeCopy.remove(2);
    treeCopy.remove(6);
    cout << "Displaying the copied tree after removing even numbers: ";
    treeCopy.display();
    cout << "Expected: 3 5 7 8" << endl;

    // Perform inorder traversal on the copied tree
    cout << "Inorder traversal of the copied tree: ";
    treeCopy.inorder();
    cout << "Expected: 3 5 7 8" << endl;

    return 0;
}



