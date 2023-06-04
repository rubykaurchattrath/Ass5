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


    // Test inserting duplicate keys
    tree.insert(7); // Already present, should be ignored
    cout << "Displaying the tree with duplicate keys: ";
    tree.display();
    cout << "Expected: 2 3 5 6 7 8" << endl;

    // Remove a key that is not in the tree
    tree.remove(9); // Not present, should have no effect
    cout << "Displaying the tree after removing a non-existent key: ";
    tree.display();
    cout << "Expected: 2 3 5 6 7 8" << endl;

    return 0;
    
}


