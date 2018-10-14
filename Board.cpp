//
// Created by spite on 8/14/18.
//

#include <iostream>
#include "Board.h"

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


void Board::displayBoard() {


    for(auto i = 0; i < m_Board.size(); i++)
    {
        for(auto j = 0; j < m_Board[0].size(); j++)
        {
            std::cout << (m_Board[i][j])->getState();
        }
        std::cout << std::endl;
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

void Board::calculateNewBoardState(std::vector<std::vector<std::shared_ptr<Cell>>> &tempBoard)
{

    std::vector<int> neighbours{};

    for(auto height = 0; height < m_Board.size(); height++)
    {
        for(auto width = 0; width < m_Board[0].size(); width++)
        {
            // First most cases
                    if(0 < height && 0 < width)
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
                        tempBoard[height][width]->changeState(Cell::determineNewState(neighbours));
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
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours));
                    neighbours.clear();
                }
                //Upper right corner
                if(width == m_Board[0].size())
                {
                    neighbours.resize(3);

                    neighbours = {m_Board[height + 1][width - 1]->getState(), m_Board[height + 1][width]->getState(),
                                  m_Board[height][width - 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours));
                    neighbours.clear();
                }
            }
            //Last row
            if(height == m_Board.size())
            {
                //Lower left corner
                if(width == 0)
                {
                    neighbours.resize(3);

                    neighbours = {m_Board[height - 1][width + 1]->getState(), m_Board[height - 1][width]->getState(),
                                  m_Board[height][width + 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours));
                    neighbours.clear();
                }
                //Lower right corner
                if(width == 0)
                {
                    neighbours.resize(3);

                    neighbours = {m_Board[height - 1][width - 1]->getState(), m_Board[height - 1][width]->getState(),
                                  m_Board[height][width - 1]->getState()};
                    tempBoard[height][width]->changeState(Cell::determineNewState(neighbours));
                    neighbours.clear();
                }
            }



        }
    }


}
