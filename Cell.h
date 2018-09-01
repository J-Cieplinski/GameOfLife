//
// Created by spite on 8/14/18.
//

#ifndef GAME_OF_LIFE_CELL_H
#define GAME_OF_LIFE_CELL_H

#include <vector>
#include <random>
#include <ctime>

class Cell {
private:
    bool m_isAlive;
public:
    Cell();
    void checkAndChangeState(const std::vector<int> neighbours);
    const int getState() const;

};


#endif //GAME_OF_LIFE_CELL_H
