#pragma once

#include "../Player.h"

class OneLayer: public Player {
public:
    void getMove(NineBoard &board, int &row, int &col) const override
    {
        // Check for winning positions first
        int winningPos = getWinningPos(board, symbol_);
        if (winningPos != -1) {
            row = winningPos / 3;
            col = winningPos % 3;
            return;
        }
        // If there is no winning positions check enemy winning positions and try block them
        char enemySymbol = symbol_ == 'X' ? 'O' : 'X';
        int losePos = getWinningPos(board, enemySymbol);
        if (losePos != -1) {
            row = losePos / 3;
            col = losePos % 3;
            return;
        }
        //Otherwise make random move.
        int randRowCol = board.randomLegalMove();
        row = randRowCol / 3;
        col = randRowCol % 3;
    }
    std::string getName() const override {
        return "One Layer Player";
    }
    unique_ptr<Player> child_clone() const override {
        return make_unique<OneLayer>(*this);
    }

    void getPlayerOptions() override {};

};