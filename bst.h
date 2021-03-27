//bst.h
//Laurent, Gilles

#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class TreeNode{
public:
	//Member variables
	TreeNode* left;	//Pointer to the left side of the tree
	TreeNode* right; //Pointer to the right side of the tree
	string Value; //String value for this node

	TreeNode();	//Constructor
	~TreeNode(); //Destructor

	//Recursive function to check if this tree contains the specified string
	//string& str - INPUT reference to a string value to search for
	//return bool - true if the string exists in this node or nodes below it
	bool HasValue(string& str);

	//Insert a node of value str into the tree
	//string& str - INPUT reference to a string value to insert
	void Insert(string& str);

	//Recursive function to count the number of nodes in the tree
	//return int - the number of nodes in this tree
	int Count();

	//Recursive function to perform a Depth First Traversal
	//Nodes are added to the vector starting from the far left of the tree to the far right
	//vector<string>& nodes - OUTPUT vector containing depth ordered values from the tree
	void DFT(vector<string>& nodes);

	//Recursive function to collect the depth values of all the nodes in the tree
	//Depth is the distance of a node from the root of the tree
	//vector<int>& depths - OUTPUT vector of depth values for the nodes of this tree
	//depth - INPUT the depth of the level. this is used in the recursion, when using this on the root node, depth of 0 should be speficied
	void GetDepths(vector<int>& depths, int depth = 0);

	//Recursive function to check if the tree is balanced or not
	//A binary tree is balanced if the height difference between the left and right sides is less than or equal to 1
	//return int - -1 if the tree is unbalanced or the maximum height of the tree if it is balanced.
	int Balanced();

	//Recursive function to return the height of the tree
	//The height is the number of levels below the root
	//return int - the number of levels below this node
	int Height();

	//Recursive function to find a node and its parent
	//Used by remove
	//string& str - INPUT reference to a string value to search for
	//TreeNode* parentIn - INPUT the parent passed from above. When calling this on the root node, pass nullptr
	//TreeNode** parentOut - OUTPUT pointer to a TreeNode* variable that will hold the pointer to the found node's parent
	//return TreeNode* - pointer to the node with Value of str
	TreeNode* FindNode(string& str, TreeNode* parentIn, TreeNode** parentOut);

	//Recursive function to find the least value in the tree
	//Used by remove
	//return TreeNode* - pointer to the node in the tree with the lowest value
	TreeNode* FindMinimum();
};

class BST{
public:
	BST(); //Constructor
	~BST(); //Destructor

	//Returns the total number of nodes in the tree
	//return int - the number of nodes in the tree
	int Size();

	//Prints the average distance of nodes in the tree to stdout
	void PrintDistance();

	//Prints out all nodes of the tree using a Depth First Traversal
	void PrintDFT();

	//Prints out all nodes of the tree using a Breadth First Traversal
	void PrintBFT();

	//Insert a string into the tree. Prints an error if it already exists
	void Insert(string& str);

	//Check to see if a string exists in the tree or not
	//return bool - true if the string is in the tree
	bool Find(string& str);

	//Remove the specified value from the tree. prints an error if its not in the tree
	void Remove(string& str);

	//Check to see if the tree is balanced
	//return int - -1 if the tree is not balanced, the height of the tree if it is balanced
	int Balanced();

	//Re-arrange nodes in the tree to make it a balanced tree
	void ReBalance();

private:
	void InsertFromVector(vector<string>& elements, int start, int end);
	TreeNode* m_Tree;
};

#endif
