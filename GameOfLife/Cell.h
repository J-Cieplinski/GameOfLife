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
    static bool determineNewState(const std::vector<int>& neighbours, const bool state);
    const bool getState() const;
    void changeState(bool state);

};


#endif //GAME_OF_LIFE_CELL_H
