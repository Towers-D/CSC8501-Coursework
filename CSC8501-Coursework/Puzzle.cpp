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
	wildCard = 0;
}

Puzzle::Puzzle(vector<int> config) {
	rowColSize = sqrt(config.size() + 1);
	boardSpaces = config.size();
	results = new int[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		results[i] = 0;
	for (int i : config)
		board.push_back(i);
	wildCard = 0;
}

Puzzle::Puzzle(const Puzzle &rhs) {
	rowColSize = rhs.rowColSize;
	boardSpaces = rhs.boardSpaces;
	results = new int[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		results[i] = rhs.results[i];
	for (int i : rhs.board)
		board.push_back(i);
	wildCard = rhs.wildCard;
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
	wildCard = rhs.wildCard;
	return *this;
}

ostream& operator<<(ostream& ostr, const Puzzle& p) {
	ostr << p.boardString();
	return ostr;
}

Puzzle::~Puzzle() {
	delete[] results;
	results = nullptr;
}

void Puzzle::genPuzzle() {
	vector<int> range;
	for (int i = 1; i <= 20; i++)
		range.push_back(i);
	
	for (int i = 0; i < board.size(); i++) {
		int rnd = (rand() % range.size());
		board.at(i) = range.at(rnd);
		range.erase(range.begin() + rnd);
	}
}

unsigned long long Puzzle::calcConRows() {
	this->countComRows();
	unsigned long long val = 0;
	for (int i = rowColSize - (this->getWildCard() == 1 ? 1 : 0); i <= rowColSize; i++)
		val += (getResultFor(i) * factorial(boardSpaces - i) / 2) * ((i == rowColSize - 1) ? 1 : rowColSize - 1);
	finResult = val;
	return finResult;
}

vector<int> Puzzle::getBoard() const {
	return board;
}

unsigned long long Puzzle::getResult() {
	if (finResult == 0)
		finResult = calcConRows();
	return finResult;
}

string Puzzle::boardString() const {
	string boardStr = "";
	for (int i = 1; i <= board.size(); i++) {
		boardStr += to_string(board.at(i - 1));
		if (i % 4 == 0)
			boardStr += "\n";
		else
			boardStr += "\t";
	}
	return boardStr;
}

string Puzzle::resultString() {
	string resStr = boardString();
	unsigned long long res = getResult();
	resStr += ("\nrow = " + to_string(res) + "\n");
	resStr += ("column = " + to_string(res) + "\n");
	resStr += ("reverse row = " + to_string(res) + "\n");
	resStr += ("reverse column = " + to_string(res) + "\n\n");
	return resStr;
}

void Puzzle::setWildCard(bool b) {
	this->wildCard = b;
}

bool Puzzle::getWildCard() {
	return wildCard;
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
