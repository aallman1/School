#include<stdlib.h>
#include<stdio.h>
#include"shared.h"

int return_hash(Item* pItem, char* (*decrypt)(Item* pItem), int(*get_size)(Item* pItem))
{
	char* item = decrypt(pItem);
	char* char_key = decrypt(pItem);
	int size = get_size(pItem);
	int int_key = 0;

	int flip;

	for (int i = 0; i < size; i++)
	{
		int flip = 1 << ((int)(item[i]) - 97);
		int_key |= flip;
	}
	return int_key % GENERIC_VECTOR_MAX_CAPACITY;
}