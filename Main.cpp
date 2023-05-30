// Jasjeen Khosa and Ruby Kaur
// CSS 342

#include <iostream>
#include <cassert>
#include "ThreadedBST.h"

using namespace std;

// Method to test the ThreadedBST functionality
void testThreadedBST(int n) {
    ThreadedBST<int> bst;

    // Inserting numbers 1 to n in non-incremental order
    for (int i = n; i >= 1; i--) {
        bst.insert(i);
    }

    // Asserting the size of the tree
    assert(bst.size() == n);

    // Making a copy of the tree
    ThreadedBST<int> bstCopy(bst);

    // Deleting even numbers from the copy
    for (int i = 2; i <= n; i += 2) {
        bstCopy.remove(i);
    }

    // Asserting the size of the copy after removals
    assert(bstCopy.size() == (n + 1) / 2);

    // Asserting that the original tree is unchanged
    assert(bst.size() == n);

    // Asserting the inorder traversal of the original tree
    vector<int> expectedOriginalTraversal;
    for (int i = 1; i <= n; i++) {
        expectedOriginalTraversal.push_back(i);
    }
    vector<int> actualOriginalTraversal;
    for (auto it = bst.begin(); it != bst.end(); ++it) {
        actualOriginalTraversal.push_back(*it);
    }
    assert(expectedOriginalTraversal == actualOriginalTraversal);

    // Asserting the inorder traversal of the modified tree
    vector<int> expectedModifiedTraversal;
    for (int i = 1; i <= n; i += 2) {
        expectedModifiedTraversal.push_back(i);
    }
    vector<int> actualModifiedTraversal;
    for (auto it = bstCopy.begin(); it != bstCopy.end(); ++it) {
        actualModifiedTraversal.push_back(*it);
    }
    assert(expectedModifiedTraversal == actualModifiedTraversal);

    // Printing the inorder traversal of the original tree
    cout << "Inorder traversal of original tree: ";
    for (auto it = bst.begin(); it != bst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Printing the inorder traversal of the modified tree
    cout << "Inorder traversal of modified tree: ";
    for (auto it = bstCopy.begin(); it != bstCopy.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}
