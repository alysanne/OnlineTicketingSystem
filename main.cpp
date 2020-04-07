#include <iostream>
#include <string>
#include "seat.h"
#include "ticket.h"
#include "consumer.h"
#include "show.h"

string getLoginType();
string getMainMenuSelection();
void showSelection(string &selectedShow, string &selectedShowDate, show &show);

void interactiveSeatSelection(int numSeats, seat &seat);

using namespace std;

int main() {
    // Initial variable declarations
    string loginType, userSelection, seatSelection, selectedShow, selectedShowDate;
    int numSeats;

    // Objects
    seat seat;
    consumer appUser;
    show show;
    ticket *ticket;

    // Get user type
    loginType = getLoginType();

    // Fallback for Agent users until dev ready
    if (loginType == "2") {
        cout << "This feature is not ready yet, please check again later!" << endl;
        return EXIT_SUCCESS;
    }

    // Login and request personal details
    appUser.loginUser();
    appUser.confirmUserDetails();

    // OTS main menu
    userSelection = getMainMenuSelection();

    // Log user out
    if (userSelection == "2") {
        cout << "~~~~~ You have been logged out, thank you for using our application! ~~~~~" << endl;
        return EXIT_SUCCESS;
    }

    // Select a show
    showSelection(selectedShow, selectedShowDate, show);

    // Select a seat
    seat.initialiseFloorPlan();
    numSeats = seat.getNumSeats();
    interactiveSeatSelection(numSeats, seat); // TODO: Add seat price to rows + display total price

    // TODO: Pay for seats and generate + send tickets

    return 0;
}

void interactiveSeatSelection(int numSeats, seat &seat) {
    string input;
    do {
        for (int i = 0; i < numSeats; i++) {
            seat.displayFloorPlan();
            seat.getSeatSelection();
        }

        do {
            cout << "\nAre you happy with your choice (Y = Yes, N = No)? ";
            getline(cin, input);
        } while (input != "Y" && input != "y" && input != "N" && input != "n");

        if (input == "N" || input == "n") {
            seat.undoSeatSelection();
        }
    } while (input == "N" || input == "n");
}

void showSelection(string &selectedShow, string &selectedShowDate, show &show) {
    string input;

    do {
        show.selectShow(selectedShow, selectedShowDate);
        show.selectTime(selectedShowDate);
        do {
            cout << "\nAre you happy with your choice (Y = Yes, N = No)? ";
            getline(cin, input);
        } while (input != "Y" && input != "y" && input != "N" && input != "n");
    } while (input == "N" || input == "n");
}

string getMainMenuSelection() {
    string input;

    cout << "\n=====================================" << endl;
    cout << "============= Main Menu =============" << endl;
    cout << "=====================================\n" << endl;

    cout << "Please select what would you like to do: " << endl;
    cout << " 1. Buy tickets for upcoming shows" << endl;
    cout << " 2. Log out\n" << endl;

    cout << "Type the number for the selected option: ";
    getline(cin, input);

    while (input != "1" && input != "2") {
        cout << "Type a valid number from the options above: ";
        getline(cin, input);
    }
    return input;
}

string getLoginType() {
    string input;
    cout << "\n===========================================================================" << endl;
    cout << "\nWelcome to the Bucks Centre for the Performing Arts Online Ticketing System\n" << endl;
    cout << "===========================================================================\n" << endl;
    cout << "Please select how would you like to login: " << endl;
    cout << " 1. Log in as a Consumer" << endl;
    cout << " 2. Log in as an Agent\n" << endl;

    cout << "Type the number for the selected option: ";
    getline(cin, input);

    while (input != "1" && input != "2") {
        cout << "Type a valid number from the options above: ";
        getline(cin, input);
    }
    return input;
}

