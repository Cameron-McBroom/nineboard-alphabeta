#pragma once

#include "../Player.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class HumanPlayer : public Player {
public:
    void getMove(NineBoard &board, int &row, int &col) const override
    {
        do {
            cout << "Player "<< symbol_ << " enter move: ";
            cin >> row >> col;
            cout << endl;
        } while (!board.isValidMove(row - 1, col - 1));
        row--;
        col--;
    }
    std::string getName() const override {
        return "Human";
    }

    unique_ptr<Player> child_clone() const override {
        return make_unique<HumanPlayer>();
    }

    void getPlayerOptions() override {};
};