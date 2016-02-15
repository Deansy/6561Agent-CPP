//
// Created by cameron on 13/02/2016.
//

#ifndef INC_6561AGENT_RANDOMMOVEAGENT_H
#define INC_6561AGENT_RANDOMMOVEAGENT_H


#include "Player.h"

class RandomMoveAgent : Player {
public:
    RandomMoveAgent(Board b);

private:
    virtual void handlePlaceTurn(std::string moveInfo) override;

    virtual void handleMoveTurn(std::string moveInfo) override;

    virtual void performPlaceTurn() override;

    virtual void performMoveTurn() override;
};


#endif //INC_6561AGENT_RANDOMMOVEAGENT_H
