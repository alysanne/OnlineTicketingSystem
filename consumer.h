#ifndef OTS_CONSUMER_H
#define OTS_CONSUMER_H
#include <iostream>
#include <iomanip>
#include <string>
#include "user.h"

using namespace std;

class consumer: public user {
public:
    consumer();
    ~consumer();
    void confirmUserDetails();
    void printUpdateOptions();
    void updateUserDetails();
    void sendTicketByEmail();
    string getFullName();
protected:
    string firstName;
    string lastName;
    string emailAddress;
};

// Constructor
consumer::consumer() {
    firstName = "Jean";
    lastName = "Valjean";
    emailAddress = "jean.valjean@lesmis.com";
}

// Destructor
consumer::~consumer() {}

// Override virtual functions

void consumer::confirmUserDetails() {
    string input;
    cout << "\n================================================" << endl;
    cout << "============= Confirm user details =============" << endl;
    cout << "================================================\n" << endl;

    cout << "First name: " << firstName << endl;
    cout << "Last name: " << lastName << endl;
    cout << "Email: " << emailAddress << endl;

    do {
        cout << "\nAre these details correct? (Y = Yes, N = No): ";
        getline(cin, input);
    } while (input != "Y" && input != "y" && input != "N" && input != "n");

    if (input == "Y" || input == "y") {
        cout << "Thanks for confirming your details!" << endl;
    } else {
        updateUserDetails();
    }
}

void consumer::sendTicketByEmail() {
    cout << "Ticket sent to email address: " << emailAddress << endl;
    cout << "------------------------------------------------------------------------" << endl;
}

void consumer::updateUserDetails() {
    string input, name, lName, email;

    cout << "\n================================================" << endl;
    cout << "============== Update your details =============" << endl;
    cout << "================================================\n" << endl;

    printUpdateOptions();
    getline(cin, input);

    while (input != "4") {
        if (input == "1") {
            cout << "Please provide your first name: ";
            getline(cin, name);
            firstName = name;
            cout << "\n~~~~~~ First name updated successfully ~~~~~~\n" << endl;
        } else if (input == "2") {
            cout << "Please provide your last name: ";
            getline(cin, lName);
            lastName = lName;
            cout << "\n~~~~~~ Last name updated successfully ~~~~~~\n" << endl;
        } else if (input == "3") {
            cout << "Please provide your email address: ";
            getline(cin, email);
            emailAddress = email;
            cout << "\n~~~~~~ Email updated successfully ~~~~~~\n" << endl;
        } else {
            cout << "\n >>>>>>>> Please provide a valid option. <<<<<<<<\n" << endl;
        }

        printUpdateOptions();
        getline(cin, input);
    }

    cout << "\n~~~~~~ Thank you for updating your details ~~~~~~\n" << endl;
}

void consumer::printUpdateOptions() {
    cout << "Please select one of the options below: " << endl;
    cout << " 1. Update first name: " << firstName << endl;
    cout << " 2. Update last name: " << lastName << endl;
    cout << " 3. Update email address: " << emailAddress << endl;
    cout << " 4. Exit\n" << endl;
    cout << "Type the option selected: ";
}

string consumer::getFullName() {
    return firstName + " " + lastName;
}

#endif //OTS_CONSUMER_H
