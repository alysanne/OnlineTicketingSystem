#ifndef OTS_SHOW_H
#define OTS_SHOW_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class show {
public:
    show();
    ~show();
    void selectShow(string &showName, string &showDate);
    void selectTime(string &showTime);
    string getShowDetails();
    float getTotalPrice();
    void displaySeatSelection();
    void confirmSeatSelection();
    void initialiseFloorPlan();
    int requestNumSeats();
    int getNumSeats();
    void showAvailableSeats();
    void selectSeatsForShow();
    void undoSeatSelection();
    deque<seat> getSeatSelection();
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
    int numSeats;
    int maxSeats;
    float totalPrice;
    deque<seat> seatSelection;
};

// Constructor
show::show() {
    showName = "";
    date = "";
    time = "";
    numSeats = 0;
    maxSeats = 4;
    numSeatsPerRow = 6;
    numRows = 5;
    totalPrice = 0;
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

float show::getTotalPrice() {
    return totalPrice;
}

void show::confirmSeatSelection() {
    string input;
    cout << "You have reserved seats for " << getShowDetails() << endl;

    do {
        cout << "Do you wish to continue with the purchase of tickets? (Yes = Y, No = N): ";
        getline(cin, input);

        if (input == "N" || input == "n") {
            cout << "\n~~~~~ Your purchase has been cancelled, please start a new session to purchase tickets for a new show ~~~~~";
        }
    } while (input != "Y" && input != "y" && input != "N" && input != "n");
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

// Get the user's no. of seat
int show::requestNumSeats() {
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

int show::getNumSeats() {
    return numSeats;
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

void show::selectSeatsForShow() {
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
        seat selectedSeat = floorPlan[rowNum][seatNum];

        // Check seat status
        if (selectedSeat.getSeatStatus() != "A") {
            cout << "\n~~~~~ This seat is not available, please try again ~~~~~" << endl;
        } else {
            cout << "\n~~~~~ Seat reserved: Row " << row << " - Seat no. " << number << " ~~~~~" << endl;
            floorPlan[rowNum][seatNum].setSeatStatus("H");
            seatSelection.push_back(selectedSeat);
            seatReserved = true;
        }
    } while (!seatReserved);
}

void show::displaySeatSelection() {
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

deque<seat> show::getSeatSelection() {
    return seatSelection;
}

// Remove selected seats if user cancels
void show::undoSeatSelection() {
    while (!seatSelection.empty()) {
        seat selectedSeat = seatSelection.front();

        floorPlan[selectedSeat.getSeatRow() - 1][selectedSeat.getSeatNumber() - 1].setSeatStatus("A");
        seatSelection.pop_front();
    }
}

#endif //OTS_SHOW_H
