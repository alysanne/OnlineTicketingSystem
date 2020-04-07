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
    ~seat();
    void initialiseFloorPlan();
    int getNumSeats();
    void getSeatSelection();
    void displayFloorPlan();
    void undoSeatSelection();
private:
    void calculatePrice(double &price); // encapsulation - functions only accessed by this class, and no other part of the program
protected:
    int numRows = 5;
    int numSeatsPerRow = 6;
    char floorPlan[5][6];
    int maxSeats = 4;
    queue<string> seatSelection;
    int numSeats;
    int rNum; // used to calculate price
    double price;
};

// Constructor
seat::seat() {
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numSeatsPerRow; c++) {
            floorPlan[r][c] = '0'; // allocate memory slots for floor plan array
        }
    }

    numSeats = 0;
    rNum = 0;
    price = 0; // initialise remaining vars
}

// Destructor
seat::~seat() {}

// Initialise theatre floor plan

void seat::initialiseFloorPlan() {
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numSeatsPerRow; c++) {
            floorPlan[r][c] = 'A'; // Populate array with 'A' (available)
        }
    }
}

// Remove selected seats if user cancels

void seat::undoSeatSelection() {
    while (!seatSelection.empty()) {
        string seatCoords = seatSelection.front();

        int rowNo = seatCoords[0] - '0' - 1;
        int seatNo = seatCoords[1] - '0' - 1;
        floorPlan[rowNo][seatNo] = 'A';
        seatSelection.pop();
    }
}

// Get the user's no. of seat

int seat::getNumSeats() {
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

void seat::displayFloorPlan() {
    cout << "\n=======================================================" << endl;
    cout << "================== Select your seats ==================" << endl;
    cout << "=======================================================\n" << endl;

    cout << "\n            -------------- SCREEN --------------" << endl;

    for (int i = 0; i < numRows; i++) {
        cout << "\n          ┌───┐  ┌───┐  ┌───┐  ┌───┐  ┌───┐  ┌───┐" << endl;
        cout << " Row " << i + 1 << "   ";
        for (int j = 0; j < numSeatsPerRow; j++) {
            cout << " │ " << floorPlan[i][j] << " │ ";
        }
        cout << "\n          └───┘  └───┘  └───┘  └───┘  └───┘  └───┘";
    }
    cout << "\n Seat no.   1      2      3      4      5      6" << endl;

    cout << "\nA - Seat available" << endl;
    cout << "H - Seat on hold" << endl;
    cout << "S - Seat sold" << endl;
}

void seat::getSeatSelection() {
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
        char selectedSeat = floorPlan[rowNum][seatNum];

        // Check seat status
        if (selectedSeat != 'A') {
            cout << "\n~~~~~ This seat is not available, please try again ~~~~~" << endl;
        } else {
            cout << "\n~~~~~ Seat reserved: Row " << row << " - Seat no. " << number << " ~~~~~" << endl;
            floorPlan[rowNum][seatNum] = 'H';
            string seat = row + number;
            seatSelection.push(seat);
            seatReserved = true;
        }
    } while (!seatReserved);
}

#endif //OTS_SEAT_H
