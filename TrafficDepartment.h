#pragma once
#include <iostream>
#include <fstream>
#include "Payment.h"
#include "functions.h"
using namespace std;

class TrafficDepartment {
protected:
    Payment payment;

    bool checkPassword();
    void changePassword();
    void payFineOption();
    void addDriver();
    void addOfficer();
    void deleteDriverOrOfficer();
    void generateReports();
    void viewAllDriversOrOfficers();

public:
    void adminMenu();
};