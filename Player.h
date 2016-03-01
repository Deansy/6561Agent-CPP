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

    Tile::TileColor getTileColorForMove(int move) {
        Tile::TileColor color = Tile::TileColor::EMPTY;

        int rotationID = move % 10;

        if (rotationID == 1 || rotationID == 6) {
            color = Tile::TileColor::BLUE;
        }
        else if (rotationID == 2 || rotationID == 7) {
            color = Tile::TileColor::RED;
        }
        else if (rotationID == 3 || rotationID == 8) {
            color = Tile::TileColor::GREY;
        }

        return color;
    }

protected:
    Board currentBoard;
    std::string previousMove;
    int currentMove;
};


#endif //INC_6561AGENT_PLAYER_H
