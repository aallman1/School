#ifndef KEY_H
#define KEY_H
#include "shared.h"
#include "my_string.h"
typedef void* KEYPACK;
typedef void* KEY;

KEYPACK keypack_init_default(void);
Status keypack_init_keys(KEYPACK hKeyPack, MY_STRING hString);
Status keypack_insert(KEYPACK hKeyPack, KEY pKey);
int keypack_hash_index_at(KEYPACK hKeyPack, int index);
MY_STRING keypack_string_key_at(KEYPACK hKeyPack, int index);
KEY keypack_at(KEYPACK hKeyPack, int index);
int keypack_get_size(KEYPACK hKeyPack);
void keypack_clear(KEYPACK hKeyPack);
MY_STRING key_get_string_key(KEY hKey);
#endif // !KEY_H
