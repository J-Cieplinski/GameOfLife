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

    for(auto i = 0; i < m_Board.size(); i++)
    {
        for(auto j = 0; j < m_Board[0].size(); j++)
        {
            std::vector<int> neighbours;
            if( 0!=i || 0 !=j) {
                if (i != m_Board.size() && j != m_Board[1].size()) {
                neighbours = {m_Board[i - 1][j]->getState(), m_Board[i + 1][j]->getState(),
                              m_Board[i][j - 1]->getState(), m_Board[i][j + 1]->getState(),
                              m_Board[i - 1][j - 1]->getState(), m_Board[i - 1][j + 1]->getState(),
                              m_Board[i + 1][j - 1]->getState(), m_Board[i + 1][j + 1]->getState()};
                }
            }
            else if(i != m_Board.size() && j != m_Board[1].size())
            {
                neighbours = {m_Board[i - 1][j]->getState(), m_Board[i + 1][j]->getState(),
                              m_Board[i][j - 1]->getState(), m_Board[i][j + 1]->getState(),
                              m_Board[i - 1][j - 1]->getState(), m_Board[i - 1][j + 1]->getState(),
                              m_Board[i + 1][j - 1]->getState(), m_Board[i + 1][j + 1]->getState()};

            }


            m_Board[i][j]->checkAndChangeState(neighbours);
        }
    }


}
