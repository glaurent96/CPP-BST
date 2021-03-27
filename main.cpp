//main.cpp
//Laurent, Gilles

#include "bst.h"

//Read a string of arguments from stdin
string GetArgument(){
    string param; //Get the remaining text on the line
    getline(cin, param);
    while (isspace(param[0])) //Remove whitespace from the front of the string
        param.erase(0, 1);
    return param; //Return the arguments to the caller
}

int main(){
    BST bst; //Initialize the binary tree
    string command; //Loop until we run out of commands
    while (true){
        if(!(cin >> command)) //Read a command from stdin
            break; //If cin returns false, exit in automated mode
        if(command == "echo")
            cout << GetArgument() << endl; //Print the argument to stdout
        else if (command == "insert"){
            string arg = GetArgument();
            bst.Insert(arg); //Insert the argument into the tree
        }
        else if (command == "size")
            cout << bst.Size() << endl; //Print the size of the tree to stdout
        else if (command == "find"){
            string arg = GetArgument();
            bool found = bst.Find(arg); //Find the argument in tree
            cout << "<" << arg << "> is ";
            if (!found)
                cout << "not ";
                cout << "in tree." << endl;
        }
        else if (command == "print")
            bst.PrintDFT(); //Print the tree using Depth First Traversal
        else if (command == "breadth")
            bst.PrintBFT(); //Print the tree using Breadth First Traversal
        else if (command == "distance")
            bst.PrintDistance(); //Print the average distance of the tree
        else if (command == "balanced"){
            cout << "Tree is ";
            if (bst.Balanced() < 0) //Check if the tree is balanced
            cout << "not ";
            cout << "balanced." << endl;
        }
        else if (command == "rebalance")
            bst.ReBalance(); //Rebalance the tree
        else if (command == "remove"){
            string arg = GetArgument();
            bst.Remove(arg); //Remove the node with value arg from the tree
        }
        else if (command == "exit")
            break; //Allow user to exit in interactive mode
        else{
            GetArgument();
            cerr << "Illegal command: " << command << endl;
        }
    }
    return 0;
}
