#include <iostream>
#include <vector>
#include<memory>
#include <utility>
#include <array>
#include <set>
#include <deque>
#include <algorithm>

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


std::deque<std::pair<int, int>> handleTable(char* table, int& row, int& column){
	std::vector<std::pair<int, int>> possiblePos = { 
		std::make_pair(0, 1),
		std::make_pair(1, 0),
		std::make_pair(0, -1),
		std::make_pair(-1, 0),
		std::make_pair(0, 0)
	};
	std::deque<std::pair<int, int>> goodPersonLocation;

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

void bruteForceTheArray(char* table, std::deque<std::pair<int, int>>& goodPersonLocation, int& row, int& column){

	std::set<int> remainPossiblePos;
	bool TrueOrFalse = true;
	while((goodPersonLocation.begin() != goodPersonLocation.end()) && TrueOrFalse){
		auto location = goodPersonLocation.begin();
		int posX = location->first;
		int posY = location->second;

		if(*(table + (posY * column) + posX) == '.')
			goodPersonLocation.pop_front();
		else{
			while(posY != row){

				while(*(table + (posY * column) + posX) != '#'){
					remainPossiblePos.insert(posX);
					if(++posX == column)
						break;
				}

				while(*(table + (posY * column) + posX) != '#'){
					remainPossiblePos.insert(posX);
					if(--posX == -1)
						break;
				}

				for(auto& position: remainPossiblePos){
					switch (*(table + ((location->second + 1) * column) + position)){
						case 'G':
							*(table + ((location->second + 1) * column) + position) = '.';
						case '#':
							remainPossiblePos.erase(position);
					}
				}
			}
			goodPersonLocation.pop_front();
			if((posY == row) && (std::find(remainPossiblePos.cbegin(), remainPossiblePos.cend(), column) != remainPossiblePos.cend()))
				continue;
			else{
				TrueOrFalse = false;
				break;
			}

			++posY;
		}

	}
	std::cout << (TrueOrFalse ? "Yes" : "No" ) << std::endl;
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
		bruteForceTheArray(table, goodPersonLocation, row, column);

	}
}
