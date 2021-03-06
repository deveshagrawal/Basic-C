#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define NAME_MAX 100 // Max Size for User's Name

struct node {
  char *name;
  int age;
  struct node *nextName;
  struct node *nextAge;
};

typedef struct node NODE;

/*
 * Define a Structure to hold both the roots
 */
typedef struct {
  struct node *name;
  struct node *age;
} ROOTS;

/*
 * Create a Node from the Parameters Provided
 */
NODE *createNode(char *name, int age){
  NODE *newNode = malloc(sizeof (NODE));
  newNode->age = age;
  newNode->name = malloc(sizeof (char) * strlen(name));
  strcpy(newNode->name, name);

  return newNode;
}

/*
 * Insert a Node by age into the list
 */
NODE *addByAge(NODE *toAdd, NODE *rootAge){
  /*
   * If list is empty, add the first node
   */
  if(rootAge == NULL){
    toAdd->nextAge = rootAge;
    return toAdd;
  }

  /*
   * Search for the position to add the new node at
   */
  NODE *prev, *curr;
  prev = curr = rootAge;
  while((curr != NULL)&&(curr->age < toAdd->age)){
    prev = curr;
    curr = curr->nextAge;
  }

  /*
   * If the node to be added is before the root then add it,
   * modify the root and return the new root
   */
  if(prev != curr){
    prev->nextAge = toAdd;
    toAdd->nextAge = curr;

    return rootAge;
  }
  else{
    toAdd->nextAge = curr;

    return toAdd;
  }
}

/*
 * Insert a Node by Name into the list
 */
NODE *addByName(NODE *toAdd, NODE *rootName){
  /*
   * If list is empty, add the first node
   */
  if(rootName == NULL){
    toAdd->nextAge = rootName;
    return toAdd;
  }

  /*
   * Search for the position to add the new node at
   */
  NODE *prev, *curr;
  prev = curr = rootName;
  while((curr != NULL)&&(strcmp(toAdd->name, curr->name) > 0)){
    prev = curr;
    curr = curr->nextName;
  }

  /*
   * If the node to be added is before the root then add it,
   * modify the root and return the new root
   */
  if(prev != curr){
    prev->nextName = toAdd;
    toAdd->nextName = curr;

    return rootName;
  }
  else{
    toAdd->nextName = curr;

    return toAdd;
  }
}

/*
 * Insert a node into the list
 */
ROOTS addNode(char *name, int age, ROOTS root){
  // Create the node to be added
  NODE *toAdd = createNode(name , age);

  // Add it by age at the correct spot
  root.age = addByAge(toAdd, root.age);

  // Add it by name at the correct spot
  root.name = addByName(toAdd, root.name);
  
  return root;
}

/*
 * Remove a node from the list
 */
ROOTS removeNode(char *name, ROOTS root){
  NODE *prev, *curr, *toRemove;
  int found = 0;

  /*
   * Search for the node to remove
   */
  prev = curr = root.name;
  while(curr != NULL){
    if(strcmp(curr->name, name) == 0){
      found = 1;
      toRemove = curr;
      break;
    }
    prev = curr;
    curr = curr->nextName;
  }

  /*
   * If node not found , then return
   */
  if(found == 0)
    return root;
  
  /*
   * If the node to be removed is the root
   * then modify the root, and return it
   */
  if(toRemove == root.name){
    root.name = root.name->nextName;
  }
  else{
    prev->nextName = curr->nextName;
  }

  /*
   * Now search for the same node in the age list
   */
  prev = curr = root.age;
  while((curr != NULL)&&(curr != toRemove)){
    prev = curr;
    curr = curr->nextAge;
  }

  /*
   * If the node to be removed is the root
   * then modify the root, and return it
   */
  if(toRemove == root.age){
    root.age = root.age->nextAge;
  }
  else{
    prev->nextAge = curr->nextAge;
  }

  /*
   * Free up the structure to be removed
   */
  free(toRemove->name);
  free(toRemove);

  return root;
}

/*
 * Print the list ordered by Age
 */
void printByAge(NODE *rootAge){
  if(rootAge == NULL)
    return;

  printf("Printing List Ordered By Ages:\\n");
  while(rootAge != NULL){
    printf("Name: %s , Age: %d\\n", rootAge->name, rootAge->age);
    rootAge = rootAge->nextAge;
  }
}

/*
 * Print the list ordered by names
 */
void printByName(NODE *rootName){
  if(rootName == NULL)
    return;

  printf("Printing List Ordered By Names:\\n");
  while(rootName != NULL){
    printf("Name: %s , Age: %d\\n", rootName->name, rootName->age);
    rootName = rootName->nextName;
  }
}

/*
 * Function to free up the list
 */
ROOTS freeList(ROOTS root){
  NODE *curr, *next;

  /*
   * Traverse the list by age
   */
  curr = root.age;
  while(curr != NULL){
    // Copy the pointer to the next element
    next = curr->nextAge;

    // Free up the current structure
    free(curr->name);
    free(curr);

    curr = next;
  }

  // set the roots equal to NULL
  root.name = root.age = NULL; 

  return root;
}

int main(){
  ROOTS root = {NULL, NULL}; // Store the roots by name and age
  char name[NAME_MAX];
  int choice, age;
  
  do{
    printf(" 1. Add Structure\\n 2. Remove Structure\\n 3. Print Names\\n 4. Print Ages\\n 5. Exit\\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);
    getc(stdin); // Remove Newline in stdin after Integer Input
    switch(choice){
      case 1:
        printf("Enter Name: ");
        fgets(name, NAME_MAX, stdin);
        name[strlen(name)-1] = '\\0'; // Remove the newline character at the end
        printf("Enter Age: ");
        scanf("%d", &age);

        root = addNode(name, age, root);
        break;
      case 2:
        printf("Enter Name To Remove: ");
        fgets(name, NAME_MAX, stdin);
        name[strlen(name)-1] = '\\0'; // Remove the newline character at the end

        root = removeNode(name, root);
        break;
      case 3:
        printByName(root.name);
        break;
      case 4:
        printByAge(root.age);
        break;
      case 5:
        root = freeList(root);

        printf("Exiting...\\n");
        break;
      default:
        printf("Wrong Choice!!\\n");
    }
  }while(choice != 5);

  return 0;
}
}
 