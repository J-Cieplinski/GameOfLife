//
// Created by spite on 8/14/18.
//

#ifndef GAME_OF_LIFE_BOARD_H
#define GAME_OF_LIFE_BOARD_H

#include <memory>
#include <vector>
#include "Cell.h"

class Board {
private:
    std::vector<std::vector<std::unique_ptr<Cell>>> m_Board;
    void calculateNewBoardState(std::vector<std::vector<std::shared_ptr<Cell>>> &tempBoard);
public:
    Board(int width, int height, bool isAlive = true);
    void displayBoard();
    void updateBoardState();



};


#endif //GAME_OF_LIFE_BOARD_H
