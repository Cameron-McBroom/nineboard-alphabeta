#pragma  once
#include "NineBoard.h"
#include <iostream>
#include "GameStats.h"
#include "NineBoard.h"
#include <math.h>
#include <string>

class GameStats {
private:
    std::string XPlayerName_;
    std::string OPlayerName_;
    int gameCount_;
    int drawCount_;
    int xWins_;
    int oWins_;
    int totalMoves_;
    int currentGameMoves_;
    int highestMoves_;
    float lowestMoves_;

public:
    GameStats(std::string xName = "", std::string oName = "") :
            XPlayerName_(xName), OPlayerName_(oName),
            gameCount_(0), drawCount_(0), xWins_(0), oWins_(0),
            totalMoves_(0), currentGameMoves_(0), highestMoves_(0), lowestMoves_(INFINITY)
            {}

    void incrementMoves() {
        totalMoves_ ++;
        currentGameMoves_++;
    }

    int gameCount() { return gameCount_; }

    void printResults() const {
    cout << "\n\nFinal Results:" << endl;
    cout << XPlayerName_ << " X with " << xWins_ << " wins" << endl;
    cout << OPlayerName_ << " O with " << oWins_ << " wins" << endl;
    cout << "Draws  " << drawCount_ << endl;
    cout << "Highest number of moves of the match was: " << highestMoves_ << endl;
    cout << "Lowest number of moves of the match was: " << lowestMoves_ << endl;
    if (gameCount_ > 5){
        cout << "Average number of moves in each game was: " << totalMoves_ / gameCount_ << endl << endl;
        double winRate = xWins_ > oWins_ ? static_cast<double>(xWins_) / gameCount_ : static_cast<double>(oWins_) /gameCount_;
        xWins_ > oWins_ ? (cout << XPlayerName_ << " X won ") : (cout << OPlayerName_ << " O won ");
        cout << winRate*100 << " percent of the matches." << endl;
        std::cout << std::internal;
        std::cin.get();
        std::cin.get();
    }
    }

    void updateScores(NineBoard &nineBoard, const char &playerSymbol){
        gameCount_ ++;
        if (currentGameMoves_ > highestMoves_) highestMoves_ = currentGameMoves_;
        if (currentGameMoves_ < lowestMoves_) lowestMoves_ = currentGameMoves_;
        currentGameMoves_ = 0;
        char gStatus = nineBoard.status();
        if (gStatus == 'D') drawCount_ += 1;
        else if (gStatus == 'X') xWins_ += 1;
        else if (gStatus == 'O') oWins_ += 1;
        else cout << "Something went wrong\n";
    }
};