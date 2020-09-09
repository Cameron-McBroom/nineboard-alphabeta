#pragma once
#include <iostream>
#include <random>
#include <iomanip>
#include "TicTacToe.h"
#include "BoardCoordinate.h"
#include "ConsoleColours.h"

using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::setw;

class NineBoard {
private:
    TicTacToe nineBoard_[3][3];
    BoardCoordinate boardCoords_;
    vector<int> lastMove_; // used to colour last move for better usability
    int noOfMoves_;
    TicTacToe& getCurrentBoard();

    // Long display _board function broken up into smaller easier to understand functions
    void printTopBorder(const int &nineRow);
    void printBottomBorders(const int &nineRow);
    void printCentreSquares(const int &nineRow, int &nineCol, int &row);
    void printDividingLines(const int &nineRow);
    void printBody(int &nineRow, int &nineCol);

public:
    NineBoard();
    NineBoard(const NineBoard &oldBoard);
    char status();
    void displayBoard();
    int utility(char symbol);
    int utility(char symbol, int lastMove);
    bool isValidMove(int row, int col);
    vector <int> getLegalMoves();
    int randomLegalMove();
    void addMove(char playerSymbol, int row, int col);
    TicTacToe getBoard(int row, int col) const; // gets any of the nine boards by coords
    bool isFinished(); // Checks whether the previous move ended the game
    void nextBoard(int prevMoveRow, int prevMoveCol); // Takes the last move and updates to next board
};


NineBoard::NineBoard() : noOfMoves_(0) {}

NineBoard::NineBoard(const NineBoard &oldBoard)
{
    boardCoords_ = oldBoard.boardCoords_;
    noOfMoves_ = oldBoard.noOfMoves_;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            nineBoard_[i][j] = TicTacToe(oldBoard.nineBoard_[i][j]);
}

bool NineBoard::isFinished() {
    char gameStat = getCurrentBoard().gameStatus();
    return gameStat == 'X' || gameStat == 'O' || noOfMoves_ >= 81;
}

TicTacToe& NineBoard::getCurrentBoard() {
    return nineBoard_[boardCoords_.row()][boardCoords_.col()];
}

TicTacToe NineBoard::getBoard(int row, int col) const {
    TicTacToe board = nineBoard_[row][col];
    return board;
}

void NineBoard::nextBoard(int prevMoveRow, int prevMoveCol){
    // Safety check for win
    if (isFinished()) return;

    // Make sure next board not full
    TicTacToe next = getBoard(prevMoveRow, prevMoveCol);
    if (next.gameStatus() == 'C'){
        boardCoords_.setRC(prevMoveRow, prevMoveCol);
        return;
    }
    // If full, loop to find one that isn't
    int randRow{}, randCol{};
    while (next.gameStatus() == 'D') {
        getBoard(rand() % 3, rand() % 3);
    }
    boardCoords_.setRC(randRow, randCol);
}

void NineBoard::addMove(char playerSymbol, int row, int col) {
    noOfMoves_++;
    // store last move coord, to colour last _player move
    lastMove_ = {boardCoords_.row(), boardCoords_.col(), row, col};
    getCurrentBoard().addMove(playerSymbol, row, col);
}

void NineBoard::displayBoard() {
    int nineRow{}, nineCol{};
    printTopBorder(nineRow);
    printBody(nineRow, nineCol);
    cout << endl;
}

char NineBoard::status() {
    return getCurrentBoard().gameStatus();
}

vector<int> NineBoard::getLegalMoves() {
    return getCurrentBoard().getLegalMoves();
}

int NineBoard::randomLegalMove() {
   return getCurrentBoard().randomLegalMove();
}

int NineBoard::utility(char symbol) {
    return getCurrentBoard().boardUtility(symbol);
}

int NineBoard::utility(char symbol, int lastMove) {
    return getCurrentBoard().boardUtility(symbol, lastMove);
}

bool NineBoard::isValidMove(int row, int col) {
    return getCurrentBoard().isValidMove(row, col);
}

void NineBoard::printBody(int &nineRow, int &nineCol) {
    //Main board printing loop
    for (nineRow = 0; nineRow < 3; nineRow++){
        for (int row = 0; row < 3; row++) {
            printCentreSquares(nineRow, nineCol, row);
            cout << endl;
            if (row != 2)
                printDividingLines(nineRow);
            if (row < 2) cout << endl;
        }
        printBottomBorders(nineRow);
    }
}
void NineBoard::printTopBorder(const int &nineRow) {
    for (int col = 0; col < 3; col++){
        if (boardCoords_.col() == col && boardCoords_.row() == nineRow)
            cout << red << " * * * * * * * * * " << white;
        else
            cout << " - - - - - - - - - ";
    }
    cout << endl;
}
void NineBoard::printBottomBorders(const int &nineRow) {
    for (int col = 0; col < 3; col++){
        // since it prints bottom lines of each square some need to print twice
        if (boardCoords_.col() == col && (boardCoords_.row() == nineRow || boardCoords_.row() == nineRow + 1) ) {
            cout << red <<" * * * * * * * * * " << white;
        }
        else cout  << " - - - - - - - - - ";
    }
    cout << endl;
}
void NineBoard::printDividingLines(const int &nineRow) {
    for (int col = 0; col < 3; col++)
        if (boardCoords_.row() == nineRow && boardCoords_.col() == col)
            cout << red <<"*"<< white <<" ---   ---   --- "<< red <<"*"<< white;
        else
            cout << "| ---   ---   --- |";
}
void NineBoard::printCentreSquares(const int &nineRow, int &nineCol, int &row) {
    for (nineCol = 0; nineCol < 3; nineCol++){
        if (boardCoords_.row() == nineRow && boardCoords_.col() == nineCol)
            cout << red << "*" << white;
        else
            cout << "|";
        for (int col = 0; col < 3; col++) {
            char spot = getBoard(nineRow, nineCol).spot(row, col);
            if ( vector<int>{nineRow, nineCol, row, col} == lastMove_) cout << red;
            else if (spot == 'X') cout << yellow;
            else if (spot == 'O') cout << green;
            cout << setw(3) << spot << white;
            if (col != 3 && boardCoords_.col() == nineCol && boardCoords_.row() == nineRow) {
                col == 2 ? cout << red <<"  *" << white: cout << "  |";
            } else if (col != 3) cout << "  |";
        }
    }
}


