#include <iostream>
#include <cmath>
using namespace std;

void printArray(int array[], int solutionNumber) {
    cout << "Solution Number: " << solutionNumber << endl;
    // loops through the row numbers
    for (int row = 0; row < 8; row++) {
        // loops through the column numbers and compares the value at each column number to the current row number
        for (int col = 0; col < 8; col++) {
            // if the value inside of the array at the current column number is equal to the current row number, then a 1 is printed because that means that that specific column has a queen at that specific row; otherwise, a 0 is printed, and the loop moves on after a line break
            if (array[col] == row) cout << "1 ";
            else cout << "0 ";
        }
        cout << endl;
    }
    cout << endl;
}

bool tests(int array[]) {
    // loops from 7th to 0th column (this is necessary because otherwise it would only be running the tests for the last column and it should be running for every single column)
    for (int colNumber = 7; colNumber > 0; colNumber--) {
        // this inner for-loop goes from i to the current column number and checks to see if the any of the previous values before array[colNumber] are equal (queen on same row) or if the difference between row values and column values is equal (queen on diagonal)
        for (int i = 0; i < colNumber; i++) {
            if (array[i] == array[colNumber] || (colNumber - i) == abs(array[colNumber] - array[i])) {
                return false;
            }
        }
    }
    return true;
}

void updateBoard(int array[], int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7) {
    array[0] = i0;
    array[1] = i1;
    array[2] = i2;
    array[3] = i3;
    array[4] = i4;
    array[5] = i5;
    array[6] = i6;
    array[7] = i7;
}

int main() {
    // this array holds where each queen is at on the chess board (the array's index indicates the column number of the chess board and the value at that index indicates which row the queen is in)
    int board[8];
    // this variable holds the solution number and increments it by 1 when the tests for a configuration of queens pass
    int solutionNumber = 0;
    // 8 nested for-loops to go through every possibility of placing queens and then running the tests each time a configuration is updated to see if that configuration is viable or not
    for (int i0 = 0; i0 < 8; i0++) {
        for (int i1 = 0; i1 < 8; i1++) {
            for (int i2 = 0; i2 < 8; i2++) {
                for (int i3 = 0; i3 < 8; i3++) {
                    for (int i4 = 0; i4 < 8; i4++) {
                        for (int i5 = 0; i5 < 8; i5++) {
                            for (int i6 = 0; i6 < 8; i6++) {
                                for (int i7 = 0; i7 < 8; i7++) {
                                    updateBoard(board, i0, i1, i2, i3, i4, i5, i6, i7);
                                    // if this evaluates to false, it means the configuration of current queen placement is NOT good, and if true, then it IS GOOD
                                    if (tests(board)) {
                                        solutionNumber++;
                                        // prints the configuration given that the tests have been passed for the current configuration of queens
                                        printArray(board, solutionNumber);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}