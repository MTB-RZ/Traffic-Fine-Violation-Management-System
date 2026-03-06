#include <iostream>
#include "functions.h"
#include "TrafficDepartment.h"
using namespace std;

int main() {
    int choice;
    do {
        cout << endl << "====== TRAFFIC FINE SYSTEM ======" << endl;
        cout << "1. Generate Fine" << endl;
        cout << "2. Check Violation History" << endl;
        cout << "3. Admin Panel" << endl;
        cout << "4. Exit" << endl;
        cout << "Select Option:  ";
        choice = inputIntRange(1, 4);
        cout << endl;
        switch (choice) {
        case 1: {
            generateFine();
            break;
        }
        case 2: {
            checkViolationHistory();
            break;
        }
        case 3: {
            TrafficDepartment td;
            td.adminMenu();
            break;
        }
        }
    } while (choice != 4);

    return 0;
}