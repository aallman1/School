#include<stdio.h>
#include<stdlib.h>
#include "generic_vector.h"
#include"shared.h"
#include"my_string.h"

void generic_vector_destroy(GENERIC_VECTOR* phGeneric_vector);
Status generic_vector_pop_back(GENERIC_VECTOR hGeneric_vector);
Status generic_vector_push_back(GENERIC_VECTOR hGeneric_vector, Item* pItem);
Item* generic_vector_at(GENERIC_VECTOR hGeneric_vector, int index);

struct generic_vector
{
	int size;
	int capacity;
	Item* data;
	void (*destroy_item)(Item* pItem);
	Status(*assign)(Item* pLeft, Item Right);
};

typedef struct generic_vector Generic_vector;


GENERIC_VECTOR generic_vector(GENERIC_VECTOR hCopyVector)
{
	Generic_vector* pCopyVector = (Generic_vector*)hCopyVector;
	Generic_vector* pGeneric_vector = (Generic_vector*)malloc(sizeof(Generic_vector));
	if (pGeneric_vector != NULL)
	{
		pGeneric_vector->size = 0;
		pGeneric_vector->capacity = pCopyVector->capacity;
		pGeneric_vector->destroy_item = pCopyVector->destroy_item;
		pGeneric_vector->assign = pCopyVector->assign;
		pGeneric_vector->data = (Item*)malloc(sizeof(Item) * (pCopyVector->capacity));
		if (pGeneric_vector->data == NULL)
		{
			free(pGeneric_vector);
			return NULL;
		}

		for (int i = 0; i < pGeneric_vector->capacity; i++)
		{
			pGeneric_vector->data[i] = NULL;
		}
		for (int i = 0; i < pCopyVector->size; i++)
		{
			generic_vector_push_back(pGeneric_vector, pCopyVector->data[i]);
		}
	
	}
	return pGeneric_vector;
}

GENERIC_VECTOR generic_vector_init_default(void(*destroy_item)(Item* pItem), Status(*assign)(Item* pLeft, Item Right))
{

	Generic_vector* pGeneric_vector = (Generic_vector*)malloc(sizeof(Generic_vector));

	if (pGeneric_vector != NULL)
	{
		pGeneric_vector->size = 0;
		pGeneric_vector->capacity = 1;
		pGeneric_vector->destroy_item = destroy_item;
		pGeneric_vector->assign = assign;
		pGeneric_vector->data = (Item*)malloc(sizeof(Item) * (pGeneric_vector->capacity));
		if (pGeneric_vector->data == NULL)
		{
			free(pGeneric_vector);
			return NULL;
		}

		for (int i = 0; i < pGeneric_vector->capacity; i++)
		{
			pGeneric_vector->data[i] = NULL;
		}
	}
	return (GENERIC_VECTOR)pGeneric_vector;
}

int generic_vector_get_size(GENERIC_VECTOR hGeneric_vector)
{
	Generic_vector* pGeneric_vector = (Generic_vector*)hGeneric_vector;
	return pGeneric_vector->size;
}

Status generic_vector_push_back(GENERIC_VECTOR hGeneric_vector, Item* pItem)
{
	Generic_vector* pGeneric_vector = (Generic_vector*)hGeneric_vector;
	Item* temp;
	if (pGeneric_vector->size >= pGeneric_vector->capacity)
	{
		temp = (Item*)(malloc(sizeof(Item) * (pGeneric_vector->capacity * 2)));
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (int i = 0; i < (pGeneric_vector->capacity * 2); i++)
		{
			temp[i] = NULL;
		}
		for (int i = 0; i < pGeneric_vector->size; i++)
		{
			temp[i] = pGeneric_vector->data[i];
		}
		free(pGeneric_vector->data);
		pGeneric_vector->data = temp;
		pGeneric_vector->capacity *= 2;
	}

	Status status = pGeneric_vector->assign(&(pGeneric_vector->data[pGeneric_vector->size]), pItem);

	if (status != FAILURE)
	{
		pGeneric_vector->size++;
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

Status generic_vector_pop_back(GENERIC_VECTOR hGeneric_vector)
{
	Generic_vector* pGeneric_vector = (Generic_vector*)hGeneric_vector;

	if (pGeneric_vector->size > 0)
	{
		pGeneric_vector->size--;
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

Item* generic_vector_at(GENERIC_VECTOR hGeneric_vector, int index)
{
	Generic_vector* pGeneric_vector = (Generic_vector*)hGeneric_vector;

	if (index > pGeneric_vector->size - 1 || index < 0)
	{
		return NULL;
	}
	else
	{
		return(pGeneric_vector->data[index]);
	}
}

void generic_vector_print(GENERIC_VECTOR hVector)
{
	Generic_vector* pGeneric_vector = (Generic_vector*)hVector;
	int i = 0;
	while (i < pGeneric_vector->size)
	{
		char* string = my_string_c_str(pGeneric_vector->data[i]);
		printf("%d: %s\n", i, string);
		i++;
	}
}


void generic_vector_destroy(GENERIC_VECTOR* phGeneric_vector)
{
	if (*phGeneric_vector == NULL) return;
	Generic_vector* pGeneric_vector = (Generic_vector*)*phGeneric_vector;
	for (int i = 0; i < pGeneric_vector->capacity; i++)
	{
		if (pGeneric_vector->data[i] != NULL)
		{
			//print_c_string(pGeneric_vector->data[i]);
			pGeneric_vector->destroy_item(&(pGeneric_vector->data[i]));
			
		}
	}
	free(pGeneric_vector->data);
	free(pGeneric_vector);
	*phGeneric_vector = NULL;
}