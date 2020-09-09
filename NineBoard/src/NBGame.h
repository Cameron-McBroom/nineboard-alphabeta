#pragma once
#include <iostream>

#include "NineBoard.h"
#include "Player.h"
#include "Menu.h"
#include "GameStats.h"

class NBGame {
public:
    NBGame();
    ~NBGame();
    void play();
    void printResults();
private:
    // Players and board
    GameStats gameStats;
    Menu menu;
    NineBoard nineBoard;
    vector<unique_ptr<Player>> players;
    int turn;

    //Helper methods
    void getNextMove();
    void changeTurn();
    void playAgain();
    void resetBoard();

    // Simulation methods
    bool simulation;
    bool displayFinishingBoard;
    int simulationCount;
    void makeSimulation();
    void printProgress();
};


NBGame::NBGame() : turn(1), simulationCount(0), simulation(false), displayFinishingBoard(false)
{
    menu.display();
    players = menu.getStartingPlayers(std::move(players));
    gameStats = GameStats(players[0]->getName(), players[1]->getName());
    if (!players[0]->isHuman() && !players[1]->isHuman()) makeSimulation();
}

NBGame::~NBGame() {}

void NBGame::play()
{
    bool done {false};
    while (!done) {
        changeTurn();
        if (!simulation) nineBoard.displayBoard();
        getNextMove();
        gameStats.incrementMoves();
        done = nineBoard.isFinished();
    }
    if (!simulation || displayFinishingBoard) nineBoard.displayBoard();
    playAgain();
}

void NBGame::getNextMove()
{
    int row{0}, col{0};
    players[turn]->getMove(nineBoard, row, col);
    nineBoard.addMove(players[turn]->symbol(), row, col);
    nineBoard.nextBoard(row, col);
}

void NBGame::makeSimulation()
{
    cout << "How many matches would you like to run? ";
    cin >> simulationCount;
    cout << "\nWould you like to print the game ending board each match?\n(Y / N) ";
    char ans;
    cin >> ans;
    if (ans == 'Y' || ans == 'y') displayFinishingBoard = true;
    simulation = true;
}

void NBGame::playAgain()
{
    // Updates the current match scores avg, max, min moves etc.
    gameStats.updateScores(nineBoard, players[turn]->symbol());

    // If simulation no need to ask to play again
    if (simulation && gameStats.gameCount() < simulationCount) {
        printProgress();
        resetBoard();
        play();
    }

    // If not simulation prompt user if they want to play again
    if (!simulation) {
        cout << "Player " << players[turn]->symbol() << " wins!" << endl;
        if (menu.playAgain())  {
            resetBoard();
            play();
        }
    }
}

void NBGame::resetBoard()
{
    nineBoard = NineBoard();
}

void NBGame:: printResults() {
    if (simulation) printProgress();
    gameStats.printResults();
}

void NBGame::changeTurn(){turn == 0 ? turn = 1 : turn = 0;}

void NBGame::printProgress() {
    // Code courtesy of stack overflow answer
    float progress =  gameStats.gameCount() / static_cast<float>(simulationCount);
    int barWidth = 52;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}





