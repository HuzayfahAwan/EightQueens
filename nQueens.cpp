#include <iostream>
#include <cmath>
using namespace std;

void initializeBoardToAllZeros(int* array, int n) {
    for (int i = 0; i < n; i++) {
        *(array + i) = 0;
    }
}

void backtrack(int board[], int &col, int n) {
    col--; // go back one column
    if (col < 0) return; // if the column has been backtracked to a value that is less than 0, all solutions have been printed, so terminate method
    board[col]++; // move on to the next row
    // if the previous column has moved beyond the last row, then reset the queen's row value for that column and backtrack again to the previous column 
    if (board[col] > (n-1)) { 
        board[col] = 0;
        backtrack(board, col, n);
    }
    /* the test above does not have to be done inside of this function, but having it here makes it so that the while-loop in the main() function runs one less time.
       for example -> If the column = 7 and row = 7 and a queen cannot be placed in spot 7,7 then the program makes the row = 8 by incrementing it by 1. After that,
                      the row > 7 condition in main() says to reset the row value for that column and backtrack by going to the previous column and incrementing the row value.
                      So now, column = 6 and let's say row = 7. If that's the case, then the backtrack() function increments row to 8 and sends the information back to main().
                      The while-loop would then have to run again and initiate another backtrack. To avoid this, the row > 7 condition can also be placed here in addition to main(),
                      so that one backtrack() call from main() saves the while-loop in main() from running again by initiating more than one backtrack recursively if necessary.
     */
}

bool tests(int board[], int col) {
    // looping through the columns before the column that is currently being checked for placing a queen in the current row value and comparing the values on each iteration for all directions (horizontal, up-diagonal, down-diagonal)
    for (int i = 0; i < col; i++) {
        if (board[col] == board[i] || (col - i) == abs(board[col] - board[i])) return false; // if one of these tests fail, a queen cannot be placed in the current row value of the current column of the board
    }
    return true; // if the statement above inside of the for-loop never evaluates to true after all iterations are complete, then it means that a queen can be placed in the current row value of the current column of the board
}

int nQueens(int n) {
    int numOfSolutions = 0, col = 1;
    // initialize the chess board and the values inside of each of the indices tell the row that the queen in that column is currently placed in)
    int* board = new int[n];
    // initialize the chess board to hold all zeros
    initializeBoardToAllZeros(board, n);
    // if the program backtracks beyond the first column, then that indicates that all solutions have been found and the function should terminate
    while (col != -1) { 
        // if the program has moved beyond the last column, it means a solution has been found and should be printed, then backtracking should initiate to find a different solution
        if (col > (n-1)) {
            numOfSolutions++;
            backtrack(board, col, n); // backtrack by passing in the chess board array (called by reference by default) and column number (manually called by reference in formal parameter list)
        }
        // if the previous column has moved beyond the last row, then reset the queen's row value for that column and backtrack again to the previous column 
        else if (board[col] > (n-1)) {
            board[col] = 0;
            backtrack(board, col, n);
        }
        // checks if the row that the queen is placed in currently is ok, and if yes, then the program moves to the next column
        else if (tests(board, col)) col++;
        // otherwise it moves to the next row and checks the conditions above all over again
        else board[col]++;
    }
    delete[] board;
    return numOfSolutions;
}

int main() {
    int n;
    cout << "Enter an integer and I will tell you how many solutions there are for the Eight Queens problem for every integer starting from 1 up to and including that integer: ";
    cin >> n;
    for (int i = 1; i <= n; i++) cout << "There are " << nQueens(i) << " solutions to the " << i << " queens problem." << endl;
    return 0;
}