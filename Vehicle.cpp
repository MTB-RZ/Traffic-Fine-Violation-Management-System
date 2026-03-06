#include "Vehicle.h"

Vehicle::Vehicle(long int id, char* model) {
    vehicleId = id;
    modelName = nullptr;
    copyArray(model, modelName);
}
Vehicle::~Vehicle() {
    delete[] modelName;
}
long int Vehicle::getVehicleId() {
    return vehicleId;
}
char* Vehicle::getModelName() {
    return modelName;
}