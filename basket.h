#ifndef OTS_BASKET_H
#define OTS_BASKET_H
#include <iostream>
#include <iomanip>
#include <string>
#include "seat.h"
#include "show.h"


using namespace std;

class basket {
public:
    basket();
    ~basket();
    float getTotalPrice();
    void displaySeatSelection();
    bool confirmSeatSelection(show &show);
    int requestNumSeats();
    int getNumSeats();
    void selectSeatsForShow(show &show);
    void undoSeatSelection(show &show);
    deque<seat> getSeatSelection();
protected:
    int numSeats;
    int maxSeats;
    float totalPrice;
    deque<seat> seatSelection;
};

// Constructor
basket::basket() {
    numSeats = 0;
    maxSeats = 4;
    totalPrice = 0;
}

// Destructor
basket::~basket() {}

float basket::getTotalPrice() {
    return totalPrice;
}

void basket::displaySeatSelection() {
    cout << "\n================================================" << endl;
    cout << "================== Your seats ==================" << endl;
    cout << "================================================" << endl;

    for (int i = 0; i < seatSelection.size(); i++) {
        seat seat = seatSelection[i];

        cout << "\n-- Seat " << i + 1 << " --" << endl;
        seat.getSeatDetails();

        totalPrice += seat.getSeatPrice();
    }

    cout << "\nTotal price: £" << totalPrice << endl;
}

bool basket::confirmSeatSelection(show &show) {
    string input;
    cout << "You have reserved seats for " << show.getShowDetails() << endl;

    do {
        cout << "Do you wish to continue with the purchase of tickets? (Yes = Y, No = N): ";
        getline(cin, input);

        if (input == "N" || input == "n") {
            cout << "\n~~~~~ Your purchase has been cancelled, please start a new session to purchase tickets for a new show ~~~~~";
            return false;
        }
    } while (input != "Y" && input != "y" && input != "N" && input != "n");
    return true;
}


// Get the user's no. of seat
int basket::requestNumSeats() {
    string input;

    cout << "\n============================================" << endl;
    cout << "========== Select number of seats ==========" << endl;
    cout << "============================================\n" << endl;

    do {
        cout << "How many tickets would you like to purchase (Max. " << maxSeats << "): "; // prompt users to enter number of tickets
        getline(cin, input);

        try {
            numSeats = stoi(input);
        } catch (invalid_argument) {
            continue;
        } catch (out_of_range) {
            continue;
        }
    } while (numSeats != 1 && numSeats != 2 && numSeats != 3 && numSeats != 4);

    return numSeats;
}

int basket::getNumSeats() {
    return numSeats;
}

void basket::selectSeatsForShow(show &show) {
    string row, number;
    bool seatReserved = false;

    do {
        cout << "\n~~~~~ Please select your seat ~~~~~" << endl;
        cout << "Seat row: ";
        getline(cin, row);

        while (row != "1" && row != "2" && row != "3" && row != "4" && row != "5") {
            cout << "Type a valid row: ";
            getline(cin, row);
        }

        cout << "Seat number: ";
        getline(cin, number);

        while (number != "1" && number != "2" && number != "3" && number != "4" && number != "5" && number != "6") {
            cout << "Type a valid seat number: ";
            getline(cin, number);
        }

        int rowNum = stoi(row) - 1;
        int seatNum = stoi(number) - 1;
        seat selectedSeat = show.getSelectedSeat(row, number);

        // Check seat status
        if (selectedSeat.getSeatStatus() != "A") {
            cout << "\n~~~~~ This seat is not available, please try again ~~~~~" << endl;
        } else {
            cout << "\n~~~~~ Seat reserved: Row " << row << " - Seat no. " << number << " ~~~~~" << endl;
            show.selectSeat(selectedSeat);
            seatSelection.push_back(selectedSeat);
            seatReserved = true;
        }
    } while (!seatReserved);
}

// Remove selected seats if user cancels
void basket::undoSeatSelection(show &show) {
    while (!seatSelection.empty()) {
        seat selectedSeat = seatSelection.front();

        show.deselectSeat(selectedSeat);
        seatSelection.pop_front();
    }
}

deque<seat> basket::getSeatSelection() {
    return seatSelection;
}

#endif //OTS_BASKET_H
