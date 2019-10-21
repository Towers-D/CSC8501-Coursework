#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;

class Puzzle {
public:
	//Base Functions
	Puzzle(int size = 4);
	Puzzle(vector<int> config);
	Puzzle(const Puzzle &copy);
	Puzzle& operator=(const Puzzle& rhs);
	~Puzzle();

	void genPuzzle();
	unsigned long long calcComRows();

protected:
	int* results;
	int rowColSize;
	int boardSpaces;
	vector<int> board;

	void countComRows();
	void clearResults();

	int getResultFor(int ind);
	void setResultAt(int ind, int val);
};

