#include "Bike.h"

Bike::Bike(long int id, char* model) : Vehicle(id, model) {}
char* Bike::getType() {
    return (char*)"Bike";
}