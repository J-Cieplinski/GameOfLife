//
// Created by spite on 8/14/18.
//

#include <iostream>
#include <fstream>
#include "Board.h"
#include <iso646.h>
#include <chrono>
#include <thread>


Board::Board(int width, int height, bool isAlive) {

	m_Board.resize(height);

    for(auto& x : m_Board)
    {
        x.resize(width);
		for (auto& y : x)
			y = std::make_unique<Cell>();	
    }
}


Board::Board(std::string fileLocation)
{
	loadBoardState(fileLocation);
}

void Board::displayBoard() {

	std::this_thread::sleep_for(std::chrono::milliseconds(500));	
	system("cls");


	std::ostream board(std::cout.rdbuf());
	board << "\x1b[45m";

    for(auto i = 0; i < m_Board.size(); i++)
    {
        for(auto j = 0; j < m_Board[0].size(); j++)
        {
			auto temp = m_Board[i][j]->getState();
			if (temp)
			{
				board << "\x1b[33m";
				board << m_map[temp];
			}
			else
			{
				board << "\x1b[30m";
				board << m_map[temp];
			}
			board << ' ';

        }
        board << std::endl;
    }
	board << "\x1b[37m";

}

void Board::updateBoardState() {

    std::vector<std::vector<std::unique_ptr<Cell>>> tempBoard;
    tempBoard.resize(m_Board.size());
    for(auto& x : tempBoard)
    {
        x.resize(m_Board[0].size());
    }
    for(auto& x : tempBoard)
    {
        for(auto& y : x)
        {
            y = std::make_unique<Cell>();
        }
    }

    calculateNewBoardState(tempBoard);

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
	m_Board.resize(height);

	for (auto& x : m_Board)
	{
		x.resize(width);
		for (auto& y : x)
			y = std::make_unique<Cell>();
	}


	while (file.is_open())
	{
		for (auto& x : m_Board)
		{
			for (auto& y : x)
			{
					file >> temp;
					y->changeState(temp);
			}
		}

		file.close();	

	}

}

void Board::saveBoardState(std::string boardLocation)
{
	std::fstream file;

	file.open(boardLocation, std::fstream::out);
	
	while(file.is_open())
	{
		file << m_Board.size();
		file << " ";
		file << m_Board[1].size();
		file << std::endl;

		for (auto& x : m_Board)
		{
			for (auto& y : x)
			{
				file << y->getState();
				file << " ";
			}
			file << std::endl;
		}

		file.close();
	}
	
	

}

void Board::calculateNewBoardState(std::vector<std::vector<std::unique_ptr<Cell>>> &tempBoard)
{

    std::vector<int> neighbours{};

    for(auto height = 0; height < m_Board.size(); height++)
    {
        for(auto width = 0; width < m_Board[0].size(); width++)
        {
			auto currentCellState = m_Board[height][width]->getState();
					// First most cases
			if(0 < width && 0 < height && m_Board.size()-1 > height && m_Board[1].size()-1 > width)
            {
				neighbours.resize(8);

				for(auto i = -1; i <= 1; i++)
                {
					for(auto j = -1; j <= 1; j++)
                    {
						if(not (0 == j and 0 == i)) // don't pass the cell itself to check
                        {
							neighbours.push_back(m_Board[height+i][width+j]->getState()); // get all cells around
                        }
                    }
                 }
				tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, currentCellState));
                neighbours.clear();
			}

            //First row
            if(height == 0)
            {
				neighbours.resize(3);

                // Upper left corner
                if(width == 0)
                {
                    neighbours = {m_Board[height + 1][width + 1]->getState(), m_Board[height + 1][width]->getState(),
                                  m_Board[height][width + 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }

                //Upper right corner
                if(width == m_Board[0].size()-1)
                {
                    neighbours = {m_Board[height + 1][width - 1]->getState(), m_Board[height + 1][width]->getState(),
                                  m_Board[height][width - 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }
            //Last row
            if(height == m_Board.size()-1)
            {
				neighbours.resize(3);

                //Lower left corner
                if(width == 0)
                {

                    neighbours = {m_Board[height - 1][width + 1]->getState(), m_Board[height - 1][width]->getState(),
                                  m_Board[height][width + 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }

                //Lower right corner
                if(width == m_Board[0].size()-1)
                {

                    neighbours = {m_Board[height - 1][width - 1]->getState(), m_Board[height - 1][width]->getState(),
                                  m_Board[height][width - 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }

            // upper border
            if(height == 0)
            {
                if(width > 0 && width < m_Board[0].size()-1)
                {
                    neighbours.resize(5);

                    for(auto i = 0; i <= 1; i++)
                    {
                        for(auto j = -1; j <= 1; j++)
                        {
                            neighbours.push_back(m_Board[height+i][width+j]->getState());
                        }
                    }
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }

            //lower border
            if(height == m_Board.size()-1)
            {
                if(width > 0 && width < m_Board[0].size()-1)
                {
                    neighbours.resize(5);
                    for(auto i = -1; i <= 0; i++)
                    {
                        for(auto j = -1; j <= 1; j++)
                        {
                            neighbours.push_back(m_Board[height+i][width+j]->getState());
                        }
                    }
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }

            //left border
            if(width == 0)
            {
                if(height > 0 && height < m_Board.size()-1)
                {
                    neighbours.resize(5);
                    for(auto i = -1; i <= 1; i++)
                    {
                        for(auto j = 0; j <= 1; j++)
                        {
                            neighbours.push_back(m_Board[height+i][width+j]->getState());
                        }
                    }
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }

            //right border
            if(width == m_Board[0].size()-1)
            {
                if(height > 0 && height < m_Board.size()-1)
                {
                    neighbours.resize(5);
                    for(auto i = -1; i <= 1; i++)
                    {
                        for(auto j = -1; j <= 0; j++)
                        {
                            neighbours.push_back(m_Board[height+i][width+j]->getState());
                        }
                    }
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, currentCellState));
                    neighbours.clear();
                }
            }
        }
    }

    for(auto height = 0; height < m_Board.size(); height++) {
        for (auto width = 0; width < m_Board[0].size(); width++) {

            m_Board[height][width] = std::move(tempBoard[height][width]);
        }
    }



}
