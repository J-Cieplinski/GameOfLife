#pragma once

#include <vector>
#include <random>

class Cell {
private:
    bool isAlive_;
public:
    Cell();
    static bool determineNewState(const std::vector<int>& neighbours, const bool state);
    bool getState() const;
    void changeState(const bool state);

};
