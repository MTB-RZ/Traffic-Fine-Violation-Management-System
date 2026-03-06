#include "Person.h"

Person::Person() {
    name = nullptr;
    id = 0;
}
Person::Person(char* n, long int i) {
    id = i;
    name = nullptr;
    copyArray(n, name);
}
Person::Person(const Person& other) {
    id = other.id;
    name = nullptr;
    if (other.name) {
        copyArray(other.name, name);
    }
}
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        delete[] name;
        name = nullptr;
        id = other.id;
        if (other.name) {
            copyArray(other.name, name);
        }
    }
    return *this;
}
Person::~Person() {
    delete[] name;
}
char* Person::getName() const {
    return name;
}
long int Person::getId() const {
    return id;
}