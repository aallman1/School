#include "vector.h"
#include "generic.h"
#include<stdio.h>
#include<stdlib.h>
#include "vector.h"
typedef struct vector Vector;
struct vector
{
	int size;
	int capacity;
	ITEM* data;
	void(*item_destroy)(ITEM* hItem);
};

VECTOR vector_init_default(void(*p_item_destroy)(ITEM* hItem))
{
	Vector* pVector = (Vector*)malloc(sizeof(Vector));
	if (pVector != NULL)
	{
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (ITEM*)malloc(sizeof(ITEM) * (pVector->capacity));
		pVector->item_destroy = p_item_destroy;
		if (pVector->data == NULL)
		{
			free(pVector);
		}
	}
	return (VECTOR)pVector;
}


Status vector_insert(VECTOR hVector, ITEM data_item)
{
	Vector* pVector = (Vector*)hVector;
	if (pVector->size >= pVector->capacity)
	{
		pVector->capacity *= 2;
		ITEM* temp = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity);
		if (temp == NULL)
		{
			pVector->capacity = pVector->capacity / 2;
			return FAILURE;
		}
		for (int i = 0; i < pVector->size; i++)
		{
			temp[i] = pVector->data[i];
		}
		free(pVector->data);
		pVector->data = temp;
	}
	pVector->data[pVector->size] = data_item;
	pVector->size++;
	
	return SUCCESS;
}


Status vector_pop(VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
		
	for (int i = 1; i < pVector->size; i++)
	{
		pVector->data[i - 1] = pVector->data[i];
	}
	pVector->size--;
	return SUCCESS;
}

ITEM vector_at(VECTOR hVector, int index)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->data[index];
}

ITEM* vector_get_data(VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->data;
}

int vector_get_size(VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->size;
}

void vector_destroy(VECTOR* phVector)
{
	Vector* pVector = (Vector*)*phVector;
	free(pVector->data);
	free(pVector);
	phVector = NULL;
}