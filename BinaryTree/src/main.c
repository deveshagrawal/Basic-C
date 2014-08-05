#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include "binarytree.h"

/* file names to store the searched path */
char filename[256][256];
/* Number of path */
int len = 0;

/* Search all files */
int trave_dir(char* path, int depth);
/* Build binary tree by alphabetically */
int compareLexically(TreeDataTypePtr data1, TreeDataTypePtr data2);
/* Print node */
void printNode(TreeDataTypePtr data);

int main(int argc, char** argv)
{
  int i = 0;
  int cmd = -1;
  char buf1[256] = {0};
  char buf2[256] = {0};
  Tree* root = NULL;
  Tree* node = NULL;
  
  /* Check argument parameters */
  if(argc < 2)
  {
    printf("please specify a directory as argument parameter!!!\n");
    return -1;
  }
  
  printf("Welcome to BinaryTree FileManager\n");
  /* Search files under directory argv[1]*/
  trave_dir(argv[1], 0);
  /* Create binary tree */
  root = createBinTree(&compareLexically);
  for(i = 0; i < len; ++i)
  {
    addToTree(&root, filename[i]);
  }
  /* Show file manager menu */
  do
  {
    printf("---------Menu---------\n");
    printf("Display: 1\n");
    printf("Delete: 2\n");
    printf("Rename: 3\n");
    printf("Move: 4\n");
    printf("Exit: 5\n");
    if(!fscanf(stdin, "%d", &cmd))
    {
      printf("Read error!!!\n");
      break;
    }
    /* Show file name in order */
    if(cmd == 1)
    {
      printInOrder(root, &printNode);
    }
    else if(cmd == 2)
    {
      /* Enter to be deleted file name */
      printf("Please enter the file path to delete\n");
      memset(buf1, 0, sizeof(char)*256);
      if(!fscanf(stdin, "%s", buf1))
      {
        printf("Read error!!!\n");
        break;
      }
      if(strlen(buf1) > 0 && buf1[strlen(buf1)-1] == '\n')
      {
        buf1[strlen(buf1)-1] = '\0';
      }
      
      if(remove(buf1) != 0)
      {
        printf("Delete file %s error!!!\n", buf1);
      }
      else
      {
        removeFromTree(&root, buf1);
      }
    }
    else if(cmd == 3 || cmd == 4)
    {
      /* Enter to be renamed or moved original file name */
      if(cmd == 3)
      {
        printf("Please enter the original file path to rename\n");
      }
      else
      {
        printf("Please enter the original file path to move\n");
      }
      memset(buf1, 0, sizeof(char)*256);
      if(!fscanf(stdin, "%s", buf1))
      {
        printf("Read error!!!\n");
        break;
      }
      if(strlen(buf1) > 0 && buf1[strlen(buf1)-1] == '\n')
      {
        buf1[strlen(buf1)-1] = '\0';
      }
      /* Enter to be renamed or moved target file name */
      if(cmd == 3)
      {
        printf("Please enter the target file path to rename\n");
      }
      else
      {
        printf("Please enter the target file path to move\n");
      }
      memset(buf2, 0, sizeof(char)*256);
      if(!fscanf(stdin, "%s", buf2))
      {
        printf("Read error!!!\n");
        break;
      }
      if(strlen(buf2) > 0 && buf2[strlen(buf2)-1] == '\n')
      {
        buf2[strlen(buf2)-1] = '\0';
      }
      
      node = Search(root, buf1);
      if(!node)
      {
        printf("Original file path %s does not exist\n", buf1);
      }
      else
      {
        if(rename(buf1, buf2))
        {
          if(cmd == 3)
            printf("Rename file from %s to %s error!!!\n", buf1, buf2);
          else
            printf("Move file from %s to %s error!!!\n", buf1, buf2);
        }
        else
        {
          strncpy(node->content, buf2, strlen(buf2)+1);
        }
      }
    }
  }
  while(cmd != 5); /* Terminate when exit command entered */ 
  
  destroyBinTree(root); /* Destroy tree */
  return 0;
}

int trave_dir(char* path, int depth)
{
  DIR *d = NULL;
  struct dirent *file;
  struct stat sb;  
  char buf[256] = {0};
  
  if(!(d = opendir(path)))
  {
    printf("error opendir %s!!!\n", path);
    return -1;
  }
  
  while((file = readdir(d)) != NULL)
  {
    if(!strncmp(file->d_name, ".", 1) || !strncmp(file->d_name, "..", 1))
      continue;
    
    memset(buf, 0, sizeof(char)*256);
    strncpy(buf, path, strlen(path)+1);
    strcat(buf, "/");
    strcat(buf, file->d_name);
    
    strcpy(filename[len++], buf);
    
    if(stat(file->d_name, &sb) >= 0 && S_ISDIR(sb.st_mode))
    {
      memset(buf, 0, sizeof(char)*256);
      trave_dir(buf, depth + 1);
    }
  }
  closedir(d);
  
  return 0;
}

int compareLexically(TreeDataTypePtr data1, TreeDataTypePtr data2)
{
  return strcmp((const char*)data1, (const char*)data2);
}

void printNode(TreeDataTypePtr data)
{
  printf("Filename: %s\n", (const char*)data);
}