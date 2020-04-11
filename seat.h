#ifndef OTS_SEAT_H
#define OTS_SEAT_H
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>

using namespace std;

class seat {
public:
    seat();
    seat(int seatRow, int seatNumber, float price, string status, string show);
    ~seat();
    void getSeatDetails();
    float getSeatPrice();
    void setSeatStatus(string newStatus);
    string getSeatStatus();
    int getSeatRow();
    int getSeatNumber();
protected:
    float price;
    int seatNumber;
    int seatRow;
    string status;
    string show;
};

// Constructors
seat::seat() {}

seat::seat(int seatRow, int seatNumber, float price, string status, string show) {
    this -> seatNumber = seatNumber;
    this -> seatRow = seatRow;
    this -> price = price;
    this -> status = status;
    this -> show = show;
}

// Destructor
seat::~seat() {}

void seat::setSeatStatus(string newStatus) {
    status = newStatus;
}

string seat::getSeatStatus() {
    return status;
}

int seat::getSeatRow() {
    return seatRow;
}

int seat::getSeatNumber() {
    return seatNumber;
}

float seat::getSeatPrice() {
    return price;
}

void seat::getSeatDetails() {
    cout << "Show: " << show << endl;
    cout << "Row: " << getSeatRow() << endl;
    cout << "Seat no.: " << getSeatNumber() << endl;
    cout << "Price: £" << getSeatPrice() << endl;
}

#endif //OTS_SEAT_H
