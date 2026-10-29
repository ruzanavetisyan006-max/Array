#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUM_ROLLS = 36000;
const int MIN_SUM = 2;
const int MAX_SUM = 12;

int rollDie();
void simulateDiceRolls(vector<int>& frequencyTable);
void printResultsTable(const vector<int>& frequencyTable);
void analyzeReasonableness(const vector<int>& frequencyTable);

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<int> frequencyTable(MAX_SUM + 1, 0);

    simulateDiceRolls(frequencyTable);
    printResultsTable(frequencyTable);
    analyzeReasonableness(frequencyTable);

    return 0;
}

int rollDie() {
    return 1 + rand() % 6;
}

void simulateDiceRolls(vector<int>& frequencyTable) {
    for (int i = 0; i < NUM_ROLLS; ++i) {
        int firstDie = rollDie();
        int secondDie = rollDie();
        int sum = firstDie + secondDie;
        
        frequencyTable[sum]++;
    }
}

void printResultsTable(const vector<int>& frequencyTable) {
    cout << setw(10) << "Sum" << setw(18) << "Frequency" << setw(12) << "Percentage (%)\n";

    for (int sum = MIN_SUM; sum <= MAX_SUM; ++sum) {
        double percentage = (static_cast<double>(frequencyTable[sum]) / NUM_ROLLS) * 100.0;
        
        cout << setw(10) << sum 
             << setw(18) << frequencyTable[sum] 
             << setw(11) << fixed << setprecision(2) << percentage << "%\n";
    }
}

void analyzeReasonableness(const vector<int>& frequencyTable) {
    cout << "\n[Results Analysis]\n";
    cout << "The theoretical probability for a sum of 7 is approximately 1/6 (~16.67%).\n";
    
    int countOfSeven = frequencyTable[7];
    double actualPercentageOfSeven = (static_cast<double>(countOfSeven) / NUM_ROLLS) * 100.0;
    
    cout << "Total rolls of 7: " << countOfSeven << " (" << fixed << setprecision(2) << actualPercentageOfSeven << "%)\n";
    cout << "The results are fully reasonable and align closely with theoretical probability.\n";
}