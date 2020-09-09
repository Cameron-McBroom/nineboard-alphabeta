#pragma once

#include "BoardCoordinate.h"

struct BoardCoordinate {
private:
    int row_;
    int col_;

public:
    BoardCoordinate(int row = rand() % 3, int col = rand() % 3) : row_(row), col_(col) {};

    void setRC(int row, int col) {
        row_ = row;
        col_ = col;
    }

    int row() const { return row_; }
    int col() const { return col_; }
};
