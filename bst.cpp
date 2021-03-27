//bst.cpp
//Laurent, Gilles

#include "bst.h"

BST::BST(){
	m_Tree = NULL; //Make sure the tree starts with a value of null
}

BST::~BST(){
	if (m_Tree) //If the tree exists
		delete m_Tree; //Delete it and all its child nodes recursively
}

int BST::Size(){
	if (m_Tree)
		return m_Tree->Count();
	return 0;
}

void BST::PrintDistance(){
	vector<int> distances;
	if (m_Tree)
		m_Tree->GetDepths(distances); //Get the distances from the tree
	double sum = 0;
	for (auto n : distances)
		sum += n; //Add all the distances
	double average = distances.size() > 0 ? sum / distances.size() : 0; //Calculate the average of all the distances
	cout << "Average distance of nodes to root = " << average << endl; //Print the average
}

//Helper function to print out a vector of node values. Used by PrintDFT and PrintBFT
void PrintNodes(vector<string>& nodes){
	cout << "{";
	for (size_t i = 0; i < nodes.size(); i++){
		cout << nodes[i];
		if (i < nodes.size() - 1)
			cout << ", ";
	}
	cout << "}" << endl;
}

void BST::PrintDFT(){
	//Do the depth first traversal and collect a vector of string values
	vector<string> nodes;
	if (m_Tree)
		m_Tree->DFT(nodes);

	//Print all the string values
	PrintNodes(nodes);
}

void BST::PrintBFT(){
	//Put the root node of the tree into a queue
	queue<TreeNode*> breadth;
	if (m_Tree)
		breadth.push(m_Tree);

	//Use the queue for a breadth first search of the tree adding values into the nodes vector as we go
	//As we visit each node
	vector<string> nodes;
	while (breadth.size() > 0){	//While we have nodes to process in the queue
		//Get the first node in the queue
		TreeNode* n = breadth.front();

		//Remove the first node from the queue
		breadth.pop();

		//Put the node's value into the vector
		nodes.push_back(n->Value);

		//If there is a left node, add the left node to the queue
		if (n->left)
			breadth.push(n->left);

		//If there is a right node, add the right node to the queue
		if (n->right)
			breadth.push(n->right);
	}
	//Print all the nodes
	PrintNodes(nodes);
}

void BST::Insert(string& str){
	//Check to see if the string already exists in the tree
	if (Find(str)){
		//Print an error and return
		cerr << "insert <" << str << "> failed. String already in tree." << endl;
		return;
	}
	if (m_Tree == nullptr){
		//No nodes in the tree yet, just make a new node here for the root of the tree
		m_Tree = new TreeNode();
		m_Tree->Value = str;
	}
	else{
		//Put the string into the tree where it belongs
		m_Tree->Insert(str);
	}
}

bool BST::Find(string& str){
	if(m_Tree == NULL)
		return false; //Cant find the string in an empty tree

	//Check the tree nodes for the string
	return m_Tree->HasValue(str);
}

void BST::Remove(string& str){
	//Check to make sure the tree isnt empty and the string is in the tree
	if (m_Tree == NULL || !Find(str))
		cout << str << " not in tree and cannot be removed." << endl;

	//Find the node and its parent in the tree
	TreeNode* parent;
	TreeNode* n = m_Tree->FindNode(str, NULL, &parent);
	if (n->left && n->right){
		//The complex case.
		//Find the minimum value on the B side of the children
		TreeNode* min = n->right->FindMinimum();

		//Save the value
		string val = min->Value;

		//Now remove min from the tree - it will be one of the easy cases
		Remove(val);

		//Now change n to be the val we just removed
		n->Value = val;

		//Done, dont delete n
		return;
	}
	else if (n->left){
		//Only has Left
		if (parent){
			//The node is either the left node or right node of the parent
			//Replace that pointer with this node's left node effectively removing it from the tree
			if (parent->left == n)
				parent->left = n->left;
			else if (parent->right == n)
				parent->right = n->left;
		}
		else{
			//No parent means this is the root node
			//Make the root node the left node of this node
			m_Tree = n->left;
		}

		//Set the nodes left pointer to null so it doesnt get deleted when we delete this node
		n->left = NULL;
	}
	else if (n->right){
		//Only has Right
		if (parent){
			//The node is either the left node or right node of the parent
			//Replace that pointer with this node's right node effectively removing it from the tree
			if (parent->left == n)
				parent->left = n->right;
			else if (parent->right == n)
				parent->right = n->right;
		}
		else{
			//No parent means this is the root node
			//Make the root node the left node of this node
			m_Tree = n->right;
		}

		//Set the nodes right pointer to null so it doesnt get deleted when we delete this node
		n->right = NULL;
	}
	else{
		//No children
		if (parent){
			//The node is either the left node or right node of the parent
			//Set that pointer to null
			if (parent->left == n)
				parent->left = NULL;
			else if (parent->right == n)
				parent->right = NULL;
		}
		else
			m_Tree = NULL; //No parent means this is the root, we need to null the root here
	}

	//Now actually delete the node
	delete n;
}

int BST::Balanced(){
	if (!m_Tree)
		return 0; //Empty tree is balanced with height 0

	//Calculate the tree balance recursively
	return m_Tree->Balanced();
}

void BST::ReBalance(){
	if (m_Tree){
		//Get the list of values from the tree using a Depth First Traversal
		vector<string> nodes;
		m_Tree->DFT(nodes);

		//Delete the entire tree
		delete m_Tree;
		m_Tree = NULL;

		//Rebuild the tree using the middle of the array as the root
		InsertFromVector(nodes, 0, (int)nodes.size() - 1);
	}
}

void BST::InsertFromVector(vector<string>& elements, int start, int end){
	//Determine the range of indices to be added
	int range = end - start;
	if (range < 0)
		return;	//When range is negative, we know we are done because start > end

	//Find the middle of the range
	int middle = start + (range / 2);

	//Add the value in the middle of the range
	Insert(elements[middle]);

	//Recurse and add elements to the left of the middle
	InsertFromVector(elements, start, middle - 1);

	//Recurse and add elements to the right of the middle
	InsertFromVector(elements, middle + 1, end);
}

TreeNode::TreeNode(){
	//Make sure Left & Right pointers are null to start out
	//This is important, the algorithm uses null values to know where the limits of the tree are
	//If these are not initialized, they start with unpredictable values and may be treated as valid pointers
	left = NULL;
	right = NULL;
}

TreeNode::~TreeNode(){
	//Recursively delete left side
	if (left)
		delete left;

	//Recursively delete right side
	if (right)
		delete right;
}

bool TreeNode::HasValue(string& str){
	//Check if this node is the one
	if (Value == str)
		return true;

	//Look to the left
	if (left && left->HasValue(str))
		return true;

	//Look to the right
	if (right && right->HasValue(str))
		return true;

	//Didn't find it here
	return false;
}

TreeNode* TreeNode::FindNode(string& str, TreeNode* parentIn, TreeNode** parentOut){
	//Check if this is the node we are looking for
	if (Value == str){
		*parentOut = parentIn;	//Store the parent in parentOut
		return this;			//Return this node as the one the caller is looking for
	}

	if (left){
		//Check the left side of the tree using this node as the parent
		TreeNode* n = left->FindNode(str, this, parentOut);
		if (n)
			return n; //If one was found to the left, use it
	}
	if (right){
		//Check the right side of the tree using this node as the parent
		TreeNode* n = right->FindNode(str, this, parentOut);
		if (n)
			return n; //If one was found to the right, use it
	}

	//Didn't find it here
	return NULL;
}

TreeNode* TreeNode::FindMinimum(){
	//Recurse while there is a left node
	if (left)
		return left->FindMinimum();

	//No left node, this node has to be the minimum value in the tree. Return this node
	return this;
}

void TreeNode::Insert(string& str){
	//Compare the string to this node's value
	//Negative means the string comes before this node's value
	//Zero means the string is equal to this node's value (which isn't possible with the current architecture)
	//Positive means the string comes after this node's value
	int cmp = str.compare(Value);
	if (cmp < 0){
		//The string belongs somewhere to the left
		if (left)
			left->Insert(str); //There is a node on the left, pass the string on to that node for insertion
		else{
			//Nothing to the left currently. Put a new node there with this value
			left = new TreeNode();
			left->Value = str;
		}
	}
	else{
		//The string belongs somewhere to the right
		if (right)
			right->Insert(str);
		else{
			right = new TreeNode();
			right->Value = str;
		}
	}
}

int TreeNode::Count(){
	//Count this node
	int count = 1;

	//Count left children recursively
	if (left)
		count += left->Count();

	//Count right children recursively
	if (right)
		count += right->Count();

	//Return the count of this node and the children of this node
	return count;
}

void TreeNode::DFT(vector<string>& nodes){
	//Recurse down the left side of the tree
	if (left)
		left->DFT(nodes);

	//Put this node's value into the vector
	nodes.push_back(Value);

	//Recurse down the right side of the tree
	if (right)
		right->DFT(nodes);
}

void TreeNode::GetDepths(vector<int>& depths, int depth){
	//Put the depth of this node into the vector
	depths.push_back(depth);

	//Recurse down the left side increasing depth as we go down each level
	if (left)
		left->GetDepths(depths, depth + 1);

	//Recurse down the right side increasing depth as we go down each level
	if (right)
		right->GetDepths(depths, depth + 1);
}

int TreeNode::Balanced(){
	//Get the height of the left side, zero if nothing to the left
	int LeftHeight = left ? left->Height() : 0;

	//Get the height of the right side, zero if nothing to the right
	int RightHeight = right ? right->Height() : 0;

	//Check to see if the tree is balanced
	if (abs(LeftHeight - RightHeight) <= 1 && //If the difference between the left height and the right height is less than 1, the tree is balanced
		(!left || left->Balanced() >= 0) &&	 //Check the left side recursively for balance
		(!right || right->Balanced() >= 0)) //Check the right side recursively for balance
		return Height(); //Balanced, return the height of the tree
	return -1; //Not balanced, return -1
}

int TreeNode::Height(){
	//The height of this node is 1 + the biggest height of left and right
	return 1 + max(left ? left->Height() : 0, right ? right->Height() : 0);
}
