# C++ Binary Search Tree

---
### Overview
This program takes in various inputs to populate and search through a binary search tree data structure, and is also able to handle any illegal input commands. Input commands include: insert, size, distance, find, print, breadth, balanced, and rebalance.


> The goal of this program is to practice implementing the Binary Tree data structure, write recursive functions, parse input commands, and practice using the STL vector and queue in C++.
&nbsp;
---
### Input Commands
Command | Argument | Action | Potential Errors
------ | ------ | ------ | ------
echo | String | Write the string to standard output. Does not insert into tree. | None
insert | String | Insert the given string into the binary search tree. The tree must maintain the BST property after insert. | Prints error if string already in tree.
size | None | Print the number of elements (aka number of nodes) in the tree. | None (0 if tree is empty)
find | String | Prints if the given string is or is not in the tree. | None
print | None | Use a depth-first traversal (dft) to print all elements in the tree. | None (Prints empty brackets if tree is empty)
breadth | None | Use a breadth-first traversal (bft) to print all elements in the tree. | None (Prints empty brackets if tree is empty)
distance | None | Prints the average distance nodes are from the root. The root’s distance is 0. The root’s children are distance == 1, the root’s grandchildren are distance == 2, and so on. Calculates the distance for ALL nodes and then takes the average. | None (Prints 0 if there are 0 or 1 nodes in the tree)
balanced | None | Prints if the tree is balanced or not balanced (this type of balanced is called “height-balanced”. | None (Balanced if empty)
rebalance | None | Modify the tree so it is balanced. | None
---
### Sample Input/Output
Input | Output
------ | ------
insert Monday  | None
insert Tuesday   | None  
insert Wednesday   | None  
insert Thursday   | None  
insert Friday  | None  
echo Number of nodes in the tree:   | Number of nodes in the tree: 
size | 5
distance | Average distance of nodes to root = 1.2
find Monday | <Monday> is in tree.
find Sunday | <Sunday> is not in tree.
echo The nodes in depth-first order: | The nodes in depth-first order:
print | {Friday, Monday, Thursday, Tuesday, Wednesday}
echo The nodes in breadth-first order: | The nodes in breadth-first order:
breadth | {Monday, Friday, Tuesday, Thursday, Wednesday}
balanced | Tree is balanced.
insert Saturday | None
balanced | Tree is not balanced.
print | {Friday, Monday, Saturday, Thursday, Tuesday, Wednesday}
breadth | {Monday, Friday, Tuesday, Thursday, Wednesday, Saturday}
rebalance | None
balanced | Tree is balanced.
print | {Friday, Monday, Saturday, Thursday, Tuesday, Wednesday}
breadth | {Saturday, Friday, Tuesday, Monday, Thursday, Wednesday}
distance | Average distance of nodes to root = 1.5
---
### Installation
Clone my repo:
```bash
git clone https://github.com/glaurent96/CPP-BST.git
```
---
### Compile and run the program
Compile the program:
```bash
cd CPP-BST
make
```
Run the created executable file:
```bash
./bst
```
Type in your input and then press Ctrl-C to exit the program.

---
### Run Automated Tests
Double click on tests.zip file to unzip the tests folder.
&nbsp;
Run executable testing script:
```bash
./run_tests bst
```

>The script will create a results folder with all the program outputs generated from the tests. Check the tests folder if any tests fail to compare with expected output.

Run vimDiffError(vde) executable followed by test number to compare your error output with test error outputs:
```bash
./vde 40
```
---
