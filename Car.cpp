#include "Car.h"

Car::Car(long int id, char* model) : Vehicle(id, model) {}
char* Car::getType() {
    return (char*)"Car";
}