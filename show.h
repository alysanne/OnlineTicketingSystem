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
protected:
    string shows [5][2] = {
            {"Les Miserables", "20/04/2020"},
            {"Wicked", "20/04/2020"},
            {"Harry Potter and the Cursed Child", "20/04/2020"},
            {"Matilda", "20/04/2020"},
            {"Phantom of the Opera", "20/04/2020"}
    } ; // this data would come from a DB
    string showTimes [2] = {"11:00", "18:00"}; // this data would come from a DB
    string selectedShowName;
    string selectedShowDate;
    string selectedShowTime;
};

// Constructor
show::show() {
    selectedShowName = "";
    selectedShowDate = "";
    selectedShowTime = "";
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

    this -> selectedShowName = showName;
    this -> selectedShowDate = showDate;
}

void show::selectTime(string &showTime) {
    string input;

    cout << "\n========================================" << endl;
    cout << "=========== Select show time ===========" << endl;
    cout << "========================================\n" << endl;

    cout << "Please select a show time for " << selectedShowName  << ": " << endl;

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

    this -> selectedShowTime = showTime;
}


#endif //OTS_SHOW_H
