#include <iostream>
#include <vector>

using namespace std;

const int FLOOR_SIZE = 20;

struct Command {
    int id;
    int steps;
};

enum Direction { RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3 };

void executeCommands(const vector<Command>& commands, vector<vector<int>>& floor);
void printFloor(const vector<vector<int>>& floor);

int main() {
    vector<vector<int>> floor(FLOOR_SIZE, vector<int>(FLOOR_SIZE, 0));

    vector<Command> commands = {
        {2, 0},
        {5, 12},
        {3, 0},
        {5, 12},
        {3, 0},
        {5, 12},
        {3, 0},
        {5, 12},
        {1, 0},
        {6, 0},
        {9, 0}
    };

    executeCommands(commands, floor);

    return 0;
}

void executeCommands(const vector<Command>& commands, vector<vector<int>>& floor) {
    int currentRow = 0;
    int currentCol = 0;
    int currentDirection = RIGHT;
    bool isPenDown = false;

    const int rowMoves[4] = {0, 1, 0, -1};
    const int colMoves[4] = {1, 0, -1, 0};

    for (const auto& cmd : commands) {
        switch (cmd.id) {
            case 1:
                isPenDown = false;
                break;
            case 2:
                isPenDown = true;
                floor[currentRow][currentCol] = 1;
                break;
            case 3:
                currentDirection = (currentDirection + 1) % 4;
                break;
            case 4:
                currentDirection = (currentDirection + 3) % 4;
                break;
            case 5: { 
                int steps = cmd.steps;
                for (int s = 0; s < steps; ++s) {
                    int nextRow = currentRow + rowMoves[currentDirection];
                    int nextCol = currentCol + colMoves[currentDirection];

                    if (nextRow >= 0 && nextRow < FLOOR_SIZE && nextCol >= 0 && nextCol < FLOOR_SIZE) {
                        currentRow = nextRow;
                        currentCol = nextCol;
                        if (isPenDown) {
                            floor[currentRow][currentCol] = 1;
                        }
                    } else {
                        break;
                    }
                }
                break;
            }
            case 6:
                printFloor(floor);
                break;
            case 9:
                return;
            default:
                cout << "Unknown command: " << cmd.id << "\n";
                break;
        }
    }
}

void printFloor(const vector<vector<int>>& floor) {
    for (int r = 0; r < FLOOR_SIZE; ++r) {
        for (int c = 0; c < FLOOR_SIZE; ++c) {
            if (floor[r][c] == 1) {
                cout << "* ";
            } else {
                cout << "  ";
            }
        }
        cout << "\n";
    }
}