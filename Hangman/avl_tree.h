#ifndef AVL_TREE_H
#define AVL_TREE_H
#include"shared.h"
#include"my_string.h"

typedef void* TREE;

//Status node_insert(Node** root, MY_STRING hKey);
Status tree_insert(TREE hTree, MY_STRING hKey, int vectorIndex);
TREE tree_init_default(void);
void tree_destroy(TREE* phTree);
int tree_essential_key_index(TREE hTree);
MY_STRING tree_essential_key(TREE hTree);



#endif // !AVL_TREE_H
