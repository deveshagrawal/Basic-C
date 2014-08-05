#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"

int (*m_comparePointer) (TreeDataTypePtr data1, TreeDataTypePtr data2);
/************************
createBinTree
this function returns a pointer to a binary tree.  You must send pointers to the compare
and destroy functions when you create the tree.
createBinTree returns null if the memory allocation fails.

An example call to this function is: myTree = createBinTree(&compare, &destroyDataNode);
*********************/
Tree * createBinTree(int (*comparePointer) (TreeDataTypePtr data1, TreeDataTypePtr data2))
{
  m_comparePointer = comparePointer;
  return NULL;
}


/*************************
destroyBinTree

this function destroys the binary tree and all data that is in the tree
when destroy is called.
****************************/
void  destroyBinTree(Tree * toDie)
{ 
  if(toDie)
  {
    destroyBinTree(toDie->left);
    destroyBinTree(toDie->right);
    free(toDie);
  }
}

/****************************
addToTree

This function adds the data item to the tree. The item is added in-order using the
compare function

*******************************/
void addToTree(Tree** root, TreeDataTypePtr data)
{
  int ret = 0;
  Tree* parent = NULL;
  Tree* newNode = NULL;
  Tree* node = (*root);
  while(node)
  {
    ret = (*m_comparePointer)(data, node->content);
    if(ret == 0)
    {
      printf("Identical key %s already exists in the tree!!!\n", (const char*)data);
      return;
    }
    else if(ret < 0)
    {
      parent = node;
      node = node->left;
    }
    else
    {
      parent = node;
      node = node->right;
    }
  }
 
  if(parent)
  {
    newNode = (Tree*)malloc(sizeof(Tree));
    strncpy(newNode->content, data, strlen(data)+1);
    newNode->left = NULL;
    newNode->right = NULL;
    if(ret < 0)
    {
      parent->left = newNode;
    }
    else
    {
      parent->right = newNode;
    }
  }
  else if(!(*root))
  {
    *root = (Tree*)malloc(sizeof(Tree));
    strncpy((*root)->content, data, strlen(data)+1);
    (*root)->left = NULL;
    (*root)->right = NULL;
  }
}

/****************************
Search

This function searches the data item to the tree. 

*******************************/
Tree* Search(Tree * root, TreeDataTypePtr key)
{
  int ret = 0;
  Tree* node = root;
  while(node)
  {
    ret = (*m_comparePointer)(key, node->content);
    if(!ret)
    {
      return node;
    }
    else if(ret < 0)
    {
      node = node->left;
    }
    else
    {
      node = node->right;
    }
  }
  return NULL;
}

/******************************
FindMin

This function find the node with minimum data in the sub-tree of node

****************************/
Tree* FindMin(Tree* node)
{
  while(node->left)
  {
    node = node->left;
  }
  return node;
} 

/******************************
removeFromTree

This function removes a data item from the tree and adjusts the remaining 
branches of the tree to keep the tree in the proper order

****************************/
Tree* removeFromTree(Tree ** root, TreeDataTypePtr data)
{
  int ret;
  Tree* TmpCell = NULL;
  if (*root)
  {
    ret = (*m_comparePointer)(data, (*root)->content);
    if (ret < 0)
      (*root)->left = removeFromTree(&(*root)->left, data);
    else if (ret > 0)
      (*root)->right = removeFromTree(&(*root)->right, data);
    else
    {
      if ((*root)->left && (*root)->right ) {
        TmpCell = FindMin((*root)->right); 
        strncpy((*root)->content, TmpCell->content, strlen(TmpCell->content)+1);
        (*root)->right = removeFromTree(&(*root)->right, (*root)->content);
      } else {
        TmpCell = (*root);
        if ((*root)->left == NULL )
          (*root) = (*root)->right;
        else if ((*root)->right == NULL )
          (*root) = (*root)->left;
        free(TmpCell);
      }
    }
  }
  return *root;
} 

/*******************************
printInOrder

This function prints the tree using an inOrder traversal
A sample call to this function is: printInOrder(myTree, &printNode);

where printNode is the function to print a data item
*********************************/
void printInOrder(Tree * root, void (* printNode) (TreeDataTypePtr data))
{
  Tree* node = root;
  if(node)
  {
    printInOrder(node->left, printNode);
    (*printNode)(node->content);
    printInOrder(node->right, printNode);
  }
}

/*******************************
printPreOrder

This function prints the tree using a preOrder traversal
A sample call to this function is: printPreOrder(myTree, &printNode);

where printNode is the function to print a data item
*********************************/
void printPreOrder(Tree * root, void (* printNode) (TreeDataTypePtr data))
{
  Tree* node = root;
  if(node)
  {
    (*printNode)(node->content);
    printInOrder(node->left, printNode);
    printInOrder(node->right, printNode);
  }
}


/*********************************
isTreeEmpty

this function returns true if the tree has no data and false otherwise
**********************************/
int isTreeEmpty(Tree * root)
{
  return root != NULL;
}