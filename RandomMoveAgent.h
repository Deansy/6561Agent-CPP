//
// Created by cameron on 13/02/2016.
//

#ifndef INC_6561AGENT_RANDOMMOVEAGENT_H
#define INC_6561AGENT_RANDOMMOVEAGENT_H


#include "Player.h"

class RandomMoveAgent : public Player {
public:
    RandomMoveAgent(Board b);
    RandomMoveAgent(Board b, int currentMove);
    RandomMoveAgent();


    void handlePlaceTurn(std::string moveInfo);
    void handleMoveTurn(std::string moveInfo);
    void performPlaceTurn();
    void performMoveTurn();
};


#endif //INC_6561AGENT_RANDOMMOVEAGENT_H
