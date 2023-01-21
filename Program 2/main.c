#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "queue.h"
#include "car.h"

//fix memory leak, pass function including destroy to init

int get_ferry_length(void);
int get_number_of_cars(void);
int get_number_of_test_cases(void);
int get_car_length(void);
Bank get_car_bank(void);
int ferry_service(ferry_length_meters, hCar_queue_left, hCar_queue_right);
void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{
	int number_of_test_cases = get_number_of_test_cases();
	
	while (number_of_test_cases > 0)
	{
		QUEUE hCar_queue_left = queue_init_default(car_assign_next, car_destroy, car_get_next);
		QUEUE hCar_queue_right = queue_init_default(car_assign_next, car_destroy, car_get_next);
		CAR hTemp_car;
		int ferry_length_meters = get_ferry_length();
		int number_of_cars = get_number_of_cars();
		while (number_of_cars > 0)
		{
			int car_length = get_car_length();
			Bank car_bank = get_car_bank();
			hTemp_car = car_init_new_car(car_length, car_bank);
			if (car_get_bank(hTemp_car) == LEFT)
			{
				hCar_queue_left = queue_enqueue(hCar_queue_left, hTemp_car, car_assign_next);
			}
			else
			{
				hCar_queue_right = queue_enqueue(hCar_queue_right, hTemp_car, car_assign_next);
			}
			number_of_cars--;
		}
		printf("%d\n", ferry_service(ferry_length_meters, hCar_queue_left, hCar_queue_right));
		number_of_test_cases--;
		clear_keyboard_buffer();
		queue_destroy(&hCar_queue_left);
		queue_destroy(&hCar_queue_right);
	}
}

int get_number_of_test_cases(void)
{
	int number_of_test_cases;
	scanf("%d", &number_of_test_cases);
	return number_of_test_cases;
}

int get_ferry_length(void)
{
	int ferry_length;
	scanf("%d", &ferry_length);
	return ferry_length;
}

int get_number_of_cars(void)
{
	int number_of_cars;
	scanf("%d", &number_of_cars);
	return number_of_cars;
}

int get_car_length(void)
{
	int car_length;
	scanf("%d ", &car_length);
	return car_length;
}

Bank get_car_bank(void)
{
	char bank_string[6];
	scanf(" %s", bank_string);
	if (!strcmp(bank_string, "left"))
	{
		return LEFT;
	}
	else
	{
		return RIGHT;
	}
}

int ferry_service(ferry_length_meters, hCar_queue_left, hCar_queue_right)
{
	const int ferry_length_cm = ferry_length_meters * 100;
	int river_crosses = 0;
	int temp;
	int car_length_in_current_trip = 0;

	while (!(queue_empty(hCar_queue_left)) || !(queue_empty(hCar_queue_right)))
	{
		if (!(queue_empty(hCar_queue_left)))
		{
			river_crosses++;
			while (ferry_length_cm >= (car_length_in_current_trip + car_get_length(queue_get_front(hCar_queue_left))))
			{
				temp = car_get_length(queue_get_front(hCar_queue_left));
				car_length_in_current_trip = car_length_in_current_trip + temp;
				
				hCar_queue_left = queue_dequeue(hCar_queue_left, car_get_next, car_destroy);
				if (queue_empty(hCar_queue_left))
				{
					break;
				}
			}
		}
		else if (!(queue_empty(hCar_queue_right)))
		{
			river_crosses++;
		}

		car_length_in_current_trip = 0;
		
		if (!(queue_empty(hCar_queue_right)))
		{
			river_crosses++;
			while (ferry_length_cm >= (car_length_in_current_trip + car_get_length(queue_get_front(hCar_queue_right))))
			{
				
				temp = car_get_length(queue_get_front(hCar_queue_right));
				car_length_in_current_trip = car_length_in_current_trip + temp;
				
				hCar_queue_right = queue_dequeue(hCar_queue_right, car_get_next, car_destroy);
				if (queue_empty(hCar_queue_right))
				{
					break;
				}
			}
		}
		else if (!(queue_empty(hCar_queue_left)))
		{
			river_crosses++;
		}
		car_length_in_current_trip = 0;

		if (queue_empty(hCar_queue_left) && queue_empty(hCar_queue_right))
		{
			return river_crosses;
		}
	}
}

void clear_keyboard_buffer(void) {
	char ch;
	scanf("%c", &ch);
	while (ch != '\n' && ch != '\0')
	{
		scanf("%c", &ch);
	}

}

