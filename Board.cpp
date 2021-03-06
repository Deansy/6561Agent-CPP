#include "Board.h"
#include "Player.h"

// TODO: Bring over all comments
// TODO: Test

std::vector<Board::MOVE> Board::getSlides() {
	std::vector <Board::MOVE> validSlides;



	Board b = Board(this);
	b.slideUp();

	if (!(b == this)) {
		validSlides.push_back(MOVE::UP);
	}

	Board c = Board(this);
	c.slideDown();

	if (!(c == this)) {
		validSlides.push_back(MOVE::DOWN);
	}

	Board d = Board(this);
	d.slideLeft();

	if (!(d == this)) {
		validSlides.push_back(MOVE::LEFT);
	}


	Board e = new Board(this);
	e.slideRight();

	if (!(e == this)) {
		validSlides.push_back(MOVE::RIGHT);
	}


	return validSlides;
}

bool Board::isEmpty(int x, int y) {
	if (board[x - 1][y - 1].tileColor == Tile::TileColor::EMPTY) {
		return true;
	}
	return false;
}

void Board::placeTile(Tile::TileColor tileColor, int xPos, int yPos, int value) {
	if (xPos <= boardWidth && xPos >= 1) {
		if (yPos <= boardWidth && yPos >= 1) {
			Tile x = board[xPos - 1][yPos - 1];
			if (x.tileColor != Tile::TileColor::EMPTY) {
				//System.err.println("Can only place tiles in empty slots, Printing board");
				//System.err.println("X:" + xPos + " Y:" + yPos);

				//printBoard(true);
			}
			else {
				board[xPos - 1][yPos - 1] = Tile(tileColor, xPos - 1, yPos - 1, value);
			}
		}
		else {
			// System.err.println("Invalid Y coordinate: " + yPos);
		}

	}
	else {
		//System.err.println("Invalid X coordinate: " + xPos);
	}

}

std::set<int> Board::placeTurns = { 1, 2, 3, 6, 7, 8 };

Board::Board() {




    for (int x = 0; x < boardWidth; x++) {
		for (int y = 0; y < boardWidth; y++) {
			board[x][y] = Tile(Tile::TileColor::EMPTY, x, y, 0);
		}
	}
}

Board::Board(Board *oldBoard) {
	for (int x = 0; x < boardWidth; x++) {
		for (int y = 0; y < boardWidth; y++) {
			board[x][y] = oldBoard->board[x][y];
		}
	}
}

void Board::slideBoard(Board::MOVE m) {
	switch (m) {
	case MOVE::LEFT: 
		slideLeft();
		break;
	case MOVE::RIGHT:
		slideRight();
		break;
	case MOVE::UP:
		slideUp();
		break;
	case MOVE::DOWN:
		slideDown();
		break;
	}
}

void Board::slideDown() {
	for (int i = 0; i < 2; i++) {

		Tile boardCopy[boardWidth][boardHeight];
		//std::copy(std::begin(board), std::end(board), std::begin(boardCopy));
		std::copy(&board[0][0], &board[0][0] + boardWidth*boardHeight, &boardCopy[0][0]);

		for (int y = 0; y < 4; y++) {
			for (int x = 3; x >0; x--) {
				if (boardCopy[x][y].value == 0) {
					for (int k = x - 1; k >= 0; k--) {
						if (boardCopy[k][y].value != 0) {
							boardCopy[x][y] = boardCopy[k][y];

							boardCopy[x][y].xPos = x;
							boardCopy[x][y].yPos = y;

							boardCopy[k][y] = Tile(Tile::TileColor::EMPTY, k, y, 0);
							break;

						}
					}
				}
			}
		}

		std::copy(&boardCopy[0][0], &boardCopy[0][0] + boardWidth*boardHeight, &board[0][0]);

		if (i == 0) {
			mergeDown();
		}

	}
}

void Board::slideUp() {
	for (int i = 0; i < 2; i++) {

		Tile boardCopy[boardWidth][boardHeight];
		std::copy(&board[0][0], &board[0][0] + boardWidth*boardHeight, &boardCopy[0][0]);

		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if (boardCopy[x][y].value == 0) {
					for (int k = x + 1; k < 4; k++) {
						if (boardCopy[k][y].value != 0) {
							boardCopy[x][y] = boardCopy[k][y];

							boardCopy[x][y].xPos = x;
							boardCopy[x][y].yPos = y;

							boardCopy[k][y] = Tile(Tile::TileColor::EMPTY, k, y, 0);
							break;

						}
					}
				}
			}
		}

		std::copy(&boardCopy[0][0], &boardCopy[0][0] + boardWidth*boardHeight, &board[0][0]);

		if (i == 0) {
			mergeUp();
		}

	}
}

void Board::slideLeft() {
	for (int i = 0; i < 2; i++) {

		Tile boardCopy[boardWidth][boardHeight];
		std::copy(&board[0][0], &board[0][0] + boardWidth*boardHeight, &boardCopy[0][0]);

		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 4; y++) {
				if (boardCopy[x][y].value == 0) {
					for (int k = y+1; k < 4; k++) {
						if (boardCopy[x][k].value != 0) {
							boardCopy[x][y] = boardCopy[x][k];

							boardCopy[x][y].xPos = x;
							boardCopy[x][y].yPos = y;

							boardCopy[x][k] = Tile(Tile::TileColor::EMPTY, x, k, 0);
							break;

						}
					}
				}
			}
		}

		std::copy(&boardCopy[0][0], &boardCopy[0][0] + boardWidth*boardHeight, &board[0][0]);

		if (i == 0) {
			mergeLeft();
		}

	}
}

void Board::slideRight() {
	for (int i = 0; i < 2; i++) {

		Tile boardCopy[boardWidth][boardHeight];
		std::copy(&board[0][0], &board[0][0] + boardWidth*boardHeight, &boardCopy[0][0]);

		for (int x = 0; x < 4; x++) {
			for (int y = 3; y >= 0; y--) {
				if (boardCopy[x][y].value == 0) {
					for (int k = y - 1; k >= 0; k--) {
						if (boardCopy[x][k].value != 0) {
							boardCopy[x][y] = boardCopy[x][k];

							boardCopy[x][y].xPos = x;
							boardCopy[x][y].yPos = y;

							boardCopy[x][k] = Tile(Tile::TileColor::EMPTY, x, k, 0);
							break;

						}
					}
				}
			}
		}

		std::copy(&boardCopy[0][0], &boardCopy[0][0] + boardWidth*boardHeight, &board[0][0]);

		if (i == 0) {
			mergeRight();
		}

	}
}

void Board::mergeUp() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			Tile tileOne = board[j][i];
			Tile tileTwo = board[j+1][i];

			if ((tileOne.value != 0) && tileOne.value == tileTwo.value) {
				if (tileOne.tileColor == tileTwo.tileColor) {
					board[j][i] = Tile(tileOne.tileColor, j, i, tileOne.value * 3);
					board[j + 1][i] = Tile(Tile::TileColor::EMPTY, j + 1, i, 0);
				}
				else {
					board[j][i] = Tile(Tile::TileColor::EMPTY, j, i, 0);
					board[j+1][i] = Tile(Tile::TileColor::EMPTY, j+1, i, 0);
				}
			}

		}
	}
}

void Board::mergeDown() {
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j > 0; j--) {
			Tile tileOne = board[j][i];
			Tile tileTwo = board[j-1][i];

			if ((tileOne.value != 0) && tileOne.value == tileTwo.value) {
				if (tileOne.tileColor == tileTwo.tileColor) {
					board[j][i] = Tile(tileOne.tileColor, j, i, tileOne.value * 3);
					board[j-1][i] = Tile(Tile::TileColor::EMPTY, j -1, i, 0);
				}
				else {
					board[j][i] = Tile(Tile::TileColor::EMPTY, j, i, 0);
					board[j-1][i] = Tile(Tile::TileColor::EMPTY, j - 1, i, 0);
				}
			}

		}
	}
}

void Board::mergeLeft() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			Tile tileOne = board[i][j];
			Tile tileTwo = board[i][j+1];

			if ((tileOne.value != 0) && tileOne.value == tileTwo.value) {
				if (tileOne.tileColor == tileTwo.tileColor) {
					board[i][j] = Tile(tileOne.tileColor, i, j, tileOne.value * 3);
					board[i][j+1] = Tile(Tile::TileColor::EMPTY, i, j+1, 0);
				}
				else {
					board[i][j] = Tile(Tile::TileColor::EMPTY, i, j+1, 0);
					board[i][j+1] = Tile(Tile::TileColor::EMPTY, i, j+1, 0);
				}
			}

		}
	}
}

void Board::mergeRight() {
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j > 0; j--) {
			Tile tileOne = board[i][j];
			Tile tileTwo = board[i][j - 1];

			if ((tileOne.value != 0) && tileOne.value == tileTwo.value) {
				if (tileOne.tileColor == tileTwo.tileColor) {
					board[i][j] = Tile(tileOne.tileColor, i, j, tileOne.value * 3);
					board[i][j - 1] = Tile(Tile::TileColor::EMPTY, i, j - 1, 0);
				}
				else {
					board[i][j] = Tile(Tile::TileColor::EMPTY, i, j + 1, 0);
					board[i][j - 1] = Tile(Tile::TileColor::EMPTY, i, j - 1, 0);
				}
			}

		}
	}
}

void Board::printBoard(bool errorPrint) {
    static std::string ANSI_RESET = "\u001B[0m";
    static std::string ANSI_RED = "\u001B[31m";
    static std::string ANSI_BLUE = "\u001B[34m";
    static std::string ANSI_BLACK = "\u001B[30m";

	if (errorPrint) {
		// TODO: Implement
	}
	else {
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 4; y++) {
				if (board[x][y].tileColor == Tile::TileColor::BLUE) {
					std::cout << ANSI_BLUE << " " << board[x][y].value << " " << ANSI_RESET;// << std::endl;
				}
				else if (board[x][y].tileColor == Tile::TileColor::GREY) {
					std::cout << ANSI_BLACK << " " << board[x][y].value << " " << ANSI_RESET;// << std::endl;
				}
				else if (board[x][y].tileColor == Tile::TileColor::RED) {
					std::cout << ANSI_RED << " " << board[x][y].value << " " << ANSI_RESET;// << std::endl;
				}
				else {
					std::cout << "0 ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

std::vector<std::pair<Board::MOVE , Board>> Board::getSlidesWithBoard() {
    std::vector<std::pair<Board::MOVE , Board>> validSlidesWithBoard;

    Board b = Board(this);
    b.slideUp();

    if (!(b == this)) {
        std::pair<MOVE, Board> x = std::make_pair(MOVE::UP, b);
        validSlidesWithBoard.push_back(x);
    }

    Board c = Board(this);
    c.slideDown();

    if (!(c == this)) {
        std::pair<MOVE, Board> x = std::make_pair(MOVE::DOWN, c);
        validSlidesWithBoard.push_back(x);
    }

    Board d = Board(this);
    d.slideLeft();

    if (!(d == this)) {
        std::pair<MOVE, Board> x = std::make_pair(MOVE::LEFT, d);
        validSlidesWithBoard.push_back(x);
    }

    Board e = Board(this);
    e.slideRight();

    if (!(e == this)) {
        std::pair<MOVE, Board> x = std::make_pair(MOVE::RIGHT, e);
        validSlidesWithBoard.push_back(x);
    }



    return validSlidesWithBoard;
};


std::vector<std::pair<Board, Board::NewStateData>> Board::getNextStatesWithStateData(int currentMove) {
	std::vector<std::pair<Board, NewStateData>> nextStates;


    //std::cout << currentMove << std::endl;
    static std::set<int> placeTurns = { 1, 2, 3, 6, 7, 8 };
    bool isPlaceTurn = placeTurns.find((currentMove + 1) % 10) != placeTurns.end();
	if (isPlaceTurn) {
		Tile::TileColor color = Player::getTileColorForMove((currentMove + 1) % 10);
        std::vector<std::pair<int, int>> places = getPlaces(color, 0);
        for (int i = 0; i < places.size(); i++) {
            std::pair<int, int> x = places[i];
            Board b = Board(this);
            b.placeTile(color, x.first, x.second, 1);

            Board::NewStateData nsd = Board::NewStateData(x.first, x.second, color);
            std::pair<Board, NewStateData> pair = std::make_pair(b, nsd);
            nextStates.push_back(pair);
        }
	}
    else {
        std::vector<MOVE> slides = getSlides();
        for (int i = 0; i < slides.size(); i++) {
            MOVE x = slides[i];
            Board b = Board(this);
            b.slideBoard(x);

            if (b.gameScore() != 0) {
                NewStateData nsd = NewStateData(x);

                std::pair<Board, NewStateData> pair = std::make_pair(b, nsd);
                nextStates.push_back(pair);
            }
        }
    }

    return nextStates;
};


std::vector<std::pair<int, int>> Board::getPlaces(Tile::TileColor colorToConsider, int placesToGet) {
    std::vector<std::pair<int, int>> places;

    for (int x = 1; x <= boardHeight; x++) {
        for (int y = 1; y<= boardWidth; y++) {
            if (isEmpty(x, y)) {
                std::pair<int ,int> pair = std::make_pair(x, y);

                places.push_back(pair);
            }
        }
    }

	if (placesToGet > 0) {

		std::vector<std::pair<int, int>> v2(places.begin(), places.begin() + placesToGet);
		return v2;
	}

    return places;
}

int Board::getBoardScore() {
	int total = 0;
	for (int i = 0; i < boardWidth; i ++) {
		for (int j = 0; j < boardHeight; j++) {
			total += board[i][j].value;
		}
	}

	return total;
}

Tile Board::getTileAt(int x, int y) {
	return board[x][y];
}


int Board::gameScore() {

    int totalScore = 0;
    for (int x = 0; x < boardWidth; x++){
        for (int y = 0 ; y < boardHeight; y++) {
            totalScore += this->board[x][y].value;
        }
    }

    return totalScore;

}




// Equals
bool Board::operator== (const Board &Ref) const {

    for (int x = 0; x < boardHeight; x++) {
        for (int y = 0; y < boardWidth; y++) {
            if (!(Ref.board[x][y] == board[x][y])) {
                return false;
            }
        }
    }


	return true;
}