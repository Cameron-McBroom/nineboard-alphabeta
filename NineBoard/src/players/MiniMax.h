#pragma once

#include "../Player.h"

class MiniMax : public Player {
private:
    int maxDepth_;
public:
    MiniMax(int maxDepth = 5) : maxDepth_(maxDepth) {}

    void getMove(NineBoard &board, int &row, int &col) const override
    {
        char oppSymbol = (symbol_ == 'X' ? 'O' : 'X');
        float bestScore {-INFINITY};
        int move {};
        for (auto const & legalMove : board.getLegalMoves()) {
            NineBoard copyBoard = NineBoard(board);
            copyBoard.addMove(symbol_, legalMove / 3, legalMove % 3);
            int utility = copyBoard.utility(symbol_, legalMove);
            if (utility >= 10000)  {
                move = legalMove;
                break;
            }
            float score = miniMax(copyBoard, 0, symbol_, oppSymbol,false, legalMove,  utility);
            if (score > bestScore) {
                bestScore = score;
                move = legalMove;
            }
        }
        row = move / 3;
        col = move % 3;
    }

    float miniMax(NineBoard &board, int depth, char symbol, char oppSymbol, bool maximizer, int lastMove, int scoreSoFar) const {
        char result = board.status();
        if (result != 'C' || depth == maxDepth_) {
            return scoreSoFar;
        }
        board.nextBoard(lastMove / 3, lastMove % 3);
        if (maximizer) {
            float bestScore = -INFINITY;
            for (const int &move : board.getLegalMoves()) {
                NineBoard copyBoard = NineBoard(board);
                copyBoard.addMove(symbol, move / 3, move % 3);
                int utility = copyBoard.utility(symbol, move);
                float score = miniMax(copyBoard, depth + 1, symbol, oppSymbol, false, move, scoreSoFar + utility);
                if (score > bestScore) bestScore = score;
            }
            return bestScore;
        } else {
            float bestScore = INFINITY;
            for (const int &move : board.getLegalMoves()) {
                NineBoard copyBoard = NineBoard(board);
                copyBoard.addMove(oppSymbol, move / 3, move % 3);
                int utility = copyBoard.utility(symbol, move);
                float score = miniMax(copyBoard, depth + 1, symbol, oppSymbol, true, move, scoreSoFar + utility);
                if (score < bestScore) bestScore = score;
            }
            return bestScore;
        }
    }
    std::string getName() const override {
        return "MiniMax Player";
    }

    unique_ptr<Player> child_clone() const override {
        return make_unique<MiniMax>(*this);
    }

    void getPlayerOptions() override {
        int depth {};
        cout << "What depth would you like to set MiniMax to? ";
        cin >> depth;
        while (depth > 10 || depth < 0) {
            cout << "Depth must be below 10 and above 0.\n What depth would you like to set?";
            cin >> depth;
        }
        cout << endl;
        maxDepth_ = depth;
    }

};

