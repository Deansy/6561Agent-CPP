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

	static std::set<int> placeTurns() {
		std::set<int> placeTurns = { 1, 2, 3, 6, 7, 8 };
		return placeTurns;
	}

	void placeTile(Tile::TileColor tileColor, int xPos, int yPos, int value);
	void printBoard(bool errorPrint);
	bool isEmpty(int x, int y);
	Board();
	Board(Board *oldBoard);
	bool operator == (const Board &Ref) const;

	static const int boardWidth = 4;
	static const int boardHeight = 4;

	int gameScore();

	std::vector<Board::MOVE> getSlides();

	void slideBoard(Board::MOVE m);

	//TODO: Implement
	std::vector<std::pair<MOVE, Board>> getSlidesWithBoard();
	std::vector<std::pair<int, int>> getPlaces(Tile::TileColor colorToConsider, int placesToGet);


	class NewStateData {
    public:
		int x = -1;
		int y = -1;

		Board::MOVE move;
		Tile::TileColor color;


		NewStateData() {
			// Make the compiler happy
		}

		NewStateData(Board::MOVE move) {
			this->move = move;
		}
		NewStateData(int x, int y, Tile::TileColor color) {
			this->x = x;
			this->y = y;
			this->color = color;
		}
	};



	std::vector<std::pair<Board, Board::NewStateData>> getNextStatesWithStateData(int currentMove);

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