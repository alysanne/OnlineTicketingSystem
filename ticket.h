#ifndef OTS_TICKET_H
#define OTS_TICKET_H
#include <iostream>
#include <iomanip>
#include <string>
#include "seat.h"
#include "consumer.h"
#include "show.h"

using namespace std;

class ticket {
public:
    ticket();
    ticket(seat &seat, show &show, consumer &user, float price);
    ~ticket();
    void generateTicket();
    void sendTicket();
protected:
    seat seat;
    float price;
    show show;
    consumer user;
};

// Constructor
ticket::ticket() {
    price = 0;
}

ticket::ticket(class seat &seat, class show &show, class consumer &user, float price) {
    this -> seat = seat;
    this -> show = show;
    this -> user = user;
    this -> price = price;
}

// Destructor
ticket::~ticket() {}

// Print tickets using data from derived classes
void ticket::generateTicket() {
    cout << "Show: " << show.getShowDetails() << endl;
    cout << "Seat: Row " << seat.getSeatRow() << ", Seat No. " << seat.getSeatNumber() << endl;
    cout << "Price: £" << seat.getSeatPrice() << endl;
    cout << "Ticket owner: " << user.getFullName() << endl;
}

void ticket::sendTicket() {
    user.sendTicketByEmail();
}

#endif //OTS_TICKET_H
