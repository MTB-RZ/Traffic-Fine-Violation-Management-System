#pragma once
#include "Vehicle.h"

class Bike : public Vehicle {
public:
    Bike(long int id, char* model);
    char* getType();
};