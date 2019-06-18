#include <iostream>
#include "Board.h"
#include <random>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));
    Board board(20,20);
    board.displayBoard();


    while(1) {
        board.updateBoardState();
        board.displayBoard();
    }
    return 0;
}