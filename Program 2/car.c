#include "car.h"
#include "bank.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct car Car;

struct car
{
	int length;
	Bank bank;
	Car* next;
};


CAR car_init_new_car(int length, Bank bank)
{
	Car* pCar = (Car*)malloc(sizeof(Car));
	if (pCar != NULL)
	{
		pCar->length = length;
		pCar->bank = bank;
		pCar->next = NULL;
		
	}
	return (CAR)pCar;
}

Bank car_get_bank(CAR hCar)
{
	Car* pCar = (Car*)hCar;
	return pCar->bank;
}

int car_get_length(CAR hCar)
{
	Car* pCar = (Car*)hCar;
	return pCar->length;
}

CAR car_get_next(CAR hCar)
{
	Car* pCar = (Car*)hCar;
	return pCar->next;
}

Status car_assign_next(CAR hCAR_start, CAR hCar_next)
{
	Car* pCar_start = (Car*)hCAR_start;
	if (pCar_start->next == NULL)
	{
		pCar_start->next = hCar_next;
		return SUCCESS;
	}
	return FAILURE;	
}

void car_destroy(CAR hCar)
{
	Car* pCar = (Car*)hCar;
	free(pCar);
}


