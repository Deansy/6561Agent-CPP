//
// Created by Cameron Deans on 29/03/2016.
//

#include "MonteCarloAgent.h"


MonteCarloAgent::MonteCarloAgent(Board board) {
    currentMove = 1;
    currentBoard = board;

    currentNode = MCTSNode();

    for (int i = 0; i < 1000; i++) {
        currentNode.selectAction();
    }
}

MonteCarloAgent::MonteCarloAgent() {
    currentMove = 1;
    currentBoard = Board();

    currentNode = MCTSNode();

    for (int i = 0; i < 1000; i++) {
        currentNode.selectAction();
    }
}

void MonteCarloAgent::handlePlaceTurn(std::string moveInfo) {
    //std::cerr << "Handle Place Turn" << std::endl;
    previousMove = moveInfo;


    int xPos = atoi(moveInfo.substr(0,1).c_str());
    int yPos = atoi(moveInfo.substr(1,1).c_str());

    currentBoard.placeTile(Player::getTileColorForMove(currentMove), xPos, yPos, 1);

    currentMove++;


    currentNode = currentNode.getChildNodeWithBoard(currentBoard);
}

void MonteCarloAgent::handleMoveTurn(std::string moveInfo) {

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

    currentNode = currentNode.getChildNodeWithBoard(currentBoard);
}

void MonteCarloAgent::performPlaceTurn() {
    // Every 10 moves
    if (currentMove % 10 == 0) {
        for (int i = 0; i < 200; i++) {
            currentNode.selectAction();
        }
    }

    if (currentNode.children.empty()) {
        currentNode.expand();
    }

    MCTSNode nextNode = currentNode.getMostVisitedChild();

    Board::NewStateData nsd = nextNode.stateData;

    currentBoard.placeTile(nsd.color, nsd.x, nsd.y, 1);
    printf("%d%d\n",nsd.x,nsd.y);
    fflush(stdout);

    currentMove++;

    currentNode = nextNode;


}

void MonteCarloAgent::performMoveTurn() {
    // Every 10 moves
    if (currentMove % 10 == 0) {
        for (int i = 0; i < 200; i++) {
            currentNode.selectAction();
        }
    }

    if (currentNode.children.empty()) {
        currentNode.expand();
    }

    MCTSNode nextNode = currentNode.getMostVisitedChild();
    Board::NewStateData nsd = nextNode.stateData;

    currentBoard.slideBoard(nsd.move);

    switch (nsd.move) {
        case Board::MOVE::LEFT:
            printf("L\n");
            std::cerr << "L" <<std::endl;
            break;
        case Board::MOVE::RIGHT:
            printf("R\n");
            std::cerr << "R" <<std::endl;
            break;
        case Board::MOVE::UP:
            printf("U\n");
            std::cerr << "U" <<std::endl;
            break;
        case Board::MOVE::DOWN:
            printf("D\n");
            std::cerr << "D" <<std::endl;
            break;
    }

    currentNode = nextNode;
    currentMove++;

    fflush(stdout);
}


