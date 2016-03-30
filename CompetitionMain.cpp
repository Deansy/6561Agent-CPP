//
// Created by cameron on 13/02/2016.
//

#include <stdlib.h>
#include <stdio.h>
#include "CompetitionMain.h"
#include "RandomMoveAgent.h"
#include "DepthLimitedDFSAgent.h"
#include "MonteCarloAgent.h"


void CompetitionMain::gameLoop() {
//    currentBoard = Board();

    currentMove = 1;
    previousStates = std::vector<Board>();



    //std::cin >> player;
    //getline(std::cin, player);
    char player[10];
    //std::cerr << "Test" << std::endl;

    scanf("%s", &player);
    //std::cerr << "Test" << std::endl;



    currentPlayer = new MonteCarloAgent();
    //currentPlayer = new DepthLimitedDFSAgent();


    //std::cerr << "I am player: " << player << std::endl;


    if (strcmp(player, "A") == 0) {
        // place a tile
        performPlaceTurn();
    }

    while (true) {
        char input[10];
        scanf("%s",&input);

        //std::cerr << "Input = " << input <<  std::endl;


        if (strcmp(input, "Quit") == 0) {
            exit(0);
        }


        if (strcmp(input, "U") == 0 || strcmp(input, "D") == 0 || strcmp(input, "L") == 0 || strcmp(input, "R") == 0) {
            handleMoveTurn(input);
        }
        else {
            handlePlaceTurn(input);
        }

        std::set<int> placeTurns = { 1, 2, 3, 6, 7, 8 };

        if (placeTurns.find(currentMove % 10) != placeTurns.end()) {
            performPlaceTurn();
        }
        else {
            performMoveTurn();
        }

        //std::cerr << "End loop"  << std::endl;
    }






}

void CompetitionMain::handlePlaceTurn(std::string moveInfo) {

    currentMove++;
    currentPlayer->handlePlaceTurn(moveInfo);
}

void CompetitionMain::handleMoveTurn(std::string moveInfo) {
    currentMove++;
    currentPlayer->handleMoveTurn(moveInfo);
}

void CompetitionMain::performPlaceTurn() {
    currentMove++;
    currentPlayer->performPlaceTurn();
}

void CompetitionMain::performMoveTurn() {
    currentMove++;
    currentPlayer->performMoveTurn();
}
