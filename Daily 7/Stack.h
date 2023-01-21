#ifndef STACK_H
#define STACK_H
typedef void* STACK;
#include "status.h"
#include "boolean.h"

STACK init_stack(void);
Status stack_insert(STACK hStack, char char_entered); //TAKES STACK handle
Status stack_pop(STACK hStack);//TAKES STACK handle
char get_top(STACK hStack);//TAKES STACK HANDLE (STACK)
Boolean stack_empty(STACK hStack);//TAKES STACK HANDLE (STACK)
void destroy_stack(STACK* phStack); //TAKES STACK*

#endif // !STACK_H