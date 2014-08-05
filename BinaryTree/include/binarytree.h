#ifndef BINTREE_GUARD
#define BINTREE_GUARD

#define MAX_SIZE 256
struct BinTree
{
  struct BinTree* left;
  struct BinTree* right;
  struct BinTree* parent;
  char content[MAX_SIZE];
};

typedef struct BinTree Tree;
typedef void * TreeDataTypePtr;
typedef int bool;
enum {false, true};

/************************
createBinTree
this function returns a pointer to a binary tree.  You must send pointers to the compare
and destroy functions when you create the tree.
createBinTree returns null if the memory allocation fails.

An example call to this function is: myTree = createBinTree(&compare, &destroyDataNode);
*********************/

Tree * createBinTree(int (*comparePointer) (TreeDataTypePtr data1, TreeDataTypePtr data2));


/*************************
destroyBinTree

this function destroys the binary tree and all data that is in the tree
when destroy is called.
****************************/

void  destroyBinTree(Tree * toDie);

/****************************
addToTree

This function adds the data item to the tree. The item is added in-order using the
compare function

*******************************/
void addToTree(Tree ** theTree, TreeDataTypePtr data);

/******************************
FindMin

This function find the node with minimum data in the sub-tree of node

****************************/
Tree* FindMin(Tree* node);

/******************************
removeFromTree

This function removes a data item from the tree and adjusts the remaining 
branches of the tree to keep the tree in the proper order

****************************/
Tree* removeFromTree(Tree ** theTree, TreeDataTypePtr data);

/*******************************
printInOrder

This function prints the tree using an inOrder traversal
A sample call to this function is: printInOrder(myTree, &printNode);

where printNode is the function to print a data item
*********************************/
void printInOrder(Tree * theTree, void (* printNode) (TreeDataTypePtr data));

/*******************************
printPreOrder

This function prints the tree using a preOrder traversal
A sample call to this function is: printPreOrder(myTree, &printNode);

where printNode is the function to print a data item
*********************************/
void printPreOrder(Tree * theTree, void (* printNode) (TreeDataTypePtr data));

Tree* Search(Tree * root, TreeDataTypePtr key);

/*********************************
isTreeEmpty

this function returns true if the tree has no data and false otherwise
**********************************/
bool isTreeEmpty(Tree * theTree);

#endif