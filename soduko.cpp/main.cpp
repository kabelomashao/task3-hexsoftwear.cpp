#include <iostream>
#include <chrono> // For time tracking
using namespace std;

#define N 9 // Sudoku size

// Function to print the Sudoku board
void printBoard(int board[N][N]) {
    cout << "\nSudoku Board:\n";
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed at board[row][col]
bool isValid(int board[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num || board[x][col] == num) return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) return false;
        }
    }

    return true;
}

// Function for the player to enter and erase numbers
void playerInput(int board[N][N]) {
    int row, col, num;
    while (true) {
        cout << "\nOptions:\n1. Enter Number\n2. Erase Number\n3. Exit Game\nChoice: ";
        int choice;
        cin >> choice;
        if (choice == 3) {
            cout << "Game exited.\n";
            exit(0);
        }

        cout << "Enter row (0-8), column (0-8): ";
        cin >> row >> col;

        if (choice == 1) {
            cout << "Enter number (1-9): ";
            cin >> num;
            if (isValid(board, row, col, num)) {
                board[row][col] = num;
                cout << "Number placed successfully!\n";
            } else {
                cout << "Invalid move! Try again.\n";
            }
        } else if (choice == 2) {
            board[row][col] = 0;
            cout << "Number erased successfully!\n";
        }

        printBoard(board);
    }
}

// Backtracking function to solve Sudoku
bool solveSudoku(int board[N][N], int row, int col) {
    if (row == N - 1 && col == N) return true;
    if (col == N) { row++; col = 0; }
    if (board[row][col] != 0) return solveSudoku(board, row, col + 1);

    for (int num = 1; num <= N; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board, row, col + 1)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int board[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    auto start = chrono::high_resolution_clock::now(); // Start timer
    printBoard(board);

    cout << "\nEnter numbers manually or let the program solve the puzzle.\n";
    playerInput(board); // Player can interact

    if (solveSudoku(board, 0, 0)) {
        auto end = chrono::high_resolution_clock::now(); // Stop timer
        chrono::duration<double> elapsed = end - start;

        cout << "\nCongratulations! Sudoku solved successfully.\n";
        printBoard(board);
        cout << "Time taken: " << elapsed.count() << " seconds\n";
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
