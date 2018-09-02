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


    for (auto i = 0; i < m_Board.size(); i++) {
        for (auto j = 0; j < m_Board[0].size(); j++) {
            std::vector<int> neighbours;

            if (i == 0) {
                if (j == 0) {
                    neighbours.resize(3);
                    neighbours = {m_Board[i][j + 1]->getState(), m_Board[i + 1][j]->getState(),
                                  m_Board[i + 1][j + 1]->getState()};
                } else if (j == (m_Board[0].size() - 1)) {
                    neighbours.resize(3);
                    neighbours = {m_Board[i + 1][j - 1]->getState(), m_Board[i][j - 1]->getState(),
                                  m_Board[i + 1][j]->getState()};
                } else {
                    neighbours.resize(5);
                    neighbours = {m_Board[i + 1][j]->getState(), m_Board[i + 1][j + 1]->getState(),
                                  m_Board[i + 1][j - 1]->getState(), m_Board[i][j + 1]->getState(),
                                  m_Board[i][j - 1]->getState()};
                }
            }
            else if(i == (m_Board.size() - 1))
            {
                if(j == 0)
                {
                    neighbours.resize(3);
                    neighbours = {m_Board[i][j + 1]->getState(), m_Board[i - 1][j]->getState(),
                                  m_Board[i - 1][j + 1]->getState()};
                }
                else if(j == (m_Board[0].size() - 1))
                {
                    neighbours.resize(3);
                    neighbours = {m_Board[i][j - 1]->getState(), m_Board[i - 1][j]->getState(),
                                  m_Board[i - 1][j - 1]->getState()};
                }
                else
                {
                    neighbours.resize(5);
                    neighbours = {m_Board[i - 1][j]->getState(), m_Board[i - 1][j - 1]->getState(),
                                  m_Board[i][j - 1]->getState(), m_Board[i - 1][j + 1]->getState(),
                                  m_Board[i][j + 1]->getState()};
                }
            }
            else
            {

                neighbours.resize(8);
                neighbours = {m_Board[i - 1][j]->getState(), m_Board[i + 1][j]->getState(),
                              m_Board[i][j - 1]->getState(), m_Board[i][j + 1]->getState(),
                              m_Board[i - 1][j - 1]->getState(), m_Board[i - 1][j + 1]->getState(),
                              m_Board[i + 1][j - 1]->getState(), m_Board[i + 1][j + 1]->getState()};
            }


            tempBoard[i][j]->changeState(m_Board[i][j]->determineNewState(neighbours));
        }
    }

    for (auto i = 0; i < m_Board.size(); i++) {
        for (auto j = 0; j < m_Board[0].size(); j++) {

            m_Board[i][j] = std::move(tempBoard[i][j]);

        }
    }
}
