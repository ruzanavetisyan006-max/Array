#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

const int NUM_PRODUCTS = 5;
const int NUM_SALESPEOPLE = 4;

void inputSalesData(vector<vector<double>>& salesMatrix);
void calculateTotals(vector<vector<double>>& salesMatrix);
void printTable(const vector<vector<double>>& salesMatrix);

int main() {
    vector<vector<double>> salesMatrix(NUM_PRODUCTS + 1, vector<double>(NUM_SALESPEOPLE + 1, 0.0));

    cout << "Enter sales slips (salesperson [1-4], product [1-5], dollar value).\n";
    cout << "Enter 0 0 0 or EOF to finish input.\n\n";

    inputSalesData(salesMatrix);
    calculateTotals(salesMatrix);
    printTable(salesMatrix);

    return 0;
}

void inputSalesData(vector<vector<double>>& salesMatrix) {
    int salesperson;
    int product;
    double dollarValue;

    while (cin >> salesperson >> product >> dollarValue) {
        if (salesperson == 0 && product == 0 && dollarValue == 0) {
            break;
        }

        if (salesperson >= 1 && salesperson <= NUM_SALESPEOPLE &&
            product >= 1 && product <= NUM_PRODUCTS) {
            // Adjusting to 0-based indexing
            salesMatrix[product - 1][salesperson - 1] += dollarValue;
        } else {
            cout << "Invalid input. Salesperson must be 1-4, product must be 1-5.\n";
        }
    }
}

void calculateTotals(vector<vector<double>>& salesMatrix) {
    double grandTotal = 0.0;

    for (int i = 0; i < NUM_PRODUCTS; ++i) {
        double rowTotal = 0.0;
        for (int j = 0; j < NUM_SALESPEOPLE; ++j) {
            rowTotal += salesMatrix[i][j];
        }
        salesMatrix[i][NUM_SALESPEOPLE] = rowTotal;
    }

    for (int j = 0; j < NUM_SALESPEOPLE; ++j) {
        double colTotal = 0.0;
        for (int i = 0; i < NUM_PRODUCTS; ++i) {
            colTotal += salesMatrix[i][j];
        }
        salesMatrix[NUM_PRODUCTS][j] = colTotal;
        grandTotal += colTotal;
    }

    salesMatrix[NUM_PRODUCTS][NUM_SALESPEOPLE] = grandTotal;
}

void printTable(const vector<vector<double>>& salesMatrix) {
    cout << setw(12) << "Product";
    for (int j = 1; j <= NUM_SALESPEOPLE; ++j) {
        cout << setw(12) << ("Sp " + to_string(j));
    }
    cout << setw(14) << "Total" << "\n";

    for (int i = 0; i < NUM_PRODUCTS; ++i) {
        cout << setw(12) << ("Prod " + to_string(i + 1));
        for (int j = 0; j <= NUM_SALESPEOPLE; ++j) {
            cout << setw(12) << fixed << setprecision(2) << salesMatrix[i][j];
        }
        cout << "\n";
    }

    cout << setw(12) << "Total";
    for (int j = 0; j <= NUM_SALESPEOPLE; ++j) {
        cout << setw(12) << fixed << setprecision(2) << salesMatrix[NUM_PRODUCTS][j];
    }
}