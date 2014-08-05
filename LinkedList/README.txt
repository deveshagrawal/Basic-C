Here is the assignment requirements for a doubly linkedlist:

The Problem

It's possible to have multiple pointers in a linked list and sort the same structures differently using each set of pointers.
For this assignment, create an ordered linked list where each structure contains two pointers. The pointers should order the list based on two different criteria, the name string and the age integer.

The ordering of the structures is done entirely through pointers. The location of the structures in memory does not change.

Method

Use the following structure in your program.
struct node {
   char *name;
   int  age;
   struct node *nextName;
   struct node *nextAge;
};
When you add or remove a structure in the list you will need to update both sets of pointers.
Each name and age pair should be stored in a single structure. Do not create multiple structures containing the same data and do not create two seperate lists. Both lists should remain sorted at all times.

The program should print the following menu when it is started:

1. Add structure
2. Remove structure
3. Print names
4. Print ages
5. Exit
When Add structure is selected then ask the user for the name and age which will be stored in the structure.
Enter name:
Enter age:
The name can contain blank spaces. Create a structure, store the name and age in it, and place the structure in the list so that it is sorted correctly by both name and age.
When Remove structure is selected, ask the user for the name of the record to remove. Search through the list and remove the structure from the list. Update both sets of pointers so the list is correctly sorted after the structure has been removed. Don't forget to free the structure once it has been removed from the list.

When Print names is chosen then print out the list sorted by name. You should be able to step through the list using the nextName pointers and print out each structure. Print both the name and age from one record on a single line.

When Print age is selected then print out the records based on the age sorted list. This is the same as Print names but you traverse the age pointers.

Exit should end the program. Free the structures before the program ends.