#pragma  once
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>

using std::setw;
using std::vector;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;

class TicTacToe {
private:
    int _noOfMoves;
    char _board[3][3];

public:
    TicTacToe();
    TicTacToe(const TicTacToe& oldBoard);
    char spot(int row, int col) const;
    void addMove(char player, int r, int c);
    bool isValidMove(int r, int c);
    char gameStatus();
    int boardUtility(char playerSymbol);
    int boardUtility(const char symbol, const int lastMove);
    vector<int> getLegalMoves();
    int randomLegalMove();
    friend ostream& operator <<(ostream& outs, const TicTacToe& board);

};


TicTacToe::TicTacToe(const TicTacToe &oldBoard) {
    _noOfMoves = oldBoard._noOfMoves;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            _board[i][j] = oldBoard._board[i][j];
}

TicTacToe::TicTacToe() : _noOfMoves(0) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            _board[i][j] = ' ';
}

char TicTacToe::spot(const int row, const int col) const {
    return _board[row][col];
}

bool TicTacToe::isValidMove(int row, int col) {
    if (row > 3 || row < 0 || col > 3 || col < 0 || _board[row][col] != ' ') {
        cout << "Illegal move, make sure its on the board and the space is free\n";
        // prevent infinite loop by clearing cin if not integer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

char TicTacToe::gameStatus()
{
    // Check for win
    int firstDiag{}, secondDiag{};
    for (int i = 0; i < 3; i++) {
        //Check diagonals
        if (_board[i][i] == 'X') firstDiag += 1;
        if (_board[i][i] == 'O') firstDiag -= 1;
        if (_board[i][2 - i] == 'X') secondDiag += 1;
        if (_board[i][2 - i] == 'O') secondDiag -= 1;
        // Check count
        if (firstDiag == 3 || secondDiag == 3) return 'X';
        if (firstDiag == -3 || secondDiag == -3) return 'O';

        //Check rows & columns
        int rows{0}, cols{0};
        for (int j = 0; j < 3; j++) {
            if (_board[i][j] == 'X') rows += 1;
            if (_board[j][i] == 'X') cols += 1;
            if (_board[i][j] == 'O') rows -= 1;
            if (_board[j][i] == 'O') cols -= 1;
        }
        if (rows == 3 || cols == 3) return 'X';
        if (rows == -3 || cols == -3) return 'O';
    }
    // Check for draw
    if (_noOfMoves == 9) return 'D';

    return 'C';
}

void TicTacToe::addMove(char playerSymbol, int row, int col) {
    // Updates the move onto the _board
    _board[row][col] = playerSymbol;
    _noOfMoves++;

}

vector<int> TicTacToe::getLegalMoves() {
    vector<int> legalMoves{};
    for (int i = 0; i < 9; i ++)
        if (_board[i /3][i % 3] == ' ')
            legalMoves.push_back(i);
    return legalMoves;
}

int TicTacToe::boardUtility(const char symbol) {
    bool win {false};
    int score {0};
    char oppSymbol = (symbol == 'X' ? 'O' : 'X');
    const vector <vector<int>> winTriads {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Cols
            {0, 4, 8}, {2, 4, 6} // Diagonals
    };
    for (const auto &triad : winTriads) {
        int triadSum {};
        for (const auto &move: triad) {
            if (spot(move / 3, move % 3) == symbol) triadSum++;
            if (spot(move / 3, move % 3) == oppSymbol) triadSum--;
        }
        if (triadSum == -3) {
            score = -10000;
            win = true;
        }
        else if (triadSum == 3) {
            score = 10000;
            win = true;
        }
        else if (triadSum == -2) score = -3000;
        else if (triadSum == 2) score = 3000;
        else if (triadSum == -1) score = -10;
        else if (triadSum == 1) score = 10;

        if (win) break;
    }
    return score;
}

int TicTacToe::boardUtility(const char symbol, const int lastMove) {
    bool win {false};
    int score {0};
    char oppSymbol = (symbol == 'X' ? 'O' : 'X');
    const vector <vector<int>> winTriads {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Cols
            {0, 4, 8}, {2, 4, 6} // Diagonals
    };
    for (auto const &triad : winTriads) {
        int triadSum {};
        for (int move: triad) {
            if (spot(move / 3, move % 3) == symbol) triadSum += 1;
            if (spot(move / 3, move % 3) == oppSymbol) triadSum -= 1;
        }
        if (triadSum == -3) {
            score = -100000;
            win = true;
        }
        else if (triadSum == 3) {
            score = 100000;
            win = true;
        }
        else if (triadSum == -2) score -= 3000;
        else if (triadSum == 2) score += 3000;
        else if (triadSum == -1)  {
            // If -1 then player blocked
            if (_board[triad[0]/3][triad[0]/3] == symbol ||
            _board[triad[1]/3][triad[1]/3] == symbol ||
            _board[triad[1]/3][triad[1]/3] == symbol)
                score += 1000;
        }
        else if (triadSum == 1) {
            // If 1 && oppSymbol then player blocked
            if (_board[triad[0]/3][triad[0]/3] == oppSymbol ||
                _board[triad[1]/3][triad[1]/3] == oppSymbol ||
                _board[triad[1]/3][triad[1]/3] == oppSymbol)
                score -= 1000;
        }
        if (win) break;
    }
    // Slight increase in score if last move was a corner or middle position
    const vector <int> corners {0, 2, 6, 8};
    if (!win) {
        if (lastMove == 4 && spot(lastMove / 3, lastMove % 3) == symbol) score += 5;
        if (lastMove == 4 && spot(lastMove / 3, lastMove % 3) == oppSymbol) score -= 5;

        for (const int & corner : corners) {
            if (lastMove == corner && spot(lastMove / 3, lastMove % 3) == symbol) score += 2;
            if (lastMove == corner && spot(lastMove / 3, lastMove % 3) == oppSymbol) score -= 2;
        }
    }
    return score;
}

ostream &operator<<(ostream &out, const TicTacToe &board) {
    out << " - - - - - - - - - " << endl;
    for (int row = 0; row < 3; row++) {
        out << "|";
        for (int col = 0; col < 3; col++) {
            out << setw(3) << board._board[row][col];
            if (col != 3) out << "  |";
        }
        out << endl;
        if (row != 2)
            out << "| ---   ---   --- |\n";
    }
    out << " - - - - - - - - - " << endl;
    return out;
}

int TicTacToe::randomLegalMove() {
    vector <int> legalMoves {getLegalMoves()};
    int index = rand() % legalMoves.size();
    return legalMoves[index];
}


















