// 6561Agent.cpp : Defines the entry point for the console application.
//


#include "CompetitionMain.h"
#include "DepthLimitedDFSAgent.h"
#include "MonteCarloAgent.h"


int main(int argc, char* argv[])
{
	CompetitionMain main = CompetitionMain();

	//main.gameLoop();


	Player *agent = new MonteCarloAgent();
	agent->performPlaceTurn();

	Board b = Board();
//	b.placeTile(Tile::TileColor::RED, 1 , 1, 1);
//	b.placeTile(Tile::TileColor::RED, 1 , 2, 1);
//	b.slideBoard(Board::MOVE::DOWN);


	return 0;
}

