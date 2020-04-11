#ifndef OTS_SHOW_H
#define OTS_SHOW_H
#include <iostream>
#include <iomanip>
#include <string>
#include "seat.h"

using namespace std;

class show {
public:
    show();
    ~show();
    void selectShow(string &showName, string &showDate);
    void selectTime(string &showTime);
    string getShowDetails();
    void initialiseFloorPlan();
    void showAvailableSeats();
    seat getSelectedSeat(string row, string number);
    void deselectSeat(seat selectedSeat);
    void selectSeat(seat selectedSeat);
protected:
    string shows [5][2] = {
            {"Les Miserables", "20/04/2020"},
            {"Wicked", "20/04/2020"},
            {"Harry Potter and the Cursed Child", "20/04/2020"},
            {"Matilda", "20/04/2020"},
            {"Phantom of the Opera", "20/04/2020"}
    } ; // this data would come from a DB
    string showTimes [2] = {"11:00", "18:00"}; // this data would come from a DB
    string showName;
    string date;
    string time;
    int numRows;
    int numSeatsPerRow;
    seat floorPlan[5][6];
    float rowPrices [5] = {50.00, 47.50, 35.00, 25.00, 15.00};
};

// Constructor
show::show() {
    showName = "";
    date = "";
    time = "";
    numSeatsPerRow = 6;
    numRows = 5;
}

// Destructor
show::~show() {}

// Customer selects upcoming show
void show::selectShow(string &showName, string &showDate) {
    string input;
    cout << "\n=========================================" << endl;
    cout << "============= Select a show =============" << endl;
    cout << "=========================================\n" << endl;

    cout << "Please select a show to proceed: " << endl;

    for (int i = 0; i < sizeof(shows)/ sizeof(shows[0]); i++) {
        cout << " " << i + 1 << ". " << shows[i][0] << " - " << shows[i][1] << endl;
    }

    cout << "\nType the number for the selected option: ";
    getline(cin, input);

    while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5") {
        cout << "Type a valid number from the options above: ";
        getline(cin, input);
    }

    showName = shows[stoi(input) - 1][0];
    showDate = shows[stoi(input) - 1][1];

    this -> showName = showName;
    this -> date = showDate;
}

void show::selectTime(string &showTime) {
    string input;

    cout << "\n========================================" << endl;
    cout << "=========== Select show time ===========" << endl;
    cout << "========================================\n" << endl;

    cout << "Please select a show time for " << showName  << ": " << endl;

    for (int i = 0; i < sizeof(showTimes)/ sizeof(showTimes[0]); i++) {
        cout << " " << i + 1 << ". " << showTimes[i] << endl;
    }

    cout << "\nType the number for the selected option: ";
    getline(cin, input);

    while (input != "1" && input != "2") {
        cout << "Type a valid number from the options above: ";
        getline(cin, input);
    }

    showTime = showTimes[stoi(input) - 1];

    this -> time = showTime;
}

string show::getShowDetails() {
    return showName + " on the " + date + " at " + time;
}

// Initialise theatre floor plan
void show::initialiseFloorPlan() {
    // Initialise floor plan seats as available
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numSeatsPerRow; j++) {
            seat newSeat = seat(i + 1, j + 1, rowPrices[i], "A", showName);
            floorPlan[i][j] = newSeat;
        }
    }
}

void show::showAvailableSeats() {
    cout << "\n=======================================================" << endl;
    cout << "================== Select your seats ==================" << endl;
    cout << "=======================================================\n" << endl;

    cout << "\n            -------------- SCREEN --------------" << endl;
    cout << "\n                                                    Seat Price";
    for (int i = 0; i < numRows; i++) {
        cout << "\n          ┌───┐  ┌───┐  ┌───┐  ┌───┐  ┌───┐  ┌───┐" << endl;
        cout << " Row " << i + 1 << "   ";
        for (int j = 0; j < numSeatsPerRow; j++) {
            cout << " │ " << floorPlan[i][j].getSeatStatus() << " │ ";
        }
        cout << "    £" << rowPrices[i];
        cout << "\n          └───┘  └───┘  └───┘  └───┘  └───┘  └───┘";
    }
    cout << "\n Seat no.   1      2      3      4      5      6" << endl;

    cout << "\nA - Seat available" << endl;
    cout << "H - Seat on hold" << endl;
    cout << "S - Seat sold" << endl;
}

void show::deselectSeat(seat selectedSeat) {
    floorPlan[selectedSeat.getSeatRow() - 1][selectedSeat.getSeatNumber() - 1].setSeatStatus("A");

}

void show::selectSeat(seat selectedSeat) {
    floorPlan[selectedSeat.getSeatRow() - 1][selectedSeat.getSeatNumber() - 1].setSeatStatus("H");

}

seat show::getSelectedSeat(string row, string number) {
    int rowNum = stoi(row) - 1;
    int seatNum = stoi(number) - 1;
    return floorPlan[rowNum][seatNum];
}

#endif //OTS_SHOW_H
