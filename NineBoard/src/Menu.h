#pragma once

#include "Player.h"
#include <memory>
#include <iomanip>
#include "players/HumanPlayer.h"
#include "players/OneLayer.h"
#include "players/TwoLayer.h"
#include "players/RandomPlayer.h"
#include "players/MiniMax.h"
#include "players/MonteCarlo.h"
#include "players/AlphaBeta.h"

class Menu {
public:
    Menu() {
        // creates a vector of all player strategies
        registerPlayer(make_unique<HumanPlayer>());
        registerPlayer(make_unique<RandomPlayer>());
        registerPlayer(make_unique<OneLayer>());
        registerPlayer(make_unique<TwoLayer>());
        registerPlayer(make_unique<MiniMax>());
        registerPlayer(make_unique<AlphaBeta>());
        registerPlayer(make_unique<MonteCarlo>());
    }

    void display() const {
        // Will loop through all types of _player strategies and generate dynamic menu
        std::cout <<  setw(45) <<"CHOOSE TWO STARTING OPTIONS" << std::endl;
        std::cout << setw(54) << "Select any two from below. First will play as X" << std::endl;
        std::cout << "================================================================" << std::endl;
        size_t choice{1};
        for (const auto &player: players_) {
            std::cout << std::setfill('.')
            << std::setw(57) << std::left << player->getName()
            << std::left << "Enter " << choice << endl;
            choice ++;
        }
        std::cout << std::internal << std::setfill(' ');
        std::cout.flush();
    }

     vector<unique_ptr<Player>> getStartingPlayers(vector<unique_ptr<Player>> players){
        // Takes two un-initialized player objects, and sets them based on keyboard input
        int choice1{}, choice2{};
        while (choice1 < 1 || choice1 > players_.size()){
            std::cin >> choice1;
        }
        while (choice2 < 1 || choice2 > players_.size()){
            std::cin >> choice2;
        }

        // Assign to the player objects passed in, and set player 1 symbol to 'X'
        players.emplace_back(std::move(players_[choice1 - 1]->clone('X')));
        players.emplace_back(std::move(players_[choice2 - 1]->clone('O')));

        //Prompt user for any strategy specific options
        players[0]->getPlayerOptions();
        players[1]->getPlayerOptions();

        return players;
    }
    bool playAgain() {
        char ans{};
        std::cout << "Would you like to play again? (y/n)";
        std::cin >> ans;
        if (ans == 'Y' || ans == 'y') return true;
        else return false;
    }

private:
    // Holds each of the player strategies
    vector<unique_ptr<Player>> players_;
    void registerPlayer(unique_ptr<Player> player) {
        players_.emplace_back(std::move(player));
    }

};