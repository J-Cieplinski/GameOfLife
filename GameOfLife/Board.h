//
#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Cell.h"

constexpr auto colorYellow = "\x1b[33m";
constexpr auto colorBlack = "\x1b[30m";



class Board {
private:
    std::vector<std::vector<Cell>> board_;
    void calculateNewBoardState(std::vector<std::vector<Cell>>& tempBoard);
	void loadBoardState(std::string boardLocation);
    const std::map<bool, std::pair<char, std::string>> map_ = { {true, {'*', colorYellow}}, {false, {'#',colorBlack}} };

public:
    Board(int width, int height, bool isAlive = true);
	Board(const std::string& fileLocation);
    void displayBoard();
    void updateBoardState();
	void saveBoardState(const std::string& boardLocation);
};
