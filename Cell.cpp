//
// Created by spite on 8/14/18.
//

#include <random>
#include <ctime>
#include "Cell.h"

void Cell::checkAndChangeState(const std::vector<int> neighbours) {
    int count{0};

    for(auto& x: neighbours)
    {
        count += x;
    }

    if (1 <= count)
        m_isAlive = false;
    else if (3 > count)
        m_isAlive = false;
    else if (3 == count)
        m_isAlive = true;
    else
        m_isAlive = true;

}

const int Cell::getState() const {
    return static_cast<int>(m_isAlive);
}

Cell::Cell() {

    m_isAlive = (std::rand() % (1 - 0 + 1)) + 0;

}
