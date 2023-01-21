#ifndef QUEUE_H
#define QUEUE_H
#include "Boolean.h"
#include "status.h"
typedef void* QUEUE;
typedef void* ITEM;

QUEUE queue_init_default(Status(*p_assign_next)(ITEM hItem, ITEM hItem_next), void (*p_destroy_item)(ITEM* hItem), ITEM(*p_get_next_item)(ITEM hItem));
QUEUE queue_enqueue(QUEUE hQ, ITEM hItem);
QUEUE queue_dequeue(QUEUE hQ);
Boolean queue_empty(QUEUE hQ);
QUEUE queue_get_front(QUEUE hQ);
void queue_destroy(QUEUE* hQ);
int queue_get_queue_size(QUEUE hQ);
#endif // !QUEUE_H
