#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"
/* file name array */
const char* fileNames[3] = {"abc", "efg", "hij"};
/* size of file name array */
int len = sizeof(fileNames) / sizeof(const char*);
/* printNode2 function */
void printNode2(TreeDataTypePtr data);
/* compare lexcically function */
int compareLexically2(TreeDataTypePtr data1, TreeDataTypePtr data2);

int main(int argc, char** argv)
{
  int i = 0;
  Tree* root = NULL;
  
  printf("Welcome to BinaryTree TestCases\n");
  /* Create binary tree */
  root = createBinTree(&compareLexically2);
  for(i = 0; i < len; ++i)
  {
    /* Add node with filenames into binary tree */
    addToTree(&root, (TreeDataTypePtr)fileNames[i]);
  }
  /* Print binary tree nodes by in order */
  printInOrder(root, &printNode2);
  /* Destroy binary tree */
  destroyBinTree(root); /* Destroy tree */
  return 0;
}
/* Compare binary tree node by lexically */
int compareLexically2(TreeDataTypePtr data1, TreeDataTypePtr data2)
{
  return strcmp((const char*)data1, (const char*)data2);
}
/* Print node */
void printNode2(TreeDataTypePtr data)
{
  printf("Filename: %s\n", (const char*)data);
}