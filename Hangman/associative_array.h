#ifndef ASSOCIATIVE_ARRAY_H
#include"my_string.h"
typedef void* MAP;
MAP map_init_default(void);
Status map_insert(MAP hMap, MY_STRING key, MY_STRING word);
MY_STRING map_most_common_key(MAP hMap);
GENERIC_VECTOR map_common_key_word_bank(MAP hMap);
void map_destroy(MAP* phMap);
#endif // !ASSOCIATIVE_ARRAY_H
