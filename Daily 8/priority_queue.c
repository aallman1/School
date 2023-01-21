#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"
#include "node.h"

struct priority_queue
{
	int size;
	int capacity;
	Node** data;
};

typedef struct priority_queue Priority_queue;

//void priority_queue_fix_down(Priority_queue* pQ, int index, int size);


PRIORITY_QUEUE priority_queue_init_default(void)
{
	Priority_queue* pQ = (Priority_queue*)malloc(sizeof(Priority_queue));
	if (pQ != NULL)
	{
		pQ->size = 0;
		pQ->capacity = 1;
		pQ->data = (Node**)malloc(sizeof(Node) * pQ->capacity);
	}
	return (PRIORITY_QUEUE)pQ;
}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
	Priority_queue* pQ = (Priority_queue*)hQueue;
	Node* temp_node = (Node*)malloc(sizeof(Node));

	if (temp_node == NULL)
	{
		return FAILURE;
	}

	temp_node->priority_level = priority_level;
	temp_node->data_item = data_item;

	if (pQ->size >= pQ->capacity)
	{
		Node** temp_data = (Node**)malloc(sizeof(Node) * (pQ->capacity * 2));
		if (temp_data == NULL)
		{
			return FAILURE;
		}

		for (int i = 0; i < pQ->size; i++)
		{
			temp_data[i] = pQ->data[i];
		}

		free(pQ->data);
		pQ->data = temp_data;
		pQ->capacity *= 2;
	}
	pQ->data[pQ->size] = temp_node;
	pQ->size++;
	
	priority_queue_heap_sort(pQ->data, pQ->size);
	return SUCCESS;
}

void priority_queue_heap_sort(Node** data, int size)
{
	heapify_nodes(data, size);
}

Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
	Priority_queue* pQ = (Priority_queue*)hQueue;
	if (pQ->size == 0)
	{
		return FAILURE;
	}
	remove_max_node(pQ->data, &pQ->size);
	pQ->size--;
	return SUCCESS;
}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus)
{
	Priority_queue* pQ = (Priority_queue*)hQueue;
	if (pQ->size > 0)
	{
		*pStatus = SUCCESS;
		return pQ->data[0]->priority_level;
	}
	*pStatus = FAILURE;
	return 0000;
}


Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{
	Priority_queue* pQ = (Priority_queue*)hQueue;
	if (pQ->size == 0)
	{
		return TRUE;
	}
	return FALSE;
}


void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{
	Priority_queue* pQ = (Priority_queue*)*phQueue;
	free(pQ->data);
	free(pQ);
	phQueue = NULL;
}