//
// Created by Cameron Deans on 10/03/2016.
//

#include "DepthLimitedDFSAgent.h"

DepthLimitedDFSAgent::DepthLimitedDFSAgent(Board b) {
    currentBoard = b;
    currentMove = 1;\

    std::cerr << "DFS Start" << std::endl;

    srand(time(NULL));
}

DepthLimitedDFSAgent::DepthLimitedDFSAgent() {
    currentBoard = Board();
    currentMove = 1;\

    std::cerr << "DFS Start" << std::endl;

    srand(time(NULL));
}

void DepthLimitedDFSAgent::handlePlaceTurn(std::string moveInfo) {
    //std::cerr << "Handle Place Turn" << std::endl;
    previousMove = moveInfo;


    int xPos = atoi(moveInfo.substr(0,1).c_str());
    int yPos = atoi(moveInfo.substr(1,1).c_str());

    currentBoard.placeTile(Player::getTileColorForMove(currentMove), xPos, yPos, 1);
    currentMove++;
}

void DepthLimitedDFSAgent::handleMoveTurn(std::string moveInfo) {

    if (moveInfo == "U") {
        currentBoard.slideBoard(Board::MOVE::UP);
    }
    else if (moveInfo == "D") {
        currentBoard.slideBoard(Board::MOVE::DOWN);
    }
    else if (moveInfo == "L") {
        currentBoard.slideBoard(Board::MOVE::LEFT);
    }
    else if (moveInfo == "R") {
        currentBoard.slideBoard(Board::MOVE::RIGHT);
    }

    currentMove++;

}

void DepthLimitedDFSAgent::performPlaceTurn() {

    double score = 0;
    int depth = 4;
    int sampleSize = 1;

    int placesToGet = 5;

    std::pair<int, int> moveToMake = std::make_pair(-1, -1);

    std::vector<std::pair<int, int>> places = currentBoard.getPlaces(Player::getTileColorForMove(currentMove), placesToGet);


    if (places.size() > 0) {



        for (int i = 0; i < places.size(); i++) {
            std::pair<int, int> coord = places[i];

            double resultCounter = 0;
            int x = coord.first;
            int y = coord.second;

            Board newBoard = Board(currentBoard);
            newBoard.placeTile(Player::getTileColorForMove(currentMove), x, y , 1);

            for (int j = 0; j < sampleSize; j++) {
                double result = DepthLimitedSearch(newBoard, depth);
                resultCounter += result;
            }

            double averageScore = resultCounter / sampleSize;

            if (averageScore >= score) {
                score = averageScore;
                moveToMake = coord;
            }


        }

        int x = moveToMake.first;
        int y = moveToMake.second;



        if (currentBoard.isEmpty(x, y )) {
            currentBoard.placeTile(Player::getTileColorForMove(currentMove), x , y ,1);

            std::cerr << "MOVE - "<< currentMove << ": " << x << y << std::endl;
            printf("%d%d\n",x,y);
            fflush(stdout);

            currentMove++;
        }
        else {
            // Tile not empty
        }
    }



}

void DepthLimitedDFSAgent::performMoveTurn() {
    double score = 0;
    Board::MOVE move;

    int depth = 4;
    int sampleSize = 1;




    std::vector<Board::MOVE> slides = currentBoard.getSlides();



    if (slides.size() > 0) {
        for (int i = 0 ; i < slides.size(); i++) {
            Board::MOVE m = slides[i];

            double resultCounter = 0;

            Board newBoard = Board(currentBoard);
            newBoard.slideBoard(m);

            for (int j = 0; j < sampleSize; j++) {
                double result = DepthLimitedSearch(newBoard, depth);
                resultCounter += result;
            }

            double averageScore = resultCounter / sampleSize;

            if (averageScore >= score) {
                score = averageScore;
                move = m;
            }

        }
    }

    currentBoard.slideBoard(move);

    std::cerr << "MOVE - "<< currentMove << ": ";

    switch (move) {
        case Board::MOVE::LEFT:
            printf("L\n");
            std::cerr << "L" <<std::endl;
            break;
        case Board::MOVE::RIGHT:
            printf("R\n");
            std::cerr << "R" <<std::endl;
            break;
        case Board::MOVE::UP:
            printf("U\n");
            std::cerr << "U" <<std::endl;
            break;
        case Board::MOVE::DOWN:
            printf("D\n");
            std::cerr << "D" <<std::endl;
            break;
    }

    fflush(stdout);

    currentMove++;


}

double DepthLimitedDFSAgent::DepthLimitedSearch(Board b, int depth) {
    double score = 0.0;

    int placesToGet = 5;

    int hardCodedDepth = 4;



    if (depth == 0) {
        score = boardTotalHeuristic(b);
    }
    else {

        std::set<int> placeTurns = { 1, 2, 3, 6, 7, 8 };

        if (placeTurns.find((currentMove + ((hardCodedDepth + 1) - depth)) % 10) != placeTurns.end()) {
            Tile::TileColor color = Player::getTileColorForMove((currentMove + ((hardCodedDepth + 1) - depth)) % 10);


            std::vector<std::pair<int, int>> places = b.getPlaces(color, placesToGet);

            for (int i = 0; i < places.size(); i++) {
                std::pair<int, int> pair = places[i];
                int x = pair.first;
                int y = pair.second;

                Board newBoard = Board(b);
                newBoard.placeTile(color, x , y,1);

                double current = DepthLimitedSearch(newBoard, depth - 1);
                score = std::max(score, current);
            }
        }
        else {
            std::vector<std::pair<Board::MOVE , Board>> slides = b.getSlidesWithBoard();

            for (int i = 0; i < slides.size(); i++) {
                std::pair<Board::MOVE , Board> pair = slides[i];
                double current = DepthLimitedSearch(pair.second, depth - 1);
                score = std::max(score, current);
            }

        }
    }

    return score;
}


double DepthLimitedDFSAgent::boardTotalHeuristic(Board b) {
    int boardScore = b.getBoardScore();

    double oneColor = oneColorMajority(b);

    return (boardScore * 1.5) + (oneColor * 20);
}

double DepthLimitedDFSAgent::oneColorMajority(Board b) {
    int redTiles = 0;
    int blueTiles = 0;
    int greyTiles = 0;

    for (int x = 0; x < b.boardHeight; x++) {
        for (int y = 0; y < b.boardWidth; y++) {
            Tile t = b.getTileAt(x, y);

            if (t.tileColor == Tile::TileColor::RED) {
                redTiles++;
            }
            if (t.tileColor == Tile::TileColor::BLUE) {
                blueTiles++;
            }
            if (t.tileColor == Tile::TileColor::GREY) {
                greyTiles++;
            }
        }


    }

    int totalTiles = redTiles + blueTiles + greyTiles;
    if (totalTiles > 0) {
        int redBlue = std::max(redTiles, blueTiles);
        int blueGrey = std::max(blueTiles, greyTiles);

        int mixMax = std::max(redBlue, blueGrey);

        if (mixMax == redTiles) {
            return redTiles / totalTiles;
        }
        else if (mixMax == blueTiles) {
            return blueTiles / totalTiles;
        }
        else if (mixMax == greyTiles) {
            return greyTiles / totalTiles;
        }
    }

    return 0;
}


