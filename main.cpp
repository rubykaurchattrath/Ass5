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

// Test Method 1: Test basic functionality and insertion order
void test1() {
    cout << "Test 1" << endl;
    ThreadedBST<int> bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(20);

    cout << "Inorder traversal: ";
    for (auto it = bst.begin(); it != bst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

// Test Method 2: Test removal of nodes
void test2() {
    cout << "Test 2" << endl;
    ThreadedBST<int> bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(20);

    bst.remove(7);
    bst.remove(15);

    cout << "Inorder traversal: ";
    for (auto it = bst.begin(); it != bst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

// Test Method 3: Test finding nodes
void test3() {
    cout << "Test 3" << endl;
    ThreadedBST<int> bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(20);

    auto it1 = bst.find(7);
    if (it1 != bst.end()) {
        cout << "Found: " << *it1 << endl;
    } else {
        cout << "Not Found" << endl;
    }

    auto it2 = bst.find(8);
    if (it2 != bst.end()) {
        cout << "Found: " << *it2 << endl;
    } else {
        cout << "Not Found" << endl;
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: ./program_name <number_of_nodes>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);

    test1();
    test2();
    test3();

    testThreadedBST(n);

    return 0;
}
