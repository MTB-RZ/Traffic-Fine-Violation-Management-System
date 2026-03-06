#pragma once
#include "functions.h"

class Vehicle {
protected:
    long int vehicleId;
    char* modelName;
public:
    Vehicle(long int id, char* model);
    virtual ~Vehicle();
    long int getVehicleId();
    char* getModelName();
    virtual char* getType() = 0;
};