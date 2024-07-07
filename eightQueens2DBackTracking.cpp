#include <iostream>
using namespace std;

/* Complete the Eight Queens 2-dimensional array program with backtracking (i.e. print the board) that we worked on in class. */ 

// checks to see if their is a queen on the row that you are currently trying to place a queen in by looping through every spot in that row up to the current column you're at
bool rowTest(int chessBoard[][8], int row, int col) {
    for (int i = 0; i < col; i++) {
        if (chessBoard[row][i] == 1) {
            return false;
        }
    }
    return true;
}

// checks to see if their is a queen on the up-diagonal direction in the previous rows by looping through the previous columns, going one row and column back at a time
bool upDiagonalTest(int chessBoard[][8], int row, int col) {
    for (int j = 1; (row - j) >= 0 && (col - j) >= 0; j++) {
        if (chessBoard[row - j][col - j] == 1) {
            return false;
        }
    }
    return true;
}

// checks to see if their is a queen on the down-diagonal direction in the previous rows by looping through the previous columns, going one row down and one column back at a time
bool downDiagonalTest(int chessBoard[][8], int row, int col) {
    for (int k = 1; (row + k) <= 7 && (col - k) >= 0; k++) {
        if (chessBoard[row + k][col - k] == 1) {
            return false;
        }
    }
    return true;
}

int main() {
    // create the chess board, initialize each spot on the board to 0, and create variables to keep track of the row and column number of the board and solutionNumber to be printed
    int board[8][8] = {0}, row, col = 0, solutionNumber = 0;
    // place a queen in the first row and first column of the chess board (the top-left spot)
    board[0][0] = 1;
    // go to the next column by incrementing it by 1
    nextColumn:
        col++;
    // check to see if the column number has been incremented to 8, and if so, then you're off the board, meaning a solution has been found
        if (col == 8) goto print;
    // intialize row variable to -1 because it will be incremented to 0 in the next line of code
    row = -1;
    // go to the next row by incrementing it by 1
    nextRow:
        row++;
    // check to see if the row number has been incremented to 8, and if so, then you're off the board, meaning you can't place a queen at any spot in that column and need to backtrack to remove the previous queen and find a different ordering of queens
        if (row == 8) goto backtrack;
    // check to see if the row and diagonal directions tests pass, and if they do continue to the next column to place the next queen, if not go to the next row, which will jump to the previous lines of code and re-run the tests once the row has been incremented
    if (rowTest(board, row, col) && upDiagonalTest(board, row, col) && downDiagonalTest(board, row, col)) {
        // place a queen and move to the next column
        board[row][col] = 1;
        goto nextColumn;
    } else goto nextRow;
    // go back one column, start at the top spot of that column by changing row variable to 0 and loop through each row until you find a queen, once you do find a queen, remove it and go to the next row to see if that spot passes the tests
    backtrack:
        col--;
        row = 0;
        // the first column has ran out of spots where the first queen can be placed when this condition is true, meaning the program has backtracked to before column 0, which if off the board, signaling that the program has found all solutions
        if (col == -1) goto end;
        while (board[row][col] != 1) row++;
        board[row][col] = 0;
        goto nextRow;
    // this will print the solution and the solution number by incrementing its variable and running a nested for-loop to print the chess board, then backtracking to find a different solution
    print:
        solutionNumber++;
        cout << endl << "Solution: " << solutionNumber << endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        goto backtrack;
    end:
        return 0;
}