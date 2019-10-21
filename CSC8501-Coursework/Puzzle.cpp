#include "Puzzle.h"

//Functions used by class, but not apart of object
unsigned long long factorial(int n) {
	if (n == 1)
		return 1;
	return n * factorial(n - 1);
}


//Public Functions
Puzzle::Puzzle(int size) {
	rowColSize = size;
	//-1 for Blank space
	boardSpaces = (rowColSize * rowColSize) - 1;
	//-1 as we never calculate contuous rows of size 1
	results = new int[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		results[i] = 0;
	for (int i = 0; i < boardSpaces; i++)
		board.push_back(0);
}

Puzzle::Puzzle(vector<int> config) {
	rowColSize = sqrt(config.size() + 1);
	boardSpaces = config.size();
	results = new int[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		results[i] = 0;
	for (int i : config)
		board.push_back(i);
}

Puzzle::Puzzle(const Puzzle &rhs) {
	rowColSize = rhs.rowColSize;
	boardSpaces = rhs.boardSpaces;
	results = new int[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		results[i] = rhs.results[i];
	for (int i : rhs.board)
		board.push_back(i);
}

Puzzle& Puzzle::operator=(const Puzzle& rhs) {
	if (this == &rhs) return (*this);
	delete[] results;
	rowColSize = rhs.rowColSize;
	boardSpaces = rhs.boardSpaces;
	results = new int[rowColSize - 1];
	for (int i = 0; i < boardSpaces; i++)
		board.push_back(0);
	for (int i = 0; i < rowColSize - 1; ++i)
		results[i] = rhs.results[i];
	return *this;
}

Puzzle::~Puzzle() {
	delete[] results;
	results = nullptr;
}

//int arr[8] = { 1, 18, 6, 7, 8, 9, 16, 13 };
//int arr[15] = { 4, 19, 12, 6, 18, 3, 17, 10, 2, 9, 16, 5, 15, 11, 7 };
void Puzzle::genPuzzle() {
	vector<int> range;
	for (int i = 1; i <= 20; i++)
		range.push_back(i);
	srand(time(0));
	
	for (int i = 0; i < board.size(); i++) {
		int rnd = (rand() % range.size());
		board.at(i) = range.at(rnd);
		range.erase(range.begin() + rnd);
	}
		
}

unsigned long long Puzzle::calcComRows() {
	this->countComRows();
	unsigned long long val = 0;
	for (int i = rowColSize - 1; i <= rowColSize; i++)
		val += (getResultFor(i) * factorial(boardSpaces - i) / 2) * ((i == rowColSize - 1) ? 1 : rowColSize - 1);
	return val;
}

//Protected Functions

void Puzzle::countComRows() {
	this->clearResults();
	sort(board.begin(), board.end());

	for (int i = 2; i <= rowColSize; i++) {
		for (int j = 0; j < boardSpaces; j++) {
			int check = 0;
			for (int x = 1; x < i; x++)
				if ((j + x) < (boardSpaces ) && board.at(j) == board.at(j + x) - x) 
					check++;
			if (check == i - 1)
				setResultAt(i, getResultFor(i) + 1);
		}
	}
}

void Puzzle::clearResults() {
	for (int i = 0; i < rowColSize - 1; i++) {
		results[i] = 0;
	}
}

int Puzzle::getResultFor(int ind) {
	return results[ind - 2];
}

void Puzzle::setResultAt(int ind, int val) {
	results[ind - 2] = val;
}
