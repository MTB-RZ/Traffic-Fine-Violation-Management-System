#include "Violation.h"

Violation::Violation() {
    name = nullptr;
    fine = 0;
}
Violation::Violation(char* n, int f) {
    fine = f;
    name = nullptr;
    copyArray(n, name);
}
Violation::Violation(const Violation& other) {
    fine = other.fine;
    name = nullptr;
    if (other.name) {
        copyArray(other.name, name);
    }
}
Violation& Violation::operator=(const Violation& other) {
    if (this != &other) {
        delete[] name;
        name = nullptr;
        fine = other.fine;
        if (other.name) {
            copyArray(other.name, name);
        }
    }
    return *this;
}
Violation::~Violation() {
    delete[] name;
}
char* Violation::getName() const {
    return name;
}
int Violation::getFine() const {
    return fine;
}