#pragma once
#include "NineBoard.h"
#include <memory>

using std::unique_ptr;
using std::make_unique;

class Player {
public:
    Player(char symbol = 'X') : symbol_(symbol){};
    virtual ~Player() {}
    virtual void getPlayerOptions() = 0;
    virtual void getMove(NineBoard &currentBoard, int &row, int &col) const = 0;
    virtual std::string getName() const = 0;

    unique_ptr<Player> clone(char new_symbol) const {
        std::unique_ptr<Player> new_player = child_clone();
        new_player->symbol_ = new_symbol;
        return new_player;
    };

    char symbol() {
        return symbol_;
    }

    bool isHuman() {
        return getName() == "Human";
    }

protected:
    char symbol_;
    virtual unique_ptr<Player> child_clone() const = 0;

    // Helper method used in various player strategies - returns 0-8
    int getWinningPos(NineBoard &board, const char playerSymbol) const {
        vector<int> legalMoves = board.getLegalMoves();
        for (const auto &move: legalMoves) {
            NineBoard copyBoard = NineBoard(board);
            copyBoard.addMove(playerSymbol, move / 3, move % 3);
            if (copyBoard.status() == playerSymbol) return move;
        }
        return -1;
    }
};