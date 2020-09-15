#include <random>
#include "Cell.h"

bool Cell::determineNewState(const std::vector<int>& neighbours, const bool state) // TODO too hacky?
{
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

    isAlive_ = (std::rand() % (1 - 0 + 1)) + 0;

}

void Cell::changeState(const bool state) {
    isAlive_ = state;
}
