#ifndef INIT_HANGMAN_H
#define INIT_HANGMAN_H
#include<stdio.h>
#include<stdlib.h>
#include<crtdbg.h>
#include"shared.h"
#include"my_string.h"
#include"generic_vector.h"


GENERIC_VECTOR* getFullWordBank(FILE* pfDictionary);
#endif // !INIT_HANGMAN_H
