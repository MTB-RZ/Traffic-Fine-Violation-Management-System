#include <iostream>
#include <fstream>
using namespace std;

class Violation;
class Officer;
class Vehicle;
class Car;
class Bike;

int loadTicketCounter();
void saveTicketCounter(int id);
int inputIntRange(int min, int max);
void copyArray(char* source, char*& destination);
void displayArray(char* array);
void intToChar(int num, char* result);
void appendArray(char* base, char* add);
void normalizeString(char* str);
bool sameString(char* a, char* b);
void inputString(char*& newArr, int size);
int loadViolations(const char* fileName, Violation*& list);
bool driverExistsAndValid(long int id, char* name, char*& ticketsOut);
void updateDriverFile(long int id, char* name, int newTicketId);
bool officerExists(long int id, char*& nameOut);
void updateOfficerFile(long int id, char* name);
void generateTicketFileName(int ticketId, char* fileName);
void generateFine();
void showTicketById();
void showDriverHistory();
void checkViolationHistory();
void addViolation();
void removeViolation();