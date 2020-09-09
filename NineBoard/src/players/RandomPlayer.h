#pragma once

#include "../Player.h"

class RandomPlayer: public Player {
public:
    void getMove(NineBoard &board, int &row, int &col) const override {
        int randMove = board.randomLegalMove();
        row = randMove / 3;
        col = randMove % 3;
    }

    std::string getName() const override {
        return "Random Player";
    }

    unique_ptr<Player> child_clone() const override {
        return make_unique<RandomPlayer>(*this);
    }

    void getPlayerOptions() override {};

};