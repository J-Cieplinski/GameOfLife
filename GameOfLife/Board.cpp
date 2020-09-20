//
// Created by spite on 8/14/18.
//

#include <iostream>
#include <fstream>
#include "Board.h"
#include <chrono>
#include <thread>


constexpr auto colorMagenta = "\x1b[45m";


Board::Board(int width, int height, bool isAlive) {
    board_.resize(height, std::vector<Cell>(width));
    backBoard_ = board_;
}


Board::Board(const std::string& fileLocation)
{
	loadBoardState(fileLocation);
}

void Board::displayBoard() {

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	system("cls");


    std::ostream board(std::cout.rdbuf());
	board << colorMagenta;

    bool cellState{};

	for(const auto& row : board_) {
		for(const auto& column : row) {
            cellState = column.getState();
			board << map_.at(cellState).second << map_.at(cellState).first << ' ';
		}
		board << '\n';
	}

}

void Board::updateBoardState() {

    calculateNewBoardState();

}

void Board::loadBoardState(std::string boardLocation)
{
	std::ifstream file;
	
	file.open(boardLocation);
	int temp{ 0 };
	int height{ 0 };
	int width{ 0 };

	//get board dimensions and resize as needed
	file >> height;
	file >> width;

    board_.resize(height, std::vector<Cell>(width));
	


	while (file.is_open())
	{
		for (auto& x : board_)
		{
			for (auto& y : x)
			{
					file >> temp;
					y.changeState(temp);
			}
		}

		file.close();	

	}

} //TODO Fix Loading

void Board::saveBoardState(const std::string& boardLocation)
{
	std::fstream file;

	file.open(boardLocation, std::fstream::out);
	
	while(file.is_open())
	{
		file << board_.size();
		file << " ";
		file << board_[1].size();
		file << std::endl;

		for (auto& x : board_)
		{
			for (auto& y : x)
			{
				file << y.getState();
				file << " ";
			}
			file << std::endl;
		}

		file.close();
	}
	
	

}

void Board::calculateUpperLeftCorner(const int width, const int height, const bool currentCellState)
{
    if (width == 0) {
    const std::vector<int> neighbours = { board_[height + 1][width + 1].getState(), board_[height + 1][width].getState(),
									 board_[height][width + 1].getState() };
    	
        backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
    }
}

void Board::calculateUpperRightCorner(const int width, const int height, const bool currentCellState)
{
    if (width == board_[0].size() - 1) {
    const std::vector<int> neighbours = { board_[height + 1][width - 1].getState(), board_[height + 1][width].getState(),
										board_[height][width - 1].getState() };
    	
        backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
    }
}

void Board::calculateLowerLeftCorner(const int width, const int height, const bool currentCellState)
{
    if (width == 0) {

        const std::vector<int> neighbours = { board_[height - 1][width + 1].getState(), board_[height - 1][width].getState(),
                      board_[height][width + 1].getState() };
        backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
    }
}

void Board::calculateLowerRightCorner(const int width, const int height, const bool currentCellState)
{
    if (width == board_[0].size() - 1) {

        const std::vector<int> neighbours = { board_[height - 1][width - 1].getState(), board_[height - 1][width].getState(),
                      board_[height][width - 1].getState() };
        backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
    }
}

void Board::calculateUpperBorder(const int width, const int height, const bool currentCellState)
{
    if (width > 0 && width < board_[0].size() - 1)
    {
        std::vector<int> neighbours;

        for (auto i = 0; i <= 1; i++)
        {
            for (auto j = -1; j <= 1; j++)
            {
                neighbours.push_back(board_[height + i][width + j].getState());
            }
        }
        backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
    }
}

void Board::calculateLowerBorder(const int width, const int height, const bool currentCellState)
{
    if (width > 0 && width < board_[0].size() - 1)
    {
        std::vector<int> neighbours;

        for (auto i = -1; i <= 0; i++)
        {
            for (auto j = -1; j <= 1; j++)
            {
                neighbours.push_back(board_[height + i][width + j].getState());
            }
        }
        backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
    }
}

void Board::calculateLeftBorder(const int width, const int height, const bool currentCellState)
{
    if (height > 0 && height < board_.size() - 1)
    {
        std::vector<int> neighbours;
        for (auto i = -1; i <= 1; i++)
        {
            for (auto j = 0; j <= 1; j++)
            {
                neighbours.push_back(board_[height + i][width + j].getState());
            }
        }
        backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
    }
}

void Board::calculateRightBorder(const int width, const int height, const bool currentCellState)
{
    if (height > 0 && height < board_.size() - 1)
    {
        std::vector<int> neighbours;
        for (auto i = -1; i <= 1; i++)
        {
            for (auto j = -1; j <= 0; j++)
            {
                neighbours.push_back(board_[height + i][width + j].getState());
            }
        }
        backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
    }
}

void Board::calculateBoardCenter(const int width, const int height, const bool currentCellState)
{
    if (0 < width && 0 < height && board_.size() - 1 > height && board_[1].size() - 1 > width)
    {
        std::vector<int> neighbours;


        for (auto i = -1; i <= 1; i++)
        {
            for (auto j = -1; j <= 1; j++)
            {
                if (!(0 == j && 0 == i)) // don't pass the cell itself to check
                {
                    neighbours.push_back(board_[height + i][width + j].getState()); // get all cells around
                }
            }
        }
        backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
        neighbours.clear();
    }
}

void Board::calculateNewBoardState()
{

    for(auto height = 0; height < board_.size(); height++)
    {
        for(auto width = 0; width < board_[0].size(); width++)
        {
			auto currentCellState = board_[height][width].getState();
        	
			// Board Center
            calculateBoardCenter(width, height, currentCellState);

            //First row
            if(height == 0)
            {
                // Upper left corner
                calculateUpperLeftCorner(width, height, currentCellState);

                //Upper right corner
                calculateUpperRightCorner(width, height, currentCellState);
            }
            //Last row
            if(height == board_.size()-1)
            {
            	//Lower left corner
                calculateLowerLeftCorner(width, height, currentCellState);

                //Lower right corner
                calculateLowerRightCorner(width, height, currentCellState);
            }

            // upper border
            if(height == 0)
            {
                calculateUpperBorder(width, height, currentCellState);
            }

            //lower border
            if(height == board_.size()-1)
            {
                calculateLowerBorder(width, height, currentCellState);
            }

            //left border
            if(width == 0)
            {
                calculateLeftBorder(width, height, currentCellState);
            }

            //right border
            if(width == board_[0].size()-1)
            {
                calculateRightBorder(width, height, currentCellState);
            }
        }
    }

    std::swap(board_, backBoard_);

}
