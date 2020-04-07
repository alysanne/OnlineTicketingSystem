#ifndef OTS_TICKET_H
#define OTS_TICKET_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class ticket {
public:
    ticket();
    ~ticket();
    void setPrice(double price);
    void printTicket(string showName, string showDate, string showTime, int numSeats, string fName, string sName, string address);
    virtual double cost() = 0; // virtual function used by derived classes
protected:
    double totalCost;
};

// Constructor
ticket::ticket() {
    totalCost = 0; // init total cost
}

// Destructor
ticket::~ticket() {}

// Calculate discount cost from total price
void ticket::setPrice(double price) {
    totalCost = price;
    cout << "\nThe total price of your tickets (including any applicable discount) is " << (char)156 << this -> cost() << ".\n" << endl;
    system("PAUSE");
}

// Print tickets using data from derived classes
void ticket::printTicket(string showName, string showDate, string showTime, int numSeats, string fName, string sName, string address) {
    system("CLS");
    cout << "\nYOUR TICKETS\n" << endl;
    cout << "Show: " << showName << endl;
    cout << "Date: " << showDate << endl;
    cout << "Time: " << showTime << endl;
    cout << "No. seats: " << numSeats << endl;
    cout << "Total cost: " << char(156) << this -> cost() << endl;
    cout << "Ticket purchased by: " << fName << " " << sName << endl;
    cout << "Address: " << address << endl;
}
#endif //OTS_TICKET_H
