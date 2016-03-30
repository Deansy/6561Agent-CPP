//
// Created by Cameron Deans on 29/03/2016.
//

#include <cmath>
#include "MCTSNode.h"
#include "RandomMoveAgent.h"

MCTSNode::MCTSNode() {
    board = Board();
    currentMove = 0;
    srand(time(NULL));

}

MCTSNode::MCTSNode(Board b, int cMove) {
    board = b;
    currentMove = cMove;
    srand(time(NULL));

}

MCTSNode* MCTSNode::getMostVisitedChild() {
    if (!children.empty()) {
        double visits = children.at(0)->nVisits;
        MCTSNode* mostVisitedChild = children.at(0);
        for (int i = 0; i < children.size(); i++) {
            MCTSNode* x = children.at(0);
            if (x->nVisits > visits) {
                visits = x->nVisits;
                mostVisitedChild = x;
            }
        }
        return mostVisitedChild;
    }
    else {
        //Error
        this->expand();
        this->getMostVisitedChild();
    }

    return new MCTSNode();
}

MCTSNode* MCTSNode::getChildNodeWithBoard(Board b) {
    if (!children.empty()) {
        for (int i = 0; i < children.size(); i++) {
            MCTSNode* x =  children.at(i);

            if (x->board == b) {
                return x;
            }

        }
    }

    MCTSNode* newNode = new MCTSNode(b, currentMove + 1);

    return newNode;
}

void MCTSNode::selectAction() {
    std::vector<MCTSNode*> visited;


    MCTSNode *cur = this;

    visited.push_back(cur);

    while (!cur->children.empty()) {
        cur = cur->select();
        visited.push_back(cur);
    }

    int i = cur->currentMove;
    cur->expand();
    double value = 0;
    MCTSNode* newNode = cur->select();

    if (newNode == nullptr) {
        cur->board.printBoard(false);
        newNode = cur->select();
    }

    value = rollOut(newNode);

    visited.push_back(newNode);

    for (int i = 0; i < visited.size(); i++) {
        MCTSNode* x =  children.at(0);

        x->updateStats(value);
    }
}

void MCTSNode::expand() {
    std::vector<std::pair<Board, Board::NewStateData>> boards = board.getNextStatesWithStateData(currentMove);
    if (boards.size() > 5) {
        for (int i = 0; i < 5 ; i++) {
            MCTSNode* newNode = new MCTSNode();
            newNode->board = boards[i].first;
            newNode->stateData = boards[i].second;
            newNode->currentMove = currentMove + 1;


            children.push_back(newNode);
        }
    }
    else {
        for (int i = 0; i < boards.size() ; i++) {
            MCTSNode* newNode = new MCTSNode();
            newNode->board = boards[i].first;
            newNode->stateData = boards[i].second;
            newNode->currentMove = currentMove + 1;


            children.push_back(newNode);

        }
    }
}

MCTSNode* MCTSNode::select() {
    MCTSNode* selected = new MCTSNode();

    double bestValue = -std::numeric_limits<double>::max();

    try {
        for (int i = 0; i < children.size(); i++) {
            MCTSNode* n = children.at(i);

            double uctValue = n->totValue / (n->nVisits + n->epsilon) +
                              sqrt(log(nVisits + 1) / (n->nVisits + epsilon)) +
                              rand() * epsilon;
            if (uctValue > bestValue) {
                selected = n;
                bestValue = uctValue;
            }
        }
    }
    catch (int e) {
        std::cout << "An exception occurred. Exception Nr. " << e << '\n';
    }

    if (children.empty()) {

    }

    return selected;
}

double MCTSNode::rollOut(MCTSNode* n) {
    RandomMoveAgent randAgent = RandomMoveAgent(&n->board, n->currentMove);
    for (int i = 0; i < 20; i++) {
        if (Board::placeTurns.find((currentMove + i) % 10) != Board::placeTurns.end()) {
            randAgent.performPlaceTurn();
        }
        else {
            randAgent.performMoveTurn();
        }
    }

    int score = randAgent.currentBoard.gameScore();

    return score;
}

void MCTSNode::updateStats(double value) {
    nVisits++;
    totValue += value;
}
