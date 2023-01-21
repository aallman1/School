#ifndef PLAY_HANGMAN_H
#define PLAY_HANGMAN_H
#include<stdlib.h>
#include<stdio.h>
#include"init_hangman.h"
#include "generic_vector.h"
#include "avl_tree.h"
#include "associative_array.h"
#include"my_string.h"
#include"shared.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<MMsystem.h>
#include<conio.h>


int init_play(GENERIC_VECTOR* pWBankArray);
Status depositKeys(GENERIC_VECTOR hWord_bank, MAP game_map, char guess, int word_length, char* given_letters, int given_letter_count);
void gameLoop(int word_length, int n_guesses, Boolean show_words, GENERIC_VECTOR hVector_words);
char getGuess(char* spent_letters, int spent_letter_count);
GENERIC_VECTOR updateWordBank(MAP game_map);
Boolean key_contains_guess(MY_STRING game_key, char guess, int word_length);
int getWordLength(void);
char getGuess(char* spent_letters, int spent_letter_count);
int getGuesses(void);
void greetings(void);
#endif // !PLAY_HANGMAN_H
