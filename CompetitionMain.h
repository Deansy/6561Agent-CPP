//
// Created by cameron on 13/02/2016.
//

#ifndef INC_6561AGENT_COMPETITIONMAIN_H
#define INC_6561AGENT_COMPETITIONMAIN_H


#include "Board.h"
#include "Player.h"
#include <String>

class CompetitionMain {
public:
    void gameLoop();

private:
    //Board currentBoard;
    //std::string player;
    int currentMove;

    std::vector<Board> previousStates;



    void handlePlaceTurn(std::string moveInfo);

    void handleMoveTurn(std::string moveInfo);

    void performPlaceTurn();

    void performMoveTurn();


    Player *currentPlayer;
};


#endif //INC_6561AGENT_COMPETITIONMAIN_H
