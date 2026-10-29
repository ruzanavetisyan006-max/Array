#include <iostream>
#include <vector>

using namespace std;

const int TOTAL_SEATS = 10;
const int FIRST_CLASS_START = 0;
const int FIRST_CLASS_END = 4;
const int ECONOMY_START = 5;
const int ECONOMY_END = 9;

void displayMenu();
int getSectionChoice();
bool assignSeat(vector<int>& seats, int start, int end);
void handleFullSection(vector<int>& seats, int preferredChoice);
void printBoardingPass(int seatNumber);
bool isPlaneFull(const vector<int>& seats);

int main() {
    vector<int> seats(TOTAL_SEATS, 0);
    while (!isPlaneFull(seats)) {
        displayMenu();
        int choice = getSectionChoice();

        if (choice == 1) {
            if (!assignSeat(seats, FIRST_CLASS_START, FIRST_CLASS_END)) {
                handleFullSection(seats, 1);
            }
        } 
        else if (choice == 2) {
            if (!assignSeat(seats, ECONOMY_START, ECONOMY_END)) {
                handleFullSection(seats, 2);
            }
        } 
        else {
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }

    cout << "\nAll seats are booked. The plane is full.\n";
    return 0;
}

void displayMenu() {
    cout << "\nPlease type 1 for \"First Class\"\n";
    cout << "Please type 2 for \"Economy\"\n";
    cout << "Your choice: ";
}

int getSectionChoice() {
    int choice;
    cin >> choice;
    return choice;
}

bool assignSeat(vector<int>& seats, int start, int end) {
    for (int i = start; i <= end; ++i) {
        if (seats[i] == 0) {
            seats[i] = 1;
            printBoardingPass(i + 1);
            return true;
        }
    }
    return false;
}

void handleFullSection(vector<int>& seats, int preferredChoice) {
    char response;
    
    if (preferredChoice == 1) {
        cout << "\nFirst Class is full. Would you like to be placed in Economy? (y/n): ";
        cin >> response;
        if (response == 'y' || response == 'Y') {
            if (!assignSeat(seats, ECONOMY_START, ECONOMY_END)) {
                cout << "Economy is also full.\n";
            }
        } else {
            cout << "Next flight leaves in 3 hours.\n";
        }
    } else {
        cout << "\nEconomy is full. Would you like to be placed in First Class? (y/n): ";
        cin >> response;
        if (response == 'y' || response == 'Y') {
            if (!assignSeat(seats, FIRST_CLASS_START, FIRST_CLASS_END)) {
                cout << "First Class is also full.\n";
            }
        } else {
            cout << "Next flight leaves in 3 hours.\n";
        }
    }
}

void printBoardingPass(int seatNumber) {
    cout << " Seat Number: " << seatNumber << "\n";
    if (seatNumber >= 1 && seatNumber <= 5) {
        cout << " Section:     First Class\n";
    } else {
        cout << " Section:     Economy\n";
    }
}

bool isPlaneFull(const vector<int>& seats) {
    for (int seat : seats) {
        if (seat == 0) {
            return false;
        }
    }
    return true;
}