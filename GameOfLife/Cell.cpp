//
// Created by spite on 8/14/18.
//

#include <random>
#include <ctime>
#include "Cell.h"

bool Cell::determineNewState(const std::vector<int>& neighbours) {
    int count{0};

    for(auto& x: neighbours)
    {
        count += x;
    }

    if (1 >= count)
        return false;
    else if (3 < count)
        return false;
    else if (3 == count)
        return true;
    else
        return true;

}

const bool Cell::getState() const {
    return m_isAlive;
}

Cell::Cell() {

    m_isAlive = (std::rand() % (1 - 0 + 1)) + 0;

}

void Cell::changeState(bool state) {
    m_isAlive = state;
}
