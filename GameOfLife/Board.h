//
#pragma once

#include <map>
#include <string>
#include <vector>

#include "Cell.h"

constexpr auto colorYellow = "\x1b[33m";
constexpr auto colorBlack = "\x1b[30m";



class Board {
private:
    std::vector<std::vector<Cell>> board_;
    std::vector<std::vector<Cell>> backBoard_;
    void calculateUpperLeftCorner(const int width, const int height, const bool currentCellState);
    void calculateUpperRightCorner(const int width, const int height, const bool currentCellState);
    void calculateLowerLeftCorner(const int width, const int height, const bool currentCellState);
    void calculateLowerRightCorner(const int width, const int height, const bool currentCellState);
    void calculateUpperBorder(const int width, const int height, const bool currentCellState);
    void calculateLowerBorder(const int width, const int height, const bool currentCellState);
    void calculateLeftBorder(const int width, const int height, const bool currentCellState);
    void calculateRightBorder(const int width, const int height, const bool currentCellState);
    void calculateBoardCenter(const int width, const int height, const bool currentCellState);


    void calculateNewBoardState();
	void loadBoardState(std::string boardLocation);
    const std::map<bool, std::pair<char, std::string>> map_ = { {true, {'*', colorYellow}}, {false, {'#',colorBlack}} };

public:
    Board(int width, int height, bool isAlive = true);
	Board(const std::string& fileLocation);
    void displayBoard();
    void updateBoardState();
	void saveBoardState(const std::string& boardLocation);
};
