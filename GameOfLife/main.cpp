#include <iostream>
#include "Board.h"
#include <random>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));
	/*Board board1(20,20);
	board1.displayBoard();*/

	/*int temp{ 10 };

	while(temp >= 0) {
		board1.updateBoardState();
		board1.displayBoard();
		temp--;
	}
	board1.saveBoardState("board_state.txt");

	system("Pause");
	system("cls");*/

	Board board("board_state.txt");
	system("Pause");


	while (1)
	{
		board.displayBoard();
		board.updateBoardState();
	}

	system("pause");
	return 0;
}