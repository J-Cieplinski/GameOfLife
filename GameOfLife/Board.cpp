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
    }

    for(auto& x : m_Board)
    {
        for(auto& y : x)
        {
            y = std::make_unique<Cell>();
        }
    }

}


Board::Board(std::string fileLocation)
{
	loadBoardState(fileLocation);
}

void Board::displayBoard() {

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));	
	system("cls");

	std::ostream board(std::cout.rdbuf());

    for(auto i = 0; i < m_Board.size(); i++)
    {
        for(auto j = 0; j < m_Board[0].size(); j++)
        {
            board << (m_Board[i][j])->getState();
			board << ' ';
        }
        board << std::endl;
    }

}

void Board::updateBoardState() {

    std::vector<std::vector<std::shared_ptr<Cell>>> tempBoard;
    tempBoard.resize(m_Board.size());
    for(auto& x : tempBoard)
    {
        x.resize(m_Board[0].size());
    }
    for(auto& x : tempBoard)
    {
        for(auto& y : x)
        {
            y = std::make_shared<Cell>();
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

	file >> height;
	file >> width;

{								//Create Board
								//TODO messy, think of something else later
	m_Board.resize(height);

		for (auto& x : m_Board)
		{
			x.resize(width);
		}

		for (auto& x : m_Board)
		{
			for (auto& y : x)
			{
				y = std::make_unique<Cell>();
			}
		}
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

void Board::calculateNewBoardState(std::vector<std::vector<std::shared_ptr<Cell>>> &tempBoard) // TODO rewrite needed, hacky
{

    std::vector<int> neighbours{};

    for(auto height = 0; height < m_Board.size(); height++)
    {
        for(auto width = 0; width < m_Board[0].size(); width++)
        {
			auto tmp = m_Board[height][width]->getState();
            // First most cases
                    if(0 < height && 0 < width && m_Board.size()-1 > width && m_Board[1].size()-1 > height)
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
                        tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, tmp));
                        neighbours.clear();
                    }
            //First row
            if(height == 0)
            {
                // Upper left corner
                if(width == 0)
                {
                    neighbours.resize(3);

                    neighbours = {m_Board[height + 1][width + 1]->getState(), m_Board[height + 1][width]->getState(),
                                  m_Board[height][width + 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, tmp));
                    neighbours.clear();
                }
                //Upper right corner
                if(width == m_Board[0].size()-1)
                {
                    neighbours.resize(3);

                    neighbours = {m_Board[height + 1][width - 1]->getState(), m_Board[height + 1][width]->getState(),
                                  m_Board[height][width - 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, tmp));
                    neighbours.clear();
                }
            }
            //Last row
            if(height == m_Board.size()-1)
            {
                //Lower left corner
                if(width == 0)
                {
                    neighbours.resize(3);

                    neighbours = {m_Board[height - 1][width + 1]->getState(), m_Board[height - 1][width]->getState(),
                                  m_Board[height][width + 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, tmp));
                    neighbours.clear();
                }
                //Lower right corner
                if(width == m_Board[0].size()-1)
                {
                    neighbours.resize(3);

                    neighbours = {m_Board[height - 1][width - 1]->getState(), m_Board[height - 1][width]->getState(),
                                  m_Board[height][width - 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, tmp));
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
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, tmp));
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
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, tmp));
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
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, tmp));
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
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours, tmp));
                    neighbours.clear();
                }
            }
        }
    }

    for(auto height = 0; height < m_Board.size(); height++) {
        for (auto width = 0; width < m_Board[0].size(); width++) {

            *m_Board[height][width] = *tempBoard[height][width];	//TODO change this to transfer ownership of a pointer
        }
    }



}
