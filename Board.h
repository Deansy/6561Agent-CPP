#include "Tile.h"
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <utility>


class Board {

public:

	enum MOVE {
		LEFT, UP, DOWN, RIGHT
	};

	const std::set<int> placeTurns = { 1, 2, 3, 6, 7, 8 };

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


	const std::string ANSI_RESET = "\u001B[0m";
	const std::string ANSI_RED = "\u001B[31m";
	const std::string ANSI_BLUE = "\u001B[34m";
	const std::string ANSI_BLACK = "\u001B[30m";


	//TODO: Implmement
	std::vector<std::pair<MOVE, Board>> getSlidesWithBoard();
	std::vector<std::pair<int, int>> getPlaces(Tile::TileColor colorToConsider);


private:
	void initBoard();
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