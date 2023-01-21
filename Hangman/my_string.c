#include<stdio.h>
#include<stdlib.h>
#include "shared.h"
#include "my_string.h"

struct my_string
{
	int size;
	int capacity;
	char* data;
};

typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
	My_string* pMy_string;
	pMy_string = (My_string*)malloc(sizeof(My_string));
	if (pMy_string != NULL)//malloc can fail
	{
		pMy_string->capacity = 7;
		pMy_string->size = 0;
		pMy_string->data = (char*)(malloc(sizeof(char) * (pMy_string->capacity)));
		return (MY_STRING)pMy_string;
	}
	else
	{
		return (MY_STRING)pMy_string;
	}
}

MY_STRING my_string_init_string(MY_STRING hCopy)
{
	return (my_string_init_c_string(my_string_c_str(hCopy)));
}

MY_STRING my_string_init_c_string(const char* c_string)
{
	My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
	int string_size = 0;
	int i = 0;
	while (c_string[string_size] != '\0')
	{
		string_size++;
	}
	if (pMy_string != NULL)
	{
		pMy_string->size = string_size;
		pMy_string->capacity = string_size + 1;
		pMy_string->data = (char*)(malloc(sizeof(char) * (pMy_string->capacity)));
	}
	if (pMy_string->data == NULL)
	{
		free(pMy_string);
		return NULL;
	}
	while (i <= string_size)
	{
		pMy_string->data[i] = c_string[i];
		i++;
	}
	return (MY_STRING)pMy_string;

}
int my_string_get_capacity(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->capacity;
}
int my_string_get_size(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->size;
}
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string* left_string = (My_string*)hLeft_string;
	My_string* right_string = (My_string*)hRight_string;
	int left_string_size = my_string_get_size(left_string);
	int right_string_size = my_string_get_size(right_string);
	int i = 0;
	while (i < left_string_size && i < right_string_size)
	{
		if ((int)left_string->data[i] != (int)right_string->data[i])
		{
			if ((int)left_string->data[i] > (int)right_string->data[i]);
			{
				return 1;
			}
			return -1;
		}
		i++;
	}
	if (left_string_size > right_string_size)
	{
		return 1;
	}
	else if (right_string_size > left_string)
	{
		return -1;
	}
	return 0;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	pMy_string->size = 0;
	char char_from_file;
	int noc = fscanf(fp, "%c", &char_from_file);
	int i = 0;
	int k = 0;
	char* temp;
	//ungetc(char_from_file, fp);
	if (noc != -1)
	{
		while (char_from_file != '\n' && noc != -1)
		{

			if (pMy_string->size >= pMy_string->capacity)
			{
				temp = (char*)malloc(sizeof(char) * pMy_string->capacity * 2);
				if (temp == NULL)
				{
					return FAILURE;
				}

				for (k = 0; k < pMy_string->size; k++)
				{
					temp[k] = pMy_string->data[k];
				}
				free(pMy_string->data);
				pMy_string->data = temp;
				pMy_string->capacity = pMy_string->capacity * 2;
			}
			pMy_string->data[i] = char_from_file;
			noc = fscanf(fp, "%c", &char_from_file);
			i++;
			pMy_string->size++;
		}

		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}

}


Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	int i = 0;
	char char_to_write = pMy_string->data[i];

	if (!char_to_write)
	{
		return FAILURE;
	}
	else
	{
		while (i < pMy_string->size)
		{
			fprintf(fp, "%c", char_to_write);
			i++;
			char_to_write = pMy_string->data[i];

		}

		return SUCCESS;
	}
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
	My_string* pMy_string = (My_string*)hMy_string;
	char* temp;
	int i = 0;
	if (pMy_string->size >= pMy_string->capacity)
	{
		temp = (char*)malloc(sizeof(char) * (pMy_string->capacity * 2));
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pMy_string->size; i++)
		{
			temp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = temp;
		pMy_string->capacity *= 2;
	}
	pMy_string->data[pMy_string->size] = item;
	pMy_string->size++;
	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	if (pMy_string->size <= 0)
	{
		return FAILURE;
	}
	pMy_string->size--;
	return SUCCESS;
}

char my_string_at(MY_STRING hMy_string, int index)
{
	My_string* pMy_string = (My_string*)hMy_string;

	if (index < 0 || index >= pMy_string->size)
	{
		return NULL;
	}
	return pMy_string->data[index];
}
char* my_string_c_str(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	char* temp;
	int i = 0;

	if (pMy_string->size >= pMy_string->capacity)
	{
		temp = (char*)malloc(sizeof(char) * (pMy_string->capacity + 1));
		if (temp == NULL)
		{
			return NULL;
		}
		for (i = 0; i < pMy_string->size; i++)
		{
			temp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = temp;
		pMy_string->capacity++;
	}
	pMy_string->data[pMy_string->size] = '\0';
	return pMy_string->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_string* pResult = (My_string*)hResult;
	My_string* pAppend = (My_string*)hAppend;
	char* temp;
	int i = 0;
	//if pResult->capacity is less than pResult->size + pAppend->size, resize to accomodate;
	if (pResult->capacity < pResult->size + pAppend->size)
	{
		temp = (char*)malloc(sizeof(char) * (pResult->size + pAppend->size));
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pResult->size; i++)
		{
			temp[i] = pResult->data[i];
		}
		free(pResult->data);
		pResult->data = temp;
		pResult->capacity = pResult->size + pAppend->size;
	}
	for (i = 0; i < pAppend->size; i++)
	{
		pResult->data[pResult->size + i] = pAppend->data[i];
	}
	pResult->size = pResult->size + i;
	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	if (pMy_string->size == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void print_c_string(MY_STRING hString) //test
{
	My_string* pString = (My_string*)hString;
	int i = 0;
	if (pString->size == 0)
	{
		printf("string is empty\n");
	}
	while (i < pString->size)
	{
		printf("%c", pString->data[i]);
		i++;
	}
	printf("\n\n");

}

Status my_string_assignment(Item* pLeft, Item Right)
{
	My_string* pString_right = (My_string*)Right;
	My_string* pString_left = (My_string*)*pLeft;

	if (pString_left == NULL)
	{
		pString_left = my_string_init_c_string(my_string_c_str(pString_right));
		*pLeft = pString_left;
		return SUCCESS;
	}
	else
	{
		if (pString_right != NULL)
		{
			my_string_destroy(&pString_left);
			pString_left = my_string_init_c_string(my_string_c_str(pString_right));
			*pLeft = pString_left;
			return SUCCESS;
		}
		else
		{
			return FAILURE;
		}
	}
}

MY_STRING my_string_init_default_key(int word_length)
{
	char* starting_key_string = (char*)malloc(sizeof(char) * (word_length + 1));
	int i = 0;
	while (i < word_length)
	{
		starting_key_string[i] = '_';
		i++;
	}
	starting_key_string[i] = '\0';
	MY_STRING key = my_string_init_c_string(starting_key_string);
}



void my_string_destroy(Item* pItem)//takes pointer to handle of object to destroy
{
	My_string* pMy_string = (My_string*)(*pItem); //object pointer declared and set equal to the derefenced value of the pointer (or handle) to change handle
	free(pMy_string->data);
	free(pMy_string);
	//pItem = NULL;
}