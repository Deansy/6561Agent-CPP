//
// Created by Cameron Deans on 29/03/2016.
//

#ifndef INC_6561AGENT_MCTSNODE_H
#define INC_6561AGENT_MCTSNODE_H


#include "Board.h"

class MCTSNode {

    Board board;
    int currentMove;

    double nVisits, totValue;
    double epsilon = 1e-6;





public:
    Board::NewStateData stateData;
    std::vector<MCTSNode> children;
    MCTSNode();
    MCTSNode(Board b, int currentMove);

    MCTSNode getMostVisitedChild();
    MCTSNode getChildNodeWithBoard(Board b);

    void selectAction();
    void expand();
    MCTSNode* select();
    double rollOut(MCTSNode* n);
    void updateStats(double value);


};


#endif //INC_6561AGENT_MCTSNODE_H
