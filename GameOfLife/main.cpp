#include <iostream>
#include "Board.h"
#include <random>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));
	Board board1(30,30);
	board1.displayBoard();

	int temp{ 10 };

	while (temp >= 0) {
		board1.updateBoardState();
		board1.displayBoard();
		temp--;
	}
	board1.saveBoardState("board_state.txt");

	system("pause");
	return 0;
}