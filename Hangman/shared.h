#ifndef SHARED_H
#define SHARED_H
#include<stdlib.h>
#include<stdio.h>
enum BOOLEAN { FALSE, TRUE };
typedef enum BOOLEAN Boolean;
enum STATUS { FAILURE, SUCCESS };
typedef enum STATUS Status;
typedef void* Item;
#define MAX_WORD_LENGTH 29
enum MODE { LOCAL, GLOBAL };
typedef enum MODE Mode;
#endif // !SHARED_H