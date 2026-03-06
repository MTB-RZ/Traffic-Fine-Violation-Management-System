#include "Ticket.h"

Ticket::Ticket(int id, int status) {
    ticketId = id;
    paid = status;
}
int Ticket::getId() const {
    return ticketId;
}
int Ticket::isPaid() const {
    return paid;
}
void Ticket::markPaid() {
    if (paid) {
        cout << "Ticket " << ticketId << " is already PAID." << endl;
        return;
    }
    else {
        int totalTickets = loadTicketCounter();
        int** ticketData = new int* [totalTickets];
        for (int i = 0; i < totalTickets; i++) {
            ticketData[i] = new int[2];
        }

        ifstream in("all_tickets.txt");
        if (in) {
            for (int i = 0; i < totalTickets; i++) {
                in >> ticketData[i][0] >> ticketData[i][1];
            }
            in.close();
        }

        ticketData[ticketId - 1][1] = 1;
        paid = 1;

        ofstream out("all_tickets.txt");
        for (int i = 0; i < totalTickets; i++) {
            out << ticketData[i][0] << "\t" << ticketData[i][1] << endl;
        }
        out.close();

        for (int i = 0; i < totalTickets; i++) {
            delete[] ticketData[i];
        }
        delete[] ticketData;

        cout << "Ticket " << ticketId << " marked as PAID." << endl;
        updateTicketFileStatus();
    }
}
void Ticket::saveToAllTicketsFile() {
    ofstream out("all_tickets.txt", ios::app);
    out << ticketId << "\t" << paid << endl;
    out.close();
}
void Ticket::updateTicketFileStatus() {
    char fileName[30];
    generateTicketFileName(ticketId, fileName);

    ifstream in(fileName);
    if (!in) {
        cout << "Ticket file not found." << endl;
        return;
    }
    else {
        char** lines = nullptr;
        int lineCount = 0;
        char buffer[200];

        while (in.getline(buffer, 200)) {
            char* temp = new char[200];
            int i = 0;
            while (buffer[i] != '\0') {
                temp[i] = buffer[i];
                i++;
            }
            temp[i] = '\0';

            char** newLines = new char* [lineCount + 1];
            for (int j = 0; j < lineCount; j++) {
                newLines[j] = lines[j];
            }
            newLines[lineCount] = temp;
            if (lines) {
                delete[] lines;
            }
            lines = newLines;

            lineCount++;
        }
        in.close();

        if (lineCount > 0) {
            delete[] lines[lineCount - 1];
            char* statusLine = new char[20];
            char statusText[] = "Status: PAID";
            int i = 0;
            while (statusText[i] != '\0') {
                statusLine[i] = statusText[i];
                i++;
            }
            statusLine[i] = '\0';
            lines[lineCount - 1] = statusLine;
        }

        ofstream out(fileName);
        for (int i = 0; i < lineCount; i++) {
            out << lines[i] << endl;
            delete[] lines[i];
        }
        delete[] lines;
        out.close();
    }
}