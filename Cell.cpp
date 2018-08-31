//
// Created by spite on 8/14/18.
//

#include <random>
#include <ctime>
#include "Cell.h"

void Cell::checkAndChangeState(std::vector<int> neighbours) {
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

const bool Cell::getState() const {
    return m_isAlive;
}

Cell::Cell() {
    std::mt19937 generator(std::time(nullptr));
    std::uniform_int_distribution<int>distribution(0,1);
    m_isAlive = static_cast<bool>(distribution(generator));
}
