//
// Created by cameron on 13/02/2016.
//

#include <stdlib.h>
#include "CompetitionMain.h"


void CompetitionMain::gameLoop() {

    currentBoard = Board();

    currentMove = 1;
    previousStates = std::vector<Board>();

    // TODO: Get input
    // Scanner in = new Scanner(System.in);
    // player = in.next();
    std::cin >> player;

    // TODO:
    // currentPlayer = new DepthLimitedDFSAgent(currentBoard);

    std::cerr << "I am player: " << player;


    if (player == "A") {
        // place a tile
        performPlaceTurn();
    }

    while (true) {
        std::string input;

        std::cin >> input;

        if (input == "Quit") {
            exit(0);
        }

        if (input == "U"|| input == "D" || input == "L" || input == "R") {
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
    }






}

void CompetitionMain::handlePlaceTurn(std::string moveInfo) {

}

void CompetitionMain::handleMoveTurn(std::string moveInfo) {

}

void CompetitionMain::performPlaceTurn() {

}

void CompetitionMain::performMoveTurn() {

}

Tile::TileColor CompetitionMain::getTileColorForMove(int move) {
    // TODO:
    return Tile::TileColor::RED ;
}
