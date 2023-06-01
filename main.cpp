// Jasjeen Khosa and Ruby Kaur
// CSS 342

#include <iostream>
#include "ThreadedBST.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./program_name <number_of_nodes>" << endl;
        return 1;
    }

    int n = stoi(argv[1]);

    ThreadedBST bst;
    for (int i = n; i >= 1; i--) {
        bst.insert(i);
    }

    ThreadedBST copy = bst;
    ThreadedBST::InorderIterator bstIterator = bst.begin();
    ThreadedBST::InorderIterator copyIterator = copy.begin();

    while (bstIterator != bst.end()) {
        cout << *bstIterator << " ";
        ++bstIterator;
    }
    std::cout << std::endl;

    while (copyIterator != copy.end()) {
        cout << *copyIterator << " ";
        ++copyIterator;
    }
    cout << endl;

    return 0;
}

