# NineBoard Tic Tac Toe w/ Alpha Beta & Monte Carlo
Nineboard TicTacToe using OOP principles, along with Alpha Beta Minimax and Monte Carlo AIs

The program currently only works on Windows due to colour of the console text.

You can find and run the executable file under: **cmake-build-release-mingw > NineBoard.exe**

## How to play
1. First choose any of the following options

![Image of starting menu](https://i.imgur.com/83e3fB4.png)

2. If you decide to play as a human player, you can choose your position on the board by enter two numbers; row & column (1 - 3). Leave a space inbetween the input as follows:

![Image of enter coordiantes](https://i.imgur.com/8IIyB2W.png)

3. The previous move dictates the next board of play. e.g since the last move was on 1,3 , the current board of play is now top right corner

![Current board of play](https://i.imgur.com/kiDtGL1.png)

4. The first player to get three in a row on any board wins the game.

# How run simulations between two AI Players

- You can select two AI players to play against themselves to measure which ones perform better. After selecting two computer players the program will prompt you for how many simulations you would like to run, along with any other player specific options.

![Simulation options](https://i.imgur.com/EULvq3w.png)

- If you test out the Monte Carlo Algorithm, you have the option to set the amount of games it will simulation for each move. (e.g if there are 5 legal moves the player can make, it will simulate x number of games for each legal move and make the move the ends in the highest number of wins.

- You can see how far the simulation is by looking at the loading bar, regular minimax at depth of > 5 can be pretty slow. This will help give you an idea of how long the simulation will take

- Finally, after the simulation, you can see the results of the match:

![Final Results](https://i.imgur.com/0trqXNw.png)

Looks like Alpha beta takes the cake this time!

# Challenges and Learnings from the project
- The game has been built using the Object Oriented Paradigm. I learnt a great deal about how to compose objects, and how to encapsulate and hide complexity. If you look at the nineboard class, most of the functionality is straight from the TicTacToe class.

- Taking the concept of minimax and alpha beta and putting it into c++ code was quite a challenge, it involved thinking recursively. This part of the project took me the most amount of time and effort.

- This project is structured in a way that you could take the logic and players and apply them to a more graphically pleasing implementation.
