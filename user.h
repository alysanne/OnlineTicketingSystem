#ifndef OTS_USER_H
#define OTS_USER_H

#include <iostream>
#include <iomanip>
#include <string>
#include "show.h"
#include "basket.h"

using namespace std;

class user {
public:
    user();
    ~user();
    void loginUser();
    void requestPaymentDetails();
    void payBasket(basket &basket);
    virtual void sendTicketByEmail() {};
protected:
    string userName;
    string password;
    string cardNumber;
    void requestInput(string &input, string inputCue);
    bool validateUsername(string username);
    bool validatePassword(string password);
};

// Constructor
user::user() {
    userName = ""; // any username allowed for login
    password = "admin"; // password would be fetched from a database
}

// Destructor
user::~user() {}

void user::requestInput(string &input, string inputCue) {
    cout << inputCue;
    getline(cin, input);
}

bool user::validateUsername(string value) {
    // Returns true if valid, false if invalid
    return value.length() < 10 && value.length() > 2;
}

bool user::validatePassword(string value) {
    // Returns true if valid, false if invalid
    return value.compare(password) == 0;
}

// Customer log in
void user::loginUser() {
    string usernameInput;
    string passwordInput;

    cout << "\n================================================" << endl;
    cout << "====== Please log in to access the system ======" << endl;
    cout << "================================================\n" << endl;

    // Handle username input and validation
    requestInput(usernameInput, "Please enter your username: ");

    while (!validateUsername(usernameInput)) {
        cout << "Your username should between 2 and 10 characters" << endl;
        requestInput(usernameInput, "Please re-enter your username: ");
    }

    // Save username
    userName = usernameInput;

    // Handle password input and validation
    for (int i = 3; i > 0; i--) {
        requestInput(passwordInput, "Please enter your password: ");

        if (validatePassword(passwordInput)) {
            cout << "\n~~~~~~ Login was successful, welcome " << usernameInput << " ~~~~~~\n" << endl;
            break;
        }
        cout << "The password is incorrect, you have " << i - 1 << " more attempt(s)." << endl;
    }
}

void user::requestPaymentDetails() {
    string card;
    requestInput(card, "Please provide your payment card number: ");

    this -> cardNumber = card;
}

void user::payBasket(basket &basket) {
    cout << "\n~~~~~~ Processing payment for items ~~~~~~" << endl;
    cout << "\nCard number " << cardNumber << " will be charged £" << basket.getTotalPrice() << endl;
    cout << ". . ." << endl;
    cout << ". . ." << endl;
    cout << ". . ." << endl;
    cout << "\n~~~~~~ Payment was successful ~~~~~~\n" << endl;
}

#endif //OTS_USER_H
