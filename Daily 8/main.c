#include<stdio.h>
#include<stdlib.h>
#include "priority_queue.h"
//expensive, implement with vector

int main(int argc, char* argv[])
{
	PRIORITY_QUEUE hQ = priority_queue_init_default();
	printf("Default priority queue should be initialized.\n\n");
	printf("Inserting data values 0-21 with priority levels 0-20, both in order from least to greatest.\n\n");

	priority_queue_insert(hQ, 1000, 9001);
	Status status;
	int intended_repeititions = 20;
	int repetitions = 0;
	int k = 0;
	int i = 1;


	do {
		status = priority_queue_insert(hQ, k, i);
		k++;
		i++;
		repetitions++;

	} while (status && repetitions <= intended_repeititions);


	if (repetitions == intended_repeititions)
	{
		printf("PRIORITY_QUEUE_INSERT: Intended repetitions (%d) hit successfully. No failure indicated while inserting the digits.\n\n", repetitions);
	}
	
	priority_queue_insert(hQ, 6, 42);

	if (status)
	{
		printf("PRIORITY_QUEUE_FRONT: The data value from the highest priority item is: (%d).\nNo failure indicated in retrieiving the data value.\n\n", priority_queue_front(hQ, &status));
	}

	status = priority_queue_service(hQ);
	
	
	if (status)
	{
		printf("PRIORITY_QUEUE_SERVICE: The priority queue has been serviced.\nNo failure was indicated in servicing the queue.\n\n");

		
		if (status)
		{
			printf("PRIORITY_QUEUE_FRONT: The data value from the highest priority item is: (%d).\nNo failure indicated in retrieiving the data value.\n", priority_queue_front(hQ, &status));
		}
	}

	printf("Servicing and printing values from the priority Queue:\n\n");
	do{
		
		status = priority_queue_service(hQ);
		printf("(%d)\n", priority_queue_front(hQ, &status));

	} while (status);

	if (priority_queue_is_empty)
	{
		printf("\nPRIORITY_QUEUE_EMPTY: The priority queue is now empty.\n");
	}

	
	priority_queue_destroy(&hQ);

	
	printf("\nThe priority queue has been destroyed.\n");


}