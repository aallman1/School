#ifndef MY_STRING_H
#define MY_STRING_H
#include<stdio.h>
#include"shared.h"

typedef void* MY_STRING;
MY_STRING my_string_init_default(void);
void my_string_destroy(Item* pItem);
MY_STRING my_string_init_c_string(const char* c_string);
int my_string_get_capacity(MY_STRING hMy_string);
int my_string_get_size(MY_STRING hMy_string);
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);
Status my_string_extraction(MY_STRING hMy_string, FILE* fp);
Status my_string_insertion(MY_STRING hMy_string, FILE* fp);
Status my_string_push_back(MY_STRING hMy_string, char item);
Status my_string_pop_back(MY_STRING hMy_string);
char my_string_at(MY_STRING hMy_string, int index);
char* my_string_c_str(MY_STRING hMy_string);
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend);
Boolean my_string_empty(MY_STRING hMy_string);
void print_c_string(MY_STRING hString);
void my_string_destroy(Item* pItem);//takes pointer to handle of object to destroy
Status my_string_assignment(Item* pLeft, Item Right);
MY_STRING my_string_init_default_key(int word_length);
MY_STRING my_string_init_string(MY_STRING hCopy);


#endif // !STRING_H
