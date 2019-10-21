#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

class Puzzle {
public:
	//Base Functions
	Puzzle(int size = 4);
	Puzzle(vector<int> config);
	Puzzle(const Puzzle &copy);
	Puzzle& operator=(const Puzzle& rhs);
	friend ostream& operator<<(ostream& ostr, const Puzzle& p);
	//friend istream& operator>>(istream& ostr, Puzzle& p);
	~Puzzle();

	void genPuzzle();
	unsigned long long calcConRows();
	vector<int> getBoard() const;

	unsigned long long getResult();
	string boardString() const ;
	string resultString();

protected:
	int* results;
	int rowColSize;
	int boardSpaces;
	vector<int> board;
	unsigned long long finResult = 0;

	void countComRows();
	void clearResults();

	int getResultFor(int ind);
	void setResultAt(int ind, int val);
};
