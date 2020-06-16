#include <iostream>
#include <vector>
#include<memory>
#include <utility>
#include <array>
#include <set>
#include <deque>
#include <algorithm>

char* handleInput(int&, int&);
std::deque<std::pair<int, int>> handleTable(char*, int&, int&, bool&);
void bruteForceTheArray(char*, std::deque<std::pair<int, int>>&, int& , int&, bool&);
void checkOutput(char*, int&, int&);

int main(int argc, const char* argv[]){
	int test; // number of text case
	std::cin >> test;

	for(int iter=0; iter != test; ++iter) {
		int row;
		int column;
		std::cin >> row >> column;
		/* std::cout << "test number: " << iter << std::endl; */

		char* table = handleInput(row, column);
		bool TrueOrFalse = true;
		/* checkOutput(table, row, column); */
		auto goodPersonLocation = handleTable(table, row, column, TrueOrFalse);
		/* checkOutput(table, row, column); */
		bruteForceTheArray(table, goodPersonLocation, row, column, TrueOrFalse);
		std::cout << (TrueOrFalse ? "Yes" : "No" ) << std::endl;
		delete [] table;
	}
}

char* handleInput(int& row, int& column) {

	char* table = new char[row*column];
	for(int yter=0; yter != row; ++yter){
		for(int xter=0; xter != column; ++xter){
			std::cin >> *(table + (yter*column) + xter);
		}
	}
	return table;

}

void checkOutput(char* table, int& row, int& column){

	for(int yter=0; yter != row; ++yter){
		for(int xter=0; xter != column; ++xter){
			std::cout << *(table + (yter * column) + xter);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}


std::deque<std::pair<int, int>> handleTable(char* table, int& row, int& column, bool& TrueOrFalse){

	if(*(table + row*column) == 'B'){
		TrueOrFalse = false;
	}
	std::vector<std::pair<int, int>> possiblePos = { 
		std::make_pair(0, 1),
		std::make_pair(1, 0),
		std::make_pair(0, -1),
		std::make_pair(-1, 0),
	};
	std::deque<std::pair<int, int>> goodPersonLocation;

	for(int xter=0; xter != row; ++xter){
		for(int yter=0; yter != column; ++yter){
			std::array<int, 4> remainPossiblePos{ 0, 1, 2, 3 };
			if(xter == 0){
				remainPossiblePos[3] = 4;
			} 
			if (xter == (row - 1)){
				remainPossiblePos[1] = 4;
			}
			if(yter == 0){
				remainPossiblePos[2] = 4;
			}
			if(yter == (column -1)){
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
									TrueOrFalse = false;
									return goodPersonLocation;
								case '.':
									*(table + (posY*column) + posX) = '#';
							}
						} 					
					}
				case 'G':
					goodPersonLocation.push_back(std::make_pair(xter, yter));
			}
		}
	}

	return goodPersonLocation;

}


void printSet(std::set<int> setNeedToPrint){
	for(auto& setMember : setNeedToPrint){
		std::cout << setMember << " ";
	}
	std::cout << std::endl;
}


void bruteForceTheArray(char* table, std::deque<std::pair<int, int>>& goodPersonLocation, int& row, int& column, bool& TrueOrFalse){

	if((goodPersonLocation.size() == 0) && (*(table + row*column) != 'B')){
		TrueOrFalse = true;
		return;
	}

	std::set<int> remainPossiblePos;
	while((!goodPersonLocation.empty()) && TrueOrFalse){
		auto location = goodPersonLocation.begin();
		int posX = location->first;
		int posY = location->second;

		if(*(table + (posY * column) + posX) == '.')
			goodPersonLocation.pop_front();
		else{
			while(posY != row){

				for(int iter=0; *(table + (posY * column) + posX + iter) != '#' && ((posX + iter) != column); ++iter){
					remainPossiblePos.insert(posX + iter);
				}

				for(int iter=0; *(table + (posY * column) + posX + iter) != '#' && ((posX + iter) != -1); --iter){
					remainPossiblePos.insert(posX + iter);
				}

				while(posY != (row -1)){
					std::set<int> remainPossiblePos_ver2;
					for(auto& position: remainPossiblePos){
						switch (*(table + ((posY + 1) * column) + position)){
							case 'G':
								*(table + ((posY + 1) * column) + position) = '.';
								remainPossiblePos_ver2.insert(position);
								break;
							case '.':
								remainPossiblePos_ver2.insert(position);
								break;
						}
					}
					remainPossiblePos = remainPossiblePos_ver2;
				}
				++posY;
			}
			TrueOrFalse = (std::find(remainPossiblePos.cbegin(), remainPossiblePos.cend(), (column - 1)) != remainPossiblePos.cend()) ? true : false;
			if(TrueOrFalse)
				break;
			goodPersonLocation.pop_front();
		}

	}

}

