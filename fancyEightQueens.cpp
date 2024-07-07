#include <iostream>
using namespace std;

/* NOTE: if you're printing on a black background, then everything will be inverted color-wise -> this code is meant for white backgrounds, HOWEVER
         both ways work. */

// defining a new type called "box" which will be the type for the black box, white box, black queen box, and white queen box
typedef char box[5][7];

void printFancyChessBoardWithSolution(box* board[][8], box* bq, box* wq, int queenPositions[], int &solutionNum) {
    cout << "\n\nSolution Number: " << ++solutionNum << "\n\n";
    // this for-loop changes the positions of board based on what the array of Queen positions says is a solution
    for (int m = 0; m < 8; m++) {
        /* if the sum of the row and the column of the queens array is even, then set that row and column of the board array to a blackQueenBox */
        if ((queenPositions[m] + m) % 2 == 0) board[queenPositions[m]][m] = bq;
        /* otherwise, if the sum of the row and the column of the queens array is odd --> set that row and column of the board array to a whiteQueenBox */
        else board[queenPositions[m]][m] = wq;
    }
    // this for-loop prints the upper-border of the fancy chess board
    cout << "  ";
    /* the bound is (7 * 8) + 1 because each strip of characters being printed is 7 characters long and it's done 8 times, and then you need to add
       an additional character to go on top of the right-side vertical border 
    */
    for (int n = 0; n <= ((7 * 8) + 1); n++) {
        cout << char(196); // prints a horizontal line -> here it's being used as a border for the top of the fancy chess board
    }
    cout << endl;
    // these quadruply nested for-loops print the actual fancy chess board
    for (int r = 0; r < 8; r++) { // keeps track of the row
        for (int strip = 0; strip < 5; strip++) { // keeps track of how many strips of characters have been printed
            cout << "  " << char(179); // prints a vertical border on the left of the chess board before each strip is printed
            for (int c = 0; c < 8; c++) { // keeps track of the column
                // keeps track of how many pixels (characters) have been printed from either the blackBox, whiteBox, blackQueenBox, or whiteQueenBox
                for (int pixel = 0; pixel < 7; pixel++) {
                    /* * is used on (board[r][c]) to dereference it -> since the chessBoard 2D array points to variables of type "box" dereferencing
                       board[r][c] will always either give you a blackBox, whiteBox, blackQueenBox, or whiteQueenBox, and from there the program just
                       prints each character inside of that box (these characters have been initialized by previous methods in the program call stack)
                    */
                    cout << (*board[r][c])[strip][pixel];
                }
            }
            /* at the end of the first line of strips for each column, another vertical border is printed, but this time on the right of the chess board */
            cout << char(179) << endl;
        }
    }
    // this for-loop prints the bottom-border of the fancy chess board
    /* the bound is (7 * 8) + 1 because each strip of characters being printed is 7 characters long and it's done 8 times, and then you need to add
       an additional character to go on top of the right-side vertical border 
    */
    cout << "  ";
    for (int p = 0; p <= ((7 * 8) + 1); p++) {
        cout << char(196); // prints a horizontal line -> here it's being used as a border for the bottom of the fancy chess board
    }
}

void backtrack(int board[], int* col) {
    *col -= 1; // go back one column
    if (*col < 0) return; // if the column has been backtracked to a value that is less than 0, all solutions have been printed, so terminate method
    board[*col]++; // move on to the next row
    // if the previous column has moved beyond the last row, then reset the queen's row value for that column and backtrack again to the previous column 
    if (board[*col] > 7) { 
        board[*col] = 0;
        backtrack(board, col);
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

void initializeChessBoardOfPointers(box* board[][8], box* bb, box* wb) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((row + col) % 2 == 0) board[row][col] = bb; // if the row + the column is even, then make board[row][col] point to a blackBox
            else board[row][col] = wb; // otherwise if the row and column's sum is odd, then make board[row][col] point to a whiteBox
        }
    }
}

void initializeAllVariablesOfType_box(box bb, box wb, box bq, box wq) {
    /* these nested for-loops go through each entry of each variable of type "box" and initialize them to the correct characters -> either black or 
       blank (white)
    */
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            bb[i][j] = char(219); // filling in each entry of the blackBox with a black character 
            wb[i][j] = ' '; // filling in each entry of the whiteBox with a blank (white) character
            bq[i][j] = ' '; // filling in each entry of the blackQueenBox with a blank (white) character -> will later be changed to depict a black crown
            wq[i][j] = char(219); // filling in each entry of the whiteQueenBox with a black character -> will later be changed to depict a white crown
        }
    }
    // now that blackQueenBox and whiteQueenBox have their backgrounds filled -> change certain entries of those 2D arrays to depict the Queen crowns
    bq[1][1] = char(219);
    bq[1][3] = char(219);
    bq[1][5] = char(219);
    bq[2][1] = char(219);
    bq[2][3] = char(219);
    bq[2][5] = char(219);
    bq[3][1] = char(219);
    bq[3][2] = char(219);
    bq[3][3] = char(219);
    bq[3][4] = char(219);
    bq[3][5] = char(219);
    wq[1][1] = ' ';
    wq[1][3] = ' ';
    wq[1][5] = ' ';
    wq[2][1] = ' ';
    wq[2][3] = ' ';
    wq[2][5] = ' ';
    wq[3][1] = ' ';
    wq[3][2] = ' ';
    wq[3][3] = ' ';
    wq[3][4] = ' ';
    wq[3][5] = ' ';
}

int main() {
    /* these variables will be 2D arrays of either black or blank (white) characters -> blackBox and whiteBox will either contain all black or blank 
       (white) characters; blackQueenBox will contain blank (white) characters with black characters in certain places such that a black queen crown 
       is depicted; whiteQueenBox will contain black characters with blank (white) characters in certain places such that a white queen crown is 
       depicted; chessBoard is a 2D array of "box" pointers -> each pointer will point to either a blackBox or a whiteBox OR a blackQueenBox or a 
       whiteQueenBox IF there is a Queen in that position of the board.
    */
    box blackBox, whiteBox, blackQueenBox, whiteQueenBox, *chessBoard[8][8];
    // the method below fills up the variables of type "box" with the appropriate characters
    initializeAllVariablesOfType_box(blackBox, whiteBox, blackQueenBox, whiteQueenBox);
    // the method below sets the pattern of the chess board (alternating black-white)
    initializeChessBoardOfPointers(chessBoard, &blackBox, &whiteBox);
    /* the 1D array whereAreTheQueens tells you which position or row each Queen is in for each column of the chessboard; col keeps track of the
       index of whereAreTheQueens; solutionNumber keeps track of which solution the program is currently up to
    */
    int whereAreTheQueens[8] = {0}, col = 1, solutionNumber = 0;
    // if the program backtracks beyond the first column, then that indicates that all 92 solutions have been found and the program should terminate
    while (col != -1) { 
        // if the program has moved beyond the last column, it means a solution has been found and should be printed, then backtracking should initiate to find a different solution
        if (col > 7) {
            // prints a virtual fancy chess board to display the discovered solution
            printFancyChessBoardWithSolution(chessBoard, &blackQueenBox, &whiteQueenBox, whereAreTheQueens, solutionNumber);
            /* re-intializing the fancy chess board back to the state it was in before depicting the positions of the queens of the current solution, so it
               can get ready for printing the next solution 
            */
            initializeChessBoardOfPointers(chessBoard, &blackBox, &whiteBox);
            // backtrack by passing in the chess board array (called by reference by default) and column number (manually called by reference in formal parameter list)
            backtrack(whereAreTheQueens, &col);
        }
        // if the previous column has moved beyond the last row, then reset the queen's row value for that column and backtrack again to the previous column 
        else if (whereAreTheQueens[col] > 7) {
            whereAreTheQueens[col] = 0;
            backtrack(whereAreTheQueens, &col);
        }
        // checks if the row that the queen is placed in currently is ok, and if yes, then the program moves to the next column
        else if (tests(whereAreTheQueens, col)) col++;
        // otherwise it moves to the next row and checks the conditions above all over again
        else whereAreTheQueens[col]++;
    }
    return 0;
}