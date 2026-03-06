#pragma once
#include "functions.h"

class Violation {
protected:
    char* name;
    int fine;
public:
    Violation();
    Violation(char* n, int f);
    Violation(const Violation& other);
    Violation& operator=(const Violation& other);
    ~Violation();
    char* getName() const;
    int getFine() const;
};