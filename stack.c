#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void printNode(Node * node)
{
	printf("%d", node->id);
}

void printList(Node * top)
{
	Node * temp = NULL;

	for(temp = top; temp!=NULL; temp=temp->next)
	{
		printNode(temp);
		printf(" ");
	}

	if (!top)
		printf("List is empty");

	printf("\n");
}

void push(Node ** top, int element)
{
	Node * newNode = (Node *) malloc(sizeof(Node));

	if(!newNode)
	{
		printf("Allocation error \n");
		exit(1);
	}

	newNode->id = element;
	newNode->next = *top;
	(*top) = newNode;
}

void pop(Node ** top)
{
	Node * deletedElement = *top;

	if (deletedElement)
		*top = (*top)->next;

	free(deletedElement);
}

// int main()
// {
// 	Node * top = NULL;
//
// 	push(&top, 5);		printList(top);
// 	push(&top, 6);		printList(top);
// 	push(&top, 7);		printList(top);
//
// 	pop(&top);		printList(top);
// 	pop(&top);		printList(top);
// 	pop(&top);		printList(top);
//
// 	return 0;
// }
