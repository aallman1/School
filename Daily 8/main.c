#include<stdio.h>
#include<stdlib.h>
#include "priority_queue.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char* argv[])
{
	PRIORITY_QUEUE hQ = priority_queue_init_default();

	priority_queue_insert(hQ, 1000, 9001);
	Status status;
	int intended_repeititions = 20;
	int repetitions = 0;
	int k = 0;
	int i = 1;


	do {
		status = priority_queue_insert(hQ, rand() >> 5, i);
		k++;
		i++;
		repetitions++;

	} while (status && repetitions <= intended_repeititions);
	
	priority_queue_insert(hQ, 6, 42);

	printf("Servicing and printing values from the priority Queue:\n\n");

	while(!priority_queue_is_empty(hQ))
	{
		printf("Priority Level: %d : Data Item: %d\n", priority_queue_front(hQ, &status)[0], priority_queue_front(hQ, &status)[1]);
		priority_queue_service(hQ);
	}
	for (int i = 0; i < 10; i++)
	{
		priority_queue_insert(hQ, rand(), rand());
	}
	
	priority_queue_destroy(&hQ);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
}