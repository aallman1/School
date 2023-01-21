#include<stdio.h>
#include<stdlib.h>
#include "my_string.h"
#include "keypack.h"
#include "hash.h"
#include <math.h>

struct key
{
	MY_STRING key_string;
	int key_index;
};

typedef struct key Key;

struct key_pack
{
	Key** pack;
	int size;
	int capacity;
};

typedef struct key_pack KeyPack;

Key* key_init(MY_STRING hKeyString, int hash_index);

KEYPACK keypack_init_default(void)
{
	KeyPack* pKeyPack = (KeyPack*)malloc(sizeof(KeyPack));
	if (pKeyPack != NULL)
	{
		pKeyPack->size = 0;
		pKeyPack->capacity = 1;
		pKeyPack->pack = (Key**)malloc(sizeof(Key*) * pKeyPack->capacity);
		if (pKeyPack->pack == NULL)
		{
			free(pKeyPack);
		}
	}
	return pKeyPack;
}


Status keypack_init_keys(KEYPACK hKeyPack, MY_STRING hString)
{
	Key* tKey;
	MY_STRING hSubmitKey;
	Boolean is_set;
	int size = my_string_get_size(hString);
	char* cpSubmitKey = (char*)malloc(sizeof(char) * size);
	int hash_index;
	if (cpSubmitKey == NULL)
	{
		return FAILURE;
	}

	for (int i = 1; i <= (pow(2, size)/ 2); i++)
	{
		for (int k = 0; k < size; k++)
		{
			is_set = ((i & (1 << k)) >> k);
			if (is_set)
			{
				cpSubmitKey[k] = my_string_at(hString, k);
				continue;
			}
			cpSubmitKey[k] = '_';
		}
		cpSubmitKey[size] = '\0';
		hSubmitKey = my_string_init_c_string(cpSubmitKey);
		hash_index = i == pow(2, size) - 1 ? return_hash(hSubmitKey, my_string_c_str, my_string_get_size) : -1;
		tKey = key_init(hSubmitKey, hash_index);
		if (!(keypack_insert(hKeyPack, tKey)))
		{
			return FAILURE;
		};
	}
	return SUCCESS;
}

Key* key_init(MY_STRING hKeyString, int hash_index)
{
	Key* pKey = (Key*)malloc(sizeof(Key));
	if (pKey != NULL)
	{
		pKey->key_string = hKeyString;
		pKey->key_index = hash_index;
	}
	return pKey;
}
Status keypack_insert(KEYPACK hKeyPack, KEY hKey)
{
	KeyPack* pKeyPack = (KeyPack*)hKeyPack;
	if (pKeyPack->size >= pKeyPack->capacity)
	{
		Key** tPack = (Key**)malloc(sizeof(Key*) * (pKeyPack->capacity * 2));
		if (tPack == NULL)
		{
			return FAILURE;
		}
		for (int i = 0; i < pKeyPack->size; i++)
		{
			tPack[i] = pKeyPack->pack[i];
		}
		free(pKeyPack->pack);
		pKeyPack->pack = tPack;
		pKeyPack->capacity *= 2;
	}
	pKeyPack->pack[pKeyPack->size] = (Key*)hKey;
	pKeyPack->size++;
	return SUCCESS;
}
int keypack_get_size(KEYPACK hKeyPack)
{
	KeyPack* pKeyPack = (KeyPack*)hKeyPack;
	return pKeyPack->size;
}

int keypack_hash_index_at(KEYPACK hKeyPack, int index)
{
	KeyPack* pKeyPack = (KeyPack*)hKeyPack;
	return pKeyPack->pack[index]->key_index;
}

MY_STRING keypack_string_key_at(KEYPACK hKeyPack, int index)
{
	KeyPack* pKeyPack = (KeyPack*)hKeyPack;
	return pKeyPack->pack[index]->key_string;
}

KEY keypack_at(KEYPACK hKeyPack, int index)
{
	KeyPack* pKeyPack = (KeyPack*)hKeyPack;
	return pKeyPack->pack[index];
}

void keypack_clear(KEYPACK hKeyPack)
{
	KeyPack* pKeyPack = (KeyPack*)hKeyPack;
	free(pKeyPack->pack);
	pKeyPack->pack = (KeyPack*)malloc(sizeof(Key*) * pKeyPack->capacity);
	pKeyPack->size = 0;
}

MY_STRING key_get_string_key(KEY hKey)
{
	Key* pKey = (Key*)hKey;
	return pKey->key_string;
}