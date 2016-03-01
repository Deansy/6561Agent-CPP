//
// Created by cameron on 13/02/2016.
//

#include "RandomMoveAgent.h"
#include <sstream>
#include <time.h>
#include <stdio.h>

RandomMoveAgent::RandomMoveAgent(Board b) {
    currentBoard = b;
    currentMove = 1;\

    std::cerr << "RMAgent Start" << std::endl;

    srand(time(NULL));
}

RandomMoveAgent::RandomMoveAgent() {
    currentBoard = Board();
    currentMove = 1;\

    std::cerr << "RMAgent Start" << std::endl;

    srand(time(NULL));
}

void RandomMoveAgent::handlePlaceTurn(std::string moveInfo) {
    //std::cerr << "Handle Place Turn" << std::endl;
    previousMove = moveInfo;


    int xPos = atoi(moveInfo.substr(0,1).c_str());
    int yPos = atoi(moveInfo.substr(1,1).c_str());

    currentBoard.placeTile(Player::getTileColorForMove(currentMove), xPos, yPos, 1);
    currentMove++;


}

void RandomMoveAgent::handleMoveTurn(std::string moveInfo) {

    //std::cerr << "HandleMoveTurn" << std::endl;

    if (moveInfo == "U") {
        currentBoard.slideBoard(Board::MOVE::UP);
    }
    else if (moveInfo == "D") {
        currentBoard.slideBoard(Board::MOVE::DOWN);
    }
    else if (moveInfo == "L") {
        currentBoard.slideBoard(Board::MOVE::LEFT);
    }
    else if (moveInfo == "R") {
        currentBoard.slideBoard(Board::MOVE::RIGHT);
    }

    currentMove++;


}

void RandomMoveAgent::performPlaceTurn() {
    std::cerr << "Perform Place Turn: " <<  currentMove << std::endl;
    std::cerr.flush();

    int x = rand() % 4;
    int y = rand() % 4;

    if (currentBoard.isEmpty(x, y)) {
        x++;
        y++;

        std::string move = std::to_string(x) + std::to_string(y);

        if (move != previousMove) {
            currentBoard.placeTile(Player::getTileColorForMove(currentMove), x , y, 1);

            printf("%s\n", move.c_str());
            fflush(stdout);


            currentMove++;
        }
        else {
            // Duplicate Move
            std::cerr << "1" << std::endl;
            performPlaceTurn();
        }
    }
    else {
        // Retying
        std::cerr << "2" << std::endl;
        performPlaceTurn();
    }
}

void RandomMoveAgent::performMoveTurn() {
    std::cerr << "Perform Move Turn: " << currentMove << std::endl;
    int n = rand() % 4;


    std::string move;

    switch (n) {
        case 0:
            move = "U";
            break;

        case 1:
            move = "D";
            break;
        case 2:
            move = "L";
            break;

        case 3:
            move = "R";
            break;
        default:
            exit(0);
            break;
    }



    if (strcmp(move.c_str(), previousMove.c_str()) == 0) {
        // retying
        std::cerr << "Duplicate MOVE 1" << std::endl;
        performMoveTurn();
    }



    else {
        Board beforeMove(currentBoard);

        std::cerr << "123 " << move  << std::endl;

        if (strcmp(move.c_str(), "U") == 0){
            currentBoard.slideBoard(Board::MOVE::UP);
            std::cerr << "SLIDE U" <<  std::endl;
        }
        else if (strcmp(move.c_str(), "D") == 0) {
            currentBoard.slideBoard(Board::MOVE::DOWN);
            std::cerr << "SLIDE D" <<  std::endl;
        }
        else if (strcmp(move.c_str(), "L") == 0) {
            currentBoard.slideBoard(Board::MOVE::LEFT);
            std::cerr << "SLIDE L" <<  std::endl;
        }
        else if (strcmp(move.c_str(), "R") == 0) {
            currentBoard.slideBoard(Board::MOVE::RIGHT);
            std::cerr << "SLIDE R" <<  std::endl;
        }
        else {
            std::cerr << "XX" << move.c_str() << std::endl;
        }

        std::cerr << "345" << std::endl;

        if (currentBoard == beforeMove) {
            // Duplicate move
            std::cerr << "Duplicate MOVE 2" << std::endl;
            performMoveTurn();
        }
        else {
            std::cerr << currentMove << " : " << move.c_str() << std::endl;
            printf("%s\n", move.c_str());
            fflush(stdout);
            currentMove++;
        }
    }
}
