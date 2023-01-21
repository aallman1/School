#include<stdlib.h>
#include "node.h"

void node_destroy(Node** pNode)
{
	free(*pNode);
}

void heapify_nodes(Node** data, int size)
{
	for (int i = (size / 2) - 1; i >= 0; i--)
	{
		fix_down_nodes(data, i, size);
	}
}

//write fix up on the insert..

void fix_down_nodes(Node** data, int index, int number_of_elements)
{
	Node* temp;
	int ind_l, ind_r, ind_m;
	if (number_of_elements >= 2)
	{
		ind_l = 2 * index + 1;
		ind_r = 2 * index + 2;

		if (ind_r < number_of_elements)
		{
			data[ind_l]->priority_level > data[ind_r]->priority_level ? (ind_m = ind_l) : (ind_m = ind_r);

			if (data[ind_m]->priority_level > data[index]->priority_level)
			{
				temp = data[index];
				data[index] = data[ind_m];
				data[ind_m] = temp;
				fix_down_nodes(data, ind_m, number_of_elements);
			}
		}

		else if (ind_l < number_of_elements)
		{
			ind_m = ind_l;
			if (data[ind_m]->priority_level > data[index]->priority_level)
			{
				temp = data[index];
				data[index] = data[ind_m];
				data[ind_m] = temp;
				fix_down_nodes(data, ind_m, number_of_elements);
			}
		}
	}
}

void fix_up_nodes(Node** data, int index)
{
	int parent = (index - 1) / 2;
	if (data[parent]->priority_level < data[index]->priority_level)
	{
		Node* temp = data[parent];
		data[parent] = data[index];
		data[index] = temp;
		fix_up_nodes(data, (index - 1) / 2);
	}
}
void remove_max_node(Node** data, int* size)
{
	Node* temp = data[0];
	data[0] = data[*size - 1];
	data[*size - 1] = temp;
	free(data[*size - 1]);
	(*size)--;
	fix_down_nodes(data, 0, *size);
	
}
