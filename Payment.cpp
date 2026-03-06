#include "Payment.h"

void Payment::markTicketPaid(int ticketId) {
    Ticket t(ticketId);
    t.markPaid();
}