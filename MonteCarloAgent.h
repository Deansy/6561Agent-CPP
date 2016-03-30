//
// Created by Cameron Deans on 29/03/2016.
//

#ifndef INC_6561AGENT_MONTECARLOAGENT_H
#define INC_6561AGENT_MONTECARLOAGENT_H


#include "Board.h"
#include "MCTSNode.h"
#include "Player.h"

class MonteCarloAgent : public Player {
public:
    int currentMove;
    Board currentBoard;
    std::string previousMove;

    MCTSNode* currentNode;

    MonteCarloAgent();
    MonteCarloAgent(Board board);

private:
    void handlePlaceTurn(std::string moveInfo);
    void handleMoveTurn(std::string moveInfo);
    void performPlaceTurn();
    void performMoveTurn();
};



#endif //INC_6561AGENT_MONTECARLOAGENT_H
