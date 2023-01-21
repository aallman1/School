#include<stdlib.h>
#include<stdio.h>
#include"avl_tree.h"
#include "keypack.h"
#include <math.h>

typedef struct node Node;
typedef struct avl_tree Tree;

int getBalance(Node* node);
Status node_insert(Node** root, MY_STRING hKey, int vectorIndex);
void essential_key_index(Node* root, int* max_count);
void essential_node(Node* root, Node** temp, int* max_count);
Node* rightRotate(Node* node_a);
Node* leftRotate(Node* node_a);
void _tree_destroy(Node* root);
void updateHeight(Node* node);

struct node
{
	Node* right;
	Node* left;
	int index;
	int vectorSize;
	MY_STRING key;
	int height;
};

struct avl_tree
{
	Node* root;
};

Status tree_insert(TREE hTree, MY_STRING hKey, int vectorIndex)
{
	Tree* pTree = (Tree*)hTree;
	
	node_insert(&pTree->root, hKey, vectorIndex);
}

TREE tree_init_default(void)
{
	Tree* pTree = (Tree*)malloc(sizeof(Tree));
	if (pTree != NULL)
	{
		pTree->root = NULL;
	}
	return pTree;
}

Status node_insert(Node** root, MY_STRING hKey, int vectorIndex)
{
	int compare; 

	if (*root == NULL)
	{
		Node* temp = (Node*)malloc(sizeof(Node));
		temp->key = hKey;
		temp->index = vectorIndex;
		temp->left = NULL;
		temp->right = NULL;
		temp->vectorSize = 1;
		temp->height = 1;
		(*root) = temp;
		return SUCCESS;
	}

	compare = my_string_compare((*root)->key, hKey);

	if (compare > 0) //if root key > key
	{
		tree_insert(&(*root)->left, hKey, vectorIndex);
	}
	else if (compare < 0) //if root key < key
	{
		tree_insert(&(*root)->right, hKey, vectorIndex);
	}
	else
	{
		my_string_destroy(&hKey);
		(*root)->vectorSize++;
		return SUCCESS;
	}

	(*root)->height = max(height((*root)->left), height((*root)->right)) + 1;

	int balance = getBalance((*root));

	if ((*root)->left) {
		if (balance < -1 && my_string_compare((*root)->left->key, hKey) > 0) { //
			*root = rightRotate(*root);
		}
		else if (balance < -1 && my_string_compare((*root)->left->key, hKey) < 0)
		{
			(*root)->left = leftRotate((*root)->left);
			*root = rightRotate(*root);
		}
	}
	if ((*root)->right) {
		if (balance > 1 && my_string_compare((*root)->right->key, hKey) < 0)
		{
			*root = leftRotate(*root);
		}
		else if (balance > 1 && my_string_compare((*root)->right->key, hKey) > 0)
		{
			(*root)->right = rightRotate((*root)->right);
			*root = leftRotate(*root);
		}
	}
	return SUCCESS;
}


Node* rightRotate(Node* node_a)
{
	Node* node_b = node_a->left; //parent's left (node b)
	Node* node_d = node_b->right; //node a's new left child

	node_b->right = node_a; //node_b becomes parent
	node_a->left = node_d; //node_a get's node b's right child
	//node c no change
	
	//node_a->height = //max(height(node_a->left), height(node_a->right)) + 1;
	updateHeight(node_a);
	updateHeight(node_b);
	//node_b->height = max(height(node_b->left), height(node_b->right)) + 1;

	return node_b;
}

Node* leftRotate(Node* node_a)
{
	Node* node_b = node_a->right;
	Node* node_d = node_a->left;

	node_b->left = node_a;
	node_a->right = node_d;

	updateHeight(node_a);// max(height(node_a->left), height(node_a->right)) + 1;
	updateHeight(node_b);// max(height(node_b->left), height(node_b->right)) + 1;

	// Return new root
	return node_b;
}

int tree_essential_key_index(TREE hTree)
{
	Tree* pTree = (Tree*)hTree;
	int max_count = 0;
	Node* e_node;
	essential_node(pTree->root, &e_node, &max_count);
	return e_node->index;
}

MY_STRING tree_essential_key(TREE hTree)
{
	Tree* pTree = (Tree*)hTree;
	Node* e_node;
	int max_count = 0;
	essential_node(pTree->root, &e_node, &max_count);
	return e_node->key;
}

void essential_node(Node* root, Node** temp, int* max_count)
{
	Node* current = root;
	if (current != NULL)
	{
		essential_node(current->left, temp, max_count);
		if (current->vectorSize > *max_count)
		{
			*max_count = current->vectorSize;
			*temp = current;
		}
		essential_node(current->right, temp, max_count);
	}
}

void essential_key_index(Node* root, int* max_count)
{
	Node* current = root;
	if (current != NULL)
	{
		essential_key_index(current->left, max_count);
		if (current->vectorSize > *max_count)
		{
			*max_count = current->vectorSize;
		}
		essential_key_index(current->right, max_count);
	}
}

void updateHeight(Node* node)
{
	node->height = (height(node->left) > height(node->right) ? height(node->left) + 1 : height(node->right)) + 1; 
}

int get_depth(Node* node)
{
	int left_depth, right_depth;
	left_depth = right_depth = 0;
	if (node)
	{
		if (node->left)
		{
			left_depth += (get_depth(node->left) + 1);
		}
		if (node->right)
		{
			right_depth += (get_depth(node->right) + 1);
		}
		return max(left_depth, right_depth);
	}
	return 0;
}

void tree_destroy(TREE* phTree)
{
	Tree* pTree = (Tree*)*phTree;
	_tree_destroy(pTree->root);
	free(pTree);
	phTree = NULL;
}

void _tree_destroy(Node* root)
{
	Node* current = root;
	if (current != NULL)
	{
		_tree_destroy(current->left);
		_tree_destroy(current->right);
		my_string_destroy(&(current->key));
		free(current);
	}
}

int height(Node* node)
{
	return (node == NULL) ? 0 : node->height;
}
int getBalance(Node* N)
{
	if (N == NULL)
		return 0;
	return height(N->right) - height(N->left);
}