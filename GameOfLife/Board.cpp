//
// Created by spite on 8/14/18.
//

#include <iostream>
#include <fstream>
#include "Board.h"
#include <iso646.h>
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

void Board::calculateNewBoardState()
{

    std::vector<int> neighbours{};

    for(auto height = 0; height < board_.size(); height++)
    {
        for(auto width = 0; width < board_[0].size(); width++)
        {
			auto currentCellState = board_[height][width].getState();
			// First most cases
			if(0 < width && 0 < height && board_.size()-1 > height && board_[1].size()-1 > width)
            {
				neighbours.resize(8);

				for(auto i = -1; i <= 1; i++)
                {
					for(auto j = -1; j <= 1; j++)
                    {
						if(not (0 == j and 0 == i)) // don't pass the cell itself to check
                        {
							neighbours.push_back(board_[height+i][width+j].getState()); // get all cells around
                        }
                    }
                 }
				backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
                neighbours.clear();
			}

            //First row
            if(height == 0)
            {
				neighbours.resize(3);

                // Upper left corner
                if(width == 0)
                {
                    neighbours = {board_[height + 1][width + 1].getState(), board_[height + 1][width].getState(),
                                  board_[height][width + 1].getState()};
                    backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }

                //Upper right corner
                if(width == board_[0].size()-1)
                {
                    neighbours = {board_[height + 1][width - 1].getState(), board_[height + 1][width].getState(),
                                  board_[height][width - 1].getState()};
                    backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }
            //Last row
            if(height == board_.size()-1)
            {
				neighbours.resize(3);

                //Lower left corner
                if(width == 0)
                {

                    neighbours = {board_[height - 1][width + 1].getState(), board_[height - 1][width].getState(),
                                  board_[height][width + 1].getState()};
                    backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }

                //Lower right corner
                if(width == board_[0].size()-1)
                {

                    neighbours = {board_[height - 1][width - 1].getState(), board_[height - 1][width].getState(),
                                  board_[height][width - 1].getState()};
                    backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }

            // upper border
            if(height == 0)
            {
                if(width > 0 && width < board_[0].size()-1)
                {
                    neighbours.resize(5);

                    for(auto i = 0; i <= 1; i++)
                    {
                        for(auto j = -1; j <= 1; j++)
                        {
                            neighbours.push_back(board_[height+i][width+j].getState());
                        }
                    }
                    backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }

            //lower border
            if(height == board_.size()-1)
            {
                if(width > 0 && width < board_[0].size()-1)
                {
                    neighbours.resize(5);
                    for(auto i = -1; i <= 0; i++)
                    {
                        for(auto j = -1; j <= 1; j++)
                        {
                            neighbours.push_back(board_[height+i][width+j].getState());
                        }
                    }
                    backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }

            //left border
            if(width == 0)
            {
                if(height > 0 && height < board_.size()-1)
                {
                    neighbours.resize(5);
                    for(auto i = -1; i <= 1; i++)
                    {
                        for(auto j = 0; j <= 1; j++)
                        {
                            neighbours.push_back(board_[height+i][width+j].getState());
                        }
                    }
                    backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }

            //right border
            if(width == board_[0].size()-1)
            {
                if(height > 0 && height < board_.size()-1)
                {
                    neighbours.resize(5);
                    for(auto i = -1; i <= 1; i++)
                    {
                        for(auto j = -1; j <= 0; j++)
                        {
                            neighbours.push_back(board_[height+i][width+j].getState());
                        }
                    }
                    backBoard_[height][width].changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }
        }
    }

    std::swap(board_, backBoard_);

}
