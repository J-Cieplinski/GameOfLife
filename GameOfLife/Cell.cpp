#include <random>
#include "Cell.h"

bool Cell::determineNewState(const std::vector<int>& neighbours, const bool state) {
    auto count{0};

    for(const auto& x: neighbours)
    {
        count += x;
    }

	if (2 > count)
		return false;
	else if (3 < count)
		return false;
	else if (3 == count)
		return true;
	else if (2 == count && state)
		return true;
}

bool Cell::getState() const {
    return isAlive_;
}

Cell::Cell() {
    isAlive_ = Cell::distribution_(Cell::geEngine_);
}

void Cell::changeState(const bool state) {
    isAlive_ = state;
}


std::random_device Cell::randomDevice_;
std::mt19937 Cell::geEngine_(Cell::randomDevice_());
std::bernoulli_distribution Cell::distribution_(0.4);