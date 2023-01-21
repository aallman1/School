#include<stdio.h>
#include<stdlib.h>
#include "queue.h"


struct queue
{

	Status(*assign_next)(ITEM hItem, ITEM hItem_next);
	void (*destroy_item)(ITEM hItem);
	ITEM (*get_next_item)(ITEM hItem);
	ITEM* front;
	ITEM* back;
	int size;
};

typedef struct queue Queue;

QUEUE queue_init_default(Status(*p_assign_next)(ITEM hItem, ITEM hItem_next), void (*p_destroy_item)(ITEM* hItem), ITEM(*p_get_next_item)(ITEM hItem))
{
	Queue* pQueue = (Queue*)malloc(sizeof(Queue));
	if (pQueue != NULL)
	{
		pQueue->assign_next = p_assign_next;
		pQueue->destroy_item = p_destroy_item;
		pQueue->get_next_item = p_get_next_item;
		pQueue->front = NULL;
		pQueue->back = NULL;
		pQueue->size = 0;
	}
	return (QUEUE)pQueue;
}

QUEUE queue_enqueue(QUEUE hQ, ITEM hItem)
{
	Queue* pQueue = (Queue*)hQ;
	if (pQueue->front == NULL)
	{
		pQueue->front = hItem;
		pQueue->back = hItem;
	}
	else
	{
		pQueue->assign_next(pQueue->back, hItem);
		pQueue->back = hItem;
	}
	pQueue->size++;
	return (QUEUE)pQueue;
}
QUEUE queue_dequeue(QUEUE hQ)
{
	Queue* pQueue = (Queue*)hQ;
	if (pQueue->size == 0)
	{
		return (QUEUE)pQueue;
	}
	ITEM temp_item = pQueue->front;
	pQueue->front = pQueue->get_next_item(pQueue->front);
	pQueue->destroy_item(temp_item);
	pQueue->size--;
	return (QUEUE)pQueue;
}

QUEUE queue_get_front(QUEUE hQ)
{
	Queue* pQueue = (Queue*)hQ;
	return pQueue->front;
}
Boolean queue_empty(QUEUE hQ)
{
	Queue* pQueue = (Queue*)hQ;
	if (pQueue->size == 0)
	{
		return TRUE;
	}
	return FALSE;
}

int queue_get_queue_size(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;
	return pQ->size;
}
void queue_destroy(QUEUE* hQ)
{
	Queue* pQueue = (Queue*)*hQ;
	ITEM temp;
	while (pQueue->front != NULL)
	{
		temp = pQueue->front;
		pQueue->front = pQueue->get_next_item(pQueue->front);
		pQueue->destroy_item(temp);
	}
	free(pQueue);
	hQ = NULL;	
}