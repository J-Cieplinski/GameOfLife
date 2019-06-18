//
// Created by spite on 8/14/18.
//

#ifndef GAME_OF_LIFE_BOARD_H
#define GAME_OF_LIFE_BOARD_H

#include <memory>
#include <vector>
#include <string>
#include "Cell.h"
#include <map>

class Board {
private:
    std::vector<std::vector<std::unique_ptr<Cell>>> m_Board;
    void calculateNewBoardState(std::vector<std::vector<std::unique_ptr<Cell>>> &tempBoard);
	void loadBoardState(std::string boardLocation);
	std::map<bool, char> m_map = { std::make_pair(true, '*'), std::make_pair(false, '#') };

public:
    Board(int width, int height, bool isAlive = true);
	Board(std::string fileLocation);
    void displayBoard();
    void updateBoardState();
	void saveBoardState(std::string boardLocation);
};




#endif //GAME_OF_LIFE_BOARD_H
