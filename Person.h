#pragma once
#include "functions.h"

class Person {
protected:
    char* name;
    long int id;
public:
    Person();
    Person(char* n, long int i);
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();
    char* getName() const;
    long int getId() const;
};