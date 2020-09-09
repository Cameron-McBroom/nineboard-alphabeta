#pragma once
#include "../Player.h"

class TwoLayer: public Player {
public:
    void getMove(NineBoard &board, int &row, int &col) const override
    {
        // first check any winning moves on current _board
        int winPos = getWinningPos(board, symbol_);
        if (winPos != -1) {
            row = winPos / 3;
            col = winPos % 3;
            return;
        }
        // if none then for each possible move check the next board to see if the opponent has a winning move.
        const char oppSymbol = symbol_ == 'X' ? 'O' : 'X';
        vector <int> safeMoves;
        vector <int> legalMoves = board.getLegalMoves();
        for (auto const & legalMove : legalMoves) {
            NineBoard copyBoard = NineBoard(board);
            // Add our move
            copyBoard.addMove(symbol_, legalMove / 3, legalMove % 3);
            // change to next board
            copyBoard.nextBoard(legalMove / 3, legalMove % 3 );
            // See if opponent can make winning move on next board
            int losingPos = getWinningPos(copyBoard, oppSymbol);
            // exclude that _board from next move if so
            if (losingPos == -1) {
                safeMoves.push_back(legalMove);
            }
        }

        //If no safe moves, we're dead anyways so make random move
        if (safeMoves.empty()) {
            int randMove = board.randomLegalMove();
            row = randMove / 3;
            col = randMove % 3;
            return;
        }

        //Otherwise, pick the one with the lowest opponent utility
        // (utility function returns negative for opponent symbol)
        float bestUtility{-INFINITY};
        int bestBoardCoords;
        const vector <int> corners {0, 2, 6, 8};
        for (auto const &move: safeMoves){
            NineBoard copyBoard = NineBoard(board);
            copyBoard.nextBoard(move / 3 , move % 3);
            auto utility = static_cast<float>(copyBoard.utility(symbol_));
            if (move == 4) utility += 5; // slight preference for middle
            if (count(corners.begin(), corners.end(), move)) utility += 3; // slight preference for corners
            if (utility > bestUtility) {
                bestUtility = utility;
                bestBoardCoords = move;
            }
        }
        row = bestBoardCoords / 3;
        col = bestBoardCoords % 3;
    }
    std::string getName() const override {
        return "Two Layer Player";
    }

    unique_ptr<Player> child_clone() const override {
        return make_unique<TwoLayer>(*this);
    }

    void getPlayerOptions() override {};

};