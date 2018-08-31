//
// Created by spite on 8/14/18.
//

#ifndef GAME_OF_LIFE_CELL_H
#define GAME_OF_LIFE_CELL_H

#include <vector>

class Cell {
private:
    bool m_isAlive;
    void checkAndChangeState(std::vector<int> neighbours);
public:
    Cell();
    const bool getState() const;

};


#endif //GAME_OF_LIFE_CELL_H
