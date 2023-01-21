#include "play_hangman.h"
#include<conio.h>
#include<curses.h>


MY_STRING return_other_word(GENERIC_VECTOR hVector_words, char guess, int word_length);
Boolean check_win(MY_STRING game_key, int word_length);
void classic_stub(void);
void animated_start(void);
int init_play(GENERIC_VECTOR* pWBankArray)
{
	
	PlaySound(TEXT("music\\main_castle.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	animated_start();
	PlaySound(NULL, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	PlaySound(TEXT("music\\play_theme.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	greetings();
	do
	{
		
		int word_length = getWordLength();
		clear();
		endwin();
		int n_guesses = getGuesses();
		clear();
		endwin();
		clear_keyboard_buffer();
		Boolean show_words = showWordCount();
		clear();
		endwin();
		
		clear_keyboard_buffer();
		gameLoop(word_length, n_guesses, show_words, generic_vector(pWBankArray[word_length - 1]));

	}while (play_again());
	
	
	for (int i = 0; i < MAX_WORD_LENGTH; i++)
	{
		generic_vector_destroy(&(pWBankArray[i]));
	}
	free(pWBankArray);
}

void animated_start(void)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	WINDOW* start = initscr();
	printw("\e[?25l");
	curs_set(0);

	box(start, 240, 240);
	move(5, 10);

	char hangman_04[] = "\t\t         ____              _ \n";
	char hangman_1[] = ("\t\t	  _	|  __| __    __(?)| |\n");
	char hangman_2[] = ("\t\t	 | |    | |__  \\ \\  / /|_|| |  \n");
	char hangman_3[] = ("\t\t	 | |__  | _ _|__\\ \\/ /_|_||_|_  ___     _ _  __\n");
	char hangman_4[] = ("\t\t	 | '_  \\ / _` | '\\__/_ _` |'  `'    \\/  ` | '_ \\\n");
	char hangman_5[] = ("\t\t	 | |  | | (_| | | | | (__ | | | | | | (_| | | | |\n");
	char hangman_6[] = ("\t\t    \t |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\____|_| |_|\n");
	char hangman_7[] = ("\t\t	 		    __/  |\n");
	char hangman_8[] = ("\t\t	 	           |____/\n");

	char* title[9] = { hangman_04, hangman_1, hangman_2, hangman_3, hangman_4,hangman_5, hangman_6,hangman_7, hangman_8 };


	for (int i = 0; i < 9; i++)
	{
		for (int p = 0; p < strlen(title[i]); p++)
		{
			printw("%c", title[i][p]);
			//_sleep(48);
			refresh();
		}
	}
	printw("\n\n\n\n");
	printw("\t\t\t        (1) EVIL HANGMAN (2) QUIT\n");
	refresh();

	int choice;

	scanw("%d", &choice);

	switch (choice)
	{
	case 1:
		wclear(start);
		//clear();
		endwin();
		refresh();
		break;

	case 2:
		wclear(start);
		endwin();
		refresh();
		exit(1);
		break;
	}
}


Boolean check_win(MY_STRING game_key, int word_length)
{
	for (int i = 0; i < word_length; i++)
	{
		if (my_string_at(game_key, i) == '_')
		{
			return FALSE;
		}
	}
	return TRUE;
}

void gameLoop(int word_length, int n_guesses, Boolean show_words, GENERIC_VECTOR hVector_words)
{
	Mode gameMode = GLOBAL;
	Boolean win;
	char guess;
	char* spent_letters = (char*)malloc(sizeof(char) * 26);
	char* given_letters = (char*)malloc(sizeof(char) * word_length);

	int spent_letter_count = 0;
	int given_letter_count = 0;


	MY_STRING game_key;
	MAP game_map;

	do {

		win = FALSE;
		if (show_words)
		{
			printf("Words remaining %d\n\n", generic_vector_get_size(hVector_words));
			generic_vector_print(hVector_words);
		}

		guess = getGuess(spent_letters, spent_letter_count);

		game_map = map_init_default();

		depositKeys(hVector_words, game_map, guess, word_length, given_letters, given_letter_count);
		hVector_words = updateWordBank(game_map);
		game_key = map_most_common_key(game_map);

		print_c_string(game_key);

		if (check_win(game_key, word_length))
		{
			//printf("CONGRATULATIONS!!!\n");
			win = TRUE;
				
			break;
		}

		if (key_contains_guess(game_key, guess, word_length))
		{
			given_letters[given_letter_count] = guess;
			given_letter_count++;
		}
		else
		{
			printf("Too bad.\n");
			n_guesses--;
		}
		spent_letters[spent_letter_count] = guess;
		spent_letter_count++;

		printf("Guesses remaining: %d\n", n_guesses);
		//print_c_string(game_key);

		generic_vector_destroy(&hVector_words);

		hVector_words = updateWordBank(game_map);

		map_destroy(&game_map);
		} while (n_guesses > 0);

	if (!win)
	{
		if (gameMode == GLOBAL)
		{
			game_key = generic_vector_at(hVector_words, rand() % generic_vector_get_size(hVector_words));
		}

		printf("You Lose! The Word Was: ");
		print_c_string(game_key);
		generic_vector_destroy(&hVector_words);
	}
	else
	{
		printf("Congratulations. The Word Was: \n");
		print_c_string(game_key);
		generic_vector_destroy(&hVector_words);
		map_destroy(&game_map);
	}

	free(spent_letters);
	free(given_letters);
	
}

MY_STRING return_other_word(GENERIC_VECTOR hVector_words, char guess, int word_length)
{
	Boolean isFirst = TRUE;
	MY_STRING firstWord = generic_vector_at(hVector_words, 0);
	for (int i = 0; i < word_length; i++)
	{
		if (my_string_at(firstWord, i) == guess)
		{
			isFirst = FALSE;
		}
	}
	return (isFirst) ? generic_vector_at(hVector_words, 0) : generic_vector_at(hVector_words, 1);
}

GENERIC_VECTOR updateWordBank(MAP game_map)
{
	GENERIC_VECTOR deep_bank = generic_vector(map_common_key_word_bank(game_map));
	return deep_bank;
}

Boolean key_contains_guess(MY_STRING game_key, char guess, int word_length)
{
	Boolean contains_guess = FALSE;
	for (int i = 0; i < word_length; i++)
	{
		if (my_string_at(game_key, i) == guess)
		{
			return TRUE;
		}
	}
	return FALSE;
}

Status depositKeys(GENERIC_VECTOR hWord_bank, MAP game_map, char guess, int word_length, char* given_letters, int given_letter_count)
{
	Boolean in_word = FALSE;
	char* c_key = (char*)malloc(sizeof(char) * (word_length + 1));
	int bank_size = generic_vector_get_size(hWord_bank);
	for (int i = 0; i < bank_size; i++)
	{
		in_word = FALSE;
		//char* t_word_string = my_string_c_str(generic_vector_at(hWord_bank, i));
		for (int p = 0; p < word_length; p++)
		{
			c_key[p] = (my_string_at(generic_vector_at(hWord_bank, i), p) == guess) ? guess : '_';
			for (int q = 0; q < given_letter_count; q++)
			{
				if (my_string_at(generic_vector_at(hWord_bank, i), p) == given_letters[q])
				{
					in_word = TRUE;
					c_key[p] = given_letters[q];
				}
			}
		}
			c_key[word_length] = '\0';
			MY_STRING tKey = my_string_init_c_string(c_key);
			map_insert(game_map, tKey, generic_vector_at(hWord_bank, i));
	}
	free(c_key);
	
	//GENERIC_VECTOR test = map_common_key_word_bank(game_map);
}



char getGuess(char* spent_letters, int spent_letter_count)
{
	char guess;
	Boolean cont = TRUE;
	while (cont)
	{
		printf("ENTER GUESS: ");
		cont = FALSE;
		scanf("%c", &guess);

		for (int i = 0; i < spent_letter_count; i++)
		{
			if (guess == spent_letters[i])
			{
				printf("Duplicate Entry.\n");
				clear_keyboard_buffer();
				cont = TRUE;
				break;
			}
		}
	}
	clear_keyboard_buffer();
	return guess;	
}

clear_keyboard_buffer(void)
{
	while (getchar() != '\n');
}

void greetings(void)
{
	WINDOW* main = initscr();
	box(main, 240, 240);
	char greeting[173] = "Welcome to My Little Game\n\n\n\t\t\t   The Price to Play, You'll Hang to Pay\n\n\n\t\t\tWhat's Fair is Fair - What's Right is Right!\n\n\n\t\t\t   Now Guess to Save your Mortal Rights!\n\n\n\t\t\t";
	move(2, 15);
	printw("\n\n\n\t\t\t\t");
	refresh();
	//scroll(main);

	for (int i = 0; i < 173; i++)
	{
		
		if (i == 26 || i == 66)
		{
			_sleep(190);
			
		}
		printw("%c", greeting[i]);
		refresh();
		
		// _sleep(rand() % 250);
	}

	//_sleep(400);
	printw("      ...press enter to continue...");
	refresh();

	getch();
	clear();
	refresh();
	endwin();
}

int getWordLength(void)
{
	int resp;
	printf("Enter word length: ");
	scanf("%d", &resp);
	return resp;	
}

int getGuesses(void)
{
	int resp;
	printf("Enter number of guesses: ");
	scanf("%d", &resp);
	return resp;
}

Boolean showWordCount(void)
{
	char resp;
	printf("Show remaining words? (y/n): ");
	scanf("%c", &resp);
	return resp == 'y';

}

Boolean play_again(void)
{
	char resp;
	printf("Would you like to play again?: ");
	scanf("%c", &resp);
	return resp == 'y';
}