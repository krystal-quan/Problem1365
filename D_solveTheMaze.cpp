#include <iostream>
#include <vector>
#include<memory>
#include <utility>
#include <array>

char* handleInput(int& row, int& column) {

	char* table = new char[row*column];
	for(int yter=0; yter != row; ++yter){
		for(int xter=0; xter != column; ++xter){
			std::cin >> *(table + (yter*column) + xter);
		}
	}
	return table;

}

void checkOuput(char* table, int& row, int& column){

	for(int yter=0; yter != row; ++yter){
		for(int xter=0; xter != column; ++xter){
			std::cout << *(table + (yter * column) + xter);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}

/* struct Position{ */
/* 	int posX; */
/* 	int posY; */
/* }; */

/* enum possible { */
/* 	Good = 'G', */
/* 	Bad = 'B', */
/* 	Empty = '.', */
/* 	Wall = '#' */
/* }; */


std::vector<std::pair<int, int>> handleTable(char* table, int& row, int& column){
	std::vector<std::pair<int, int>> possiblePos = { 
		std::make_pair(0, 1),
		std::make_pair(1, 0),
		std::make_pair(0, -1),
		std::make_pair(-1, 0),
		std::make_pair(0, 0)
	};
	std::vector<std::pair<int, int>> goodPersonLocation;

	for(int xter=0; xter != row; ++xter){
		for(int yter=0; yter != column; ++yter){
			std::array<int, 4> remainPossiblePos{ 0, 1, 2, 3 };
			if(xter == 0){
				/* possiblePos[3] = std::make_pair(0, 0); */
				remainPossiblePos[3] = 4;
			} 
			if (xter == (row - 1)){
				/* possiblePos[1] = std::make_pair(0, 0); */
				remainPossiblePos[1] = 4;
			}
			if(yter == 0){
				/* possiblePos[2] = std::make_pair(0, 0); */
				remainPossiblePos[2] = 4;
			}
			if(yter == (column -1)){
				/* possiblePos[0] = std::make_pair(0, 0); */
				remainPossiblePos[0] = 4;
			}

			switch(*(table + (yter*column) + xter)){
				case 'B':
					for(const auto& pos : remainPossiblePos){
						if(pos != 4){
							int posX = xter + possiblePos[pos].first; 
							int posY = yter + possiblePos[pos].second;
							switch(*(table + (posY*column) + posX)){
								case 'G':
									/* goodPersonLocation.push_back(std::make_pair(-1, -1)); */
									std::cout << "No" << std::endl;
									break;
								case '.':
									*(table + (posY*column) + posX) = '#';
								default:
									break;
							}
						} else {
							continue;
						}
					}
				case 'G':
					goodPersonLocation.push_back(std::make_pair(xter, yter));
				default:
					break;

			}
		}
	}
	return goodPersonLocation;
}

int main(int argc, const char* argv[]){
	int test; // number of text case
	std::cin >> test;

	for(int iter=0; iter != test; ++iter) {
		int row;
		int column;
		std::cin >> row >> column;

		char* table = handleInput(row, column);
		checkOuput(table, row, column);
		auto goodPersonLocation = handleTable(table, row, column);
		checkOuput(table, row, column);

	}
}
