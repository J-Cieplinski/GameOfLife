#pragma once

#include <vector>
#include <random>

class Cell {
private:
    bool isAlive_;
    static  std::random_device randomDevice_;
    static  std::mt19937 geEngine_;
    static  std::bernoulli_distribution distribution_;
public:
    Cell();
    static bool determineNewState(const std::vector<int>& neighbours, const bool state);
    bool getState() const;
    void changeState(const bool state);

};
