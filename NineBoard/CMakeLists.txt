cmake_minimum_required(VERSION 3.16)
project(NineBoard)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-static-libgcc -static-libstdc++ -static -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

set(SOURCE_FILES
        main.cpp
        src/TicTacToe.h
        src/BoardCoordinate.h
        src/NineBoard.h
        src/NBGame.h
        src/ConsoleColours.h
        src/Menu.h
        src/GameStats.h
        src/Player.h
        src/players/HumanPlayer.h
        src/players/RandomPlayer.h
        src/players/OneLayer.h
        src/players/TwoLayer.h
        src/players/MiniMax.h
        src/players/MonteCarlo.h src/players/AlphaBeta.h)

add_executable( NineBoard ${SOURCE_FILES})