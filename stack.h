#include <stdio.h>

// A node in the linked list
typedef struct SingleNode
{
        int id;
        struct SingleNode * next;
} Node;

// Print the data in the node of a stack
void printNode(Node * node);

// Inserts a given element at the beginning of stack
void push(Node ** top, int element);

// Deletes the first element of stack and returns pointer to the deleted node
void pop(Node ** top);

// prints all the elements in stack
void printList (Node * top);
