#include <iostream>
#include "Board.h"


int main() {
	
	
	std::cout << "Do you want to start new Game of Life or load?\n";
	std::cout << "1. Start New Game\n2. Load\nYour choice: ";
	auto choice{ 0 };
	std::cin >> choice;

	if (1 == choice)
	{
		auto sizeX{ 0 }, sizeY{ 0 };

		std::cout << std::endl << "Set width of your board: ";
		std::cin >> sizeX;
		std::cout << std::endl << "Set height of your board: ";
		std::cin >> sizeY;
		std::cout << std::endl;
		Board board(sizeX, sizeY);

		while (true)
		{
			board.displayBoard();
			board.updateBoardState();
		}
	}
	else if (2 == choice)
	{
		std::string saveName{};
		std::cout << "Type save to load: ";
		std::cin >> saveName;
		Board board(saveName);

		while (true)
		{
			board.displayBoard();
			board.updateBoardState();
		}
	}




	system("pause");
	return 0;
}