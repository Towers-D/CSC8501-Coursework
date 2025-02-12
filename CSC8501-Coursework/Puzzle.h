#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <ctime>
#include <thread>
#include <mutex>
//Library to handle Big Integers, credit to Sercan Tutar
#include "../sercantutar-infint-fc767ed/InfInt.h"
//@author: David Towers (160243066)

using namespace std;

class Puzzle {
	mutex mmutex;
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
	InfInt calcConRows(bool threading);
	void calcParRows();
	vector<int> getBoard() const;

	InfInt getResult(bool threading);
	string boardString() const ;
	string resultString(bool threading);
	string parString();
	void setWildCard(bool b);
	bool getWildCard();

	
protected:
	InfInt* results;
	InfInt* parArr;
	InfInt* givPar;
	void threadFunc(int i);
	int rowColSize;
	int boardSpaces;
	vector<int> board;
	vector<int> sortedBoard;
	InfInt finResult = 0;
	bool wildCard = false;
	void countGroups();
	void countUnOrded();
	void countUnRowCol(vector<int> vec);
	void clearResults();

	InfInt getResultFor(int ind);
	void setResultAt(int ind, InfInt val);
};
