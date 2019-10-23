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
	void calcParRows();
	vector<int> getBoard() const;

	unsigned long long getResult();
	string boardString() const ;
	string resultString();
	string parString();
	void setWildCard(bool b);
	bool getWildCard();

	
protected:
	int* results;
	unsigned long long * parArr;
	unsigned long long* givPar;
	int rowColSize;
	int boardSpaces;
	vector<int> board;
	vector<int> sortedBoard; // assign
	unsigned long long finResult = 0;
	bool wildCard = false;
	void countGroups();
	void countUnOrded();
	void clearResults();

	int getResultFor(int ind);
	void setResultAt(int ind, int val);
};
