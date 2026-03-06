#pragma once
#include <iostream>
#include <fstream>
#include "functions.h"
using namespace std;

class Ticket {
private:
    int ticketId;
    int paid;
    void updateTicketFileStatus();
public:
    Ticket(int id, int status = 0);
    int getId() const;
    int isPaid() const;
    void markPaid();
    void saveToAllTicketsFile();   
};