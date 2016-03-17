//
// Created by Cameron Deans on 10/03/2016.
//

#ifndef INC_6561AGENT_DEPTHLIMITEDDFSAGENT_H
#define INC_6561AGENT_DEPTHLIMITEDDFSAGENT_H

#include "Player.h"

class DepthLimitedDFSAgent : public Player {
public:
    DepthLimitedDFSAgent(Board b);
    DepthLimitedDFSAgent();

private:
    void handlePlaceTurn(std::string moveInfo);
    void handleMoveTurn(std::string moveInfo);
    void performPlaceTurn();
    void performMoveTurn();

    double DepthLimitedSearch(Board b, int depth);

    double boardTotalHeuristic(Board b);
    double oneColorMajority(Board b);
};


#endif //INC_6561AGENT_DEPTHLIMITEDDFSAGENT_H
