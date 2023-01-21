#include<stdio.h>
#include<stdlib.h>
#include "avl_tree.h"
#include "generic_vector.h"
#include "associative_array.h"
#include "shared.h"

struct associative_array
{
	TREE keyTree;
	GENERIC_VECTOR* familyBucketVector;
	int vectorCapacity;
};

typedef struct associative_array Map;
int index_hash(char* key_string, int key_length);
MAP map_init_default(void)
{
	Map* pMap = (Map*)malloc(sizeof(Map));
	pMap->keyTree = tree_init_default();
	pMap->familyBucketVector = (GENERIC_VECTOR*)malloc(sizeof(GENERIC_VECTOR));
	pMap->familyBucketVector[0] = generic_vector_init_default(my_string_destroy, my_string_assignment);
	pMap->vectorCapacity = 1;
	MY_STRING mostCommonKey = NULL;
	int maxBucketSize = 0;
}

Status map_insert(MAP hMap, MY_STRING key, MY_STRING word)
{
	int temp = 0;
	Map* pMap = (Map*)hMap;
	int vectorIndex = index_hash(my_string_c_str(key), my_string_get_size(key));

	if (vectorIndex >= pMap->vectorCapacity)
	{
		GENERIC_VECTOR* tempVectorPtr = (GENERIC_VECTOR*)malloc(sizeof(GENERIC_VECTOR) * (vectorIndex + 1));

		if (tempVectorPtr == NULL)
		{
			return FAILURE;
		}
		for (int i = 0; i < pMap->vectorCapacity; i++)
		{
			tempVectorPtr[i] = pMap->familyBucketVector[i];
		}
		for (int i = pMap->vectorCapacity; i <= vectorIndex; i++)
		{
			tempVectorPtr[i] = generic_vector_init_default(my_string_destroy, my_string_assignment);
		}
		pMap->vectorCapacity = vectorIndex + 1;
		free(pMap->familyBucketVector);
		pMap->familyBucketVector = tempVectorPtr;
	}

	return(generic_vector_push_back(pMap->familyBucketVector[vectorIndex], word) && tree_insert(pMap->keyTree, key, vectorIndex));
}

MY_STRING map_most_common_key(MAP hMap)
{
	Map* pMap = (Map*)hMap;
	return tree_essential_key(pMap->keyTree);

}

GENERIC_VECTOR map_common_key_word_bank(MAP hMap)
{
	Map* pMap = (Map*)hMap;
	int index = tree_essential_key_index(pMap->keyTree);
	return pMap->familyBucketVector[tree_essential_key_index(pMap->keyTree)];
}

int index_hash(char* key_string, int key_length)
{
	int index_hash = 0;
	char* unique_letters = (char*)malloc(sizeof(char) * (key_length));
	int ulc = 0;
	int init_p = 0;
	int word_sum = 0;
	Boolean isWord = TRUE;

	for (int i = 0; i < key_length; i++)
	{
		word_sum += i * (key_string[i] - 96);
		if (key_string[i] == '_')
		{
			isWord = FALSE;
			break;
		}
	}

	if (!isWord) {
		if (unique_letters == NULL)
		{
			printf("UNEXPECTED FAILURE ENCOUNTERED IN CRITICAL PROCESS. EXITING PROGRAM\n");
			exit(1);
		}
		for (int i = 0; i < key_length; i++)
		{
			if (key_string[i] != '_')
			{
				if (ulc == 0)
				{
					init_p = i;
				}
				if (key_string[i] != unique_letters[ulc])
				{
					ulc++;
					unique_letters[ulc] = key_string[i];
				}

				if (ulc > 1)
				{
					index_hash += i * (unique_letters[ulc - 1] - 96) + (init_p * key_length);
				}
				else
				{
					index_hash += (i + 1) + (init_p * key_length);
				}
			}
		}
	}
	else
	{
		index_hash = word_sum;
	}
	free(unique_letters);
	return index_hash;
}

void map_destroy(MAP* phMap)
{
	Map* pMap = (Map*)*phMap;
	for (int i = 0; i < pMap->vectorCapacity; i++)
	{
		generic_vector_destroy(&(pMap->familyBucketVector[i]));
	}
	free(pMap->familyBucketVector);
	tree_destroy(&(pMap->keyTree));
	free(pMap);
	*phMap = NULL;
}


