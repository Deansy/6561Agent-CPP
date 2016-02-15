//
// Created by cameron on 13/02/2016.
//

#ifndef INC_6561AGENT_PLAYER_H
#define INC_6561AGENT_PLAYER_H

#import <string>
#include "Board.h"

class Player {
public:

    virtual void handlePlaceTurn(std::string moveInfo) = 0;
    virtual void handleMoveTurn(std::string moveInfo) = 0;

    virtual void performPlaceTurn() = 0;
    virtual void performMoveTurn() = 0;


protected:
    Board currentBoard;
    std::string previousMove;
    int currentMove;
};


#endif //INC_6561AGENT_PLAYER_H
