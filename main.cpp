#include "bst.hpp"

/*
I was not able to get the graphviz extension to work, but I'm sure you will find that the BST is properly implemented

Returning "-1" signifies that a Node does not exist

Functions of the Tree
Call .add(key) to add given Node (via key) into the Tree
Call .remove(key) to remove given Node (via key) from the Tree
Call .size() to return(int) the size of the Tree
Call .exists(key) to check wether a given node (via key) exists or not (bool)
Call .root() to return(Node*) root of Tree
Call .printRoot() to return(int) value of Root
Call .minData(root)/.maxData(root) to return(int) min/max value of Tree
Call .predecessor(key) to return(int) the value of the next lesser value node
Call .successor(key) to return(int) the value of the next greater value node



*/

int main() {

    Bst<int> Tree;
    
    Tree.add(12);
    Tree.add(5);
    Tree.add(20);
    Tree.add(2);
    Tree.add(14);
    Tree.add(8);

    std::cout << "The Tree has " << Tree.size() << " Nodes." <<std::endl;
    std::cout << "Does 8 exist? (0/1) : " << Tree.exists(8) << std::endl;

    std::cout << "---Removing 8---" << std::endl;
    Tree.remove(8);

    std::cout << "Does 8 exist? (0/1) : " << Tree.exists(8) << std::endl;
    std::cout << "The Tree has " << Tree.size() << " Nodes." <<std::endl;
    
    TreeNode<int>* root = Tree.getRoot();

    std::cout << "Root of the Tree is: " << Tree.printRoot() << std::endl;

    std::cout << "Maximum of the Tree is: " << Tree.maxData(root) << std::endl;
    std::cout << "Minimum of the Tree is: " << Tree.minData(root) << std::endl;

    std::cout << "The Successor of 12 is: " << Tree.successor(12) << std::endl;
    std::cout << "The Predecessor of 2 is: " << Tree.predecessor(2) << std::endl;
};