#include "functions.h"
#include "functions.h"
#include "Violation.h"
#include "Officer.h"
#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"

int loadTicketCounter() {
    ifstream file("ticket_counter.txt");
    int last = 0;
    if (file) {
        file >> last;
    }
    file.close();
    return last;
}
void saveTicketCounter(int id) {
    ofstream file("ticket_counter.txt");
    file << id;
    file.close();
}
int inputIntRange(int min, int max) {
    char buffer[20];
    int num;
    bool valid;

    do {
        cin >> buffer;
        valid = true;
        num = 0;

        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] < '0' || buffer[i] > '9') {
                valid = false;
                break;
            }
            num = num * 10 + (buffer[i] - '0');
        }

        if (!valid || num < min || num > max) {
            cout << "Invalid input. Enter between " << min << " and " << max << ": ";
            valid = false;
        }
    } while (!valid);

    return num;
}
void copyArray(char* source, char*& destination) {
    if (destination) {
        delete[] destination;
    }
    int len = 0;
    while (source[len] != '\0') {
        len++;
    }
    destination = new char[len + 1];
    for (int i = 0; i < len; i++) {
        destination[i] = source[i];
    }
    destination[len] = '\0';
}
void displayArray(char* array) {
    for (int i = 0; array[i] != '\0'; i++) {
        cout << array[i];
    }
}
void intToChar(int num, char* result) {
    int i = 0;
    if (num == 0) {
        result[i++] = '0';
    }
    while (num > 0) {
        result[i++] = (num % 10) + '0';
        num /= 10;
    }
    result[i] = '\0';
    for (int s = 0, e = i - 1; s < e; s++, e--) {
        char t = result[s];
        result[s] = result[e];
        result[e] = t;
    }
}
void appendArray(char* base, char* add) {
    int i = 0, j = 0;
    while (base[i] != '\0') {
        i++;
    }
    while (add[j] != '\0') {
        base[i++] = add[j++];
    }
    base[i] = '\0';
}
void normalizeString(char* str) {
    if (!str || str[0] == '\0') {
        return;
    }

    if (str[0] >= 'a' && str[0] <= 'z') {
        str[0] -= 32;
    }

    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i - 1] == ' ' && str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
        else if (str[i - 1] != ' ' && str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}
bool sameString(char* a, char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }
    return true;
}
void inputString(char*& newArr, int size) {
    char* newInput = new char[size];
    cin.ignore(100, '\n');
    cin.getline(newInput, size, '\n');
    int len = 0;
    while (newInput[len] != '\0') {
        len++;
    }
    delete[] newArr;
    newArr = new char[len + 1];
    for (int i = 0; i <= len; i++) {
        newArr[i] = newInput[i];
    }
    delete[] newInput;
    newInput = nullptr;
}
int loadViolations(const char* fileName, Violation*& list) {
    ifstream file(fileName);
    if (!file) {
        return 0;
    }

    int count = 0;
    char line[200];

    while (file.getline(line, 200)) {
        count++;
    }
    file.close();

    list = new Violation[count];

    ifstream file2(fileName);
    for (int i = 0; i < count; i++) {
        char name[100];
        int fine;

        file2.getline(name, 100, '\t');
        file2 >> fine;
        file2.ignore(1000, '\n');

        list[i] = Violation(name, fine);
    }
    file2.close();

    return count;
}
bool driverExistsAndValid(long int id, char* name, char*& ticketsOut) {
    ticketsOut = nullptr;
    char** names = nullptr;
    long int* ids = nullptr;
    char** tickets = nullptr;
    int count = 0;

    ifstream in("drivers.txt");
    if (in) {
        char tempName[100], tempTickets[200];
        long int tempId;

        while (in.getline(tempName, 100, '\t')) {
            in >> tempId;
            in.ignore();
            in.getline(tempTickets, 200);

            char** newNames = new char* [count + 1];
            long int* newIds = new long int[count + 1];
            char** newTickets = new char* [count + 1];

            for (int i = 0; i < count; i++) {
                newIds[i] = ids[i];

                newNames[i] = nullptr;
                copyArray(names[i], newNames[i]);

                newTickets[i] = nullptr;
                copyArray(tickets[i], newTickets[i]);
            }

            newIds[count] = tempId;

            newNames[count] = nullptr;
            copyArray(tempName, newNames[count]);

            newTickets[count] = nullptr;
            copyArray(tempTickets, newTickets[count]);

            for (int i = 0; i < count; i++) {
                delete[] names[i];
                delete[] tickets[i];
            }
            delete[] names;
            delete[] ids;
            delete[] tickets;

            names = newNames;
            ids = newIds;
            tickets = newTickets;
            count++;
        }
        in.close();
    }

    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            normalizeString(names[i]);
            if (!sameString(names[i], name)) {
                cout << "Driver ID exists with a different name." << endl;
                for (int j = 0; j < count; j++) {
                    delete[] names[j];
                    delete[] tickets[j];
                }
                delete[] names;
                delete[] ids;
                delete[] tickets;
                return false;
            }

            copyArray(tickets[i], ticketsOut);

            for (int j = 0; j < count; j++) {
                delete[] names[j];
                delete[] tickets[j];
            }
            delete[] names;
            delete[] ids;
            delete[] tickets;
            return true;
        }
    }

    ticketsOut = new char[1];
    ticketsOut[0] = '\0';

    for (int j = 0; j < count; j++) {
        delete[] names[j];
        delete[] tickets[j];
    }
    delete[] names;
    delete[] ids;
    delete[] tickets;

    return true;
}
void updateDriverFile(long int id, char* name, int newTicketId) {
    char** names = nullptr;
    long int* ids = nullptr;
    char** tickets = nullptr;
    int count = 0;

    ifstream in("drivers.txt");
    if (in) {
        char tempName[100], tempTickets[200];
        long int tempId;

        while (in.getline(tempName, 100, '\t')) {
            in >> tempId;
            in.ignore();
            in.getline(tempTickets, 200);

            char** newNames = new char* [count + 1];
            long int* newIds = new long int[count + 1];
            char** newTickets = new char* [count + 1];

            for (int i = 0; i < count; i++) {
                newIds[i] = ids[i];

                newNames[i] = nullptr;
                copyArray(names[i], newNames[i]);

                newTickets[i] = nullptr;
                copyArray(tickets[i], newTickets[i]);
            }

            newIds[count] = tempId;

            newNames[count] = nullptr;
            copyArray(tempName, newNames[count]);

            newTickets[count] = nullptr;
            copyArray(tempTickets, newTickets[count]);

            for (int i = 0; i < count; i++) {
                delete[] names[i];
                delete[] tickets[i];
            }
            delete[] names;
            delete[] ids;
            delete[] tickets;

            names = newNames;
            ids = newIds;
            tickets = newTickets;
            count++;
        }
        in.close();
    }

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            if (newTicketId > 0) {
                int len = 0;
                while (tickets[i][len] != '\0') {
                    len++;
                }

                char* newTicketsStr = new char[len + 12];
                int j = 0;
                for (; j < len; j++) {
                    newTicketsStr[j] = tickets[i][j];
                }
                if (len > 0) {
                    newTicketsStr[j++] = ',';
                }
                char t[10];
                intToChar(newTicketId, t);
                int k = 0;
                while (t[k] != '\0') {
                    newTicketsStr[j++] = t[k++];
                }
                newTicketsStr[j] = '\0';

                delete[] tickets[i];
                tickets[i] = newTicketsStr;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        char** newNames = new char* [count + 1];
        long int* newIds = new long int[count + 1];
        char** newTickets = new char* [count + 1];

        for (int i = 0; i < count; i++) {
            newIds[i] = ids[i];

            newNames[i] = nullptr;
            copyArray(names[i], newNames[i]);

            newTickets[i] = nullptr;
            copyArray(tickets[i], newTickets[i]);
        }

        newIds[count] = id;

        newNames[count] = nullptr;
        copyArray(name, newNames[count]);

        newTickets[count] = new char[10];
        intToChar(newTicketId, newTickets[count]);

        for (int i = 0; i < count; i++) {
            delete[] names[i];
            delete[] tickets[i];
        }
        delete[] names;
        delete[] ids;
        delete[] tickets;

        names = newNames;
        ids = newIds;
        tickets = newTickets;
        count++;
    }

    ofstream out("drivers.txt");
    for (int i = 0; i < count; i++) {
        out << names[i] << "\t" << ids[i] << "\t" << tickets[i] << endl;
        delete[] names[i];
        delete[] tickets[i];
    }
    delete[] names;
    delete[] ids;
    delete[] tickets;
}
bool officerExists(long int id, char*& nameOut) {
    nameOut = nullptr;
    ifstream in("officer.txt");
    if (!in) {
        return false;
    }

    char tempName[100];
    long int tempId;

    while (in.getline(tempName, 100, '\t')) {
        in >> tempId;
        in.ignore();
        if (tempId == id) {
            nameOut = nullptr;
            copyArray(tempName, nameOut);
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}
void updateOfficerFile(long int id, char* name) {
    ofstream out("officer.txt", ios::app);
    out << name << "\t" << id << endl;
    out.close();
}
void generateTicketFileName(int ticketId, char* fileName) {
    char base[] = "TICKET_";
    char ext[] = ".txt";
    char idStr[10];

    int i = 0;
    while (base[i] != '\0') {
        fileName[i] = base[i];
        i++;
    }
    fileName[i] = '\0';

    intToChar(ticketId, idStr);
    appendArray(fileName, idStr);
    appendArray(fileName, ext);
}
void generateFine() {
    char* dName = nullptr;
    cout << "Driver Name: ";
    inputString(dName, 100);
    normalizeString(dName);

    cout << "Driver ID: ";
    long int dId = inputIntRange(100, 9999);

    char* oldTickets = nullptr;
    if (!driverExistsAndValid(dId, dName, oldTickets)) {
        delete[] dName;
        delete[] oldTickets;
        return;
    }

    cout << "Officer ID: ";
    long int oId = inputIntRange(100, 9999);

    char* oName = nullptr;
    if (officerExists(oId, oName)) {
        cout << "Officer \"";
        displayArray(oName);
        cout << "\" found." << endl;
    }
    else {
        cout << "Officer Name: ";
        inputString(oName, 100);
        normalizeString(oName);
        updateOfficerFile(oId, oName);
    }

    Officer* officer = new Officer(oName, oId);

    cout << "Vehicle Type:" << endl;
    cout << "1.Car" << endl;
    cout << "2.Bike" << endl;
    cout << "Please Enter the vehicle type: ";
    int vt = inputIntRange(1, 2);

    cout << "Vehicle ID: ";
    long int vId = inputIntRange(0, 9999);

    char* vModel = nullptr;
    cout << "Vehicle Model: ";
    inputString(vModel, 100);
    normalizeString(vModel);

    Vehicle* v;
    if (vt == 1) {
        v = (Vehicle*)new Car(vId, vModel);
    }
    else {
        v = (Vehicle*)new Bike(vId, vModel);
    }

    Violation* violations = nullptr;
    int count;
    if (vt == 1) {
        count = loadViolations("violations_car.txt", violations);
    }
    else {
        count = loadViolations("violations_bike.txt", violations);
    }

    cout << endl << "Select Violation:-" << endl;
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". ";
        displayArray(violations[i].getName());
        cout << " (Rs " << violations[i].getFine() << ")" << endl;
    }
    cout << "Enter Your option: ";
    int choice = inputIntRange(1, count);

    int ticketId = loadTicketCounter() + 1;
    saveTicketCounter(ticketId);

    updateDriverFile(dId, dName, ticketId);

    char fileName[30];
    generateTicketFileName(ticketId, fileName);

    ofstream all("all_tickets.txt", ios::app);
    all << ticketId << "\t0" << endl;
    all.close();

    ofstream ticket(fileName);
    ticket << "Ticket ID: " << ticketId << endl;
    ticket << "Driver: " << dName << " (" << dId << ")" << endl;
    ticket << "Vehicle: " << v->getType() << " | ID: " << v->getVehicleId() << " | Model: " << v->getModelName() << endl;
    ticket << "Violation: " << violations[choice - 1].getName() << endl;
    ticket << "Fine: Rs " << violations[choice - 1].getFine() << endl;
    ticket << "Officer: " << officer->getName() << " (" << officer->getId() << ")" << endl;
    ticket << "Status: UNPAID" << endl;
    ticket.close();

    cout << "Ticket Generated: ";
    displayArray(fileName);
    cout << endl;

    delete[] oldTickets;
    delete[] dName;
    delete[] vModel;
    delete[] violations;
    delete[] oName;
    delete officer;
    delete v;
}
void showTicketById() {
    cout << "Enter Ticket ID: ";
    int tId = inputIntRange(1, loadTicketCounter());

    char fileName[30];
    generateTicketFileName(tId, fileName);

    ifstream in(fileName);
    if (!in) {
        cout << "Ticket with ID " << tId << " not found." << endl;
        return;
    }

    char ch;
    cout << endl << "===== Ticket Details =====" << endl;
    while (in.get(ch)) {
        cout << ch;
    }
    cout << "===========================" << endl;
    in.close();
}
void showDriverHistory() {
    char* dName = nullptr;
    cout << "Driver Name: ";
    inputString(dName, 100);
    normalizeString(dName);

    cout << "Driver ID: ";
    long int dId = inputIntRange(100, 9999);

    char* tickets = nullptr;
    if (!driverExistsAndValid(dId, dName, tickets)) {
        delete[] dName;
        delete[] tickets;
        return;
    }

    if (tickets[0] == '\0') {
        cout << "No tickets found for this driver." << endl;
    }
    else {
        cout << "Tickets for " << dName << " (" << dId << "): " << tickets << endl;

        char tStr[20];
        int i = 0, j = 0;
        while (true) {
            if (tickets[i] == ',' || tickets[i] == '\0') {
                tStr[j] = '\0';
                i++;
                j = 0;

                int tId = 0;
                for (int k = 0; tStr[k] != '\0'; k++) {
                    tId = tId * 10 + (tStr[k] - '0');
                }

                char fileName[30];
                generateTicketFileName(tId, fileName);

                ifstream in(fileName);
                if (in) {
                    char ch;
                    cout << endl << "Ticket ID: " << tId << endl;
                    cout << "--------------------------" << endl;
                    while (in.get(ch)) {
                        cout << ch;
                    }
                    cout << "--------------------------" << endl;
                    in.close();
                }
                else {
                    cout << "Ticket file " << fileName << " missing." << endl;
                }

                if (tickets[i - 1] == '\0') {
                    break;
                }
            }
            else {
                tStr[j++] = tickets[i++];
            }
        }
    }

    delete[] dName;
    delete[] tickets;
}
void checkViolationHistory() {
    cout << endl << "Search violation history by:" << endl;
    cout << "1. Driver Name & ID" << endl;
    cout << "2. Ticket ID" << endl;
    cout << "Select Option: ";
    int choice = inputIntRange(1, 2);

    if (choice == 1) {
        showDriverHistory();
    }
    else {
        showTicketById();
    }
}
void addViolation() {
    cout << "Add Violation For:" << endl;
    cout << "1. Car" << endl << "2. Bike" << endl;
    cout << "Please Enter your choice: ";
    int type = inputIntRange(1, 2);

    const char* fileName;
    if (type == 1) {
        fileName = "violations_car.txt";
    }
    else {
        fileName = "violations_bike.txt";
    }

    char* name = nullptr;
    cout << "Violation detail: ";
    inputString(name, 100);
    normalizeString(name);

    cout << "Fine Amount (100 to 10000 PKR): ";
    int fine = inputIntRange(100, 10000);

    ofstream out(fileName, ios::app);
    if (!out) {
        cout << "Error opening file!" << endl;
        delete[] name;
        return;
    }
    out << name << "\t" << fine << endl;
    out.close();

    cout << "Violation added successfully." << endl;
    delete[] name;
}
void removeViolation() {
    cout << "Remove Violation From:" << endl;
    cout << "1. Car" << endl << "2. Bike" << endl;
    cout << endl << "Please Enter your choice: ";
    int type = inputIntRange(1, 2);

    const char* fileName;
    if (type == 1) {
        fileName = "violations_car.txt";
    }
    else {
        fileName = "violations_bike.txt";
    }

    Violation* list = nullptr;
    int count = loadViolations(fileName, list);

    if (count == 0) {
        cout << "No violations found." << endl;
        return;
    }

    cout << endl << "Violations List:" << endl;
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". ";
        displayArray(list[i].getName());
        cout << " (Rs " << list[i].getFine() << ")" << endl;
    }

    cout << endl << "Select violation to remove: ";
    int choice = inputIntRange(1, count);

    ofstream out(fileName);
    for (int i = 0; i < count; i++) {
        if (i != choice - 1) {
            out << list[i].getName() << "\t" << list[i].getFine() << endl;
        }
    }
    out.close();

    delete[] list;
    cout << "Violation removed successfully." << endl;
}