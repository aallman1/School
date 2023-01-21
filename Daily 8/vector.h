#ifndef VECTOR_H
#define VECTOR_H
#include"generic.h"
typedef void* VECTOR;
enum status { FAILURE, SUCCESS };
typedef enum status Status;
VECTOR vector_init_default(void(*p_item_destroy)(ITEM* hItem));
Status vector_insert(VECTOR hVector, ITEM data_item);
int vector_get_size(VECTOR hVector);
ITEM vector_at(VECTOR hVector, int index);
#endif // !VECTOR_H
