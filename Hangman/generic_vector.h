#ifndef GENERIC_VECTOR_H
#define GENERIC_VECTOR_H
#include "shared.h"
typedef void* GENERIC_VECTOR;

GENERIC_VECTOR generic_vector_init_default(void(*destroy_item)(Item* pItem), Status(*assign)(Item* pLeft, Item Right));
GENERIC_VECTOR generic_vector(GENERIC_VECTOR hCopyVector);
Status generic_vector_push_back(GENERIC_VECTOR hGeneric_vector, Item* pItem);
Status generic_vector_pop_back(GENERIC_VECTOR hGeneric_vector);
Item* generic_vector_at(GENERIC_VECTOR hGeneric_vector, int index);
void generic_vector_destroy(GENERIC_VECTOR* phGeneric_vector);
void generic_vector_print(GENERIC_VECTOR hVector);
int generic_vector_get_size(GENERIC_VECTOR hGeneric_vector);



#endif // !GENERIC_VECTOR_H
