#include"init_hangman.h"
#include<curses.h>
#define _CRTDBG_MAP_ALLOC

int main(int argc, char* argv[])
{
	
	FILE* pfdictionary = fopen("dictionary.txt", "r");

	GENERIC_VECTOR* pWordBankArray = getFullWordBank(pfdictionary);
	init_play(pWordBankArray);

	fclose(pfdictionary);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
}

GENERIC_VECTOR* getFullWordBank(FILE* pfDictionary)
{
	int word_length;
	MY_STRING hTempString = my_string_init_default();
	GENERIC_VECTOR* pWordBankArray = (GENERIC_VECTOR*)malloc(sizeof(GENERIC_VECTOR) * MAX_WORD_LENGTH);

	if (pWordBankArray != NULL)
	{
		for (int i = 0; i < MAX_WORD_LENGTH; i++)
		{
			pWordBankArray[i] = generic_vector_init_default(my_string_destroy, my_string_assignment);
		}
	}

	while (my_string_extraction(hTempString, pfDictionary))
	{
		word_length = my_string_get_size(hTempString);
		generic_vector_push_back(pWordBankArray[word_length - 1], hTempString);
	}
	my_string_destroy(&hTempString);
	return pWordBankArray;
}