#include "TrafficDepartment.h"

bool TrafficDepartment::checkPassword() {
    char* input = nullptr;
    cout << "Enter Admin Password: ";
    inputString(input, 20);

    ifstream file("password.txt");
    char* stored = nullptr;
    if (!file) {
        cout << "Password file missing. Please create password.txt with admin password." << endl;
        delete[] input;
        return false;
    }
    else {
        char buffer[20];
        file >> buffer;
        copyArray(buffer, stored);
        file.close();

        bool valid = sameString(input, stored);
        if (!valid) {
            cout << "Incorrect password!" << endl;
        }

        delete[] input;
        delete[] stored;
        return valid;
    }
}

void TrafficDepartment::changePassword() {
    char* oldPass = nullptr;
    char* newPass = nullptr;

    cout << "Enter old password: ";
    inputString(oldPass, 20);

    ifstream file("password.txt");
    char buffer[20];
    file >> buffer;
    file.close();

    char* stored = nullptr;
    copyArray(buffer, stored);

    if (!sameString(oldPass, stored)) {
        cout << "Old password incorrect!" << endl;
        delete[] oldPass;
        delete[] stored;
        return;
    }
    else {
        cout << "Enter new password (max 20 chars): ";
        newPass = new char[20];
        cin.getline(newPass, 20, '\n');

        ofstream out("password.txt");
        out << newPass;
        out.close();

        cout << "Password changed successfully." << endl;

        delete[] oldPass;
        delete[] newPass;
        delete[] stored;
    }
}

void TrafficDepartment::payFineOption() {
    int ticketId;
    cout << "Enter Ticket ID to mark as PAID: ";
    ticketId = inputIntRange(1, loadTicketCounter());
    payment.markTicketPaid(ticketId);
}

void TrafficDepartment::addDriver() {
    char* name = nullptr;
    cout << "Driver Name: ";
    inputString(name, 100);

    cout << "Driver ID: ";
    long int id = inputIntRange(100, 9999);

    char* tickets = nullptr;
    driverExistsAndValid(id, name, tickets);

    updateDriverFile(id, name, 0);
    cout << "Driver added successfully." << endl;

    delete[] name;
    delete[] tickets;
}

void TrafficDepartment::addOfficer() {
    char* name = nullptr;
    cout << "Officer Name: ";
    inputString(name, 100);

    cout << "Officer ID: ";
    long int id = inputIntRange(100, 9999);

    char* existing = nullptr;
    if (officerExists(id, existing)) {
        cout << "Officer updated." << endl;
        delete[] existing;
    }
    else {
        cout << "New officer added." << endl;
    }

    updateOfficerFile(id, name);
    delete[] name;
}



void TrafficDepartment::deleteDriverOrOfficer() {
    int choice;
    cout << "1. Delete Driver" << endl;
    cout << "2. Delete Officer" << endl;
    cout << "Select option: ";
    choice = inputIntRange(1, 2);

    if (choice == 1) {
        long int id;
        cout << "Enter Driver ID to delete: ";
        id = inputIntRange(100, 9999);

        ifstream in("drivers.txt");
        char** names = nullptr;
        char** tickets = nullptr;
        long int* ids = nullptr;
        int count = 0;

        char bufferName[100], bufferTickets[200];
        long int bufferId;

        while (in.getline(bufferName, 100, '\t')) {
            in >> bufferId;
            in.ignore();
            in.getline(bufferTickets, 200);

            char** newNames = new char* [count + 1];
            char** newTickets = new char* [count + 1];
            long int* newIds = new long int[count + 1];

            for (int i = 0; i < count; i++) {
                newIds[i] = ids[i];
                newNames[i] = names[i];
                newTickets[i] = tickets[i];
            }

            newIds[count] = bufferId;
            newNames[count] = new char[100];
            copyArray(bufferName, newNames[count]);
            newTickets[count] = new char[200];
            copyArray(bufferTickets, newTickets[count]);

            if (names) delete[] names;
            if (tickets) delete[] tickets;
            if (ids) delete[] ids;

            names = newNames;
            tickets = newTickets;
            ids = newIds;
            count++;
        }
        in.close();

        ofstream out("drivers.txt");
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (ids[i] != id) {
                out << names[i] << "\t" << ids[i] << "\t" << tickets[i] << endl;
            }
            else {
                found = true;
            }
            delete[] names[i];
            delete[] tickets[i];
        }
        delete[] names;
        delete[] tickets;
        delete[] ids;
        out.close();

        if (found) {
            cout << "Driver deleted." << endl;
        }
        else {
            cout << "Driver not found." << endl;
        }

    }
    else {
        long int id;
        cout << "Enter Officer ID to delete: ";
        id = inputIntRange(100, 9999);

        ifstream in("officer.txt");
        char** names = nullptr;
        long int* ids = nullptr;
        int count = 0;

        char bufferName[100];
        long int bufferId;

        while (in.getline(bufferName, 100, '\t')) {
            in >> bufferId;
            in.ignore();

            char** newNames = new char* [count + 1];
            long int* newIds = new long int[count + 1];

            for (int i = 0; i < count; i++) {
                newNames[i] = names[i];
                newIds[i] = ids[i];
            }

            newNames[count] = new char[100];
            copyArray(bufferName, newNames[count]);
            newIds[count] = bufferId;

            if (names) delete[] names;
            if (ids) delete[] ids;

            names = newNames;
            ids = newIds;
            count++;
        }
        in.close();

        ofstream out("officer.txt");
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (ids[i] != id) {
                out << names[i] << "\t" << ids[i] << endl;
            }
            else {
                found = true;
            }
            delete[] names[i];
        }
        delete[] names;
        delete[] ids;
        out.close();

        if (found) {
            cout << "Officer deleted." << endl;
        }
        else {
            cout << "Officer not found." << endl;
        }
    }
}

void TrafficDepartment::generateReports() {
    cout << endl << "====== Ticket Summary ======" << endl;

    int totalTickets = loadTicketCounter();
    int paidCount = 0;
    int unpaidCount = 0;

    ifstream in("all_tickets.txt");
    for (int i = 0; i < totalTickets; i++) {
        int tid, status;
        in >> tid >> status;
        if (status == 1) {
            paidCount++;
        }
        else {
            unpaidCount++;
        }
    }
    in.close();

    cout << "Total Tickets: " << totalTickets << endl;
    cout << "Paid Tickets: " << paidCount << endl;
    cout << "Unpaid Tickets: " << unpaidCount << endl;
}


void TrafficDepartment::viewAllDriversOrOfficers() {
    cout << endl << "View All:" << endl;
    cout << "1. Drivers" << endl;
    cout << "2. Officers" << endl;
    cout << "Select option: ";
    int choice = inputIntRange(1, 2);

    if (choice == 1) {
        ifstream in("drivers.txt");
        if (!in) {
            cout << "No drivers found." << endl;
            return;
        }
        else {
            cout << endl << "===== All Drivers =====" << endl;
            char name[100], tickets[200];
            long int id;
            while (in.getline(name, 100, '\t')) {
                in >> id;
                in.ignore();
                in.getline(tickets, 200);
                cout << "Name: " << name << endl;
                cout << "ID: " << id << endl;
                cout << "Tickets: " << tickets << endl;
                cout << "-------------------------" << endl;
            }
            in.close();
        }
    }
    else {
        ifstream in("officer.txt");
        if (!in) {
            cout << "No officers found." << endl;
            return;
        }
        else {
            cout << endl << "===== All Officers =====" << endl;
            char name[100];
            long int id;
            while (in.getline(name, 100, '\t')) {
                in >> id;
                in.ignore();
                cout << "Name: " << name << endl;
                cout << "ID: " << id << endl;
                cout << "-------------------------" << endl;
            }
            in.close();
        }
    }
}
void TrafficDepartment::adminMenu() {
    if (!checkPassword()) {
        return;
    }

    int choice;
    do {
        cout << endl << "====== ADMIN PANEL ======" << endl;
        cout << "1. Pay Fine" << endl;
        cout << "2. Add Driver" << endl;
        cout << "3. Add Officer" << endl;
        cout << "4. Delete Driver/Officer" << endl;
        cout << "5. View all Drivers/Officers" << endl;
        cout << "6. All Ticket Report" << endl;
        cout << "7. Add Violation" << endl;
        cout << "8. Remove Violation" << endl;
        cout << "9. Change Password" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << endl << "Please Enter Your choice: ";
        choice = inputIntRange(0, 9);

        switch (choice) {
        case 1: payFineOption(); break;
        case 2: addDriver(); break;
        case 3: addOfficer(); break;
        case 4: deleteDriverOrOfficer(); break;
        case 5: viewAllDriversOrOfficers(); break;
        case 6: generateReports(); break;
        case 7: addViolation(); break;
        case 8: removeViolation(); break;
        case 9: changePassword(); break;
        }
    } while (choice != 0);
}