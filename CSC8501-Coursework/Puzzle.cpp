#include "Puzzle.h"

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

void Puzzle::genPuzzle() {
	int arr[8] = { 1, 18, 6, 7, 8, 9, 16, 13 };
	for (int i = 0; i < board.size() - 1; i++)
		board.at(i) = arr[i];
}