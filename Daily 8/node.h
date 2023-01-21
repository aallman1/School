#ifndef NODE_H
#define NODE_H

struct node
{
	int priority_level;
	int data_item;
};

typedef struct node Node;
void node_destroy(Node** pNode);
void heapify_nodes(Node** data, int size);
void fix_down_nodes(Node** data, int index, int number_of_elements);
void remove_max_node(Node** data, int* size);
void fix_up_nodes(Node** data, int index);


#endif // !NODE_H
