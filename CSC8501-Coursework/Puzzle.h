#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Puzzle {
public:
	//Base Functions
	Puzzle(int size = 3);
	Puzzle(const Puzzle &copy);
	Puzzle& operator=(const Puzzle& rhs);
	~Puzzle();

	void genPuzzle();
protected:
	int* results;
	int rowColSize;
	int boardSpaces;
	vector<int> board;
};

