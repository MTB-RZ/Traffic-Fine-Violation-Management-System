#pragma once
#include "Vehicle.h"

class Car : public Vehicle {
public:
    Car(long int id, char* model);
    char* getType();
};