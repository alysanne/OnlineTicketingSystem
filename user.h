#ifndef OTS_USER_H
#define OTS_USER_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class user {
public:
    user();
    ~user();
    void loginUser();
    void getPaymentInfo();
    virtual void saveUserDetails() {};
    virtual void sendTicketByEmail() {};
protected:
    string username;
    string password;
    void requestInput(string &input, string inputCue);
    bool usernameIsValid(string username);
    bool passwordIsValid(string password);
};

// Constructor
user::user() {
    username = ""; // any username allowed for login
    password = "admin"; // password would be fetched from a database
}

// Destructor
user::~user() {}

void user::requestInput(string &input, string inputCue) {
    cout << inputCue;
    getline(cin, input);
}

bool user::usernameIsValid(string value) {
    // Returns true if valid, false if invalid
    return value.length() < 10 && value.length() > 2;
}

bool user::passwordIsValid(string value) {
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

    while (!usernameIsValid(usernameInput)) {
        cout << "Your username should between 2 and 10 characters" << endl;
        requestInput(usernameInput, "Please re-enter your username: ");
    }

    // Handle password input and validation
    for (int i = 3; i > 0; i--) {
        requestInput(passwordInput, "Please enter your password: ");

        if (passwordIsValid(passwordInput)) {
            cout << "\n~~~~~~ Login was successful, welcome " << usernameInput << " ~~~~~~\n" << endl;
            break;
        }
        cout << "The password is incorrect, you have " << i - 1 << " more attempt(s)." << endl;
    }
}

#endif //OTS_USER_H
