#pragma once

#include "../Player.h"

class MonteCarlo : public Player {
private:
    int numSimulations_;

public:
    void getMove(NineBoard &board, int &row, int &col) const override {
        // Get best score in max depth
        float highestWins{-INFINITY};
        int move{};
        vector<int> legalMoves = board.getLegalMoves();
        for (auto const &legalMove : legalMoves) {
            float positionWins = 0;
            for (int i = 0; i < numSimulations_; i++) {
                NineBoard copyBoard = NineBoard(board);
                copyBoard.addMove(symbol_, legalMove / 3, legalMove % 3);
                char result = simulateGame(copyBoard, symbol_, legalMove);
                if (result == symbol_) positionWins++;
            }
            if (positionWins > highestWins) {
                highestWins = positionWins;
                move = legalMove;
            }
        }
        row = move / 3;
        col = move % 3;
    }

    char simulateGame(NineBoard &copyBoard, char turn, const int &lastMove) const {
        char result = copyBoard.status();
        if (result == 'C') {
            copyBoard.nextBoard(lastMove / 3, lastMove % 3);
            turn == 'X' ? turn = 'O' : turn = 'X';
            int move = copyBoard.randomLegalMove();
            copyBoard.addMove(turn, move / 3 , move % 3);
            result = simulateGame(copyBoard, turn, move);
        }
        return result;
    }

    std::string getName() const override {
        return "Monte Carlo Player";
    }

    unique_ptr<Player> child_clone() const override {
        return make_unique<MonteCarlo>(*this);
    }

    void getPlayerOptions() override {
        int numGames;
        cout << "How many random simulations would you like Monte Carlo to run? ";
        cin >> numGames;
        while (numGames > 3000 || numGames < 0) {
            cout << "Simulations must be below 3000 and above 0.\nEnter simulations: ";
            cin >> numGames;
        }
        cout << endl;
        numSimulations_ = numGames;
    };
};
