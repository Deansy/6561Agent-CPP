#include "Tile.h"
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <utility>

#ifndef INC_6561AGENT_BOARD_H
#define INC_6561AGENT_BOARD_H

class Board {

public:

	enum MOVE {
		LEFT, UP, DOWN, RIGHT
	};

	//std::set<int> placeTurns = { 1, 2, 3, 6, 7, 8 };

	void placeTile(Tile::TileColor tileColor, int xPos, int yPos, int value);
	void printBoard(bool errorPrint);
	bool isEmpty(int x, int y);
	Board();
	Board(Board *oldBoard);
	bool operator == (const Board &Ref) const;

	static const int boardWidth = 4;
	static const int boardHeight = 4;

	std::vector<Board::MOVE> getSlides();

	void slideBoard(Board::MOVE m);

	//TODO: Implement
	std::vector<std::pair<MOVE, Board>> getSlidesWithBoard();
	std::vector<std::pair<int, int>> getPlaces(Tile::TileColor colorToConsider, int placesToGet);

	int getBoardScore();

	Tile getTileAt(int x, int y);


private:
	void mergeUp();
	void mergeDown();
	void mergeRight();
	void mergeLeft();

	void slideUp();
	void slideDown();
	void slideRight();
	void slideLeft();

	// board array
	Tile board[boardWidth][boardHeight];

	

};

#endif