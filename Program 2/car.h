#ifndef CAR_H
#define CAR_H
#include "bank.h"
#include "status.h"
typedef void* CAR;
CAR car_init_new_car(int length, Bank bank);
Bank car_get_bank(CAR hCar);
int car_get_length(CAR hCar);
CAR car_get_next(CAR hCar);
Status car_assign_next(CAR hCAR_start, CAR hCar_next);
void car_destroy(CAR hCar);
#endif // !CAR_H
