#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

struct node;
typedef struct node Node;
struct node
{
	char data;
	Node* next;
};


struct stack;
typedef struct stack Stack;

struct stack
{
	Node* top;
};

STACK init_stack(void)
{
	Stack* pStack = malloc(sizeof(Stack));
	if (pStack != NULL)
	{
		pStack->top = NULL;
	}
	return (STACK)pStack;
}

Status stack_insert(STACK hStack, char char_entered) //TAKES STACK handle
{
	Node* temp = (Node*)malloc(sizeof(Node));
	Stack* pStack = (Stack*)hStack;
	if (temp == NULL)
	{
		return FAILURE;
	}
	temp->data = char_entered;
	temp->next = pStack->top;
	pStack->top = temp;
	return SUCCESS;

}


Status stack_pop(STACK hStack)//TAKES STACK handle
{
	Stack* pStack = (Stack*)hStack;
	Node* temp;
	if (pStack->top == NULL)
	{
		return FAILURE;
	}

	temp = pStack->top;
	pStack->top = pStack->top->next;
	free(temp);
	return SUCCESS;
}


char get_top(STACK hStack)//TAKES STACK HANDLE (STACK)
{
	Stack* pStack = (Stack*)hStack;
	return pStack->top->data;
}


Boolean stack_empty(STACK hStack)//TAKES STACK HANDLE (STACK)
{
	Stack* pStack = (Stack*)hStack;
	if (pStack->top == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


void destroy_stack(STACK* phStack) //TAKES STACK*
{
	Stack* pStack = (Stack*)*(phStack);
	while (pStack->top != NULL)
	{
		Node* temp = pStack->top;
		pStack->top = pStack->top->next;
		free(temp);
	}
	free(pStack);
	*phStack = NULL;
}