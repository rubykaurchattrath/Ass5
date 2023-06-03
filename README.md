# Ass5
Threaded Binary Search Tree (CSS 342)

Since a binary search tree with N nodes has N + 1 NULL pointers, half the space allocated in a binary search tree for pointer information is wasted. 
Suppose that if a node has a NULL left child, we make its left child pointer link to its inorder predecessor, and if a node has a NULL right child, we make its right child pointer link to its inorder successor. 
This is known as a threaded tree and the extra links are called threads.

Note: Your TBST doesn't need to be Complete or Self-balancing but it requires to be balanced.  
You can achieve that at the point of tree creation by the order you assemble the tree. 

Some extra clarifications: You are welcome to use AVL  or self balancing functions if you like to practice your coding skills. 
However, your tree does not have to have that functionality. 
Instead to achieve balanced tree for input 1....n you can take n/2 to be the root. 
then the mid point of the left subarray (1...n/2) would be the left child and the mid point of the right subarray (n/2.....n) would be the right child of the root. 
You repeat this process until all nodes are inserted. 

Building a Threaded Binary Search Tree
Start with the BST code from the Carrano textbook and augment it so that it correctly implements a ThreadedBST.
You may do this by either modifying the existing code or by creating new classes derived from the TreeNode and BinarySearchTree classes in Carrano. 
Make sure that all of the public methods of BinarySearchTree are either correct as-is (when operating on a ThreadedBST) 
or are replaced (if you are modifying the existing classes) or overridden (if you are creating subclasses) by correct ThreadedBST methods. 
You may use a KeyType of int during your development process.

The threads can be used to make non-recursive inorder, preorder, and postorder traversals (or iterators without internal stacks). 
Implement an Inorder iterator class for your ThreadedBST. Your iterator should not use a stack; instead, it should use the thread links.


To test: 
Implement your ThreadedBST and Inorder traversal as described above. 
Then, write a program that uses these classes as follows. Your program should take a single command line argument: an integer, n, specifying the number of nodes to create in your tree. 
Your program should then create a ThreadedBST with KeyType being int and insert the numbers 1,2,…,n into that container in NON INCREMENTAL order (see above). 
It should then make a copy of that tree and delete all the even numbers from the copy. 
Finally, it should use iterators to perform an inorder traversal of each tree, outputting to cout each node’s contents 
(just put a single space between each node’s contents).

Unlike other assignments no initial code is given to you but you are free to use and/or modify any code from the Carrano textbook for this assignment from under the files.

Hint:  Make sure you think about the following before you start on your implementation:
How can we distinguish threads from real child pointers?
What are the potential advantages of using threaded trees?
What is your implementation? 
What are the sequence of steps you will go through to change the BST implementation to a Threaded BST? 
Which BST methods need to be modified/overridden and which will work as is?
 
